// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "modularity.h"

/*
    In the context of community detection, the modularity matrix is a matrix representation of the strength of connections between nodes in a network. It is calculated by subtracting the expected number of edges between nodes in a random network from the actual number of edges between nodes in the network of interest. The modularity matrix is used to identify communities within the network based on the strength of connections between nodes. Specifically, it is used to determine the modularity of a given partition of the network, which is a measure of the quality of the partition in terms of the strength of connections within and between communities.

    Compute the modularity matrix B from the adjacency matrix A. This can be done using the Newman and Girvan's formula, which is:

    B[i][j] = A[i][j] - (k[i]k[j])/(2m)

    where k[i] is the degree of node i, m is the total number of edges in the graph, and the sum is over all pairs of nodes (i,j).

    @param A
        Adjacency Matrix
    @param size
        size of adjacency square matrix

    @return
        modularity matrix

*/
double** getModularityMatrix(double** A, int size)
{
    int i, j, m;
    double ki, kj, m_ij;

    // double k[size]; // degree vector
    double* k = create_1d_array(size);
    double** B = create_2d_array(size, size);

    // calculate degree vector k
    for (i = 0; i < size; i++)
    {
        ki = 0;
        for (j = 0; j < size; j++)
            ki += A[i][j];
        k[i] = ki;
    }

    // Get Total edge
    int M = 0;
    for (i = 0; i < size; i++)
        for (j = i + 1; j < size; j++)
            M += A[i][j];

    // calculate modularity matrix B
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            m = A[i][j];
            ki = k[i];
            kj = k[j];
            m_ij = m - (ki * kj) / (2 * M);
            B[i][j] = m_ij;
        }
    }

    free(k);

    return B;
}

/*
    Calculate Modularity

    @param mod_mat
        Modularity Matrix

    @param n
        size of Modularity Matrix

    @param assignment
        an array of community assignment

    @returns
        modularity score
*/
double modularityScore(double** mod_mat, int n, int* assignment)
{
    double score = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            score += mod_mat[assignment[i]][assignment[j]];
        }
    }
    return score;
}

