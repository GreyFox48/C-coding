/**
 * @file zombie.h
 * @brief Header file for zombies.c.
 * @details See zombie.c for implementation.
 *
 * @author Matthew Olsen
 * @date October 8, 2015
 * @bug None
 */

#ifndef ZOMBIE_H_
#define ZOMBIE_H_

struct zombies{
        char dead; /* y if dead or n for alive */
        enum {SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY,
                SATURDAY} day;
        int toes;
        double blood;
        int hour;
        int min;
        int sec;
};

void input_data(struct zombies *data, int *data_element);
void get_dead(struct zombies *data, int *data_element);
void get_time(struct zombies *data, int *data_element);
void get_toes(struct zombies *data, int *data_element);
void get_blood(struct zombies *data, int *data_element);
void print_data(struct zombies *data, int *data_element);

#endif
