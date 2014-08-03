//
// Common data type declarations
//
// Copyright  2010-2013  Moe Wheatley
// Copyright  2014       Alexandru Csete
// All rights reserved.
//
// This software is released under the Simplified BSD License, see
// license.txt for details.
//
#ifndef DATATYPES_H
#define DATATYPES_H

#include <float.h>
#include <math.h>
#include <stdint.h>

// comment out to use double precision math
//#define USE_DOUBLE_PRECISION

// temporary typedefs while porting from cutesdr
typedef int32_t     qint32;
typedef uint32_t    quint32;
typedef int16_t     qint16;

/// \brief Single precision complex.
typedef struct _scplx{
    float re;
    float im;} scplx_t;

/// Double precision complex.
typedef struct _dcplx{
    double re;
    double im;} dcplx_t;

/// Complex type using S16.
typedef struct _iscplx{
    int16_t re;
    int16_t im;} stereo16_t;
typedef stereo16_t stereo_t;typedef int16_t    mono_t;
//#define TYPESTEREO16 tStereo16
//#define TYPEMONO16 int16

/// Definitions of real and complex data type
/// @fixme Use typedef isntead
#ifdef USE_DOUBLE_PRECISION
    #define real_t    double
    #define complex_t dcplx_t
#else
    #define real_t    float
    #define complex_t scplx_t
#endif

#ifdef USE_DOUBLE_PRECISION
    #define MSIN(x) sin(x)
    #define MCOS(x) cos(x)
    #define MPOW(x,y) pow(x,y)
    #define MEXP(x) exp(x)
    #define MFABS(x) fabs(x)
    #define MLOG(x) log(x)
    #define MLOG10(x) log10(x)
    #define MSQRT(x) sqrt(x)
    #define MATAN(x) atan(x)
    #define MFMOD(x,y) fmod(x,y)
    #define MATAN2(x,y) atan2(x,y)

    #define M_EPSILON DBL_EPSILON
#else
    #define MSIN(x) sinf(x)
    #define MCOS(x) cosf(x)
    #define MPOW(x,y) powf(x,y)
    #define MEXP(x) expf(x)
    #define MFABS(x) fabsf(x)
    #define MLOG(x) logf(x)
    #define MLOG10(x) log10f(x)
    #define MSQRT(x) sqrtf(x)
    #define MATAN(x) atanf(x)
    #define MFMOD(x,y) fmodf(x,y)
    #define MATAN2(x,y) atan2f(x,y)

    #define M_EPSILON FLT_EPSILON
#endif

//#define K_2PI (8.0*atan(1))   //maybe some compilers are't too smart to optimize out
#define K_2PI (2.0 * 3.14159265358979323846)
#define K_PI (3.14159265358979323846)
#define K_PI4 (K_PI/4.0)
#define K_PI2 (K_PI/2.0)
#define K_3PI4 (3.0*K_PI4)

#endif // DATATYPES_H
