/**
 * @file cpu.c
 * @brief File allowing the creation of a cpu and simple calculations.
 * @details Simulates Intel CPU archetecture.  Has three registers, in which
 * the first two are used to caluculate the third with a specified operation
 * (which could be addition, subtraction, and, or, or xor).  Has fucntions
 * to calculate the flag conditions.
 *
 * @author Matthew Olsen
 * @date November 16, 2015
 * @todo Nothing
 * @bug none
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "dllist.h"

#define BUFF 132

/**
 * Allocates and pupulates an cpu_t structure
 * @return the pointer to the created cpu_t structure
 */
struct cpu_t *create_cpu(void)
{
        struct cpu_t *cpu = malloc(sizeof(struct cpu_t));
        cpu->word_size = 0;
        cpu->unsign = 0;
        cpu->overflow = 0;
        cpu->carry = 0;
        cpu->sign = 0;
        cpu->parity = 0;
        cpu->zero = 0;
        cpu->r1_head = NULL;
        cpu->r1_tail= NULL;
        cpu->r2_head= NULL;
        cpu->r2_tail= NULL;
        cpu->r3_head= NULL;
        cpu->r3_tail= NULL;
        return cpu;
}

/**
 * Gets the word size for the calculation
 * @param cpu the cpu structure to input word size
 */
void get_word_size(struct cpu_t *cpu)
{
        char input[BUFF];
        printf("Please input the word size: ");
        while (1) {
                fgets(input, BUFF, stdin);
                cpu->word_size = atoi(input);
                if (cpu->word_size <= 64 && cpu->word_size > 0)
                        return;
                /* prompt if the user fails to input valid size */
                printf("Word size must be an integer between 1 and 64.\n");
        }
}

/**
 * Gets the desired sign from the user
 * @param cpu the cpu to input the sign information to
 */
void get_unsign(struct cpu_t *cpu)
{
        char input[BUFF];
        printf("Unsigned values (y/N): ");
        fgets(input, BUFF, stdin);
        if (input[0] == 'y' || input[0] == 'Y') {
                cpu->unsign = 1;
        } else {
                cpu->unsign = 0;
        }

}

/**
 * Creates a register from a given string
 * @param string the string representing the binary values
 * @param head the address if the head of the register
 * @param tail the tail address of the register
 */
void create_register(char *string, struct bit_t **head, struct bit_t **tail)
{
        int i = 0;
        struct bit_t *node = NULL;


        for (i = 0; i < strlen(string); i++) {
                /* changes ascii char values to actual 1 or 0 value */
                node = create_node(string[i] - '0');
                insert_tail(head, tail, node);
        }
}

/**
 * Prints the binary inside the register
 * @param head the head of the register to be printed
 */
void print_register(struct bit_t *head)
{
        while (head) {
                printf("%u", head->x);
                head = head->next;
        }
        puts(""); /* just act as an charage return */
}

/**
 * Performs binary addition with two registers.  Will keep track of the carry
 * bit from CPU and warn if overflow occured
 * @param cpu the cpu containing the registers, overflow flag, and carry bit
 */
void binary_addition(struct cpu_t *cpu)
{
        struct bit_t *r1 = cpu->r1_tail; /* for easier reading */
        struct bit_t *r2 = cpu->r2_tail;
        struct bit_t *node = NULL;
        int sum;

        while (r1 && r2) {
                /* truth tables can predicted by addition */
                sum = r1->x + r2->x + cpu->carry;
                if (sum == 0) {
                        node = create_node(0);
                        cpu->carry = 0;
                        insert_head(&(cpu->r3_head), &(cpu->r3_tail), node);
                } else if (sum == 1) {
                        node = create_node(1);
                        cpu->carry = 0;
                        insert_head(&(cpu->r3_head), &(cpu->r3_tail), node);
                } else if (sum == 2) {
                        node = create_node(0);
                        cpu->carry = 1;
                        insert_head(&(cpu->r3_head), &(cpu->r3_tail), node);
                } else {
                        node = create_node(1);
                        cpu->carry = 1;
                        insert_head(&(cpu->r3_head), &(cpu->r3_tail), node);
                }
                /* go up the list */
                r1 = r1->prev;
                r2 = r2->prev;
        }
        /* if registers 1 and 2 most significant bits were the same but the
           third register is different */
        if ((cpu->r1_head->x == cpu->r2_head->x) && (cpu->r1_head->x != cpu->r3_head->x)) {
                cpu->overflow = 1;
        }
}

/**
 * Calculates the integer value of signed binary value and converts to base 10.
 * @param cpu the cpu containing the signed values
 * @param head the head of the linked list
 * @param tail the tail of the doubly linked list
 * @return the integer value of the register
 */
long long btointSigned(struct cpu_t *cpu, struct bit_t **head, struct bit_t **tail)
{
        /* must be long long to account for signed 64 bit values */
        long long sum = 0;
        long long base = 1;
        struct bit_t *node = *tail;

        /* need to stop early b/c first bit is used to signing */
        while (node != *head) {
                sum += base * node->x;
                base*=2;
                node = node->prev;
        }
        /* largest bit in signed bits is negative*/
        sum += -base * node->x;

        return sum;
}

/**
 * Calculates the integer value of unsigned binary value and converts to base 10.
 * @param cpu the cpu containing the signed values
 * @param head the head of the linked list
 * @param tail the tail of the doubly linked list
 * @return the integer value of the register
 */
