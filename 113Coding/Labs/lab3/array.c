/**
 * @file array.c  
 * @author Matthew Olsen
 * @date September 23rd, 2015  
 * Assignment: Lab 3 
 * @brief Functions for fundamental array algorithms. 

 * @details The functions implemented include basic counting, 
 * summing, searching, and basic statistical methods (average,
 * median, the max, the min). Sorting is implemented via
 * bubble sort, a not very efficient sort, and insertion sort.
 *  
 * @bugs none
 * @todo implement floating point versions of the functions
 */


#include "array.h"
#include <stdio.h>

/** prints out the elements of an array, one element per line
 * @param a[] the array to print
 * @param size the size or length of the array
 */
void print_array(int a[], size_t size)
{
	int i;
	
	for(i = 0; i < size; i++)
		printf("a[%d] = %d\n", i, a[i]);
}

/** 
 * finds the largest element of an array
 * @param a[] the array to be searched
 * @param size the size of the array
 * @return the largest element of array a[]
 */
int find_max(int a[], size_t size){
        
        int rep;
        int max = a[0];
        for (rep = 1; rep < size; rep++) {                
                if (max < a[rep]) {
                        max = a[rep];
                }
        }
        return max;
}

/** 
 * finds the smallest element of an array
 * @param a[] the array to be searched
 * @param size the size of the array
 * @return the smallest element of array a[]
 */
int find_min(int a[], size_t size)
{
        int rep;
        int min = a[0];
        for (rep = 1; rep < size; rep++) {
                if (min > a[rep]) {
                        min = a[rep];
                }
        }
        return min;
}

/**
 * finds the midpoint of the array
 * @param a[] the array with the values
 * @param size the size of a[]
 * @return the midpoint of a[]
 */
int midpoint(int a[], size_t size)
{
        int max = find_max(a, size);
        int min = find_min(a, size);
        return (max + min) / 2;

}

/**
 * count the values in the array that are either less than,
 * less than or equal to, greater than, or greater than or 
 * equal to the given value
 * @param a[] the array with the values
 * @param size the size of a[]
 * @param type, the type of comparison to be made
 * @param value the value to be compare the elements of a[] against
 */
int get_count(int a[], size_t size, int type, int value)
{
        int count = 0;
        int rep;

        switch (type) {
        case LT:
                for(rep = 0; rep < size; rep++) {
                        if(a[rep] < value) {
                                count++;
                        }
                }
                break;
        case LE:
                for(rep = 0; rep < size; rep++) {
                        if(a[rep] <= value) {
                                count++;
                        }
                }
                break;
        case GT:
                for(rep = 0; rep < size; rep++) {
                        if(a[rep] > value) {
                                count++;
                        }
                }
                break;
        case GE:
                for(rep = 0; rep < size; rep++) {
                        if(a[rep] >= value) {
                                count++;
                        }
                }
                break;
        default:
                printf("ERROR:  Unknown value in get_count switch.\n");
        }       
        return count;
}

/**
 * finds the first index of a value in an array, or else returns 1
 * @param a[] the array to be searched
 * @param size the size of a[]
 * @param value the value to be found in a[]
 * @return the first index of value, or -1 if not found
 */
int linear_search(int a[], size_t size, int value)
{
        int rep;
        for(rep = 0; rep < size; rep++)
        {
                if(a[rep] == value) {
                        return rep;
                }
        }
        return -1;        
}

/**
 * finds the sum of all elements of an array
 * @param a[] the array to be searched
 * @param size the size of a[]
 * @return the sum of all elements of a[]
 */
int find_sum(int a[], size_t size)
{
        int rep;   
        int sum = 0;     
        for(rep = 0; rep < size; rep++)
        {
               sum += a[rep];
        }
        return sum;
}

/**
 * finds the average of all elemetents of an array
 * @param a[] the array to be searched
 * @param size the size of a[]
 * @return the sum of all elements of a[]
 */
double find_average(int a[], size_t size)
{
        double sum = find_sum(a, size);
        return sum / size;
}

/** 
 * sorts a given array utalizing a bubble sort, from smallest to largest
 * @param a[] the array to be sorted
 * @param size the size of array a[]
 */
void bubble_sort(int a[], size_t size)
{
        int i;
        int rep;
        int temp;
        
        for(i = 0; i < (size - 1); i++) {
                for(rep = size - 1; rep > i; rep--) {
                        if(a[rep] < a[rep - 1]) {
                                temp = a[rep - 1];
                                a[rep - 1] = a[rep];
                                a[rep] = temp;
                        }
                }
        }
}

/**
 * sorts a given array utalizing an insertion sort, from smallest to largest
 * @param a[] the array to be sorted
 * @param size the size of array a[]
 */
void insertion_sort(int a[], size_t size)
{
        int i;
        int rep;
        int value;

        for(i = 1; i < size; i++) {
                value = a[i];
                rep = i - 1;
                while((rep >= 0) && (value < a[rep])) {
                        a[rep + 1] = a[rep];
                        rep--;
                }
                a[rep + 1] = value; 
        }
}

/**
 * flips given array to opposite order given
 * @param a[] the array to be sorted
 * @param size the size of array a[]
 */
void reverse(int a[], size_t size)
{
        int temp;
        int rep;        
        /* (size / 2) - 1 stops rep at element before the midpoint */ 
        for(rep = 0; rep <= (size - 1) / 2; rep++) {
                temp = a[rep];
                a[rep] = a[(size - 1) - rep];
                /* size - 1 is needed for a[size - rep]  is out of bounds when rep == 0 */
                a[(size - 1) - rep] = temp;
        }
}

/**
 * finds the median of a given array
 * @param a[] the array to be sorted
 * @param size the size of array a[]
 * @return the median of the elements of an array
 */
double find_median(int a[], size_t size)
{
        int temp[size];
        int rep;

        /* didn't utalize insertion_sort on a[] because find_median
         * is to only find the median, not to also mutate a[] */
        for (rep = 0; rep < size; rep++) {
                temp[rep] = a[rep];
        }
        insertion_sort(temp, size);

        if(size % 2 == 0) {
                return (temp[(size / 2) - 1] + temp[size / 2]) / 2.0;
        } else {
                return temp[size / 2];
        }
}

/**
 * finds the number of even numbers in a given array
 * @param a[] the array to be sorted
 * @param size the size of array a[]
 * @return the count of even numbers in a[]
 */
int even_count(int a[], size_t size)
{
        int count = 0;
        int rep;

        for(rep = 0; rep < size; rep++) {
                if(a[rep] % 2 == 0) {
                        count++;
                }
        }
        
        return count;
}

/**
 * finds the number of odd numbers in a given array
 * @param a[] the array to be sorted
 * @param size the size of array a[]
 * @return the count of odd numbers in a[]
 */
int odd_count(int a[], size_t size)
{
        int count = 0;
        int rep;

        for(rep = 0; rep < size; rep++) {
                if(a[rep] % 2 == 1) {                        
                        count++;
                }
        }
        
        return count;
}

/**
 * finds the number elements divisible by a given number
 * @param a[] the array to be sorted
 * @param size the size of array a[]
 * @param value the give value to check the elements against
 * @return the count of numbers divisible by value
 */
int divisible_count(int a[], size_t size, int value)
{
        int count = 0;
        int rep;

        for(rep = 0; rep < size; rep++) {
                if(a[rep] % value == 0) {                        
                        count++;
                }
        }
        
        return count;
}
