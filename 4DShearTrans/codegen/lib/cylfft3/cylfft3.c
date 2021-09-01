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
#include "FFTImplementationCallback.h"
#include "cylfft3_data.h"
#include "cylfft3_emxutil.h"
#include "cylfft3_initialize.h"
#include "permute.h"

/* Function Definitions */
void cylfft3(const emxArray_real32_T *f, emxArray_creal32_T *F)
{
  emxArray_creal32_T *y;
  emxArray_real32_T *costab;
  emxArray_real32_T *sintab;
  emxArray_real32_T *sintabinv;
  boolean_T useRadix2;
  int i;
  int N2blue;
  int nRows;
  unsigned int ySize[5];
  emxArray_creal32_T *xPerm;
  emxArray_creal32_T *yPerm;
  static const int iv[5] = { 3, 1, 2, 4, 5 };

  int k;
  int b_k;
  int c_k;
  int i1;
  static const int iv1[5] = { 2, 3, 1, 4, 5 };

  int d_k;
  int i2;
  int subsa_idx_1;
  int e_k;
  int subsa_idx_2;
  int subsa_idx_3;
  int subsa_idx_4;
  if (!isInitialized_cylfft3) {
    cylfft3_initialize();
  }

  /* CYLFFT3 is a cylindrical FFT performed only on the first 3 dimensions */
  /*    T H   2021 */
  emxInit_creal32_T(&y, 5);
  emxInit_real32_T(&costab, 2);
  emxInit_real32_T(&sintab, 2);
  emxInit_real32_T(&sintabinv, 2);
  if ((f->size[0] == 0) || (f->size[1] == 0) || (f->size[2] == 0) || (f->size[3]
       == 0) || (f->size[4] == 0)) {
    for (i = 0; i < 5; i++) {
      ySize[i] = (unsigned int)f->size[i];
    }

    i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
    y->size[0] = f->size[0];
    y->size[1] = (int)ySize[1];
    y->size[2] = (int)ySize[2];
    y->size[3] = (int)ySize[3];
    y->size[4] = (int)ySize[4];
    emxEnsureCapacity_creal32_T(y, i);
    N2blue = f->size[0] * (int)ySize[1] * (int)ySize[2] * (int)ySize[3] * (int)
      ySize[4];
    for (i = 0; i < N2blue; i++) {
      y->data[i].re = 0.0F;
      y->data[i].im = 0.0F;
    }
  } else {
    useRadix2 = ((f->size[0] & (f->size[0] - 1)) == 0);
    c_FFTImplementationCallback_get(f->size[0], useRadix2, &N2blue, &nRows);
    c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      c_FFTImplementationCallback_r2b(f, f->size[0], costab, sintab, y);
    } else {
      c_FFTImplementationCallback_dob(f, N2blue, f->size[0], costab, sintab,
        sintabinv, y);
    }
  }

  emxInit_creal32_T(&xPerm, 5);
  emxInit_creal32_T(&yPerm, 5);
  if ((y->size[0] == 0) || (y->size[1] == 0) || (y->size[2] == 0) || (y->size[3]
       == 0) || (y->size[4] == 0)) {
    for (i = 0; i < 5; i++) {
      ySize[i] = (unsigned int)y->size[i];
    }

    ySize[1] = (unsigned int)y->size[1];
    i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
    y->size[0] = (int)ySize[0];
    y->size[1] = (int)ySize[1];
    y->size[2] = (int)ySize[2];
    y->size[3] = (int)ySize[3];
    y->size[4] = (int)ySize[4];
    emxEnsureCapacity_creal32_T(y, i);
    N2blue = (int)ySize[0] * (int)ySize[1] * (int)ySize[2] * (int)ySize[3] *
      (int)ySize[4];
    for (i = 0; i < N2blue; i++) {
      y->data[i].re = 0.0F;
      y->data[i].im = 0.0F;
    }
  } else {
    permute(y, xPerm);
    useRadix2 = ((y->size[1] & (y->size[1] - 1)) == 0);
    c_FFTImplementationCallback_get(y->size[1], useRadix2, &N2blue, &nRows);
    c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      e_FFTImplementationCallback_r2b(xPerm, y->size[1], costab, sintab, yPerm);
    } else {
      d_FFTImplementationCallback_dob(xPerm, N2blue, y->size[1], costab, sintab,
        sintabinv, yPerm);
    }

    permute(yPerm, y);
  }

  if ((y->size[0] == 0) || (y->size[1] == 0) || (y->size[2] == 0) || (y->size[3]
       == 0) || (y->size[4] == 0)) {
    for (i = 0; i < 5; i++) {
      ySize[i] = (unsigned int)y->size[i];
    }

    i = F->size[0] * F->size[1] * F->size[2] * F->size[3] * F->size[4];
    F->size[0] = (int)ySize[0];
    F->size[1] = (int)ySize[1];
    F->size[2] = y->size[2];
    F->size[3] = (int)ySize[3];
    F->size[4] = (int)ySize[4];
    emxEnsureCapacity_creal32_T(F, i);
    N2blue = (int)ySize[0] * (int)ySize[1] * y->size[2] * (int)ySize[3] * (int)
      ySize[4];
    for (i = 0; i < N2blue; i++) {
      F->data[i].re = 0.0F;
      F->data[i].im = 0.0F;
    }
  } else {
    if (nomovement(iv, y)) {
      i = xPerm->size[0] * xPerm->size[1] * xPerm->size[2] * xPerm->size[3] *
        xPerm->size[4];
      xPerm->size[0] = y->size[2];
      xPerm->size[1] = y->size[0];
      xPerm->size[2] = y->size[1];
      xPerm->size[3] = y->size[3];
      xPerm->size[4] = y->size[4];
      emxEnsureCapacity_creal32_T(xPerm, i);
      N2blue = y->size[2] * y->size[0] * y->size[1] * y->size[3] * y->size[4];
      for (i = 0; i < N2blue; i++) {
        xPerm->data[i] = y->data[i];
      }
    } else {
      i = xPerm->size[0] * xPerm->size[1] * xPerm->size[2] * xPerm->size[3] *
        xPerm->size[4];
      xPerm->size[0] = y->size[2];
      xPerm->size[1] = y->size[0];
      xPerm->size[2] = y->size[1];
      xPerm->size[3] = y->size[3];
      xPerm->size[4] = y->size[4];
      emxEnsureCapacity_creal32_T(xPerm, i);
      i = y->size[4];
      for (k = 0; k < i; k++) {
        N2blue = y->size[3];
        for (b_k = 0; b_k < N2blue; b_k++) {
          nRows = y->size[2];
          for (c_k = 0; c_k < nRows; c_k++) {
            i1 = y->size[1];
            for (d_k = 0; d_k < i1; d_k++) {
              i2 = y->size[0];
              if (0 <= y->size[0] - 1) {
                subsa_idx_1 = d_k + 1;
                subsa_idx_2 = c_k + 1;
                subsa_idx_3 = b_k + 1;
                subsa_idx_4 = k + 1;
              }

              for (e_k = 0; e_k < i2; e_k++) {
                xPerm->data[((((subsa_idx_2 + xPerm->size[0] * e_k) +
                               xPerm->size[0] * xPerm->size[1] * (subsa_idx_1 -
                  1)) + xPerm->size[0] * xPerm->size[1] * xPerm->size[2] *
                              (subsa_idx_3 - 1)) + xPerm->size[0] * xPerm->size
                             [1] * xPerm->size[2] * xPerm->size[3] *
                             (subsa_idx_4 - 1)) - 1] = y->data[(((e_k + y->size
                  [0] * (subsa_idx_1 - 1)) + y->size[0] * y->size[1] *
                  (subsa_idx_2 - 1)) + y->size[0] * y->size[1] * y->size[2] *
                  (subsa_idx_3 - 1)) + y->size[0] * y->size[1] * y->size[2] *
                  y->size[3] * (subsa_idx_4 - 1)];
              }
            }
          }
        }
      }
    }

    useRadix2 = ((y->size[2] & (y->size[2] - 1)) == 0);
    c_FFTImplementationCallback_get(y->size[2], useRadix2, &N2blue, &nRows);
    c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      e_FFTImplementationCallback_r2b(xPerm, y->size[2], costab, sintab, yPerm);
    } else {
      d_FFTImplementationCallback_dob(xPerm, N2blue, y->size[2], costab, sintab,
        sintabinv, yPerm);
    }

    if (nomovement(iv1, yPerm)) {
      i = F->size[0] * F->size[1] * F->size[2] * F->size[3] * F->size[4];
      F->size[0] = yPerm->size[1];
      F->size[1] = yPerm->size[2];
      F->size[2] = yPerm->size[0];
      F->size[3] = yPerm->size[3];
      F->size[4] = yPerm->size[4];
      emxEnsureCapacity_creal32_T(F, i);
      N2blue = yPerm->size[1] * yPerm->size[2] * yPerm->size[0] * yPerm->size[3]
        * yPerm->size[4];
      for (i = 0; i < N2blue; i++) {
        F->data[i] = yPerm->data[i];
      }
    } else {
      i = F->size[0] * F->size[1] * F->size[2] * F->size[3] * F->size[4];
      F->size[0] = yPerm->size[1];
      F->size[1] = yPerm->size[2];
      F->size[2] = yPerm->size[0];
      F->size[3] = yPerm->size[3];
      F->size[4] = yPerm->size[4];
      emxEnsureCapacity_creal32_T(F, i);
      i = yPerm->size[4];
      for (k = 0; k < i; k++) {
        N2blue = yPerm->size[3];
        for (b_k = 0; b_k < N2blue; b_k++) {
          nRows = yPerm->size[2];
          for (c_k = 0; c_k < nRows; c_k++) {
            i1 = yPerm->size[1];
            for (d_k = 0; d_k < i1; d_k++) {
              i2 = yPerm->size[0];
              if (0 <= yPerm->size[0] - 1) {
                subsa_idx_1 = d_k + 1;
                subsa_idx_2 = c_k + 1;
                subsa_idx_3 = b_k + 1;
                subsa_idx_4 = k + 1;
              }

              for (e_k = 0; e_k < i2; e_k++) {
                F->data[((((subsa_idx_1 + F->size[0] * (subsa_idx_2 - 1)) +
                           F->size[0] * F->size[1] * e_k) + F->size[0] * F->
                          size[1] * F->size[2] * (subsa_idx_3 - 1)) + F->size[0]
                         * F->size[1] * F->size[2] * F->size[3] * (subsa_idx_4 -
                          1)) - 1] = yPerm->data[(((e_k + yPerm->size[0] *
                  (subsa_idx_1 - 1)) + yPerm->size[0] * yPerm->size[1] *
                  (subsa_idx_2 - 1)) + yPerm->size[0] * yPerm->size[1] *
                  yPerm->size[2] * (subsa_idx_3 - 1)) + yPerm->size[0] *
                  yPerm->size[1] * yPerm->size[2] * yPerm->size[3] *
                  (subsa_idx_4 - 1)];
              }
            }
          }
        }
      }
    }
  }

  emxFree_creal32_T(&yPerm);
  emxFree_creal32_T(&xPerm);
  emxFree_real32_T(&sintabinv);
  emxFree_real32_T(&sintab);
  emxFree_real32_T(&costab);
  emxFree_creal32_T(&y);
}

/* End of code generation (cylfft3.c) */
