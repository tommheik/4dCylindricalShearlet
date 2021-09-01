/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_cylfft3_mex.c
 *
 * Code generation for function '_coder_cylfft3_mex'
 *
 */

/* Include files */
#include "_coder_cylfft3_mex.h"
#include "_coder_cylfft3_api.h"
#include "cylfft3.h"
#include "cylfft3_data.h"
#include "cylfft3_initialize.h"
#include "cylfft3_mexutil.h"
#include "cylfft3_terminate.h"

/* Variable Definitions */
static jmp_buf emlrtJBEnviron;

/* Function Declarations */
MEXFUNCTION_LINKAGE void cylfft3_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[1]);

/* Function Definitions */
void cylfft3_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[1])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4, 7,
                        "cylfft3");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 7,
                        "cylfft3");
  }

  /* Call the function. */
  cylfft3_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexAtExit(&cylfft3_atexit);
  emlrtLoadLibrary("C:\\ProgramData\\MATLAB\\SupportPackages\\R2020a\\3P.instrset\\mingw_w64.instrset\\bin\\libgomp-1.dll");

  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&emlrtNestLockGlobal);

  /* Module initialization. */
  cylfft3_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    /* Dispatch the entry-point. */
    cylfft3_mexFunction(nlhs, plhs, nrhs, prhs);

    /* Module termination. */
    cylfft3_terminate();
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&emlrtNestLockGlobal);
  } else {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&emlrtNestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
  }
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal,
                     &emlrtLockerFunction, omp_get_num_procs());
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_cylfft3_mex.c) */
