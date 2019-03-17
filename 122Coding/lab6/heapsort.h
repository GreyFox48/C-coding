/**
 * @file heapsort.h
 * @brief Takes in an array and makes it max heap sorted.
 * @details See heapsort.c for implementation details.
 *
 * @date April 11, 2016
 * @author Matthew Olsen
 * @bugs none
 * @todo nothing
 */

#ifndef HEAPSORT_H_
#define HEAPSORT_H_
#include <sys/types.h>

/**
 * sort an array of nel objects
 * @param base initial element of the array
 * @param nel the number of elements in the array
 * @param width the size of each element
 * @compar function pointer to comparison function 
 * @return 0 for success; -1 for error 
 *
 * The comparison function must return an integer less than, equal to, or greater than zero
 * if the first argument is considered to be less than, equal to, or greater than the second.
 *
 * The function comes from freebsd.
 */
int heapsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
void heapify(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
void check_children(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *), int parent, int max_child);
void swap(void *base, int a, int b, size_t width);
void sink_nodes(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

#endif
