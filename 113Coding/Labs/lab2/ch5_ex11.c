/**
 * @file lab2.c
 * @brief Determines location of area code inputed by user
 * 
 * @author Matthew C. Olsen
 * @date September 14, 2015
 */

#include <stdio.h>

int main(void)
{
        int input;
        printf("Please input the area code: ");
        scanf("%d", &input);

        /* determines city based on area code */
        switch (input) {
        case 229:
                printf("Albany\n");
                break;
        case 404:
        case 470:
        case 678:
        case 770:
                printf("Atlanta\n");
                break;
        case 478:
                printf("Macon\n");
                break;
        case 706:
        case 762:
                printf("Columbus\n");
                break;
        case 912:
                printf("Savannah\n");
                break;
        default:
                printf("Area Code not recognized.\n");
        }
        
        return 0;
}
