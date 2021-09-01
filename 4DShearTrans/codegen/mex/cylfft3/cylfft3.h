/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cylfft3.h
 *
 * Code generation for function 'cylfft3'
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
#include "cylfft3_types.h"

/* Function Declarations */
void cylfft3(const emlrtStack *sp, const emxArray_real32_T *f,
             emxArray_creal32_T *F);

/* End of code generation (cylfft3.h) */
