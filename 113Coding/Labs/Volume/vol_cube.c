#include <stdio.h>

int get_volume_cube(int side_length);

int main(void)
{
        int side_length = -1;
        int positive_flag = 0;        
        int area_cube;

        while (side_length <= 0) {                
                printf("Enter the side length of the cube.\n");
                scanf("%d", &side_length);

                if (side_length <= 0 && positive_flag == 0) {
                        printf("Please enter a positive value.\n");
                        positive_flag = 1;
                } else if (side_length <= 0) {
                        printf("Negative or zero value entered.\nPlease try again.\n");
                }           
        }

        area_cube = get_volume_cube(side_length);
    
        printf("Cube area = %d\n", area_cube);        

        return 0;
}

int get_volume_cube(int side_length)
{
        return side_length * side_length * side_length;
}

