/*
This programe uses struct to print the nextday depending on the current day
*/
#include <stdio.h>
int tot_days, i;

// Enumerate the number of months in a year
typedef enum month
{
    jan,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
} month;

typedef struct date
{
    month m;
    int d;
} date;

// Prints the month and day passed into the function with respect to the created struct
void printday(date *the_date)
{

    if (the_date->m == jan)
    {
        printf("January %d", the_date->d);
        tot_days = 31;
    }
    else if (the_date->m == feb)
    {
        printf("February %d", the_date->d);
        tot_days = 28;
    }
    else if (the_date->m == mar)
    {
        printf("March %d", the_date->d);
        tot_days = 31;
    }
    else if (the_date->m == apr)
    {
        printf("April %d", the_date->d);
        tot_days = 30;
    }
    else if (the_date->m == may)
    {
        printf("May %d", the_date->d);
        tot_days = 31;
    }
    else if (the_date->m == jun)
    {
        printf("June %d", the_date->d);
        tot_days = 30;
    }
    else if (the_date->m == jul)
    {
        printf("July %d", the_date->d);
        tot_days = 31;
    }
    else if (the_date->m == aug)
    {
        printf("August %d", the_date->d);
        tot_days = 31;
    }
    else if (the_date->m == sep)
    {
        printf("September %d", the_date->d);
        tot_days = 30;
    }
    else if (the_date->m == oct)
    {
        printf("October %d", the_date->d);
        tot_days = 31;
    }
    else if (the_date->m == nov)
    {
        printf("November %d", the_date->d);
        tot_days = 30;
    }
    else
    {
        printf("December %d", the_date->d);
        tot_days = 31;
    }
}

date *nextday(date *the_date)
{ // When the day chosen is the last day of the month
    if (the_date->d == tot_days)
    {
        the_date->d = (the_date->d + 1) % tot_days; // Go to 1st day of next month
        the_date->m = (the_date->m + 1) % 12;       // If we chose dec 31, then Go to jan 1
    }
    else // If we're not in the last of the month, just increment the day
        the_date->d = the_date->d + 1;
    return the_date;
}

int main()
{
    // Test date with values
    date first_date = {feb, 28};
    date second_date = {mar, 22};
    date third_date = {dec, 31};
    date dates[] = {first_date, second_date, third_date};

    for (i = 0; i < 3; i++)
    {
        // printf("Please write your current month and day e.g 'jan 2'");
        // scanf("%c %d", &month, &day);
        printf("Todays's date is ");
        printday(&dates[i]);
        printf("\nThe next day is ");
        nextday(&dates[i]);
        printday(&dates[i]);
        printf("\n\n");
    }
    return 0;
}