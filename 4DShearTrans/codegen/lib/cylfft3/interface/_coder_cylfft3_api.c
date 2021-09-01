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
#include "_coder_cylfft3_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "cylfft3",                           /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
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
static void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int32_T
  oldNumel);
static void emxFree_creal32_T(emxArray_creal32_T **pEmxArray);
static void emxFree_real32_T(emxArray_real32_T **pEmxArray);
static void emxInit_creal32_T(const emlrtStack *sp, emxArray_creal32_T
  **pEmxArray, int32_T numDimensions, boolean_T doPush);
static void emxInit_real32_T(const emlrtStack *sp, emxArray_real32_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);

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
  emxEnsureCapacity_real32_T(ret, i);
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

static void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int32_T
  oldNumel)
{
  int32_T newNumel;
  int32_T i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = emlrtCallocMex((uint32_T)i, sizeof(real32_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(real32_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }

    emxArray->data = (real32_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxFree_creal32_T(emxArray_creal32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_creal32_T *)NULL) {
    if (((*pEmxArray)->data != (creal32_T *)NULL) && (*pEmxArray)->canFreeData)
    {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_creal32_T *)NULL;
  }
}

static void emxFree_real32_T(emxArray_real32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real32_T *)NULL) {
    if (((*pEmxArray)->data != (real32_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_real32_T *)NULL;
  }
}

static void emxInit_creal32_T(const emlrtStack *sp, emxArray_creal32_T
  **pEmxArray, int32_T numDimensions, boolean_T doPush)
{
  emxArray_creal32_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_creal32_T *)emlrtMallocMex(sizeof(emxArray_creal32_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void *)
      &emxFree_creal32_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (creal32_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_real32_T(const emlrtStack *sp, emxArray_real32_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real32_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real32_T *)emlrtMallocMex(sizeof(emxArray_real32_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void *)
      &emxFree_real32_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real32_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
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
  emxInit_real32_T(&st, &f, 5, true);
  emxInit_creal32_T(&st, &F, 5, true);

  /* Marshall function inputs */
  f->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "f", f);

  /* Invoke the target function */
  cylfft3(f, F);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, F);
  emxFree_creal32_T(&F);
  emxFree_real32_T(&f);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void cylfft3_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  cylfft3_xil_terminate();
  cylfft3_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void cylfft3_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void cylfft3_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_cylfft3_api.c) */
