#pragma once
// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef MODULARITY_EXPORTS
#define MODULARITY_API __declspec(dllexport)
#else
#define MODULARITY_API __declspec(dllimport)
#endif

extern MODULARITY_API double** getModularityMatrix(double** A,
    int size);

extern MODULARITY_API double modularityScore(double** mod_mat,
    int n,
    int* assignment);

