/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * icylfft3_data.c
 *
 * Code generation for function 'icylfft3_data'
 *
 */

/* Include files */
#include "icylfft3_data.h"
#include "icylfft3.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
omp_lock_t emlrtLockGlobal;
omp_nest_lock_t emlrtNestLockGlobal;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "icylfft3",                          /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

emlrtRSInfo g_emlrtRSI = { 21,         /* lineNo */
  "fftw",                              /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\eml\\lib\\matlab\\datafun\\fftw.m"/* pathName */
};

emlrtRSInfo h_emlrtRSI = { 15,         /* lineNo */
  "MATLABFFTWCallback/fft1d",          /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\eml\\eml\\+coder\\+internal\\+fft\\MATLABFFTWCallback.m"/* pathName */
};

/* End of code generation (icylfft3_data.c) */
