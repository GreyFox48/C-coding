/* Matthew Olsen
 * September 9, 2015
 * Prelab2 Q$
 *
 * Oh geez, 7 errors.  
 */

#inlcude <stdio>
/* needs to be <stdio.h> */

int main()
{
        char input;
        printf("Enter a character: \n");
        scanf("%f", input);
        /* %f should be %c */
        /* also need & directly before input */

        switch (input) {
        case 'a':
                printf("A is for apple.\n");
                /* lacks a break; */
        case 'b';
        /* the constant expression should end with :, not ; */
                printf("B is for Banana!/n");
                /* the new line token is \n, not /n */
                break;
        default:
                printf("The letter %d isn't important!\n", input);
                /* the %d token will put a number in the place of your character, friend.
                 * use %c for letters, instead.
                 */
        }       
        
        return 0;
} 

