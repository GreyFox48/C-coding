/**
 * @file life.c
 * @brief Contains the functions to determine if a cell is alive or dead
 * in a matrix
 * @details Can create, initialize, and free a frame structure, which has a 2d
 * matrix as well as the lengths of the rows and columns.  Also has functions to
 * determine if cells in an hedge, torus, or klein pattern are alive or dead.
 *
 * @date November 30, 2015
 * @author Matthew Olsen
 * @bug None
 * @todo Nothing
 */

#include "life.h"
#include <stdlib.h>
#include <string.h>

#define LEN 132 /* utalized to help read file contents for .lif files */

#define FILE_FAILURE 100

/**
 * Creates a frame structure.  A frame strcutre is cotains a 2-Dimensional
 * matrix of unsigned characters, (matrix) and two integers to store the width
 * and height of the matrix (rows and cols respectively).
 * @param width the width of the screen in pixels
 * @param height the height of the screen in pixels
 * @param sprite_size the side length of one of the sprite squares
 * @return the pointer to a frame structure based upon the width, height
 * and sprite size
 */
struct frame_t *create_frame(int width, int height, int sprite_size)
{
        struct frame_t *frame = malloc(sizeof(struct frame_t));
        frame->rows = width / sprite_size;
	frame->cols = height / sprite_size;
	create_matrix(frame);
        return frame;
}

/**
 * Create a matrix full of dead cells. Retruns NULL in case of malloc failure
 * @param frame the frame structure with the matrix to be created.
 */
void create_matrix(struct frame_t *frame)
{
        int i;
        int j;
        unsigned char **a = malloc(frame->rows * sizeof(unsigned char *));

        if (!a) { /* in case of malloc failure */
                frame->matrix = NULL;
                return;
        }

        /* alloc the columns for the matrix */
        for (i = 0; i < frame->rows; i++) {
                a[i] = malloc(frame->cols * sizeof(unsigned char));
                if (!a[i]) { /* in case of malloc failure to create a column */
                        for (j = 0; j < i; j++) {
                                free(a[j]);
                        }
                        free(a);
                        frame->matrix = NULL;
                        return;
                }
       }

       /* initialize the matrix area as dead */
       for (i = 0; i < frame->rows; i++) {
               for (j = 0; j < frame->cols; j++) {
                        a[i][j] = 0;
                }
        }
        frame->matrix = a;
}

/**
 * Goes through each of the cells for the hedge fucntion to be detected alive
 * or dead
 * @param new the new generation of cells after the function is called
 * @param old the old generation of cells after the function is called
 */
void hedge(struct frame_t *new, struct frame_t *old)
{
        int i;
        int j;

        for (i = 0; i < new->rows; i++) {
                for (j = 0; j < new->cols; j++) {
                        new->matrix[i][j] = hedge_cell(old, i, j);
                }
        }
}

/**
 * Detects if a cell is alive or not in the hedge function, determined by the
 * game of life rules
 * @param old the old frame containing the currently alive or dead cells
 * @param x the row number of the cell
 * @param y the column number of the cell
 * @return 1 if alive, 0 if dead
 */
unsigned char hedge_cell(struct frame_t *old, int x, int y)
{
        int i;
        int j;
        unsigned char sum = 0; /* number of neighbor cells that are alive */

        /* detect all nearlby alive cells, in rows or cols one lesser, equal
         * greater to cell given by coordinate in function parameters
         */
        for (i = x - 1; i < x + 2; i++) {
                for (j = y - 1; j < y + 2; j++) {
                        /* ensure coordinates are not out of bounds */
                        if ((i >= 0 && i < old->rows) && (j >= 0 && j < old->cols)) {
                            /* prevents checking cell's own condition */
                                if (i != x || j != y) {
                                        sum += old->matrix[i][j];
                                }
                        }
                }
        }

        /* calculate if already alive cell will be alive or dead */
        if (old->matrix[x][y] == 1) {
                if (sum >= 2 && sum <= 3) {
                        return 1;
                }
        } else if (old->matrix[x][y] == 0 && sum == 3) {
                return 1;
        }
        return 0;
}

/**
 * Free a frame and all of its associated contents
 * @param frame the frame to be freed
 */
void free_frame(struct frame_t *frame)
{
        int i;

        /* free the columns */
        for (i = 0; i < frame->rows; i++) {
                free(frame->matrix[i]);
        }
        free(frame->matrix); /* free the rows */
        free(frame); /* free the rest of the frame */
        return;
}

/**
 * Determine the type of file utalized by the user and initialize the life
 * patterns.  Exits program if a file fails to open.
 * @param frame the frame structure that contains the matrix to initialize the
 * alive cells in
 * @param file the character string containing the user input
 * @param x the x coordinate the user wants the file to spawn on
 * @param y the y coorinate the user wants the file to spawn on
 * @param edge the type of edge to simulate when spawning alive cells
 */
