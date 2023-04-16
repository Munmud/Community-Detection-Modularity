#pragma once
// memory.h - Contains declarations of memory functions
#pragma once

#ifdef MEMORY_EXPORTS
#define MEMORY_API __declspec(dllexport)
#else
#define MEMORY_API __declspec(dllimport)
#endif

extern MEMORY_API double* create_1d_array(int size);

extern MEMORY_API double** create_2d_array(int rows,
    int cols);

extern MEMORY_API int* create_1d_array_int(int size);

extern MEMORY_API int** create_2d_array_int(int rows,
    int cols);

extern MEMORY_API void free_2d_array(double** arr,
    int rows);