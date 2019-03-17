/**
 * @file gl.c
 * @brief main file to implement the game of life.
 * @details Process command line arguments, create and alternate frames,
 * display the frames, selectes which type of edges to calculate for, and exit
 * the program while freeing the allocated memory.  Works with both 106.lif
 * and 105.lif files.  Can spawn up to three different patterns at once.
 *
 * @date November 30, 2015
 * @author Matthew Olsen
 * @bug None
 * @todo Nothing
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "sdl.h"
#include "life.h"

#define LEN 132

#define MALLOC_FAILURE 48
#define INVALID_EDGE 49
#define INVALID_SPRITE 50
#define INVALID_COLOR_VALUE 51
#define INVALID_FILE 52
#define INVALID_SCREEN_SIZE 53
#define EXIT_HELP 54

int main(int argc, char *argv[])
{
	/* Defualt values for the various life rendering values */
	int width = 800;
	int height = 600;
	int sprite_size = 16; /* either 2, 4, 8, or 16 */
        /* colors are RGB model valid values [0, 255] */
	unsigned char red = 255;
	unsigned char green = 255;
	unsigned char blue = 255;
	int c; /* used for the getopt function */
	int x_f = 0; /*coordinates specified by user to initialize life pattern */
	int y_f = 0;
	int x_q = 0;
	int y_q = 0;
	int x_p = 0;
	int y_p = 0;
	int temp;
	int edge = 2; /* number to represent edge type. Defualts to torus */
	int frame_count = 0; /* alternates the matrixs being shown */
	char fp_P[LEN];
	fp_P[0] = '\0'; /* sets string lenght to zero, for if later */
	char fp_Q[LEN];
	fp_Q[0] = '\0';
	char fp_F[LEN];
	/* create a defualt file to use */
	strcpy(fp_F, "./life_files/butterfly_106.lif");

	/* processing for command line arguments */
	while ((c = getopt(argc, argv, ":w:h:e:r:g:b:s:f:o:Q:q:P:p:H")) != -1) {
		switch (c) {
		case 'w': /* width */
			width = atoi(optarg);
			/* check for valid width */
			if (width < 1) {
				printf("Only numbers < 0 are valid.\nGoodbye!\n");
				exit(INVALID_SCREEN_SIZE);
			}
			break;
		case 'h': /* height */
			height = atoi(optarg);
			/* check for valid height */
			if (height < 1) {
				printf("Only numbers < 0 are valid.\nGoodbye!\n");
				exit(INVALID_SCREEN_SIZE);
			}
			break;
		case 'r': /* red color value */
			temp = atoi(optarg);
			/* casting to unsigned char would technically work,
			 * but I didn't if that would be acceptable */
			if (temp < 0 || temp > 255) {
				printf("Only numbers between 0 and 255 "
				"are valid.\nGoodbye!\n");
				exit(INVALID_SCREEN_SIZE);
			}
			red = temp;
			break;
		case 'b': /* blue color value */
			temp = atoi(optarg);
			if (temp < 0 || temp > 255) {
				printf("Only numbers between 0 and 255 "
				"are valid.\nGoodbye!\n");
				exit(INVALID_SCREEN_SIZE);
			}
			blue = temp;
			break;
		case 'g': /* green color value */
			temp = atoi(optarg);
			if (temp < 0 || temp > 255) {
				printf("Only numbers between 0 and 255 "
				"are valid.\nGoodbye!\n");
				exit(INVALID_SCREEN_SIZE);
			}
			green = temp;
			break;
		case 's': /* sprite size */
			sprite_size = atoi(optarg);
			if (sprite_size != 2 && sprite_size != 4
			    && sprite_size != 8 && sprite_size != 16) {
				    printf("Sprite size can only be 2, 4, 8,"
		    		    " or 16.\nGoodbye!\n");
				    exit(INVALID_SPRITE);
			    }
			break;
		case 'o': /* origin coordinate */
			sscanf(optarg, "%d,%d", &x_f, &y_f);
			break;
		case 'p': /* origin coordinate */
			sscanf(optarg, "%d,%d", &x_p, &y_p);
			break;
		case 'q': /* origin coordinate */
			sscanf(optarg, "%d,%d", &x_q, &y_q);
			break;
		case 'e': /* edge type */
			/* edge will be given to create_life later to implement
			 * proper screen wrapping for each edge type */
			if (!strcmp(optarg, "hedge")) {
				edge = 1;
			} else if (!strcmp(optarg, "torus")) {
				edge = 2;
			} else if (!strcmp(optarg, "klein")) {
				edge = 3;
			} else {
				printf("%s is not a valid edge.\n", optarg);
				printf("Valid options are either hedge, torus, "
				"or klein.\nGoodbye!\n");
				exit(INVALID_EDGE);
			}
			break;
		case 'f': /* file to read from */
			strncpy(fp_F, optarg, strlen(optarg) + 1);
			break;
		case 'Q': /* optional file to read from */
			strncpy(fp_Q, optarg, strlen(optarg) + 1);
			break;
		case 'P': /* optional file to read from */
			strncpy(fp_P, optarg, strlen(optarg) + 1);
			break;
		case 'H': /* help function */
			/* The width help*/
			printf("-w controls the width of the screen in pixels.\n");
			printf("\tDefault is 800.\n");

			/* The height help*/
			printf("-h controls the height of the screen in pixels.\n");
			printf("\tDefault is 600.\n");

			/* The sprite size help */
			printf("-s controls the size of the cells.\n");
			printf("\tDefault is 16.\n");
			printf("\tSprites may be squares with side lengths of "
			"2, 4, 8, or 16 pixels.\n");

			/* The edge help */
			printf("-e controls the type of edge.\n");
			printf("\tDefault is torus.\n");
			printf("\tValid options are edge, torus, and klein.\n");

			/* The file import help */
			printf("-f The file with the desired spawn pattern.\n");
			printf("\tDefault is butterfly_106.lif\n");
			printf("\tThe file name must be after ./life_files/\n");
			printf("\tExample: ./life_files/glider_106.lif\n");
			printf("\tBoth 105.lif and 106.lif files are valid.\n");

			/* The origin point help */
			printf("-o controls the origin of the spawn pattern.\n");
			printf("\t-o is used for the -f file.\n");
			printf("\tDefault is 0,0.\n");
			printf("\tThe coordinates are in refrence to a x,y "
			"plane.\n");
			printf("\tInput coordinates by inputing x,y with no "
			"spaces.\n");

			printf("-Q Another file with the desired spawn pattern.\n");
			printf("\tBoth 105.lif and 106.lif files are valid.\n");

			printf("-q controls the origin of the spawn pattern.\n");
			printf("\t-q is used for the -Q file.\n");
			printf("\tDefault is 0,0.\n");
			printf("\tThe coordinates are in refrence to a x,y "
			"plane.\n");
			printf("\tInput coordinates by inputing x,y with no "
			"spaces.\n");

			printf("-P Another file with the desired spawn pattern.\n");
			printf("\tBoth 105.lif and 106.lif files are valid.\n");

			printf("-p controls the origin of the spawn pattern.\n");
			printf("\t-p is used for the -P file.\n");
			printf("\tDefault is 0,0.\n");
			printf("\tThe coordinates are in refrence to a x,y "
			"plane.\n");
			printf("\tInput coordinates by inputing x,y with no "
			"spaces.\n");

			/* The red value help */
			printf("-r The red color value of the sprites.\n");
			printf("\tDefault is 255.\n");
			printf("\tOnly numbers between 0 and 255 are valid.\n");

			/* The blue value help*/
			printf("-b The blue color value of the sprites.\n");
			printf("\tDefault is 255.\n");
			printf("\tOnly numbers between 0 and 255 are valid.\n");

			/* The green value help*/
			printf("-g The green color value of the sprites.\n");
			printf("\tDefault is 255.\n");
			printf("\tOnly numbers between 0 and 255 are valid.\n");

		      /* Don't run the program after user only asks for help */
			exit(EXIT_HELP);
			break;
		case ':': /* error checking */
			printf("Testing... testing...\n");			/////DO THIS
			break;
		case '?':
			printf("Invalid command.  Use the command -H for help.\n");
			exit(EXIT_HELP);
			break;
		}
	}

        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */

        /* set up SDL -- works with SDL2 */
	init_sdl_info(&sdl_info, width, height, sprite_size, red, green, blue);

	/* your life initialization code here */
	struct frame_t *a = create_frame(width, height, sprite_size);
	struct frame_t *b = create_frame(width, height, sprite_size);

	/* ensure that the matrixes where initialized from create_frame*/
	if (!a->matrix || !b->matrix) {
		printf("A or B matrix allocating failed. Goodbye!\n");
		exit(MALLOC_FAILURE);
	}

	create_life(a, fp_F, x_f, y_f, edge); /* always used */

	if (strlen(fp_Q) != 0) { /* if fp_Q was given a file */
		create_life(a, fp_Q, x_q, y_q, edge);
	}
	if (strlen(fp_P) != 0) { /* if fp_P was given a file */
		create_life(a, fp_P, x_p, y_p, edge);
	}

        /* Main loop: loop forever. */
	while (1)
	{
		if (SDL_GetTicks() % 150 == 0) {
			if (frame_count % 2 == 0) {
				sdl_render_life(&sdl_info, a->matrix);
				/* determine alive cells based on chosen edge */
				/* each edge function scans cells from frame a
				 * and then writes to frame b, to create next gen
				 */
				switch (edge) {
				case 1:
					hedge(b, a);
					break;
				case 2:
					torus(b, a);
					break;
				case 3:
					klein(b, a);
					break;
				}
				/* allows alternation of frames */
				frame_count++;
				frame_count %= 2;

			} else {
				/* determine alive cells based on chosen edge */
				sdl_render_life(&sdl_info, b->matrix);
				switch (edge) {
				case 1:
					hedge(a, b);
					break;
				case 2:
					torus(a, b);
					break;
				case 3:
					klein(a, b);
					break;
				}
				/* allows alternation of frames */
				frame_count++;
				frame_count %= 2;
			}
		}
                 /* Poll for events, and handle the ones we care about.
                  * You can click the X button to close the window
                  */
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
                        /* If escape is pressed, return (and thus, quit) */
				if (event.key.keysym.sym == SDLK_ESCAPE)
					free_frame(a);
					free_frame(b);
					return 0;
				break;
			case SDL_QUIT:
				free_frame(a);
				free_frame(b);
				return(0);
			}
		}
	}
	free_frame(a);
	free_frame(b);
	return 0;
}
