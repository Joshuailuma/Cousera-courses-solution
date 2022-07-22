/*
Write a program that can give the sine of a value between 0 and 1 (non inclusive)
*/
#include <stdio.h>
#include <math.h>
int main(void)
{
    double input_value;
    double result;
    printf("Please type in a value between 0 and 1");

    scanf("%lf", &input_value);

    result = sin(input_value);

    printf("\nThe sine of %lf is %f \n", input_value, result);
    return 0;
}