/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cylfft3_mexutil.c
 *
 * Code generation for function 'cylfft3_mexutil'
 *
 */

/* Include files */
#include "cylfft3_mexutil.h"
#include "cylfft3.h"
#include "cylfft3_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
emlrtCTX emlrtGetRootTLSGlobal(void)
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX aTLS,
  void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

/* End of code generation (cylfft3_mexutil.c) */
