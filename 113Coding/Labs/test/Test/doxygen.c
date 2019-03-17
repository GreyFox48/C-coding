/**
 * @file doxygen.c
 * @brief Implements a sum function. (A brief description of what the file does).
 * @details a longer description of what the code in the file does. Optional
 * depends on the code the file contains. 
 *
 * @author Scott Chadde
 * @date Spring 2015
 * @bug None or list bugs
 * @todo Optional
 */

#include <stdio.h>

/* note: this is not a doxygen comment
 * if a function returns a void no @return is used
 *
 * Optional Doxygen tags for functions are:
 * @remarks for any notes about the function
 * @bug any bugs in the function
 * @todo anything that needs to be implemented
 * 
 * Note that there is no comma after the parameter name 
 * and you don't state the parameter's type.
 *
 * this is wrong:
 * @param int x, blah blah
 * void foo(int x) 
 * 
 * Also start the brief section one line after the /**     
 */

/* start file declarations/prototypes before main 
 * the function's body is below main 
 * no camel case or its variants for function names. 
 */

int add(int m, int n);
void print_sum(int a, int b, int sum);

int main(void)
{
        int a = 7;
        int b = 14;
        print_sum(a, b, add(a, b));
        return 0;
}

/**
* Adds two integers
* @param m the first addend
* @param n the second addend
* @return the sum m + n
*/
int add(int m, int n)
{
        return m + n;
}

/**
 * prints the sum of two integers
 * @param a the first addend
 * @param b the second addend
 * @param sum the sum of a + b
 */ 
void print_sum(int a, int b, int sum)
{
        printf("%d + %d = %d\n", a, b, sum);
}

