/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * permute.h
 *
 * Code generation for function 'permute'
 *
 */

#ifndef PERMUTE_H
#define PERMUTE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "cylfft3_types.h"

/* Function Declarations */
extern boolean_T nomovement(const int perm[5], const emxArray_creal32_T *a);
extern void permute(const emxArray_creal32_T *a, emxArray_creal32_T *b);

#endif

/* End of code generation (permute.h) */
