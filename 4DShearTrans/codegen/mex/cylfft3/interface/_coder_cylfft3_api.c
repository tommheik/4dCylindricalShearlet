/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_cylfft3_api.c
 *
 * Code generation for function '_coder_cylfft3_api'
 *
 */

/* Include files */
#include "_coder_cylfft3_api.h"
#include "cylfft3.h"
#include "cylfft3_data.h"
#include "cylfft3_emxutil.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRTEInfo f_emlrtRTEI = { 1, /* lineNo */
  1,                                   /* colNo */
  "_coder_cylfft3_api",                /* fName */
  ""                                   /* pName */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real32_T *y);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real32_T *ret);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *f, const
  char_T *identifier, emxArray_real32_T *y);
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const
  emxArray_creal32_T *u);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real32_T *y)
{
  c_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real32_T *ret)
{
  static const int32_T dims[5] = { -1, -1, -1, -1, -1 };

  const boolean_T bv[5] = { true, true, true, true, true };

  int32_T iv[5];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "single", false, 5U, dims, &bv[0],
    iv);
  ret->allocatedSize = iv[0] * iv[1] * iv[2] * iv[3] * iv[4];
  i = ret->size[0] * ret->size[1] * ret->size[2] * ret->size[3] * ret->size[4];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  ret->size[2] = iv[2];
  ret->size[3] = iv[3];
  ret->size[4] = iv[4];
  emxEnsureCapacity_real32_T(sp, ret, i, (emlrtRTEInfo *)NULL);
  ret->data = (real32_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *f, const
  char_T *identifier, emxArray_real32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(f), &thisId, y);
  emlrtDestroyArray(&f);
}

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const
  emxArray_creal32_T *u)
{
  const mxArray *y;
  int32_T i;
  const mxArray *m;
  int32_T iv[5];
  y = NULL;
  for (i = 0; i < 5; i++) {
    iv[i] = u->size[i];
  }

  m = emlrtCreateNumericArray(5, &iv[0], mxSINGLE_CLASS, mxCOMPLEX);
  emlrtExportNumericArrayR2013b(sp, m, &u->data[0], 4);
  emlrtAssign(&y, m);
  return y;
}

void cylfft3_api(const mxArray * const prhs[1], int32_T nlhs, const mxArray
                 *plhs[1])
{
  emxArray_real32_T *f;
  emxArray_creal32_T *F;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real32_T(&st, &f, 5, &f_emlrtRTEI, true);
  emxInit_creal32_T(&st, &F, 5, &f_emlrtRTEI, true);

  /* Marshall function inputs */
  f->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "f", f);

  /* Invoke the target function */
  cylfft3(&st, f, F);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, F);
  emxFree_creal32_T(&F);
  emxFree_real32_T(&f);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_cylfft3_api.c) */
