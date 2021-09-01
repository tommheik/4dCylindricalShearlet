/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cylfft3.c
 *
 * Code generation for function 'cylfft3'
 *
 */

/* Include files */
#include "cylfft3.h"
#include "cylfft3_emxutil.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 4,     /* lineNo */
  "cylfft3",                           /* fcnName */
  "G:\\4dCylindricalShearlet\\4DShearTrans\\cylfft3.m"/* pathName */
};

static emlrtRSInfo b_emlrtRSI = { 62,  /* lineNo */
  "fft",                               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\eml\\lib\\matlab\\datafun\\fft.m"/* pathName */
};

static emlrtRSInfo c_emlrtRSI = { 23,  /* lineNo */
  "fft",                               /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\eml\\eml\\+coder\\+internal\\+fft\\fft.m"/* pathName */
};

static emlrtRSInfo d_emlrtRSI = { 52,  /* lineNo */
  "executeCallback",                   /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\eml\\eml\\+coder\\+internal\\+fft\\fft.m"/* pathName */
};

static emlrtRSInfo e_emlrtRSI = { 44,  /* lineNo */
  "Custom1DFFTCallback/fft",           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+internal\\Custom1DFFTCallback.m"/* pathName */
};

static emlrtRSInfo f_emlrtRSI = { 54,  /* lineNo */
  "Custom1DFFTCallback/fftLoop",       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+internal\\Custom1DFFTCallback.m"/* pathName */
};

static emlrtRTEInfo emlrtRTEI = { 62,  /* lineNo */
  1,                                   /* colNo */
  "fft",                               /* fName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\eml\\lib\\matlab\\datafun\\fft.m"/* pName */
};

static emlrtRTEInfo b_emlrtRTEI = { 54,/* lineNo */
  13,                                  /* colNo */
  "Custom1DFFTCallback",               /* fName */
  "C:\\Program Files\\MATLAB\\R2020a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+internal\\Custom1DFFTCallback.m"/* pName */
};

static emlrtRTEInfo c_emlrtRTEI = { 4, /* lineNo */
  1,                                   /* colNo */
  "cylfft3",                           /* fName */
  "G:\\4dCylindricalShearlet\\4DShearTrans\\cylfft3.m"/* pName */
};

static emlrtRTEInfo d_emlrtRTEI = { 4, /* lineNo */
  13,                                  /* colNo */
  "cylfft3",                           /* fName */
  "G:\\4dCylindricalShearlet\\4DShearTrans\\cylfft3.m"/* pName */
};

static emlrtRTEInfo e_emlrtRTEI = { 4, /* lineNo */
  9,                                   /* colNo */
  "cylfft3",                           /* fName */
  "G:\\4dCylindricalShearlet\\4DShearTrans\\cylfft3.m"/* pName */
};

