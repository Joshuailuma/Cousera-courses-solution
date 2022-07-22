#include <stdio.h>
#include <math.h>
double i = 0.0;
double sine;
double cosine;
int main(void)
{
    while (i <= 0.9)
    {
        sine = sin(i);
        cosine = cos(i);
        printf(" The sine of %lf is %lf and The cosine of %lf is %lf\n", i, sine, i, cosine);
        i = i + 0.1;
    }
}

// #include <stdio.h> // I included this library so that I can use 'printf()' function.
// #include <math.h>  // I included this library so that I can use these functions: has  sin(), abs(), and fabs().
// #include <float.h> // I included this library so that I can use 'double' data type.

// // now I'm declaring these dumbass variables so that I can use them later to store some values in them.
// int i;
// double Interval, Absolute, Sine_Value;
// // now I'am declaring these functions so that the stupid compiler gets to know that I'm going to use them in the main function.
// double sin(double Interval);
// double abs(double Sine_Value);
// // This is the main function where compiler starts to excute the code
// int main(void)
// {
//     for (i = 0; i < 30; i++)
//     {
//         Interval = i / 10.0;        // we take every integer from 0 to 29 and devide it by 10, and then we put the answer in the variable 'Intervale'
//         Sine_Value = sin(Interval); // this function calculates the sine value.
//         Absolute = abs(Sine_Value); // this function calculates the mother fucking absolute values.
//         printf("%lf\n", Absolute);  // and finally, man I thout this will never end! the program prints the absolut of sine values of
//     }
//     printf("\n+++++++\n");
//     return 0;
// }