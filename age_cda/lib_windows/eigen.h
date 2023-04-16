#pragma once
// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef EIGEN_EXPORTS
#define EIGEN_API __declspec(dllexport)
#else
#define EIGEN_API __declspec(dllimport)
#endif


extern EIGEN_API int* getEigenVector(double** A,
    int n);


