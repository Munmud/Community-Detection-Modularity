#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_eigen.h>

/*
    Allocate an one dimentional array

    @param size
        size of array
*/
double *create_1d_array(int size)
{

    double *arr = (double *)malloc(size * sizeof(double));
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
double **create_2d_array(int rows, int cols)
{
    double **arr = (double **)malloc(rows * sizeof(double *));
    if (arr == NULL)
    {
        printf("Error: Failed to allocate memory for 2D array.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        arr[i] = (double *)malloc(cols * sizeof(double));
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
int *create_1d_array_int(int size)
{
    int *arr = (int *)malloc(size * sizeof(int));
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
int **create_2d_array_int(int rows, int cols)
{
    int **arr = (int **)malloc(rows * sizeof(int *));
    if (arr == NULL)
    {
        printf("Error: Failed to allocate memory for 2D array.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        arr[i] = (int *)malloc(cols * sizeof(int));
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
void free_2d_array(double **arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

void free_1d_array(int *arr)
{
    free(arr);
}

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
double **getModularityMatrix(double **A, int size)
{
    int i, j, m;
    double ki, kj, m_ij;

    // double k[size]; // degree vector
    double *k = create_1d_array(size);
    double **B = create_2d_array(size, size);

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
double modularityScore(double **mod_mat, int n, int *assignment)
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
        output[i] = (gsl_vector_get(&evec_i.vector, i) >= 0);
        // printf("%f ", output[i]);
    }

    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    free(data);

    return output;
}

/*
    Creates an adjacency list from the list of undirected edge
    @param edge
        an 2 dimention array of column size 2.
        Store the undirected edge
    @param edge_count
        number of edge in edge array
    @param n
        number of total nodes
*/
double **create_adj_matrix(int *edge, int edge_count, int n)
{
    double **mat = create_2d_array(n, n);
    int i, u, v;

    for (i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;

    for (i = 0; i < edge_count; i++)
    {
        u = edge[i * 2];
        v = edge[i * 2 + 1];
        mat[u][v] = 1;
        mat[v][u] = 1;
    }
    return mat;
}

/*
    Filter from the parent adjacecny list to new community adjacency list
    @param adj
        Adjacency List
    @param nodes_map
        List of nodes(0 to n-1) for new community
    @param n
        size of new community
    @return
        Adjacency List of new community
*/
double **separate_adj_matrix(double **adj, int *nodes_map, int n)
{
    int i, j;
    double **adj_mat = create_2d_array(n, n);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            adj_mat[i][j] = adj[nodes_map[i]][nodes_map[j]];

    return adj_mat;
}

/*
    @param nodes
        List of nodes found in a community
    @param n
        size of nodes
    @param final_array
        Final Assignment array to store the community id of every node
    @param community_num
        the number of assigned community to all the nodes
    @returns void
*/
void final_community_assignment(int *nodes, int n, int *final_array, int *community_num)
{
    for (int i = 0; i < n; i++)
        final_array[nodes[i]] = (*community_num);

    (*community_num)++;
}

/*
    Partition the network into two communities using the signs of the elements of the 2nd largest eigenvector of adjacency matrix.
    Specifically, assign nodes with v_i > 0 to community 1 and nodes with v_i < 0 to community 2.
    @param adj_mat
        The adjacency matrix of the network.
    @param n
        The number of nodes in the network.
    @param nodes
        An array of node indices to consider for community division.
    @param mod_mat
        The modularity matrix of the network.
    @param community_num
        The number of communities for final division
    @param final_array
        An array to store the community assignments of each node after division.
    @param mod1
        The initial modularity value of the network.
    @return void
*/
void divide_community(double **adj_mat, int n, int *nodes, double **mod_mat, int *community_num, int *final_array, double mod1)
{
    int i, j, k;
    if (n <= 2)
    {
        final_community_assignment(nodes, n, final_array, community_num);
        free_2d_array(adj_mat, n);
        free(nodes);
        return;
    }

    int *assignment = getEigenVector(adj_mat, n);
    int group1_size = 0;
    int group2_size = 0;

    for (i = 0; i < n; i++)
    {
        if (assignment[i] == 0)
            group1_size++;
        else
            group2_size++;
    }

    int *group1 = create_1d_array_int(group1_size);
    int *group1_map = create_1d_array_int(group1_size); // index of group 1
    int *group2 = create_1d_array_int(group2_size);
    int *group2_map = create_1d_array_int(group2_size); // index of group 2

    for (i = 0, j = 0, k = 0; i < n; i++)
    {
        if (assignment[i] == 0)
        {
            group1[j] = nodes[i];
            group1_map[j] = i;
            j++;
        }
        else
        {
            group2[k] = nodes[i];
            group2_map[k] = i;
            k++;
        }
    }

    free(assignment);

    double mod2, mod3;
    if (group1_size <= 1)
        mod2 = 0;
    else
        mod2 = modularityScore(mod_mat, group1_size, group1);
    if (group2_size <= 1)
        mod3 = 0;
    else
        mod3 = modularityScore(mod_mat, group2_size, group2);
    if (mod1 >= (mod2 + mod3))
    {
        final_community_assignment(nodes, n, final_array, community_num);
        free_2d_array(adj_mat, n);
        free(group1_map);
        free(group2_map);
        free(nodes);
        return;
    }

    double **mat1 = separate_adj_matrix(adj_mat, group1_map, group1_size);
    double **mat2 = separate_adj_matrix(adj_mat, group2_map, group2_size);

    free(group1_map);
    free(group2_map);

    divide_community(mat1, group1_size, group1, mod_mat, community_num, final_array, mod2);
    divide_community(mat2, group2_size, group2, mod_mat, community_num, final_array, mod3);

    free_2d_array(adj_mat, n);
    free(nodes);
}

/*
    @param edge
        an 2 dimention array of column size 2.
        Store the undirected edge
    @param edge_count
        number of edge in edge array
    @param n
        total number of nodes
    @param output
        An array to store the final assignment
    @return void
*/
int *get_community_assignment(int *edge, int edge_count, int n)
{
    int i, j;

    int *output = create_1d_array_int(n);

    /*
    Step 1: Construct the Adjacency Matrix
    Given a network with N nodes, construct its adjacency matrix A. If the network is undirected and unweighted, Aij = 1 if there is an edge between node i and node j, and Aij = 0 otherwise. If the network is weighted or directed, Aij should be the weight or direction of the edge from node i to node j.
    */
    double **adj_mat = create_adj_matrix(edge, edge_count, n);

    /*
    Step 2: Calculate the Modularity Matrix
    Using the adjacency matrix A, calculate the modularity matrix B as follows:
    B[i][j] = A[i][j] - k[i] k[j] / 2m
    where ki and kj are the degrees of nodes i and j, respectively, and m is the total number of edges in the network.
    */
    double **mod_mat = getModularityMatrix(adj_mat, n);

    /*
        start all the node (0 to n-1) in 1 community
    */
    int *nodes = create_1d_array_int(n);
    for (int i = 0; i < n; i++)
        nodes[i] = i;

    int community_num = 0;
    divide_community(adj_mat, n, nodes, mod_mat, &community_num, output, modularityScore(mod_mat, n, nodes));

    free_2d_array(mod_mat, n);

    return output;
}

// gcc -shared -o my_library.dll my_library.c -I"C:\MinGW\gsl-2.7.1\eigen\" -L"C:\MinGW\gsl-2.7.1\eigen\" -lgsl -lgslcblas

// gcc test.c -Wall -I"C:\Program Files (x86)\GnuWin32\include" -L"C:\Program Files (x86)\GnuWin32\lib" -lgslcblas -lgsl -lm -o test

// gcc my_library.c -shared -o my_library.dll -I"C:\Program Files (x86)\GnuWin32\include" -L"C:\Program Files (x86)\GnuWin32\lib" -lgsl -lgslcblas -lm

// gcc my_library.c -shared -o my_library.dll -lgsl -lgslcblas -lm

/*
    FOR windows 64 bit
    sudo apt-get install mingw-w64
    sudo apt-get install libgsl-dev

*/
// x86_64-w64-mingw32-gcc -static -shared -o my_library_win_64.dll my_library.c -lgsl -lgslcblas -lm
// x86_64-w64-mingw32-gcc -static -o myprogram.exe my_library.c -lgsl -lgslcblas -lm
