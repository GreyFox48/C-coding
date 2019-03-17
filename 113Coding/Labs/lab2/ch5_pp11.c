#include <stdio.h>

void say_tens(int tens);
void say_ones(int tens, int ones);
void say_teens(int input);
int main(void)
{
        int input;
        int ones;
        int tens;        
        
        printf("Please input a number: ");
        scanf("%d", &input);
        tens = input / 10;  /* finds tens place by truncating */
        ones = input % 10;

                
        if (input > 10 && input < 20) {
                say_teens(input);
                return 0; /* prevents improper output by ending program early */ 
        }
        say_tens(tens); /* must come first for proper output */
        say_ones(tens, ones);
        
        return 0;
}


/**
 *@param tens used to determine name for tens placement of inputed number
 */
void say_tens(int tens)
{
        switch (tens) {
        case 0:
                break; /* no input needed */
        case 1:
                printf("Ten\n"); /* all other numbers between 10 and 20 are specail cases handled by say_teens */
                break;
        case 2:
                printf("Twenty");
                break;
        case 3:
                printf("Thirty");
                break;
        case 4:
                printf("Fourty");
                break;
        case 5:
                printf("Fifty");
                break;
        case 6:
                printf("Sixty");
                break;
        case 7:
                printf("Seventy");
                break;
        case 8:
                printf("Eighty");
                break;
        case 9:
                printf("Ninety");
                break;
        default:
                printf("Error in tens");  /* error check */
        }
}

/**
 *@param tens used to determine name for ones placement of inputed number
 */
void say_ones(int tens, int ones)
{
        if (tens > 0)
                printf("-");  /* for when dash is needed in word */

        switch (ones) {
        case 0:
                break; /* no input needed */
        case 1:
                printf("one\n"); 
                break;
        case 2:
                printf("two\n");
                break;
        case 3:
                printf("three\n");
                break;
        case 4:
                printf("four\n");
                break;
        case 5:
                printf("five\n");
                break;
        case 6:
                printf("six\n");
                break;
        case 7:
                printf("seven\n");
                break;
        case 8:
                printf("eight\n");
                break;
        case 9:
                printf("nine\n");
                break;
        default:
                printf("Error in ones\n");  /* error check */
        }
}

/**
 *@param input used to determine specific name for -teen numbers
 */
void say_teens(int input)
{
        switch (input) {
        
        case 11:
                printf("eleven\n"); 
                break;
        case 12:
                printf("twelve\n");
                break;
        case 13:
                printf("thirteen\n");
                break;
        case 14:
                printf("fourteen\n");
                break;
        case 15:
                printf("fifteen\n");
                break;
        case 16:
                printf("sixteen\n");
                break;
        case 17:
                printf("seventeen\n");
                break;
        case 18:
                printf("eightteen\n");
                break;
        case 19:
                printf("nineteen\n");
                break;
        default:
                printf("Non-teen number inputed\n");  /* error check */
        }
        
}

