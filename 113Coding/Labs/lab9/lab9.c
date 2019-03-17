/**
 * @file lab9.c
 * @brief Simulates a simple cpu with a user specified word size
 * @details Allows a user to calculate two binary numbers of a specified word
 * size using a user speciifed operation.  The operation could be addition,
 * subtraction, binary and, binary or, and binary xor.
 *
 * @author Matthew Olsen
 * @date November 16, 2015
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dllist.h"
#include "cpu.h"

#define BUFF 132

void pad_zeros(struct cpu_t *cpu, char *reg_str, char *binary);
int check_string(struct cpu_t *cpu, char *string);
void clean_string(char *string);
void pretty_output(struct cpu_t *cpu, char operation);


int main(void) {
        struct cpu_t *cpu = create_cpu();
        char reg_str[BUFF]; /* the zero padded string to be turned into a reg */
        char *temp = NULL; /* temparily holds the string returned by strtok */
        char binary[BUFF]; /* stores just the user inputed binary string */
        char input[BUFF]; /* stores the binary expression the user inputed */
        char *operator; /* stores the operator the user inputed */

        REPEAT:
        get_word_size(cpu);
        get_unsign(cpu);

        INPUT: while (1) {

                /* reset the registers, for new input or if error occured */
                delete_list(&(cpu->r1_head), &(cpu->r1_tail));
                delete_list(&(cpu->r2_head), &(cpu->r2_tail));
                delete_list(&(cpu->r3_head), &(cpu->r3_tail));
                /* needs to be reset in case set to 1 from last computation */
                cpu->carry = 0;

                printf("Input binary expression: ");
                fgets(input, BUFF, stdin);

                temp = strtok(input, " ");
                strncpy(binary, temp, strlen(temp) + 1);
                clean_string(binary); /* removes spaces or \n characters */
                /* ensure binary is a valid size with valid characters */
                if (!check_string(cpu, binary)){
                        goto INPUT;
                }
                /* pad with zeros if needed */
                pad_zeros(cpu, reg_str, binary);
                create_register(reg_str, &(cpu->r1_head), &(cpu->r1_tail));


                /* stores the inputed operator for later */
                operator = strtok(NULL, " ");

                /* creates second register, same process as first register */
                temp = strtok(NULL, " ");
                strncpy(binary, temp, strlen(temp) + 1);
                clean_string(binary);
                if (!check_string(cpu, binary)){
                        goto INPUT;
                }
                pad_zeros(cpu, reg_str, binary);
                create_register(reg_str, &(cpu->r2_head), &(cpu->r2_tail));

                break;

        }

        switch (operator[0]) {
        case '+':
                binary_addition(cpu);
                break;
        case '-':
                binary_substraction(cpu);
                break;
        case '&':
                binary_and(cpu);
                break;
        case '|':
                binary_or(cpu);
                break;
        case '^':
                binary_xor(cpu);
                break;
        default:
                printf("%c is not a valid operator\n", operator[0]);
                goto INPUT; /* must start from binary input again */
                break;
        }

        pretty_output(cpu, operator[0]);
        printf("Do you want to continue? (Y/n): ");
        fgets(input, BUFF, stdin);

        if (input[0] == 'y' || input[0] == 'Y' || input[0] == '\n' ) {
                goto REPEAT;
        }
        /* free the registers */
        delete_list(&(cpu->r1_head), &(cpu->r1_tail));
        delete_list(&(cpu->r2_head), &(cpu->r2_tail));
        delete_list(&(cpu->r3_head), &(cpu->r3_tail));
        free(cpu);

        return 0;
}

/**
 * Checks a binary string to ensure that it only contains 1's or 0's, and also
 * if it is the proper word size.
 * @para cpu the cpu structure containing the proper word size
 * @param string the string to be checked
 * @return 1 if string is properly formated, 0 if not
 */
int check_string(struct cpu_t *cpu, char *string)
{
        if(strlen(string) > cpu->word_size){
                printf("Binary expression is longer than word size. Retry.\n");
                return 0;
        }

        while (*string) { /*check for non zero or one characters */
                if (*string != '1' && *string != '0') {
                        printf("Binary string can only be 1's or 0's. Retry\n");
                        return 0;
                }
                string++;
        }
        return 1;
}

/**
 * Takes two string, and copies one string into another with 0's padded at
 * the beginning
 * @param cpu the cpu with the word size
 * @param reg_str the character string to copy into and pad with zeros
 * @param binary the string to be copied, containing the binary
 */
void pad_zeros(struct cpu_t *cpu, char *reg_str, char *binary)
{
        int i;

        /* pad reg_str with zeros for the difference between word_size and
         * binary's length */
        for (i = 0; i < (cpu->word_size - strlen(binary)); i++) {
                reg_str[i] = '0';
        }
        reg_str[i] = '\0'; /* needed to tell where strncat to begin */

        /*creates the completed padded string */
        strncat(reg_str, binary, strlen(binary));
}

/**
 * Rewrites a given string to not include spaces or \n characters
 * @param string the string to be cleaned
 */
void clean_string(char *string)
{
        int i = 0;
        int j = 0;

        for ( i = j = 0; j < strlen(string); j++) {
                if (string[j] != ' ' && string[j] != '\n') {
                /* if not a space or \n, store it back into the temp string */
                        string[i++] = string[j];
                }
        }
        /* ensures last character is a null character */
        string[i] = '\0';

}

/**
 * Generates a pretty output of the cpu flags and registers
 * @param cpu the cpu containing the flags and registers to be printed
 * @param operation the operation done to generate the third register
 */
void pretty_output(struct cpu_t *cpu, char operation)
{
        int i; /* for a for loop */

        /* prints the registers and a function */
        print_register(cpu->r1_head);
        printf("%c\n", operation);
        print_register(cpu->r2_head);

        /* creates a seperation line dependent upon the word size */
        for (i = 0; i < cpu->word_size; i++) {
                printf("-");
        }
        puts("");

        print_register(cpu->r3_head);

        /* prints each individual flag as well as the decimal value of reg 3 */
        sign_flag(cpu, cpu->r3_head);
        zero_flag(cpu, cpu->r3_head);
        parity_flag(cpu);
        printf("FLAGS\nOF: %u\nCF: %u\n", cpu->overflow, cpu->carry);
        printf("SF: %u\nPF: %u\nZF: %u\n", cpu->sign, cpu->parity, cpu->zero);
        if (cpu->unsign == 0) {
                printf("Decimal: %lld\n", btointSigned(cpu, &(cpu->r3_head), &(cpu->r3_tail)));
        } else {
                printf("Decimal: %llu\n", btointUnsigned(cpu, &(cpu->r3_head), &(cpu->r3_tail)));
        }
}
