/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * icylfft3_emxutil.h
 *
 * Code generation for function 'icylfft3_emxutil'
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
void emxEnsureCapacity_creal32_T(const emlrtStack *sp, emxArray_creal32_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation);
void emxEnsureCapacity_real32_T(const emlrtStack *sp, emxArray_real32_T
  *emxArray, int32_T oldNumel, const emlrtRTEInfo *srcLocation);
void emxFree_creal32_T(emxArray_creal32_T **pEmxArray);
void emxFree_real32_T(emxArray_real32_T **pEmxArray);
void emxInit_creal32_T(const emlrtStack *sp, emxArray_creal32_T **pEmxArray,
  int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
void emxInit_real32_T(const emlrtStack *sp, emxArray_real32_T **pEmxArray,
                      int32_T numDimensions, const emlrtRTEInfo *srcLocation,
                      boolean_T doPush);

/* End of code generation (icylfft3_emxutil.h) */
