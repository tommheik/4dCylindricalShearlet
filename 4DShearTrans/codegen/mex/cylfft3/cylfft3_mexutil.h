/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cylfft3_mexutil.h
 *
 * Code generation for function 'cylfft3_mexutil'
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
emlrtCTX emlrtGetRootTLSGlobal(void);
void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX aTLS,
  void *aData);

/* End of code generation (cylfft3_mexutil.h) */
