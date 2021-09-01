/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_icylfft3_api.c
 *
 * Code generation for function '_coder_icylfft3_api'
 *
 */

/* Include files */
#include "_coder_icylfft3_api.h"
#include "icylfft3.h"
#include "icylfft3_data.h"
#include "icylfft3_emxutil.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRTEInfo f_emlrtRTEI = { 1, /* lineNo */
  1,                                   /* colNo */
  "_coder_icylfft3_api",               /* fName */
  ""                                   /* pName */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_creal32_T *y);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_creal32_T *ret);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *F, const
  char_T *identifier, emxArray_creal32_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_real32_T *u);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_creal32_T *y)
{
  c_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_creal32_T *ret)
{
  static const int32_T dims[5] = { -1, -1, -1, -1, -1 };

  const boolean_T bv[5] = { true, true, true, true, true };

  int32_T iv[5];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "single", true, 5U, dims, &bv[0], iv);
  i = ret->size[0] * ret->size[1] * ret->size[2] * ret->size[3] * ret->size[4];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  ret->size[2] = iv[2];
  ret->size[3] = iv[3];
  ret->size[4] = iv[4];
  emxEnsureCapacity_creal32_T(sp, ret, i, (emlrtRTEInfo *)NULL);
  emlrtImportArrayR2015b(sp, src, ret->data, 4, true);
  emlrtDestroyArray(&src);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *F, const
  char_T *identifier, emxArray_creal32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(F), &thisId, y);
  emlrtDestroyArray(&F);
}

static const mxArray *emlrt_marshallOut(const emxArray_real32_T *u)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[5] = { 0, 0, 0, 0, 0 };

  y = NULL;
  m = emlrtCreateNumericArray(5, &iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 5);
  emlrtAssign(&y, m);
  return y;
}

void icylfft3_api(const mxArray * const prhs[1], int32_T nlhs, const mxArray
                  *plhs[1])
{
  emxArray_creal32_T *F;
  emxArray_real32_T *f;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_creal32_T(&st, &F, 5, &f_emlrtRTEI, true);
  emxInit_real32_T(&st, &f, 5, &f_emlrtRTEI, true);

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "F", F);

  /* Invoke the target function */
  icylfft3(&st, F, f);

  /* Marshall function outputs */
  f->canFreeData = false;
  plhs[0] = emlrt_marshallOut(f);
  emxFree_real32_T(&f);
  emxFree_creal32_T(&F);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_icylfft3_api.c) */
