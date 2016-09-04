#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <complex>
#include <vector>

// Precision Numbers
typedef float real;
typedef std::complex<real> cplx;

// 1D Array
typedef std::vector<real> vec;
typedef std::vector<cplx> cplxVec;

// 2D Array
typedef std::vector<vec> mat;
typedef std::vector<cplxVec> cplxMat;

// 3D Array
typedef std::vector<mat> grid;
typedef std::vector<cplxVec> cplxMat;

// loop
typedef std::size_t loop;

#endif
