#include "life.h"
#include <stdlib.h>
#include <stdio.h> //remove if no printf

#define LEN 132

/**
 * Creates a frame structure.  A frame strcutre is cotains a 2-Dimensional
 * matrix of unsigned characters, (matrix) and two integers to store the width
 * and height of the matrix (rows and cols respectively).
 */
struct frame_t *create_frame(void)
 {
        struct frame_t *frame = malloc(sizeof(struct frame_t));
        frame->rows = 0;
        frame->cols = 0;
        frame->matrix = NULL;
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
 * @param new the frame to contain the newly alive or dead cells
 * @param old the old frame to analyze for newly dead or alive cells
 */
void hedge(struct frame_t *new, struct frame_t *old)
{
        int i;
        int j;

        /* starts at one and ends one early to avoid putting alive cells on
           edges.  This process simulates the hedge shape */
        for (i = 1; i < new->rows - 1; i++) {
                for (j = 1; j < new->cols - 1; j++) {
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
 * @return 1 if alive, zero if dead
 */
unsigned char hedge_cell(struct frame_t *old, int x, int y)
{
        int i;
        int j;
        unsigned char sum = 0;

        /* detect all nearlby alive cells */
        for (i = x - 1; i < x + 2; i++) {
                for (j = y - 1; j < y + 2; j++) {
                        if (i != x || j != y) {
                                sum += old->matrix[i][j];
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
        free(frame->matrix); /* free the matrix */
        free(frame); /* free the rest of the frame */
        return;
}

/**
 * Read in a 1.06 life file and intialize a frame with it
 * @param frame the frame to initialize life in
 * @param file the life file containing the desired pattern
 * @param x the x coordinate the user specified to place life pattern at
 * @param y the y coordinate the user specified to place life pattern at
 */
void create_life(struct frame_t *frame, FILE *fp, int x, int y, int edge)
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
                                if ((i > 0 && i < frame->rows - 1) && (j > 0 && j < frame->cols - 1)) {
                                        frame->matrix[x][y] = 1;
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
                                if (j < 0 || j >= frame->cols) {
                                        /* invert the row coordinate, to simulate
                                         * the physical characteristics of a kl
                                         * klein bottle
                                         */
                                        i = modulus(-(i - frame->rows), frame->rows);
                                        j = modulus(j, frame->cols);
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
        fclose(fp);
}

/**
 * Calculates alive or dead cells for the torus shape
 * @param new the frame to contain the new generation of cells
 * @param old the frame that contains the older generation of cells.
 * will be based off of these generations.
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
 * by the game of life rules for a
 * @param old the frame containing the currently alive or dead cells
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 */
unsigned char torus_cell(struct frame_t *old, int x, int y)
{
        int i, j;
        unsigned char sum = 0;

        /* detect all nearlby alive cells */
        for (i = x - 1; i < x + 2; i++) {
                for (j = y - 1; j < y + 2; j++) {
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
 * @param numerator the numberator of the operation
 * @param denominator the denominator of the operation
 * @return the modulus value (always positive)
 */
int modulus(int numerator, int denominator)
{
        int ans = numerator % denominator;
        /* modulus in standard math should not return a negative value */
        if (ans < 0) {
                ans = denominator + ans;
        }
        return ans;
}

/**
 * Calculates alive or dead cells for the torus shape
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
 * by the game of life rules for a torus stucture.
 * @param old the frame containing the currently alive or dead cells
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 */
unsigned char klein_cell(struct frame_t *old, int x, int y)
{
        int i, j, temp;
        unsigned char sum = 0;

        /* detect all nearlby alive cells */
        for (i = x - 1; i < x + 2; i++) {
                for (j = y - 1; j < y + 2; j++) {
                        if (i != x || j != y) {
                                if (j < 0 || j >= old->cols) {
                                        /* invert the row coordinate */
                                        temp = modulus(-(i - old->rows), old->rows);
                                        //temp = -(i - old->rows);
                                        sum += old->matrix[temp][modulus(j, old->cols)];
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
