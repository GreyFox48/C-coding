/**
 * @file dec2hex.c
 * @brief Dispalys hexidecimal values as decimal.
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
                printf("Please input the numbers you wish to convert as arguments, space seperated.\n");
                printf("Ex. ./hex2dec [NUMBER]...\n");
                return 0;
        }


        for (i = 1; i < argc; i++) {
                value = strtol(argv[i], &endptr, 16);

                if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) ||
                        (errno != 0 && value == 0)) {
                        sprintf(str, "error converting %s to a decimal value", argv[i]);
                        perror(str);
                        /* no use in further processing */
                        continue;
                }

                printf("%ld\n", value);
        }

        return 0;
}

