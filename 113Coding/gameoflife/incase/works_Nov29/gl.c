#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "sdl.h"
#include "life.h"

#define MALLOC_FAILURE 48
#define INVALID_EDGE 49
#define INVALID_SPRITE 50
#define INVALID_COLOR_VALUE 51
#define INVALID_FILE 52

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
	int x = 0; /*coordinates specified by user to initialize life pattern */
	int y = 0;
	int edge = 2; /* number to represent edge type. Defualts to torus */
	/* create FILE pointer, with a default file */
	FILE *fp = fopen("./life_files/butterfly_106.lif", "r");
	/* check to ensure the file opened properly */
	if (fp == NULL) {
		printf("failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while ((c = getopt(argc, argv, ":w:h:e:r:g:b:s:f:o:")) != -1) {
		switch (c) {
		case 'w':
			width = atoi(optarg);
			break;
		case 'h':
			height = atoi(optarg);
			break;
		case 'r':
			red = (unsigned char) atoi(optarg);
			break;
		case 'b':
			blue = (unsigned char) atoi(optarg);
			break;
		case 'g':
			green = (unsigned char) atoi(optarg);
			break;
		case 's':
			sprite_size = atoi(optarg);
			if (sprite_size != 2 && sprite_size != 4
			    && sprite_size != 8 && sprite_size != 16) {
				    printf("Sprite size can only be 2, 4, 8,"
		    		    " or 16.\nGoodbye!\n");
				    exit(INVALID_SPRITE);
			    }
			break;
		case 'o':
			sscanf(optarg, "%d,%d", &x, &y);
			break;
		case 'e':
			if (!strcmp(optarg, "hedge")) {
				edge = 1;
			} else if (!strcmp(optarg, "torus")) {
				edge = 2;
			} else if (!strcmp(optarg, "klein")) {
				edge = 3;
			} else {
				printf("%s is not a valid edge.\n", optarg);
				printf("Valid options are either hedge, torus, "
				"or klein.\nGoodbye.\n");
				exit(INVALID_EDGE);
			}
			break;
		case 'f':
			fp = fopen(optarg, "r");
			if (fp == NULL) {
				printf("failed to open file\n");
				exit(EXIT_FAILURE);
			}
			break;
		}
	}

        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */

        /* set up SDL -- works with SDL2 */
	init_sdl_info(&sdl_info, width, height, sprite_size, red, green, blue);

	/* your life initialization code here */
	struct frame_t *a = create_frame();
	struct frame_t *b = create_frame();
	a->rows = width / sprite_size;
	a->cols = height / sprite_size;
	b->rows = width / sprite_size;
	b->cols = height / sprite_size;
	create_matrix(a);
	create_matrix(b);
	int frame_count = 0; /* alternates the matrixs being shown */

	if (!a->matrix || !b->matrix) {
		printf("A or B matrix allocating failed. GTFO!\n");
		exit(MALLOC_FAILURE);
	}

	create_life(b, fp, x, y, edge);
	sdl_render_life(&sdl_info, b->matrix);


        /* Main loop: loop forever. */
	while (1)
	{
		/* your game of life code goes here  */

		/* change the  modulus value to slow the rendering */
		if (SDL_GetTicks() % 150 == 0) {
			if (frame_count % 2 == 0) {
				klein(a, b);
				sdl_render_life(&sdl_info, a->matrix);
				frame_count++;
				frame_count %= 2;

			} else {
				klein(b, a);
				sdl_render_life(&sdl_info, b->matrix);
				frame_count++;
				frame_count %= 2;
			}
		}
		/* allows alternation of frames */
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
