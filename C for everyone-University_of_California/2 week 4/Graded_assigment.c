/*
Open and read a file of integers into an array...
..that is created with the first integer telling you how many to read.
*/
#include <stdio.h>
#include <stdlib.h> //exit()
#define MAX_HW 20

// Read data from the input file
void read_data(FILE *ptr, int d[], int *size)
    {

    *size = 0; // Make the sixe to be 0. The pointer is pointing to the actual value
    // fscanf is used to get data from the file(ptr)
    // Get the drefernecre of the array d[](memory location), the read sixe into the array (*size)
    // If it is succesfull return 1. Then increment size
    // We end up having the number of element of file in the output array

    while (fscanf(ptr, "%d", &d[*size]) == 1)
        (*size)++;
    }

    // Print the ntegers on the screen
    void print_data(int d[], int size)
    {

        int i;

        for (i = 1; i < size; i++)
        {
            printf("%d\t", d[i]);
            if ((i + 1) % 10 == 0)
                printf("\n"); // Output 10 result in a line at once
        }
    }

    // Make the first integer to be the array length
    void change_array_length(int data[], int *array_size)
    {
        int i;
        for (i = 0; i < 1; i++)
        {
            *array_size = data[i];
        }
    }

    // Compute the average of the integers
    double average(int d[], int size)
    {

        int i;
        double avg = 0.0;

        for (i = 1; i < size; i++)
            avg += d[i];

        return (avg / size);
    }

int main(void)
{ 
    FILE *input_file, *output_file;

    int i, array_size = MAX_HW;

    int data[MAX_HW] = {100, 0}; // initialie to 100 and 0
    char result[100];

    input_file = fopen("question-hw3", "r+"); // r+ means someone can read and write to the file
    output_file = fopen("answer-hw3", "w+");  // It is writable and readable

    input_file = fopen("question-hw3", "r+"); // r+ means someone can read and write to the file

    // Ensure there is input or output file
    if (output_file == NULL && input_file == NULL)
    {
        printf("No output or input file");
        exit(1);
    }
    read_data(input_file, data, &array_size); // &array_size means pass in the memory location/defreference of size
    change_array_length(data, &array_size);
    printf("My %d homework scores are: ", array_size);

    print_data(data, array_size); // Print the data

    // Print to screen
    printf("\nAverage score was %10f", average(data, array_size));
    // Print to file
    fprintf(output_file, "Average score was %10f", average(data, array_size));

    printf("\n\n");
    fclose(input_file);
    fclose(output_file);
    return 0;
}
