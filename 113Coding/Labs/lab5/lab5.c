/**
 * @file lab5.c
 * @brief Makes a small database for zombie kills.
 * @details Recordes the time and day the zombie was encountered, and if
 * alive or dead.  If dead, recordes number of toes.  If foudn alive, the
 * amount of blood that oozes out once dead.
 *
 * @author Matthew Olsen
 * @date October 8, 2015
 * @bug None
 * @todo Ability to edit specific zombie entries
 */


#include <stdlib.h>
#include <stdio.h>
#include "zombie.h"

#define INPUT_LENGTH 25 /* length of input array */
#define DATA_LENGTH 5 /* amount of zombie data to be saved */

int main(void)
{
        int menu = 0;
        int rep;
        char input[INPUT_LENGTH];
        struct zombies data[DATA_LENGTH];
        int data_element = 0;
        int total_zombies = 0;

        while (1) {
                printf("1) Enter new zombie information\n");
                printf("2) Display zombie information\n");
                printf("3) Return to fighting zombies\n");
                fgets(input, INPUT_LENGTH - 1, stdin);
                menu = atoi(input);

                switch (menu){
                case 1:
                        input_data(data, &data_element);
                        data_element++; /*keeps track of what array positio to write to */
                        total_zombies++; /* to be used to prevent printing of junk data */
                        data_element = data_element % DATA_LENGTH; /* creates circular data entry in array */
                        break;
                case 2:
                        for(rep = 0; (rep < DATA_LENGTH) && (rep < total_zombies); rep++){ /*rep < total_zombies prevents printing of junk data */
                                print_data(data, &rep);
                        }
                        break;
                case 3:
                        printf("Goodbye and Good Luck!\n");
                        exit(EXIT_SUCCESS);
                default:
                        printf("I do not recognize that input.\n");
                }
        }

        printf("ERROR:  Escaped main function's while loop.\n");
        return -1;
}
