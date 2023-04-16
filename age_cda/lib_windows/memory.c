#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"


/*
    Allocate an one dimentional array

    @param size
        size of array
*/
double* create_1d_array(int size)
{

    double* arr = (double*)malloc(size * sizeof(double));
    if (arr == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    return arr;
}

/*
    Allocate an two dimentional array

    @param row
        number of rows
    @param col
        number of columns
*/
double** create_2d_array(int rows, int cols)
{
    double** arr = (double**)malloc(rows * sizeof(double*));
    if (arr == NULL)
    {
        printf("Error: Failed to allocate memory for 2D array.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        arr[i] = (double*)malloc(cols * sizeof(double));
        if (arr[i] == NULL)
        {
            printf("Error: Failed to allocate memory for 2D array.\n");
            exit(1);
        }
    }

    return arr;
}

/*
    Allocate an one dimentional array

    @param size
        size of array
*/
int* create_1d_array_int(int size)
{
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    return arr;
}

/*
    Allocate an two dimentional array

    @param row
        number of rows
    @param col
        number of columns
*/
int** create_2d_array_int(int rows, int cols)
{
    int** arr = (int**)malloc(rows * sizeof(int*));
    if (arr == NULL)
    {
        printf("Error: Failed to allocate memory for 2D array.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        arr[i] = (int*)malloc(cols * sizeof(int));
        if (arr[i] == NULL)
        {
            printf("Error: Failed to allocate memory for 2D array.\n");
            exit(1);
        }
    }

    return arr;
}

/*
    deallocate an two dimentional array

    @param row
        number of rows
*/
void free_2d_array(double** arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

void free_1d_array(int* arr)
{
    free(arr);
}