unsigned long long btointUnsigned(struct cpu_t *cpu, struct bit_t **head, struct bit_t **tail)
{
        /* must account for unsigned 64 bit values */
        unsigned long long sum = 0;
        long long base = 1;
        struct bit_t *node = *tail;
        if (cpu->unsign == 1) {
                while (node) {
                        /* node ->x value is to determine whether to add value*/
                        sum += base * node->x;
                        /* each following bit in a bit string represents a
                           number two times the value of the previous */
                        base*=2;
                        node = node->prev;
                }
        } else {
                /* need to stop early b/c first bit is used to signing */
                while (node != *head) {
                        sum += base * node->x;
                        base*=2;
                        node = node->prev;
                }
                /* largest bit in signed bits is negative*/
                sum += -base * node->x;
        }
        return sum;
}

/**
 * performs a bit flip operation on a operation
 * @param head the head of the doubly linked list
 * @param tail of the doubly linked list
 */
void bit_flip(struct bit_t *head)
{
        while (head){
                if (head->x == 1) {
                        head->x = 0;
                } else if (head->x == 0) {
                        head->x = 1;
                }
                head = head->next;
        }
}

/**
 * Performs a binary subtraction operation
 * @param cpu the cpu structure containing the strucutres
 */
void binary_substraction(struct cpu_t *cpu)
{
        int carry = 1; /* to help simulate adding 1 after bit fliping */
        int sum;
        struct bit_t *node = cpu->r2_tail;
        /* b/c orginal msb will not be perserved after bit flip, store it
           to be used to detect overflow later */
        int r2_msb = cpu->r2_head->x;
        bit_flip(cpu->r2_head);
        /* to add 1 after the bit flip */
        while (node) {
                sum = carry + node->x;
                if (sum == 1) {
                        node->x = 1;
                        /* would no longer be carrying extra bit, so stop loop*/
                        break;
                } else if (sum == 2) {
                        node->x = 0;
                        carry = 1;
                }
                node = node->prev;
        }
        binary_addition(cpu);
        /* detect overflow again b/c the one in addition is not valid due to
           r2 bit flip */
        if ((cpu->r1_head->x == r2_msb) && (cpu->r1_head->x != cpu->r3_head->x)) {
                cpu->overflow = 1;
        }
}

/**
 * Performs a binary and operation, and stores the result in the third register
 * @param cpu the cpu contaning registers one and two
 */
void binary_and(struct cpu_t *cpu)
{
        struct bit_t *r1 = cpu->r1_head; /* for easier reading */
        struct bit_t *r2 = cpu->r2_head;
        struct bit_t *node = NULL;
        int sum;

        while (r1 && r2) {
                sum = r1->x + r2->x; /*truth tables can predicted by addition*/
                if (sum == 0 || sum == 1) {
                        node = create_node(0);
                        insert_tail(&(cpu->r3_head), &(cpu->r3_tail), node);
                /* sum of 2 would only happen if both bits are 1 */
                } else if (sum == 2) {
                        node = create_node(1);
                        insert_tail(&(cpu->r3_head), &(cpu->r3_tail), node);
                }
                r1 = r1->next;
                r2 = r2->next;
        }
}

/**
 * Performs a binary or operation, and stores the result in the third register
 * @param cpu the cpu contaning registers one and two
 */
void binary_or(struct cpu_t *cpu)
{
        struct bit_t *r1 = cpu->r1_head; /* for easier reading */
        struct bit_t *r2 = cpu->r2_head;
        struct bit_t *node = NULL;
        int sum;

        while (r1 && r2) {
                sum = r1->x + r2->x; /*truth tables can predicted by addition*/
                if (sum == 0) {
                        node = create_node(0);
                        insert_tail(&(cpu->r3_head), &(cpu->r3_tail), node);
                /* would only happen if one or both bits are 1 */
                } else if (sum == 2 || sum == 1) {
                        node = create_node(1);
                        insert_tail(&(cpu->r3_head), &(cpu->r3_tail), node);
                }
                r1 = r1->next;
                r2 = r2->next;
        }
}

/**
 * Performs a binary xor operation, and stores the result in the third register
 * @param cpu the cpu contaning registers one and two
 */
void binary_xor(struct cpu_t *cpu)
{
        struct bit_t *r1 = cpu->r1_head; /* for easier reading */
        struct bit_t *r2 = cpu->r2_head;
        struct bit_t *node = NULL;
        int sum;

        while (r1 && r2) {
                sum = r1->x + r2->x; /*truth tables can predicted by addition*/
                if (sum == 2 || sum == 0) {
                        node = create_node(0);
                        insert_tail(&(cpu->r3_head), &(cpu->r3_tail), node);
                /* would only happen if only 1 of the bits was one */
                } else if (sum == 1) {
                        node = create_node(1);
                        insert_tail(&(cpu->r3_head), &(cpu->r3_tail), node);
                }
                r1 = r1->next;
                r2 = r2->next;
        }
}

/**
 * Checks the parity of the third register. Sets to 1 if number of 1's in
 * register is even. Else sets to zero.
 * @param cpu the cpu structure with the register and flag
 */
void parity_flag(struct cpu_t *cpu)
{
        int count = 0;
        struct bit_t *node = cpu->r3_head;

        while (node) {
                if (node->x == 1)
                        count++;
                node = node->next;
        }
        if (count % 2 == 0) {
                cpu->parity = 1;
        }
        cpu->parity = 0;
}

/**
 * Checks if the register is set to zero.  Sets to 1 if true, else zero.
 * @param head the head of the list
 */
void zero_flag(struct cpu_t *cpu, struct bit_t *head)
{
        while (head) {
                if (head->x == 1) {
                        cpu->zero = 0;
                        return; /* doesn't need to check further */
                }
                head = head->next;
        }
        cpu->zero = 1;
}

/**
 * Checks the most significant bit in the register. Sets to 1 if MSB is
 * 1 or sets the flag to 0 otherwise.
 * @param head the head of the list
 */
void sign_flag(struct cpu_t *cpu, struct bit_t *head)
{
        cpu->sign = head->x;
}
