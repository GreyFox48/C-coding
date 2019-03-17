#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        int hour;
        int minutes;
        int input;
        int difference;
        int flight = 1;

        printf("Enter a 24 time: ");
        scanf("%d:%d", &hour, &minutes); 
        /* converts user input to minutes in day for easier comparison */
        input = hour * 60 + minutes;
        
        /* determines closest flight number to input via smallest absolute difference */
        /* each flight departure is inputed in minutes per day */
        difference = abs(480 - input);
        if (abs(583 - input) < difference) {
                difference = abs(583 - input);
                flight = 2;
        } 
        if (abs(679 - input) < difference) {
                difference = abs(679 - input);
                flight = 3;
        } 
        if (abs(767 - input) < difference) {
                difference = abs(767 - input);
                flight = 4;
        } 
        if (abs(840 - input) < difference) {
                difference = abs(840 - input);
                flight = 5;
        } 
        if (abs(945 - input) < difference) {
                difference = abs(945 - input);
                flight = 6;
        } 
        if (abs(1140 - input) < difference) {
                difference = abs(1140 - input);
                flight = 7;
        } 
        if (abs(1305 - input) < difference) {
                difference = abs(1305 - input);
                flight = 8;
        }

        /* displays which flight is closest, based on previously determined flight number */
        switch (flight) {
        case 1:
                printf("Closest Departure time is 8:00 a.m., arriving at 10:16 a.m.\n");
                break;
        case 2:
                printf("Closest Departure time is 9:43 a.m., arriving at 11:52 a.m.\n");
                break;
        case 3:
                printf("Closest Departure time is 11:19 a.m., arriving at 1:31 p.m.\n");
                break;
        case 4:
                printf("Closest Departure time is 12:47 p.m., arriving at 3:00 p.m.\n");
                break;
        case 5:
                printf("Closest Departure time is 2:00 p.m., arriving at 4:08 p.m.\n");
                break;
        case 6:
                printf("Closest Departure time is 3:45 p.m., arriving at 5:55 p.m.\n");
                break;
        case 7:
                printf("Closest Departure time is 7:00 p.m., arriving at 9:20 p.m.\n");
                break;
        case 8:
                printf("Closest Departure time is 9:45 p.m., arriving at 11:58 p.m.\n");
                break;
        default:
                printf("No flight can be found.\n");
        }
        
        return 0;
}
