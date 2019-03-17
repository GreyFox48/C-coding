#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int width = 800;
	int height = 600;
	int sprite_size = 16; /* either 2, 4, 8, or 16 */
        /* colors are RGB model valid values [0, 255] */
	unsigned char red = 255;
	unsigned char green = 255;
	unsigned char blue = 255;
        int c;

	while ((c = getopt(argc, argv, "w:h:e:r:g:b:s:f:")) != -1)	{
	switch (c) {
		case 'w':
			width = atoi(optarg);
			printf("width is %d\n", width);
			break;
		case 'h':
			height = atoi(optarg);
			printf("height is %d\n", height);
			break;
		case 'e':
			printf("Nothing for now for Shapes :)\n");
			break;
		case 'r':
			red = atoi(optarg);
			printf("red is %d\n", red);
			break;
		case 'g':
			green = atoi(optarg);
			printf("green is %d\n", green);
			break;
		case 'b':
			blue = atoi(optarg);
			printf("blue is %d\n", blue);
			break;
		case 's':
			sprite_size = atoi(optarg);
			printf("sprite_size is %d\n", sprite_size);
			break;
		}
	}

        return 0;
}
