/**
 * @file cpu.h
 * @brief Header file for cpu.c.
 * @details See cpu.c for implementation details.
 *
 * @author Matthew Olsen
 * @date November 16, 2015
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

#ifndef CPU_H_
#define CPU_H_

struct cpu_t {
        int word_size;
        int unsign;
        int overflow;
        int carry;
        int sign;
        int parity;
        int zero;
        struct bit_t *r1_head;
        struct bit_t *r1_tail;
        struct bit_t *r2_head;
        struct bit_t *r2_tail;
        struct bit_t *r3_head;
        struct bit_t *r3_tail;
};

struct cpu_t *create_cpu();
void get_word_size(struct cpu_t *cpu);
void get_unsign(struct cpu_t *cpu);
void create_register(char *string, struct bit_t **head, struct bit_t **tail);
void print_register(struct bit_t *head);
void binary_addition(struct cpu_t *cpu);
long long btointSigned(struct cpu_t *cpu, struct bit_t **head, struct bit_t **tail);
unsigned long long btointUnsigned(struct cpu_t *cpu, struct bit_t **head, struct bit_t **tail);
void bit_flip(struct bit_t *head);
void binary_substraction(struct cpu_t *cpu);
void binary_or(struct cpu_t *cpu);
void binary_xor(struct cpu_t *cpu);
void binary_and(struct cpu_t *cpu);
void parity_flag(struct cpu_t *cpu);
void zero_flag(struct cpu_t *cpu, struct bit_t *head);
void sign_flag(struct cpu_t *cpu, struct bit_t *head);

#endif
