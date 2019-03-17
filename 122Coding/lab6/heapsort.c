/**
 * @file heapsort.c
 * @brief Takes in an array and makes it max heap sorted.
 * @details Utilizes void pointers, so could in theory heap anything based upon
 *          the param compar
 *
 * @date April 11, 2016
 * @author Matthew Olsen
 * @bugs none
 * @todo nothing
 */

#include "heapsort.h"
#include <sys/types.h>

/**
 * Swaps the elements of index a and b in a void array
 * @param base the base of the array
 * @param nel the number of elements in the array base
 * @param compar the compar function to sort by
 * @param 0 on successful return.
 */
int heapsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{        
        heapify(base, nel, width, compar);
        sink_nodes(base, nel, width, compar);

        return 0;
}

/**
 * Sinks nodes of a given max heaped void array and rearranges into ascending order as
 * determined by compar
 * @param base the base of the void array
 * @param nel the number of elemetns in base
 * @param width the size of the elements of base
 * @param compar the comparision function, which takes two contstant void pointers 
          to compare the elements
 */
void heapify(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
        int parent, i;

        for (i = nel; i > 0; i--) {
        	/* formula calculates parent from 0 based indexed list */
                parent = (i + (i % 2)) / 2 - 1;
                check_children(base, nel, width, compar, parent, nel - 1);
        }
}

/**
 * Checks the children of a given parent index for max-heapness.  If a swap
 * happens, recusively checks the children for heapness.
 * @param base the base of the void array
 * @param nel the number of elemetns in base
 * @param width the size of the elements of base
 * @param the parent node of the children to be checked
 * @param maxchild the last node to be checked
 * @param compar the comparision function, which takes two contstant void pointers 
          to compare the elements
 */
void check_children(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *), int parent, int max_child)
{
        /* default to comparing left child */
        int child = 2 * parent + 1; 

        /* ensures checks do not exceed array bounds */
        if (child > max_child) {
                return;
        /* if left child in bounds but right is not */
        } else if (child + 1 > max_child) {
                if (compar(base + width * parent, base + width * child) < 0) {
                        swap(base, child, parent, width);
                }
                return;
        }

        /* finds index of greater child */
        if (compar(base + width * child, base + width * (child + 1)) < 0)  {
                child = child + 1;
        }

        /* if true, swap and then check all related children recursively */
        if (compar(base + width * parent, base + width * child) < 0) {
                swap(base, child, parent, width);                
                check_children(base, nel, width, compar, child, max_child);
        }
}

/**
 * Swaps the elements of index a and b in a void array
 * @param base the base of the array
 * @param a the first index to be swapped
 * @param b the second index to be swapped
 * @param width the width of the elements of base
 */
void swap(void *base, int a, int b, size_t width)
{
        char temp; /* needed to hold value of one byte */
        /* byte casting to (char *), can access each indiviual byte of deferenced pointer */
        char *x = (char *)(base + width * a);
        char *y = (char *)(base + width * b);
        int i;
        /* swap each byte */
        for (i = 0; i < width; i++) {
                temp = *x;
                *x++ = *y;
                *y++ = temp;                
        }        
}


/**
 * Sinks nodes of a given max heaped void array and rearranges into ascending order as
 * determined by compar
 * @param base the base of the void array
 * @param nel the number of elemetns in base
 * @param width the size of the elements of base
 * @param compar the comparision function, which takes two contstant void pointers 
          to compare the elements
 */
void sink_nodes(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
        int i;        
        for (i = nel - 1 ; i > 0;) {
                swap(base, 0, i, width);
                i--;
                check_children(base, nel, width, compar, 0, i);
        }
}
