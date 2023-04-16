#pragma once
// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef MATH_LIBRARY_EXPORTS
#define MATH_LIBRARY_API __declspec(dllexport)
#else
#define MATH_LIBRARY_API __declspec(dllimport)
#endif


extern MATH_LIBRARY_API int sum(int a, int b);