void create_life(struct frame_t *frame, char *file, int x, int y, int edge)
{
        char *temp = NULL;
        FILE *fm = NULL;
        fm = fopen(file, "r"); /* get the file before strtok mods string */
        if (fm == NULL) {
                printf("File %s does not exist.  Goodbye!\n", file);
                exit(FILE_FAILURE);
        }
        /* file type is seperated by the last _ character */
        temp = strtok(file, "_");
        while (strtok(NULL, "_")) {
                temp = strtok(NULL, "_");
        }

        if (!strcmp(temp, "105.lif")) {
                create_life_105(frame, fm, x, y, edge);
        } else {
                create_life_106(frame, fm, x, y, edge);
        }

        fclose(fm); /* no longer needed after spawning life */
}

/**
 * Read in a 106 life file and intialize alive cells based upon the file's
 * pattern
 * @param frame the frame to initialize life in
 * @param fp the life file containing the desired pattern
 * @param x the x coordinate the user specified to place life pattern at
 * @param y the y coordinate the user specified to place life pattern at
 * @param edge the integer representing the type of edge to use when creating
 * the alive cells
 */
void create_life_106(struct frame_t *frame, FILE *fp, int x, int y, int edge)
{
        char in[LEN];
        int i, j;

        while (fgets(in, LEN, fp)) {
                /* gloss over comments, which begin with # */
                if(in[0] != '#'){
                        sscanf(in, "%d %d", &i, &j);
                        switch (edge) {
                        case 1: /* hedge pattern */
                                /* calculates the row and col value in relation
                                 * to the dimensions of the matrix */
                                i = (frame->rows / 2) + i + x;
                                j = (frame->cols / 2) + -j + -y;
                                /* ensure cordinates are within bounds for the matrix */
                                if ((i >= 0 && i < frame->rows) && (j >= 0 && j < frame->cols)) {
                                        frame->matrix[i][j] = 1;
                                }
                                break;
                        case 2: /* torus pattern */
                                /* utalization of modulus prevents array out of
                                 *  bounds errors */
                                i = modulus(((frame->rows / 2) + i + x), frame->rows);
                           /* -j to orientate given coordinates with matrix indexing */
                                j = modulus(((frame->cols / 2) + -j + -y), frame->cols);
                                frame->matrix[i][j] = 1;
                                break;
                        case 3: /* klein pattern */
                                i = (frame->rows / 2) + i + x;
                                j = (frame->cols / 2) + -j + -y;
                                if (i < 0 || i >= frame->rows) {
                                        /* invert the col coordinate */
                                        j = modulus(frame->cols - j, frame->cols);
                                        i = modulus(i, frame->rows);
                                        frame->matrix[i][j] = 1;
                                } else {
                                        i = modulus(i, frame->rows);
                                        j = modulus(j, frame->cols);
                                        frame->matrix[i][j] = 1;
                                }
                                break;
                        }
                }
        }
        //fclose(fp);
}

/**
 * Read in a 105 life file and intialize alive cells based upon the file's
 * pattern
 * @param frame the frame to initialize life in
 * @param fp the life file containing the desired pattern
 * @param x the x coordinate the user specified to place life pattern at
 * @param y the y coordinate the user specified to place life pattern at
 * @param edge the integer representing the type of edge to use when creating
 * the alive cells
 */
void create_life_105(struct frame_t *frame, FILE *fp, int x, int y, int edge)
{
        char in[LEN];
        int i, j;
        int origi, origj; /* quick fix for logic problem */
        int temp; /* used to help scan line and create cell row coordinate */

        while (fgets(in, LEN, fp)) {
                temp = 0;
                sscanf(in, "#P %d %d", &origi, &origj);
                if(in[0] != '#'){
                        while (in[temp] != '\n') { /* continue to next line after no new info on current */
                                if (in[temp] == '*') { /* if cell is alive */
                                        switch (edge) {
                                        case 1: /* hedge pattern */
                                                /* calculates the row and col value in relation
                                                 * to the dimensions of the matrix */
                                                i = (frame->rows / 2) + origi + (x + temp);
                                                j = (frame->cols / 2) + -origj + -y;
                                                /* ensure cordinates are within bounds for the matrix */
                                                if ((i >= 0 && i < frame->rows) && (j >= 0 && j < frame->cols)) {
                                                        frame->matrix[i][j] = 1;
                                                }
                                                break;
                                        case 2: /* torus pattern */
                                                /* utalization of modulus prevents array out of
                                                 *  bounds errors */
                                                i = modulus(((frame->rows / 2) + origi + (x + temp)), frame->rows);
                                           /* -j to orientate given coordinates with matrix indexing */
                                                j = modulus(((frame->cols / 2) + -origj + -y), frame->cols);
                                                frame->matrix[i][j] = 1;
                                                break;
                                        case 3: /* klein pattern */
                                                i = (frame->rows / 2) + origi + (x + temp);
                                                j = (frame->cols / 2) + -origj + -y;
                                                if (i < 0 || i >= frame->rows) {
                                                        /* invert the col coordinate */
                                                        j = modulus(frame->cols - j, frame->cols);
                                                        i = modulus(i, frame->rows);
                                                        frame->matrix[i][j] = 1;
                                                } else {
                                                        i = modulus(i, frame->rows);
                                                        j = modulus(j, frame->cols);
                                                        frame->matrix[i][j] = 1;
                                                }
                                                break;
                                        }
                                }
                                temp++;
                        }
                        y--; /* every new line on 105 grid is one y coordinate down */
                }
        }
        //fclose(fp);
}

