#ifndef EIGEN
#define EIGEN

#include <stdio.h>
#include <gsl/gsl_eigen.h>
#include "memory.h"

/*
    Partition the network into two communities using the signs of the elements of the 2nd largest eigenvector of adjacency matrix.

    Specifically, assign nodes with v_i > 0 to community 1 and nodes with v_i < 0 to community 2.

    @param A
        adjacency matrix

    @param n
        size of square adjacency matrix

    @return
        a list of community assignment
*/
int *getEigenVector(double **A, int n)
{
    int i, j;

    // double *data = malloc(n * n * sizeof(double));
    double *data = create_1d_array(n * n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            data[i * n + j] = A[i][j];

    gsl_matrix_view m = gsl_matrix_view_array(data, n, n);
    gsl_vector *eval = gsl_vector_alloc(n);
    gsl_matrix *evec = gsl_matrix_alloc(n, n);
    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(n);

    gsl_eigen_symmv(&m.matrix, eval, evec, w);
    gsl_eigen_symmv_free(w);
    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_DESC);

    // printf("Eigenvalues:\n");
    // for (i = 0; i < n; i++)
    // {
    //     printf("%.2g\n", gsl_vector_get(eval, i));
    // }

    // printf("Eigenvectors:\n");
    // for (i = 0; i < n; i++)
    // {
    //     gsl_vector_view evec_i = gsl_matrix_column(evec, i);
    //     printf("[");
    //     for (j = 0; j < n; j++)
    //     {
    //         printf("%g ", gsl_vector_get(&evec_i.vector, j));
    //     }
    //     printf("]\n");
    // }

    // Getting the eigenvector of the second largest eigenvaluses
    gsl_vector_view evec_i = gsl_matrix_column(evec, 1);

    int *output = create_1d_array_int(n);
    for (i = 0; i < n; i++)
    {
        output[i] = (gsl_vector_get(&evec_i.vector, i) < 0);
        // printf("%f ", output[i]);
    }

    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    free(data);

    return output;
}

#endif