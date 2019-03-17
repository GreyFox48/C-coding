#include <stdio.h>

int get_volume_cube(int width, int height, int depth);

int main(void)
{
        int height = -1;
        int positive_flag = 0;
        int width = -1;
        int depth = -1;
        int area_cube;

        while (height <= 0) {                
                printf("Enter the height\n");
                scanf("%d", &height);
                if (height <= 0 && positive_flag == 0) {
                        printf("Please enter a positive value\n");
                        positive_flag = 1;
                } else if (height <= 0) {
                        printf("Negative or zero value entered.\nPlease try again\n");
                }
        }

        while (width <= 0) {                
                printf("Enter the width\n");
                scanf("%d", &width);
                if (width <= 0 && positive_flag == 0) {
                        printf("Please enter a positive value\n");
                        positive_flag = 1;
                } else if (width <= 0) {
                        printf("Negative or zero value entered.\nPlease try again\n");
                }
        }
        
        while (depth <= 0) {                     
                printf("Enter the depth\n");
                scanf("%d", &depth);
                if (depth <= 0 && positive_flag == 0) {
                        printf("Please enter a positive value\n");
                        positive_flag = 1;
                } else if (depth <= 0) {
                        printf("Negative or zero value entered.\nPlease try again\n");
                }   
        }

        area_cube = get_volume_cube(width, height, depth);
    
        printf("Box area = %d\n", area_cube);        

        return 0;
}

int get_volume_cube(int width, int height, int depth)
{
        return width * height * depth;
}

