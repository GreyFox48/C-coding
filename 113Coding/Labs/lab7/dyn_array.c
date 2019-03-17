/**
 * @file dyn_array.c
 * @brief Finds the mean, med, min, and max of an inputed array.
 * @details The user will input the numbers manually one by one and the array
 * is created via the allocation of memory.
 *
 * @author Matthew Olsen
 * @date 2015-10-28
 * @bug Little error checking for user input
 * @todo Implement error checking
 */

#include <stdio.h>
#include <stdlib.h>

#define LEN 20
#define MALLOC_FAILED 1000

int *alloc_input(int *array, int input, size_t size);
void print_array(int *array, size_t size);
int *find_min(int *array, size_t size);
int *find_max(int *array, size_t size);
double find_mean(int *array, size_t size);
double find_median(int *a, size_t size);
void insertion_sort(int *array, size_t size);

int main(void)
{
        int menu = 1; /* to ensure program enters while loop */
        int input;
        size_t size; /* number of integers user inputed */
        char buff[LEN];
        int *array;

        printf("This program can find the min, max, median, and mean of an");
        printf(" inputed array of integers.\n");

        for (size = 0; menu; ){
                printf("0: Calculate array statistics and exit program\n");
                printf("1: Input new number\n");

                fgets(buff, LEN - 1, stdin);
                sscanf(buff, "%d", &menu);

                if (menu == 1){
                        printf("Input an integer for the array: ");

                        fgets(buff, LEN - 1, stdin);
                        sscanf(buff, "%d", &input);

                        array = alloc_input(array, input, size);
                        size++; /* ensures incrementing only after input */
                } else if (menu != 0){
                        printf("I do not recongnize %d\n", menu);
                }
        }

        print_array(array, size);
        printf("The min of the array is %d\n", *(find_min(array, size)));
        printf("The max of the array is %d\n", *(find_max(array, size)));
        printf("The mean of the array is %.2lf\n", find_mean(array, size));
        printf("The median of the array is %.1lf\n", find_median(array, size));

        free(array);

        return 0;
}

/**
 * creates array to store user input utalizing malloc or realloc
 * @param array the pointer to the array to store the integers in
 * @param inputs the number of elements in array, including new input
 * @param input the user input to add to array
 * @return the base address to the array
 */
int *alloc_input(int *array, int input, size_t size)
{
        if (size == 0){ /* needs to create array for first time */
                array = malloc((size + 1) * sizeof(int));

                if (array == NULL) {
                        printf("malloc failed. goodbye...\n");
                        exit(MALLOC_FAILED);
                }

                *(array + size) = input;
        } else if (size > 0){
                /* realloc was not necessary for lab but I wanted to practice
                 * with it. */
                array = realloc(array, (size + 1) * sizeof(int));
                /* because program doesn't ask for number of inputs orginally,
                 * needs to keep adjusting size with each input
                 * until user is finished */
                if (array == NULL) {
                        printf("realloc failed. goodbye...\n");
                        exit(MALLOC_FAILED);
                }

                *(array + size) = input;
        } else {
                printf("ERROR: alloc_array size value < 0\n");
        }

        return array;
}

/**
 * @param prints the integer elements of a given array
 * @param array the array to be printed
 * @param size the size of the array
 */
void print_array(int *array, size_t size)
{
        int i;
        printf("The array elements are: ");

        for (i = 0; i < size; i++){
                printf("%d\t", *(array + i));
        }

        puts("");
}

/**
 * locates the address to the minimum integer in the given array
 * @param array the array to be searched
 * @param size the size of the array
 * @return pointers the minimum integer in the array
 */
int *find_min(int *array, size_t size)
{
        int *min = array;
        int rep;

        for(rep = 0; rep < size; rep++){
                if (*(array + rep) < *min){
                        min = array + rep; /* gives memory address rather than
                                            * index */
                }
        }

        return min;
}

/**
 * locates the address to the maximum integer in the given array
 * @param array the array to be searched
 * @param size the size of the array
 * @return pointer to the maximum integer in the array
 */
int *find_max(int *array, size_t size)
{
        int *max = array;
        int rep;

        for(rep = 0; rep < size; rep++){
                if (*(array + rep) > *max){
                        max = array + rep;  /* gives memory address rather than
                                             * index */
                }
        }

        return max;
}

/**
 * calculates the mean value of all integers in the array
 * @param array the array with the integers
 * @param size the size of the array
 * @return the mean of the array
 */
double find_mean(int *array, size_t size)
{
        double mean = 0;
        int rep;

        for(rep = 0; rep < size; rep++){
                mean += *(array + rep);
        }

        return mean / size;
}

/**
 * finds the median of a given array using pointers
 * @param array the array find the median in
 * @param size the size of array
 * @return the median of the elements of an array
 */
double find_median(int *array, size_t size)
{
        int temp[size];
        int rep;

        for (rep = 0; rep < size; rep++) {
                *(temp + rep) = *(array + rep);
        }

        /* didn't utalize insertion_sort on array because find_median
         * is to only find the median, not to also mutate array */
        insertion_sort(temp, size);

        /* pointer is not given because the median may not exits in array */

        if (size % 2 == 0) {
                return (*(temp + (size / 2 - 1)) + *(temp + (size / 2))) / 2.0;
        } else {
                return *(temp + (size / 2));
        }
}

/**
 * sorts a given array utalizing an insertion sort, from smallest to largest
 * @param *array the array to be sorted
 * @param size the size of array
 */
void insertion_sort(int *array, size_t size)
{
        int i;
        int rep;
        int value;

        for(i = 1; i < size; i++) {
                value = *(array + i);
                rep = i - 1;
                /* shift all values greater than value up one index */
                while((rep >= 0) && (value < *(array + rep))) {
                        *(array + rep + 1) = *(array + rep);
                        rep--;
                }
                /* + 1 offsets previous rep-- */
                *(array + rep + 1) = value;
        }
}
