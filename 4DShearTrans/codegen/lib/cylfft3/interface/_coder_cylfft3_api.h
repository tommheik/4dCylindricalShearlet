/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_cylfft3_api.h
 *
 * Code generation for function '_coder_cylfft3_api'
 *
 */

#ifndef _CODER_CYLFFT3_API_H
#define _CODER_CYLFFT3_API_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef typedef_emxArray_creal32_T
#define typedef_emxArray_creal32_T

typedef struct {
  creal32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
} emxArray_creal32_T;

#endif                                 /*typedef_emxArray_creal32_T*/

#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T

struct emxArray_real32_T
{
  real32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real32_T*/

#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T

typedef struct emxArray_real32_T emxArray_real32_T;

#endif                                 /*typedef_emxArray_real32_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void cylfft3(emxArray_real32_T *f, emxArray_creal32_T *F);
extern void cylfft3_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1]);
extern void cylfft3_atexit(void);
extern void cylfft3_initialize(void);
extern void cylfft3_terminate(void);
extern void cylfft3_xil_shutdown(void);
extern void cylfft3_xil_terminate(void);

#endif

/* End of code generation (_coder_cylfft3_api.h) */