/* Function Definitions */
void cylfft3(const emlrtStack *sp, const emxArray_real32_T *f,
             emxArray_creal32_T *F)
{
  emxArray_creal32_T *y;
  int32_T i;
  uint32_T xSize[5];
  int32_T loop_ub;
  emxArray_creal32_T *b_y;
  real_T d;
  int64_T i1;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  emxInit_creal32_T(sp, &y, 5, &d_emlrtRTEI, true);

  /* CYLFFT3 is a cylindrical FFT performed only on the first 3 dimensions */
  /*    T H   2021 */
  st.site = &emlrtRSI;
  b_st.site = &b_emlrtRSI;
  if ((f->size[0] == 0) || (f->size[1] == 0) || (f->size[2] == 0) || (f->size[3]
       == 0) || (f->size[4] == 0)) {
    for (i = 0; i < 5; i++) {
      xSize[i] = (uint32_T)f->size[i];
    }

    i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
    y->size[0] = f->size[0];
    y->size[1] = (int32_T)xSize[1];
    y->size[2] = (int32_T)xSize[2];
    y->size[3] = (int32_T)xSize[3];
    y->size[4] = (int32_T)xSize[4];
    emxEnsureCapacity_creal32_T(&b_st, y, i, &emlrtRTEI);
    loop_ub = f->size[0] * (int32_T)xSize[1] * (int32_T)xSize[2] * (int32_T)
      xSize[3] * (int32_T)xSize[4];
    for (i = 0; i < loop_ub; i++) {
      y->data[i].re = 0.0F;
      y->data[i].im = 0.0F;
    }
  } else {
    c_st.site = &c_emlrtRSI;
    d_st.site = &d_emlrtRSI;
    e_st.site = &e_emlrtRSI;
    f_st.site = &f_emlrtRSI;
    emlrtFFTWSetNumThreads(6);
    for (i = 0; i < 5; i++) {
      xSize[i] = (uint32_T)f->size[i];
    }

    i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
    y->size[0] = f->size[0];
    y->size[1] = (int32_T)xSize[1];
    y->size[2] = (int32_T)xSize[2];
    y->size[3] = (int32_T)xSize[3];
    y->size[4] = (int32_T)xSize[4];
    emxEnsureCapacity_creal32_T(&f_st, y, i, &b_emlrtRTEI);
    d = (real_T)xSize[1] * (real_T)xSize[2] * (real_T)xSize[3] * (real_T)xSize[4];
    if (d < 2.147483648E+9) {
      i = (int32_T)d;
    } else {
      i = MAX_int32_T;
    }

    emlrtFFTWF_1D_R2C(&f->data[0], (real32_T *)&y->data[0], 1, f->size[0],
                      f->size[0], i, -1);
  }

  emxInit_creal32_T(&b_st, &b_y, 5, &e_emlrtRTEI, true);
  st.site = &emlrtRSI;
  b_st.site = &b_emlrtRSI;
  if ((y->size[0] == 0) || (y->size[1] == 0) || (y->size[2] == 0) || (y->size[3]
       == 0) || (y->size[4] == 0)) {
    for (i = 0; i < 5; i++) {
      xSize[i] = (uint32_T)y->size[i];
    }

    i = b_y->size[0] * b_y->size[1] * b_y->size[2] * b_y->size[3] * b_y->size[4];
    b_y->size[0] = (int32_T)xSize[0];
    b_y->size[1] = y->size[1];
    b_y->size[2] = (int32_T)xSize[2];
    b_y->size[3] = (int32_T)xSize[3];
    b_y->size[4] = (int32_T)xSize[4];
    emxEnsureCapacity_creal32_T(&b_st, b_y, i, &emlrtRTEI);
    loop_ub = (int32_T)xSize[0] * y->size[1] * (int32_T)xSize[2] * (int32_T)
      xSize[3] * (int32_T)xSize[4];
    for (i = 0; i < loop_ub; i++) {
      b_y->data[i].re = 0.0F;
      b_y->data[i].im = 0.0F;
    }
  } else {
    c_st.site = &c_emlrtRSI;
    d_st.site = &d_emlrtRSI;
    e_st.site = &e_emlrtRSI;
    f_st.site = &f_emlrtRSI;
    emlrtFFTWSetNumThreads(6);
    for (i = 0; i < 5; i++) {
      xSize[i] = (uint32_T)y->size[i];
    }

    i = b_y->size[0] * b_y->size[1] * b_y->size[2] * b_y->size[3] * b_y->size[4];
    b_y->size[0] = (int32_T)xSize[0];
    b_y->size[1] = y->size[1];
    b_y->size[2] = (int32_T)xSize[2];
    b_y->size[3] = (int32_T)xSize[3];
    b_y->size[4] = (int32_T)xSize[4];
    emxEnsureCapacity_creal32_T(&f_st, b_y, i, &b_emlrtRTEI);
    d = (real_T)xSize[2] * (real_T)xSize[3] * (real_T)xSize[4];
    if (d < 2.147483648E+9) {
      i = (int32_T)d;
    } else {
      i = MAX_int32_T;
    }

    i1 = (int64_T)i * (int32_T)xSize[0];
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    emlrtFFTWF_1D_C2C((real32_T *)&y->data[0], (real32_T *)&b_y->data[0],
                      (int32_T)xSize[0], y->size[1], y->size[1], (int32_T)i1, -1);
  }

  emxFree_creal32_T(&y);
  st.site = &emlrtRSI;
  b_st.site = &b_emlrtRSI;
  if ((b_y->size[0] == 0) || (b_y->size[1] == 0) || (b_y->size[2] == 0) ||
      (b_y->size[3] == 0) || (b_y->size[4] == 0)) {
    for (i = 0; i < 5; i++) {
      xSize[i] = (uint32_T)b_y->size[i];
    }

    i = F->size[0] * F->size[1] * F->size[2] * F->size[3] * F->size[4];
    F->size[0] = (int32_T)xSize[0];
    F->size[1] = (int32_T)xSize[1];
    F->size[2] = b_y->size[2];
    F->size[3] = (int32_T)xSize[3];
    F->size[4] = (int32_T)xSize[4];
    emxEnsureCapacity_creal32_T(&b_st, F, i, &c_emlrtRTEI);
    loop_ub = (int32_T)xSize[0] * (int32_T)xSize[1] * b_y->size[2] * (int32_T)
      xSize[3] * (int32_T)xSize[4];
    for (i = 0; i < loop_ub; i++) {
      F->data[i].re = 0.0F;
      F->data[i].im = 0.0F;
    }
  } else {
    c_st.site = &c_emlrtRSI;
    d_st.site = &d_emlrtRSI;
    e_st.site = &e_emlrtRSI;
    f_st.site = &f_emlrtRSI;
    emlrtFFTWSetNumThreads(6);
    for (i = 0; i < 5; i++) {
      xSize[i] = (uint32_T)b_y->size[i];
    }

    i = F->size[0] * F->size[1] * F->size[2] * F->size[3] * F->size[4];
    F->size[0] = (int32_T)xSize[0];
    F->size[1] = (int32_T)xSize[1];
    F->size[2] = b_y->size[2];
    F->size[3] = (int32_T)xSize[3];
    F->size[4] = (int32_T)xSize[4];
    emxEnsureCapacity_creal32_T(&f_st, F, i, &b_emlrtRTEI);
    d = (real_T)xSize[0] * (real_T)xSize[1];
    if (d < 2.147483648E+9) {
      i = (int32_T)d;
    } else {
      i = MAX_int32_T;
    }

    d = (real_T)xSize[3] * (real_T)xSize[4];
    if (d < 2.147483648E+9) {
      loop_ub = (int32_T)d;
    } else {
      loop_ub = MAX_int32_T;
    }

    i1 = (int64_T)loop_ub * i;
    if (i1 > 2147483647LL) {
      i1 = 2147483647LL;
    } else {
      if (i1 < -2147483648LL) {
        i1 = -2147483648LL;
      }
    }

    emlrtFFTWF_1D_C2C((real32_T *)&b_y->data[0], (real32_T *)&F->data[0], i,
                      b_y->size[2], b_y->size[2], (int32_T)i1, -1);
  }

  emxFree_creal32_T(&b_y);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (cylfft3.c) */