/**
 * Calculates alive or dead cells for the torus shape
 * @param new the frame to contain the new generation of cells
 * @param old the frame that contains the older generation of cells.
 */
void torus(struct frame_t *new, struct frame_t *old)
{
        int i, j;
        /* look through every cell on the grid */
        for (i = 0; i < new->rows; i++) {
                for (j = 0; j < new->cols; j++) {
                        /* calculates if a sinlgle cell is alive or dead */
                        new->matrix[i][j] = torus_cell(old, i, j);
                }
        }
}

/**
 * Determines if a given cell at a given coordinate is alive or dead, determined
 * by the game of life rules for a torus shape
 * @param old the frame containing the currently alive or dead cells
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 */
unsigned char torus_cell(struct frame_t *old, int x, int y)
{
        int i, j;
        unsigned char sum = 0; /* number of neighbor cells that are alive */

        /* detect all nearlby alive cells */
        for (i = x - 1; i < x + 2; i++) {
                for (j = y - 1; j < y + 2; j++) {
                        /* prevents checking cell's own condition */
                        if (i != x || j != y) {
                                /* modulus implements "wraping", in that it will
                                 * detect cells on the opposite side of the
                                 * screen
                                 */
                                sum += old->matrix[modulus(i, old->rows)][modulus(j, old->cols)];
                        }
                }
        }

        /* calculate alive or dead */
        if (old->matrix[x][y] == 1) {
                if (sum >= 2 && sum <= 3) {
                        return 1;
                }
        } else if (old->matrix[x][y] == 0 && sum == 3) {
                return 1;
        }
        return 0;
}

/**
 * Properly implements the modulus function according to standard mathmatics.
 * @param numerator the numerator of the operation
 * @param denominator the denominator of the operation
 * @return the modulus value (always positive)
 */
int modulus(int numerator, int denominator)
{
        return (numerator + denominator) % denominator;
}

/**
 * Calculates alive or dead cells for the klein shape
 * @param new the frame to contain the new generation of cells
 * @param old the frame that contains the older generation of cells.  The
 * calculation of the new generation matrix is based off of the old generation.
 */
void klein(struct frame_t *new, struct frame_t *old)
{
        int i, j;
        /* go through every single cell on the list */
        for (i = 0; i < new->rows; i++) {
                for (j = 0; j < new->cols; j++) {
                        new->matrix[i][j] = klein_cell(old, i, j);
                }
        }
}

/**
 * Determines if a given cell at a given coordinate is alive or dead, determined
 * by the game of life rules for a klein stucture.
 * @param old the frame containing the currently alive or dead cells
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 */
unsigned char klein_cell(struct frame_t *old, int x, int y)
{
        int i, j, temp;
        unsigned char sum = 0; /* number of neighbor cells that are alive */

        /* detect all nearlby alive cells */
        for (i = x - 1; i < x + 2; i++) {
                for (j = y - 1; j < y + 2; j++) {
                        /* prevents checking cell's own condition */
                        if (i != x || j != y) {
                                if (i < 0 || i >= old->rows) {
                                        /* invert the col coordinate */
                                        temp = modulus(old->cols - j, old->cols);
                                        sum += old->matrix[modulus(i, old->rows)][temp];
                                } else {
                                        sum += old->matrix[modulus(i, old->rows)][modulus(j, old->cols)];
                                }
                        }
                }
        }

        /* calculate alive or dead */
        if (old->matrix[x][y] == 1) {
                if (sum >= 2 && sum <= 3) {
                        return 1;
                }
        } else if (old->matrix[x][y] == 0 && sum == 3) {
                return 1;
        }
        return 0;
}
