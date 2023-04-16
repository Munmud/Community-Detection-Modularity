// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include<stdlib.h>
#include <stdio.h>
#include <gsl/gsl_eigen.h>
#include "MathLibrary.h"



// DLL internal state variables:
static unsigned long long previous_;  // Previous value, if any
static unsigned long long current_;   // Current sequence value
static unsigned index_;               // Current seq. position

int sum(int a, int b)
{
    return a * b;
}

