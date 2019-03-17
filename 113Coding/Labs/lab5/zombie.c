/**
 * @file lab5.c
 * @brief Implements zombie.h.
 * @details Includes functions to get user input of zombie blood, toes, and
 * time and day discovered.  Also prints can print element of array.
 *
 * @author Matthew Olsen
 * @date October 8, 2015
 * @bug None
 * @todo More robust systems to check user input
 */

#include <stdio.h>
#include <stdlib.h>
#include "zombie.h"

#define INPUT_LENGTH 25

void input_data(struct zombies *data, int *data_element){
        get_dead(data, data_element);

        switch (data[*data_element].dead){
        case 'Y':
        case 'y':
                get_time(data, data_element);
                get_toes(data, data_element);
                break;
        case 'N':
        case 'n':
                get_time(data, data_element);
                get_blood(data, data_element);
                break;
        default:
                printf("%c is not valid input.\n", data[*data_element].dead);
        }
}

void get_dead(struct zombies *data, int *data_element){
        char input[INPUT_LENGTH];

        printf("Is the zombie dead?\n");
        printf("Y for yes or N for no: ");

        fgets(input, INPUT_LENGTH - 1, stdin);
        sscanf(input, "%c", &data[*data_element].dead);
}

/**
 * Assigns day, hour, min, and sec for specified data element
 * based on user input.
 * @param data the structure array to assign values to
 * @param data_element the element to assign values to
 */
void get_time(struct zombies *data, int *data_element){
        char input[INPUT_LENGTH];

        printf("Input the day you encountered this zombie.\n");
        printf("1) Sunday\n");
        printf("2) Monday\n");
        printf("3) Tuesday\n");
        printf("4) Wednesday\n");
        printf("5) Thursday\n");
        printf("6) Friday\n");
        printf("7) Saturday\n");

        fgets(input, INPUT_LENGTH - 1, stdin);
        data[*data_element].day = atoi(input);

        printf("Input the time you encountered this zombie in hour:min:sec format: ");

        fgets(input, INPUT_LENGTH - 1, stdin);
        sscanf(input,"%d:%d:%d", &data[*data_element].hour, &data[*data_element].min, &data[*data_element].sec);
}

/**
 * Assigns toes value for a specified data element based on user input.
 * @param data the structure array to assign toes to
 * @param data_element the element to assign toes to
 */
void get_toes(struct zombies *data, int *data_element){
        char input[INPUT_LENGTH];

        printf("Input the number of toes the dead zombie has: ");
        fgets(input, INPUT_LENGTH - 1, stdin);
        data[*data_element].toes = atoi(input);
}

/**
 * Assigns mL of blood for a specified data element based on user input.
 * @param data the structure array to assign blood to
 * @param data_element the element to assign blood to
 */
void get_blood(struct zombies *data, int *data_element){
        char input[INPUT_LENGTH];

        printf("Input the mL of blood that has oozed from the now dead zombie: ");
        fgets(input, INPUT_LENGTH - 1, stdin);
        data[*data_element].blood = atof(input);
}

/**
 * Prints the values in the structured array in a specific forumula.
 * @param data the structure array to assign blood to
 * @param data_element the element to assign blood to
 */
void print_data(struct zombies *data, int *data_element){

        puts("");

                printf("%d) The zombie was encountered ", *data_element);
                /* print if found dead or not */
                if(data[*data_element].dead == 'y' || data[*data_element].dead == 'Y'){
                        printf("dead.\n");
                } else {
                        printf("alive.\n");
                }

                /*print the day and time sighted */
                printf("It was sighted ");
                switch (data[*data_element].dead){
                case SUNDAY:
                        printf("Sunday ");
                        break;
                case MONDAY:
                        printf("Monday ");
                        break;
                case TUESDAY:
                        printf("Tuesday ");
                        break;
                case WEDNESDAY:
                        printf("Wednesday ");
                        break;
                case THURSDAY:
                        printf("Thursday ");
                        break;
                case FRIDAY:
                        printf("Friday ");
                        break;
                case SATURDAY:
                        printf("Saturday ");
                        break;
                }
                printf("at %d:%d:%d.\n", data[*data_element].hour, data[*data_element].min, data[*data_element].sec);

                /* if found dead print toes, else print the volume of blood oozed */
                if(data[*data_element].dead == 'y' || data[*data_element].dead == 'Y'){
                        printf("This zombie had %d toes.\n", data[*data_element].toes);
                } else {
                        printf("It was drained of %lf of blood once it was killed.\n", data[*data_element].blood);
                }

                puts("");

}
