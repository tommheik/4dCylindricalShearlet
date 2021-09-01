/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFTImplementationCallback.h
 *
 * Code generation for function 'FFTImplementationCallback'
 *
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "cylfft3_types.h"

/* Function Declarations */
extern void c_FFTImplementationCallback_dob(const emxArray_real32_T *x, int
  n2blue, int nfft, const emxArray_real32_T *costab, const emxArray_real32_T
  *sintab, const emxArray_real32_T *sintabinv, emxArray_creal32_T *y);
extern void c_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
  emxArray_real32_T *costab, emxArray_real32_T *sintab, emxArray_real32_T
  *sintabinv);
extern void c_FFTImplementationCallback_get(int nfft, boolean_T useRadix2, int
  *n2blue, int *nRows);
extern void c_FFTImplementationCallback_r2b(const emxArray_real32_T *x, int
  n1_unsigned, const emxArray_real32_T *costab, const emxArray_real32_T *sintab,
  emxArray_creal32_T *y);
extern void d_FFTImplementationCallback_dob(const emxArray_creal32_T *x, int
  n2blue, int nfft, const emxArray_real32_T *costab, const emxArray_real32_T
  *sintab, const emxArray_real32_T *sintabinv, emxArray_creal32_T *y);
extern void e_FFTImplementationCallback_r2b(const emxArray_creal32_T *x, int
  n1_unsigned, const emxArray_real32_T *costab, const emxArray_real32_T *sintab,
  emxArray_creal32_T *y);

#endif

/* End of code generation (FFTImplementationCallback.h) */
