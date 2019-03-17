/**
 * @file dec2hex.c
 * @brief Dispalys decimal value integers as hexidecimal.
 * @details Values are inputed as arguments and the hexidecimal values are unsigned
 *
 * @date August 28, 2016
 * @author Matthew Olsen
 * @bugs None.
 * @todo Nothing
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[])
{
        int i;
        long int value;
        char str[255];
        char *endptr = NULL;

        if (argc < 2) {
                printf("Please input the hexideicmal numbers you wish to "
                        "convert to decimal as arguments, space seperated.\n");
                printf("Ex. ./dec2hex [NUMBER]...\n");
                return 0;
        }


        for (i = 1; i < argc; i++) {
                value = strtol(argv[i], &endptr, 10);

                if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) ||
                        (errno != 0 && value == 0)) {
                        sprintf(str, "error converting %s to a hexadecimal value", argv[i]);
                        perror(str);
                        /* no use in further processing */
                        continue;
                }

                printf("0x%lX\n", value);
        }

        return 0;
}

