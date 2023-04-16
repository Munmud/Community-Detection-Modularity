#pragma once
// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef COMMUNITY_DETECTION_EXPORTS
#define COMMUNITY_DETECTION_API __declspec(dllexport)
#else
#define COMMUNITY_DETECTION_API __declspec(dllimport)
#endif


extern COMMUNITY_DETECTION_API int* get_community_assignment(int* input,
    int nrows,
    int ncols);

