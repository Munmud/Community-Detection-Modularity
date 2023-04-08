#ifndef MODULARITY_H
#define MODULARITY_H

double **getModularityMatrix(double **A,
                             int size);

double modularityScore(double **mod_mat,
                       int n,
                       int *assignment);
#endif