/**
 * @file life.h
 * @brief Header file for life.c.  Specifies a frame structure.
 *
 * @date 2015-11-30
 * @author Matthew Olsen
 */

#ifndef LIFE_H_
#define LIFE_H_

#include <stdlib.h>
#include <stdio.h>

/* to keep the row and column numbers with the frames */
struct frame_t {
        int rows;
        int cols;
        unsigned char **matrix;
};

struct frame_t *create_frame(int width, int height, int sprite_size);
void create_matrix(struct frame_t *frame);
void hedge(struct frame_t *new, struct frame_t *old);
unsigned char hedge_cell(struct frame_t *old, int x, int y);
void free_frame(struct frame_t *frame);
void create_life(struct frame_t *frame, char *file, int x, int y, int edge);
void create_life_105(struct frame_t *frame, FILE *fp, int x, int y, int edge);
void create_life_106(struct frame_t *frame, FILE *fp, int x, int y, int edge);
int modulus(int numerator, int denominator);
unsigned char torus_cell(struct frame_t *old, int x, int y);
void torus(struct frame_t *new, struct frame_t *old);
void klein(struct frame_t *new, struct frame_t *old);
unsigned char klein_cell(struct frame_t *old, int x, int y);

#endif
