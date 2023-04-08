#ifndef MEMORY_H
#define MEMORY_H

double *create_1d_array(int size);

double **create_2d_array(int rows,
                         int cols);

int *create_1d_array_int(int size);

int **create_2d_array_int(int rows,
                          int cols);

void free_2d_array(double **arr,
                   int rows);

#endif
