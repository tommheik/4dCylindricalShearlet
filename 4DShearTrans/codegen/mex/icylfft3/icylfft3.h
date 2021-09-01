/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * icylfft3.h
 *
 * Code generation for function 'icylfft3'
 *
 */

#pragma once

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "omp.h"
#include "icylfft3_types.h"

/* Function Declarations */
void icylfft3(const emlrtStack *sp, const emxArray_creal32_T *F,
              emxArray_real32_T *f);

/* End of code generation (icylfft3.h) */
