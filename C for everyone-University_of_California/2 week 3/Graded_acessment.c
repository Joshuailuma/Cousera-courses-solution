/*
A linear linked list code to store a randomly generated set of 100 integers.
A routine that will rearrange the list in sorted order of these values. */

#include <stdio.h>
#include <stdlib.h>
// In can array is not allowed to be returned from a function
// Instead we return a pointer to the array, specifing the array name
// without an index
int *random_number()
{
    // declare the local variables
    static int array[100]; // Declare as static variable, address can't be returned outside a function
    int i, num;
    // printf("To get the random number from 1 to 100 \n");
    for (i = 0; i <= 100; i++)
    {
        array[i] = rand() % 100 + 1; // use rand() function to get the random number
    }
    return array;
}

// This will perform the sapping of position for the bubble sort
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// This prints the array and a text passed to it
// notice, we passed a pointer
void print_array(int how_many, int data[], char *str)
{
    int i;
    printf("%s", str);

    for (i = 0; i < how_many; i++)
        if (i % 6 == 0)
        {
            printf("\n\n");
        }
        else
        {
            printf("%d\t", data[i]);
            /* code */
        }
}

// This will do the loop transverse and call the swap function
void bubble(int data[], int how_many)
{
    int i, j, go_on;
    for (i = 0; i < how_many; i++)
    {
        print_array(how_many, data, "\ninside bubble\n");

        printf("i = %d, \ninput any int to continue:", i);
        scanf("%d", &go_on);
        for (j = how_many - 1; j > i; j--)
            if (data[j - 1] > data[j])
                swap(&data[j - 1], &data[j]);
    }
}

int main(void)
{
    const int SIZE = 100;
    int *random_numbers; // Have to be initialized as a pointer

    random_numbers = random_number();
    // Order in which functions are carried out
    print_array(SIZE, random_numbers, "My random_numbers\n");
    printf("\n\n");
    bubble(random_numbers, SIZE);
    print_array(SIZE, random_numbers, "My sorted random_numbers\n");
    printf("\n\n");
    return 0;
}
