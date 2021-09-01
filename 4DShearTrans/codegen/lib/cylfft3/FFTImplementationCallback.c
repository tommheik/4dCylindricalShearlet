/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFTImplementationCallback.c
 *
 * Code generation for function 'FFTImplementationCallback'
 *
 */

/* Include files */
#include "FFTImplementationCallback.h"
#include "cylfft3.h"
#include "cylfft3_emxutil.h"
#include <math.h>

/* Function Declarations */
static void c_FFTImplementationCallback_doH(const emxArray_real32_T *x, int
  xoffInit, emxArray_creal32_T *y, int unsigned_nRows, const emxArray_real32_T
  *costab, const emxArray_real32_T *sintab);
static void d_FFTImplementationCallback_doH(const emxArray_real32_T *x, int
  xoffInit, emxArray_creal32_T *y, int nrowsx, int nRows, int nfft, const
  emxArray_creal32_T *wwc, const emxArray_real32_T *costab, const
  emxArray_real32_T *sintab, const emxArray_real32_T *costabinv, const
  emxArray_real32_T *sintabinv);
static void d_FFTImplementationCallback_r2b(const emxArray_creal32_T *x, int
  unsigned_nRows, const emxArray_real32_T *costab, const emxArray_real32_T
  *sintab, emxArray_creal32_T *y);

/* Function Definitions */
static void c_FFTImplementationCallback_doH(const emxArray_real32_T *x, int
  xoffInit, emxArray_creal32_T *y, int unsigned_nRows, const emxArray_real32_T
  *costab, const emxArray_real32_T *sintab)
{
  emxArray_real32_T *hcostab;
  emxArray_real32_T *hsintab;
  int nRows;
  int j;
  int ihi;
  int nRowsD2;
  int k;
  int hszCostab;
  int b_j1;
  int i;
  emxArray_int32_T *wrapIndex;
  int ix;
  emxArray_creal32_T *reconVar1;
  emxArray_creal32_T *reconVar2;
  emxArray_int32_T *bitrevIndex;
  float temp_re;
  int ju;
  float temp_im;
  int loop_ub;
  boolean_T tst;
  float y_im;
  float y_re;
  float b_y_im;
  float temp2_re;
  float temp2_im;
  emxInit_real32_T(&hcostab, 2);
  emxInit_real32_T(&hsintab, 2);
  nRows = unsigned_nRows / 2;
  j = y->size[0];
  if (j >= nRows) {
    j = nRows;
  }

  ihi = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  hszCostab = costab->size[1] / 2;
  b_j1 = hcostab->size[0] * hcostab->size[1];
  hcostab->size[0] = 1;
  hcostab->size[1] = hszCostab;
  emxEnsureCapacity_real32_T(hcostab, b_j1);
  b_j1 = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real32_T(hsintab, b_j1);
  for (i = 0; i < hszCostab; i++) {
    ix = ((i + 1) << 1) - 2;
    hcostab->data[i] = costab->data[ix];
    hsintab->data[i] = sintab->data[ix];
  }

  emxInit_int32_T(&wrapIndex, 2);
  emxInit_creal32_T(&reconVar1, 1);
  emxInit_creal32_T(&reconVar2, 1);
  b_j1 = reconVar1->size[0];
  reconVar1->size[0] = nRows;
  emxEnsureCapacity_creal32_T(reconVar1, b_j1);
  b_j1 = reconVar2->size[0];
  reconVar2->size[0] = nRows;
  emxEnsureCapacity_creal32_T(reconVar2, b_j1);
  b_j1 = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = nRows;
  emxEnsureCapacity_int32_T(wrapIndex, b_j1);
  for (i = 0; i < nRows; i++) {
    temp_re = sintab->data[i];
    temp_im = costab->data[i];
    reconVar1->data[i].re = temp_re + 1.0F;
    reconVar1->data[i].im = -temp_im;
    reconVar2->data[i].re = 1.0F - temp_re;
    reconVar2->data[i].im = temp_im;
    if (i + 1 != 1) {
      wrapIndex->data[i] = (nRows - i) + 1;
    } else {
      wrapIndex->data[0] = 1;
    }
  }

  emxInit_int32_T(&bitrevIndex, 1);
  ju = 0;
  hszCostab = 1;
  loop_ub = (int)((double)unsigned_nRows / 2.0);
  b_j1 = bitrevIndex->size[0];
  bitrevIndex->size[0] = loop_ub;
  emxEnsureCapacity_int32_T(bitrevIndex, b_j1);
  for (b_j1 = 0; b_j1 < loop_ub; b_j1++) {
    bitrevIndex->data[b_j1] = 0;
  }

  for (b_j1 = 0; b_j1 <= j - 2; b_j1++) {
    bitrevIndex->data[b_j1] = hszCostab;
    ix = loop_ub;
    tst = true;
    while (tst) {
      ix >>= 1;
      ju ^= ix;
      tst = ((ju & ix) == 0);
    }

    hszCostab = ju + 1;
  }

  bitrevIndex->data[j - 1] = hszCostab;
  if ((x->size[0] & 1) == 0) {
    tst = true;
    j = x->size[0];
  } else if (x->size[0] >= unsigned_nRows) {
    tst = true;
    j = unsigned_nRows;
  } else {
    tst = false;
    j = x->size[0] - 1;
  }

  ix = xoffInit;
  if (j >= unsigned_nRows) {
    j = unsigned_nRows;
  }

  b_j1 = (int)((double)j / 2.0);
  for (i = 0; i < b_j1; i++) {
    y->data[bitrevIndex->data[i] - 1].re = x->data[ix];
    y->data[bitrevIndex->data[i] - 1].im = x->data[ix + 1];
    ix += 2;
  }

  if (!tst) {
    b_j1 = bitrevIndex->data[b_j1] - 1;
    y->data[b_j1].re = x->data[ix];
    y->data[b_j1].im = 0.0F;
  }

  emxFree_int32_T(&bitrevIndex);
  if (nRows > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  hszCostab = 2;
  ix = 4;
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += ix) {
      b_j1 = i + hszCostab;
      temp_re = y->data[b_j1].re;
      temp_im = y->data[b_j1].im;
      y->data[b_j1].re = y->data[i].re - temp_re;
      y->data[b_j1].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    nRows = 1;
    for (j = k; j < nRowsD2; j += k) {
      temp2_re = hcostab->data[j];
      temp2_im = hsintab->data[j];
      i = nRows;
      ihi = nRows + ju;
      while (i < ihi) {
        b_j1 = i + hszCostab;
        temp_re = temp2_re * y->data[b_j1].re - temp2_im * y->data[b_j1].im;
        temp_im = temp2_re * y->data[b_j1].im + temp2_im * y->data[b_j1].re;
        y->data[b_j1].re = y->data[i].re - temp_re;
        y->data[b_j1].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += ix;
      }

      nRows++;
    }

    k /= 2;
    hszCostab = ix;
    ix += ix;
    ju -= hszCostab;
  }

  emxFree_real32_T(&hsintab);
  emxFree_real32_T(&hcostab);
  ix = loop_ub / 2;
  temp_re = y->data[0].re;
  temp_im = y->data[0].im;
  y_im = y->data[0].re * reconVar1->data[0].im + y->data[0].im * reconVar1->
    data[0].re;
  y_re = y->data[0].re;
  b_y_im = -y->data[0].im;
  y->data[0].re = 0.5F * ((y->data[0].re * reconVar1->data[0].re - y->data[0].im
    * reconVar1->data[0].im) + (y_re * reconVar2->data[0].re - b_y_im *
    reconVar2->data[0].im));
  y->data[0].im = 0.5F * (y_im + (y_re * reconVar2->data[0].im + b_y_im *
    reconVar2->data[0].re));
  y->data[loop_ub].re = 0.5F * ((temp_re * reconVar2->data[0].re - temp_im *
    reconVar2->data[0].im) + (temp_re * reconVar1->data[0].re - -temp_im *
    reconVar1->data[0].im));
  y->data[loop_ub].im = 0.5F * ((temp_re * reconVar2->data[0].im + temp_im *
    reconVar2->data[0].re) + (temp_re * reconVar1->data[0].im + -temp_im *
    reconVar1->data[0].re));
  for (i = 2; i <= ix; i++) {
    temp_re = y->data[i - 1].re;
    temp_im = y->data[i - 1].im;
    b_j1 = wrapIndex->data[i - 1];
    temp2_re = y->data[b_j1 - 1].re;
    temp2_im = y->data[b_j1 - 1].im;
    y_im = y->data[i - 1].re * reconVar1->data[i - 1].im + y->data[i - 1].im *
      reconVar1->data[i - 1].re;
    y_re = y->data[b_j1 - 1].re;
    b_y_im = -y->data[b_j1 - 1].im;
    y->data[i - 1].re = 0.5F * ((y->data[i - 1].re * reconVar1->data[i - 1].re -
      y->data[i - 1].im * reconVar1->data[i - 1].im) + (y_re * reconVar2->data[i
      - 1].re - b_y_im * reconVar2->data[i - 1].im));
    y->data[i - 1].im = 0.5F * (y_im + (y_re * reconVar2->data[i - 1].im +
      b_y_im * reconVar2->data[i - 1].re));
    hszCostab = (loop_ub + i) - 1;
    y->data[hszCostab].re = 0.5F * ((temp_re * reconVar2->data[i - 1].re -
      temp_im * reconVar2->data[i - 1].im) + (temp2_re * reconVar1->data[i - 1].
      re - -temp2_im * reconVar1->data[i - 1].im));
    y->data[hszCostab].im = 0.5F * ((temp_re * reconVar2->data[i - 1].im +
      temp_im * reconVar2->data[i - 1].re) + (temp2_re * reconVar1->data[i - 1].
      im + -temp2_im * reconVar1->data[i - 1].re));
    y->data[b_j1 - 1].re = 0.5F * ((temp2_re * reconVar1->data[b_j1 - 1].re -
      temp2_im * reconVar1->data[b_j1 - 1].im) + (temp_re * reconVar2->data[b_j1
      - 1].re - -temp_im * reconVar2->data[b_j1 - 1].im));
    y->data[b_j1 - 1].im = 0.5F * ((temp2_re * reconVar1->data[b_j1 - 1].im +
      temp2_im * reconVar1->data[b_j1 - 1].re) + (temp_re * reconVar2->data[b_j1
      - 1].im + -temp_im * reconVar2->data[b_j1 - 1].re));
    hszCostab = (b_j1 + loop_ub) - 1;
    y->data[hszCostab].re = 0.5F * ((temp2_re * reconVar2->data[b_j1 - 1].re -
      temp2_im * reconVar2->data[b_j1 - 1].im) + (temp_re * reconVar1->data[b_j1
      - 1].re - -temp_im * reconVar1->data[b_j1 - 1].im));
    y->data[hszCostab].im = 0.5F * ((temp2_re * reconVar2->data[b_j1 - 1].im +
      temp2_im * reconVar2->data[b_j1 - 1].re) + (temp_re * reconVar1->data[b_j1
      - 1].im + -temp_im * reconVar1->data[b_j1 - 1].re));
  }

  emxFree_int32_T(&wrapIndex);
  if (ix != 0) {
    temp_re = y->data[ix].re;
    temp_im = y->data[ix].im;
    y_im = y->data[ix].re * reconVar1->data[ix].im + y->data[ix].im *
      reconVar1->data[ix].re;
    y_re = y->data[ix].re;
    b_y_im = -y->data[ix].im;
    y->data[ix].re = 0.5F * ((y->data[ix].re * reconVar1->data[ix].re - y->
      data[ix].im * reconVar1->data[ix].im) + (y_re * reconVar2->data[ix].re -
      b_y_im * reconVar2->data[ix].im));
    y->data[ix].im = 0.5F * (y_im + (y_re * reconVar2->data[ix].im + b_y_im *
      reconVar2->data[ix].re));
    b_j1 = loop_ub + ix;
    y->data[b_j1].re = 0.5F * ((temp_re * reconVar2->data[ix].re - temp_im *
      reconVar2->data[ix].im) + (temp_re * reconVar1->data[ix].re - -temp_im *
      reconVar1->data[ix].im));
    y->data[b_j1].im = 0.5F * ((temp_re * reconVar2->data[ix].im + temp_im *
      reconVar2->data[ix].re) + (temp_re * reconVar1->data[ix].im + -temp_im *
      reconVar1->data[ix].re));
  }

  emxFree_creal32_T(&reconVar2);
  emxFree_creal32_T(&reconVar1);
}

static void d_FFTImplementationCallback_doH(const emxArray_real32_T *x, int
  xoffInit, emxArray_creal32_T *y, int nrowsx, int nRows, int nfft, const
  emxArray_creal32_T *wwc, const emxArray_real32_T *costab, const
  emxArray_real32_T *sintab, const emxArray_real32_T *costabinv, const
  emxArray_real32_T *sintabinv)
{
  emxArray_creal32_T *ytmp;
  int hnRows;
  int ix;
  boolean_T tst;
  int ihi;
  emxArray_real32_T *costab1q;
  int nd2;
  float twid_re;
  int j;
  int k;
  emxArray_real32_T *b_costab;
  emxArray_real32_T *b_sintab;
  emxArray_real32_T *hsintab;
  emxArray_real32_T *hcostabinv;
  emxArray_real32_T *hsintabinv;
  int hszCostab;
  int i;
  emxArray_int32_T *wrapIndex;
  emxArray_creal32_T *reconVar1;
  emxArray_creal32_T *reconVar2;
  int temp_re_tmp;
  float twid_im;
  emxArray_creal32_T *fy;
  int loop_ub_tmp;
  int nRowsD2;
  int ju;
  float temp_re;
  float temp_im;
  emxArray_creal32_T *fv;
  emxInit_creal32_T(&ytmp, 1);
  hnRows = nRows / 2;
  ix = ytmp->size[0];
  ytmp->size[0] = hnRows;
  emxEnsureCapacity_creal32_T(ytmp, ix);
  if (hnRows > nrowsx) {
    ix = ytmp->size[0];
    ytmp->size[0] = hnRows;
    emxEnsureCapacity_creal32_T(ytmp, ix);
    for (ix = 0; ix < hnRows; ix++) {
      ytmp->data[ix].re = 0.0F;
      ytmp->data[ix].im = 0.0F;
    }
  }

  if ((x->size[0] & 1) == 0) {
    tst = true;
    ihi = x->size[0];
  } else if (x->size[0] >= nRows) {
    tst = true;
    ihi = nRows;
  } else {
    tst = false;
    ihi = x->size[0] - 1;
  }

  emxInit_real32_T(&costab1q, 2);
  if (ihi >= nRows) {
    ihi = nRows;
  }

  nd2 = nRows << 1;
  twid_re = 6.28318548F / (float)nd2;
  j = nd2 / 2 / 2;
  ix = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = j + 1;
  emxEnsureCapacity_real32_T(costab1q, ix);
  costab1q->data[0] = 1.0F;
  nd2 = j / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q->data[k + 1] = cosf(twid_re * (float)(k + 1));
  }

  ix = nd2 + 2;
  nd2 = j - 1;
  for (k = ix; k <= nd2; k++) {
    costab1q->data[k] = sinf(twid_re * (float)(j - k));
  }

  emxInit_real32_T(&b_costab, 2);
  emxInit_real32_T(&b_sintab, 2);
  costab1q->data[j] = 0.0F;
  j = costab1q->size[1] - 1;
  nd2 = (costab1q->size[1] - 1) << 1;
  ix = b_costab->size[0] * b_costab->size[1];
  b_costab->size[0] = 1;
  b_costab->size[1] = nd2 + 1;
  emxEnsureCapacity_real32_T(b_costab, ix);
  ix = b_sintab->size[0] * b_sintab->size[1];
  b_sintab->size[0] = 1;
  b_sintab->size[1] = nd2 + 1;
  emxEnsureCapacity_real32_T(b_sintab, ix);
  b_costab->data[0] = 1.0F;
  b_sintab->data[0] = 0.0F;
  for (k = 0; k < j; k++) {
    b_costab->data[k + 1] = costab1q->data[k + 1];
    b_sintab->data[k + 1] = -costab1q->data[(j - k) - 1];
  }

  ix = costab1q->size[1];
  for (k = ix; k <= nd2; k++) {
    b_costab->data[k] = -costab1q->data[nd2 - k];
    b_sintab->data[k] = -costab1q->data[k - j];
  }

  emxInit_real32_T(&hsintab, 2);
  emxInit_real32_T(&hcostabinv, 2);
  emxInit_real32_T(&hsintabinv, 2);
  hszCostab = costab->size[1] / 2;
  ix = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = hszCostab;
  emxEnsureCapacity_real32_T(costab1q, ix);
  ix = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real32_T(hsintab, ix);
  ix = hcostabinv->size[0] * hcostabinv->size[1];
  hcostabinv->size[0] = 1;
  hcostabinv->size[1] = hszCostab;
  emxEnsureCapacity_real32_T(hcostabinv, ix);
  ix = hsintabinv->size[0] * hsintabinv->size[1];
  hsintabinv->size[0] = 1;
  hsintabinv->size[1] = hszCostab;
  emxEnsureCapacity_real32_T(hsintabinv, ix);
  for (i = 0; i < hszCostab; i++) {
    nd2 = ((i + 1) << 1) - 2;
    costab1q->data[i] = costab->data[nd2];
    hsintab->data[i] = sintab->data[nd2];
    hcostabinv->data[i] = costabinv->data[nd2];
    hsintabinv->data[i] = sintabinv->data[nd2];
  }

  emxInit_int32_T(&wrapIndex, 2);
  emxInit_creal32_T(&reconVar1, 1);
  emxInit_creal32_T(&reconVar2, 1);
  ix = reconVar1->size[0];
  reconVar1->size[0] = hnRows;
  emxEnsureCapacity_creal32_T(reconVar1, ix);
  ix = reconVar2->size[0];
  reconVar2->size[0] = hnRows;
  emxEnsureCapacity_creal32_T(reconVar2, ix);
  hszCostab = 0;
  ix = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = hnRows;
  emxEnsureCapacity_int32_T(wrapIndex, ix);
  for (i = 0; i < hnRows; i++) {
    reconVar1->data[i].re = b_sintab->data[hszCostab] + 1.0F;
    reconVar1->data[i].im = -b_costab->data[hszCostab];
    reconVar2->data[i].re = 1.0F - b_sintab->data[hszCostab];
    reconVar2->data[i].im = b_costab->data[hszCostab];
    hszCostab += 2;
    if (i + 1 != 1) {
      wrapIndex->data[i] = (hnRows - i) + 1;
    } else {
      wrapIndex->data[0] = 1;
    }
  }

  emxFree_real32_T(&b_sintab);
  emxFree_real32_T(&b_costab);
  nd2 = xoffInit;
  ix = (int)((double)ihi / 2.0);
  for (hszCostab = 0; hszCostab < ix; hszCostab++) {
    temp_re_tmp = (hnRows + hszCostab) - 1;
    twid_im = x->data[nd2 + 1];
    ytmp->data[hszCostab].re = wwc->data[temp_re_tmp].re * x->data[nd2] +
      wwc->data[temp_re_tmp].im * twid_im;
    ytmp->data[hszCostab].im = wwc->data[temp_re_tmp].re * twid_im - wwc->
      data[temp_re_tmp].im * x->data[nd2];
    nd2 += 2;
  }

  if (!tst) {
    temp_re_tmp = (hnRows + ix) - 1;
    ytmp->data[ix].re = wwc->data[temp_re_tmp].re * x->data[nd2] + wwc->
      data[temp_re_tmp].im * 0.0F;
    ytmp->data[ix].im = wwc->data[temp_re_tmp].re * 0.0F - wwc->data[temp_re_tmp]
      .im * x->data[nd2];
    if (ix + 2 <= hnRows) {
      ix = (int)((double)ihi / 2.0) + 2;
      for (i = ix; i <= hnRows; i++) {
        ytmp->data[i - 1].re = 0.0F;
        ytmp->data[i - 1].im = 0.0F;
      }
    }
  } else {
    if (ix + 1 <= hnRows) {
      ix = (int)((double)ihi / 2.0) + 1;
      for (i = ix; i <= hnRows; i++) {
        ytmp->data[i - 1].re = 0.0F;
        ytmp->data[i - 1].im = 0.0F;
      }
    }
  }

  emxInit_creal32_T(&fy, 1);
  loop_ub_tmp = (int)((double)nfft / 2.0);
  ix = fy->size[0];
  fy->size[0] = loop_ub_tmp;
  emxEnsureCapacity_creal32_T(fy, ix);
  if (loop_ub_tmp > ytmp->size[0]) {
    ix = fy->size[0];
    fy->size[0] = loop_ub_tmp;
    emxEnsureCapacity_creal32_T(fy, ix);
    for (ix = 0; ix < loop_ub_tmp; ix++) {
      fy->data[ix].re = 0.0F;
      fy->data[ix].im = 0.0F;
    }
  }

  ihi = ytmp->size[0];
  if (ihi >= loop_ub_tmp) {
    ihi = loop_ub_tmp;
  }

  hszCostab = loop_ub_tmp - 2;
  nRowsD2 = loop_ub_tmp / 2;
  k = nRowsD2 / 2;
  ix = 0;
  nd2 = 0;
  ju = 0;
  for (i = 0; i <= ihi - 2; i++) {
    fy->data[nd2] = ytmp->data[ix];
    j = loop_ub_tmp;
    tst = true;
    while (tst) {
      j >>= 1;
      ju ^= j;
      tst = ((ju & j) == 0);
    }

    nd2 = ju;
    ix++;
  }

  fy->data[nd2] = ytmp->data[ix];
  if (loop_ub_tmp > 1) {
    for (i = 0; i <= hszCostab; i += 2) {
      temp_re = fy->data[i + 1].re;
      temp_im = fy->data[i + 1].im;
      twid_re = fy->data[i].re;
      twid_im = fy->data[i].im;
      fy->data[i + 1].re = fy->data[i].re - fy->data[i + 1].re;
      fy->data[i + 1].im = fy->data[i].im - fy->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      fy->data[i].re = twid_re;
      fy->data[i].im = twid_im;
    }
  }

  nd2 = 2;
  hszCostab = 4;
  ix = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ix; i += hszCostab) {
      temp_re_tmp = i + nd2;
      temp_re = fy->data[temp_re_tmp].re;
      temp_im = fy->data[temp_re_tmp].im;
      fy->data[temp_re_tmp].re = fy->data[i].re - fy->data[temp_re_tmp].re;
      fy->data[temp_re_tmp].im = fy->data[i].im - fy->data[temp_re_tmp].im;
      fy->data[i].re += temp_re;
      fy->data[i].im += temp_im;
    }

    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab1q->data[j];
      twid_im = hsintab->data[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re_tmp = i + nd2;
        temp_re = twid_re * fy->data[temp_re_tmp].re - twid_im * fy->
          data[temp_re_tmp].im;
        temp_im = twid_re * fy->data[temp_re_tmp].im + twid_im * fy->
          data[temp_re_tmp].re;
        fy->data[temp_re_tmp].re = fy->data[i].re - temp_re;
        fy->data[temp_re_tmp].im = fy->data[i].im - temp_im;
        fy->data[i].re += temp_re;
        fy->data[i].im += temp_im;
        i += hszCostab;
      }

      ju++;
    }

    k /= 2;
    nd2 = hszCostab;
    hszCostab += hszCostab;
    ix -= nd2;
  }

  emxInit_creal32_T(&fv, 1);
  d_FFTImplementationCallback_r2b(wwc, loop_ub_tmp, costab1q, hsintab, fv);
  nd2 = fy->size[0];
  emxFree_real32_T(&costab1q);
  emxFree_real32_T(&hsintab);
  for (ix = 0; ix < nd2; ix++) {
    twid_im = fy->data[ix].re * fv->data[ix].im + fy->data[ix].im * fv->data[ix]
      .re;
    fy->data[ix].re = fy->data[ix].re * fv->data[ix].re - fy->data[ix].im *
      fv->data[ix].im;
    fy->data[ix].im = twid_im;
  }

  d_FFTImplementationCallback_r2b(fy, loop_ub_tmp, hcostabinv, hsintabinv, fv);
  emxFree_creal32_T(&fy);
  emxFree_real32_T(&hsintabinv);
  emxFree_real32_T(&hcostabinv);
  if (fv->size[0] > 1) {
    twid_re = 1.0F / (float)fv->size[0];
    nd2 = fv->size[0];
    for (ix = 0; ix < nd2; ix++) {
      fv->data[ix].re *= twid_re;
      fv->data[ix].im *= twid_re;
    }
  }

  hszCostab = 0;
  ix = (int)(float)hnRows;
  nd2 = wwc->size[0];
  for (k = ix; k <= nd2; k++) {
    ytmp->data[hszCostab].re = wwc->data[k - 1].re * fv->data[k - 1].re +
      wwc->data[k - 1].im * fv->data[k - 1].im;
    ytmp->data[hszCostab].im = wwc->data[k - 1].re * fv->data[k - 1].im -
      wwc->data[k - 1].im * fv->data[k - 1].re;
    hszCostab++;
  }

  emxFree_creal32_T(&fv);
  for (i = 0; i < hnRows; i++) {
    ix = wrapIndex->data[i];
    twid_re = ytmp->data[ix - 1].re;
    twid_im = -ytmp->data[ix - 1].im;
    y->data[i].re = 0.5F * ((ytmp->data[i].re * reconVar1->data[i].re -
      ytmp->data[i].im * reconVar1->data[i].im) + (twid_re * reconVar2->data[i].
      re - twid_im * reconVar2->data[i].im));
    y->data[i].im = 0.5F * ((ytmp->data[i].re * reconVar1->data[i].im +
      ytmp->data[i].im * reconVar1->data[i].re) + (twid_re * reconVar2->data[i].
      im + twid_im * reconVar2->data[i].re));
    twid_re = ytmp->data[ix - 1].re;
    twid_im = -ytmp->data[ix - 1].im;
    ix = hnRows + i;
    y->data[ix].re = 0.5F * ((ytmp->data[i].re * reconVar2->data[i].re -
      ytmp->data[i].im * reconVar2->data[i].im) + (twid_re * reconVar1->data[i].
      re - twid_im * reconVar1->data[i].im));
    y->data[ix].im = 0.5F * ((ytmp->data[i].re * reconVar2->data[i].im +
      ytmp->data[i].im * reconVar2->data[i].re) + (twid_re * reconVar1->data[i].
      im + twid_im * reconVar1->data[i].re));
  }

  emxFree_creal32_T(&reconVar2);
  emxFree_creal32_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
  emxFree_creal32_T(&ytmp);
}

static void d_FFTImplementationCallback_r2b(const emxArray_creal32_T *x, int
  unsigned_nRows, const emxArray_real32_T *costab, const emxArray_real32_T
  *sintab, emxArray_creal32_T *y)
{
  int iy;
  int iDelta2;
  int iheight;
  int nRowsD2;
  int k;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  float temp_re;
  float temp_im;
  float twid_re;
  float twid_im;
  int temp_re_tmp;
  int ihi;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal32_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal32_T(y, iy);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y->data[iy].re = 0.0F;
      y->data[iy].im = 0.0F;
    }
  }

  iDelta2 = x->size[0];
  if (iDelta2 >= unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }

  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  ix = 0;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    y->data[iy] = x->data[ix];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - y->data[temp_re_tmp].re;
      y->data[temp_re_tmp].im = y->data[i].im - y->data[temp_re_tmp].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ix = 1;
    for (ju = k; ju < nRowsD2; ju += k) {
      twid_re = costab->data[ju];
      twid_im = sintab->data[ju];
      i = ix;
      ihi = ix + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iDelta2;
      }

      ix++;
    }

    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

void c_FFTImplementationCallback_dob(const emxArray_real32_T *x, int n2blue, int
  nfft, const emxArray_real32_T *costab, const emxArray_real32_T *sintab, const
  emxArray_real32_T *sintabinv, emxArray_creal32_T *y)
{
  int i;
  unsigned int sx[5];
  boolean_T ishalflength;
  emxArray_creal32_T *wwc;
  int nInt2m1;
  int nRows;
  int idx;
  int rt;
  int nInt2;
  int k;
  int b_y;
  float nt_im;
  int nrows;
  float nt_re;
  int chan;
  emxArray_creal32_T *fv;
  emxArray_creal32_T *fy;
  emxArray_creal32_T *r;
  int i1;
  int i2;
  int b_chan;
  int xoff;
  int ix;
  int minNrowsNx;
  int b_k;
  int iy;
  int temp_re_tmp;
  int ihi;
  int nRowsD2;
  int ju;
  int b_i;
  boolean_T tst;
  float temp_re;
  float temp_im;
  float twid_re;
  float twid_im;
  for (i = 0; i < 5; i++) {
    sx[i] = (unsigned int)x->size[i];
  }

  if ((nfft != 1) && ((nfft & 1) == 0)) {
    ishalflength = true;
  } else {
    ishalflength = false;
  }

  emxInit_creal32_T(&wwc, 1);
  if (ishalflength) {
    nRows = nfft / 2;
    nInt2m1 = (nRows + nRows) - 1;
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal32_T(wwc, i);
    idx = nRows;
    rt = 0;
    wwc->data[nRows - 1].re = 1.0F;
    wwc->data[nRows - 1].im = 0.0F;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }

      nt_im = -3.14159274F * (float)rt / (float)nRows;
      if (nt_im == 0.0F) {
        nt_re = 1.0F;
        nt_im = 0.0F;
      } else {
        nt_re = cosf(nt_im);
        nt_im = sinf(nt_im);
      }

      wwc->data[idx - 2].re = nt_re;
      wwc->data[idx - 2].im = -nt_im;
      idx--;
    }

    idx = 0;
    i = nInt2m1 - 1;
    for (k = i; k >= nRows; k--) {
      wwc->data[k] = wwc->data[idx];
      idx++;
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal32_T(wwc, i);
    idx = nfft;
    rt = 0;
    wwc->data[nfft - 1].re = 1.0F;
    wwc->data[nfft - 1].im = 0.0F;
    nInt2 = nfft << 1;
    for (k = 0; k <= nfft - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }

      nt_im = -3.14159274F * (float)rt / (float)nfft;
      if (nt_im == 0.0F) {
        nt_re = 1.0F;
        nt_im = 0.0F;
      } else {
        nt_re = cosf(nt_im);
        nt_im = sinf(nt_im);
      }

      wwc->data[idx - 2].re = nt_re;
      wwc->data[idx - 2].im = -nt_im;
      idx--;
    }

    idx = 0;
    i = nInt2m1 - 1;
    for (k = i; k >= nfft; k--) {
      wwc->data[k] = wwc->data[idx];
      idx++;
    }
  }

  nrows = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  y->size[3] = x->size[3];
  y->size[4] = x->size[4];
  emxEnsureCapacity_creal32_T(y, i);
  if (nfft > x->size[0]) {
    rt = x->size[4];
    for (i = 0; i < rt; i++) {
      nInt2 = y->size[3];
      for (nRows = 0; nRows < nInt2; nRows++) {
        b_y = y->size[2];
        for (k = 0; k < b_y; k++) {
          nInt2m1 = y->size[1];
          for (i1 = 0; i1 < nInt2m1; i1++) {
            idx = y->size[0];
            for (i2 = 0; i2 < idx; i2++) {
              y->data[(((i2 + y->size[0] * i1) + y->size[0] * y->size[1] * k) +
                       y->size[0] * y->size[1] * y->size[2] * nRows) + y->size[0]
                * y->size[1] * y->size[2] * y->size[3] * i].re = 0.0F;
              y->data[(((i2 + y->size[0] * i1) + y->size[0] * y->size[1] * k) +
                       y->size[0] * y->size[1] * y->size[2] * nRows) + y->size[0]
                * y->size[1] * y->size[2] * y->size[3] * i].im = 0.0F;
            }
          }
        }
      }
    }
  }

  rt = (int)sx[1] * (int)sx[2] * (int)sx[3] * (int)sx[4] - 1;

#pragma omp parallel \
 num_threads(omp_get_max_threads()) \
 private(fv,fy,r,b_chan,xoff,ix,minNrowsNx,iy,b_k,temp_re_tmp,ihi,nRowsD2,ju,b_i,tst,temp_re,temp_im,twid_re,twid_im)

  {
    emxInit_creal32_T(&fv, 1);
    emxInit_creal32_T(&fy, 1);
    emxInit_creal32_T(&r, 1);

#pragma omp for nowait

    for (chan = 0; chan <= rt; chan++) {
      b_chan = chan + 1;
      xoff = (b_chan - 1) * nrows;
      ix = r->size[0];
      r->size[0] = nfft;
      emxEnsureCapacity_creal32_T(r, ix);
      if (nfft > x->size[0]) {
        ix = r->size[0];
        r->size[0] = nfft;
        emxEnsureCapacity_creal32_T(r, ix);
        for (ix = 0; ix < nfft; ix++) {
          r->data[ix].re = 0.0F;
          r->data[ix].im = 0.0F;
        }
      }

      if ((n2blue != 1) && ((nfft & 1) == 0)) {
        d_FFTImplementationCallback_doH(x, xoff, r, x->size[0], nfft, n2blue,
          wwc, costab, sintab, costab, sintabinv);
      } else {
        minNrowsNx = x->size[0];
        if (nfft < minNrowsNx) {
          minNrowsNx = nfft;
        }

        for (b_k = 0; b_k < minNrowsNx; b_k++) {
          temp_re_tmp = (nfft + b_k) - 1;
          r->data[b_k].re = wwc->data[temp_re_tmp].re * x->data[xoff];
          r->data[b_k].im = wwc->data[temp_re_tmp].im * -x->data[xoff];
          xoff++;
        }

        ix = minNrowsNx + 1;
        for (b_k = ix; b_k <= nfft; b_k++) {
          r->data[b_k - 1].re = 0.0F;
          r->data[b_k - 1].im = 0.0F;
        }

        ix = fy->size[0];
        fy->size[0] = n2blue;
        emxEnsureCapacity_creal32_T(fy, ix);
        if (n2blue > r->size[0]) {
          ix = fy->size[0];
          fy->size[0] = n2blue;
          emxEnsureCapacity_creal32_T(fy, ix);
          for (ix = 0; ix < n2blue; ix++) {
            fy->data[ix].re = 0.0F;
            fy->data[ix].im = 0.0F;
          }
        }

        iy = r->size[0];
        ihi = n2blue;
        if (iy < n2blue) {
          ihi = iy;
        }

        xoff = n2blue - 2;
        nRowsD2 = n2blue / 2;
        b_k = nRowsD2 / 2;
        ix = 0;
        iy = 0;
        ju = 0;
        for (b_i = 0; b_i <= ihi - 2; b_i++) {
          fy->data[iy] = r->data[ix];
          minNrowsNx = n2blue;
          tst = true;
          while (tst) {
            minNrowsNx >>= 1;
            ju ^= minNrowsNx;
            tst = ((ju & minNrowsNx) == 0);
          }

          iy = ju;
          ix++;
        }

        fy->data[iy] = r->data[ix];
        if (n2blue > 1) {
          for (b_i = 0; b_i <= xoff; b_i += 2) {
            temp_re = fy->data[b_i + 1].re;
            temp_im = fy->data[b_i + 1].im;
            twid_re = fy->data[b_i].re;
            twid_im = fy->data[b_i].im;
            fy->data[b_i + 1].re = fy->data[b_i].re - fy->data[b_i + 1].re;
            fy->data[b_i + 1].im = fy->data[b_i].im - fy->data[b_i + 1].im;
            twid_re += temp_re;
            twid_im += temp_im;
            fy->data[b_i].re = twid_re;
            fy->data[b_i].im = twid_im;
          }
        }

        minNrowsNx = 2;
        xoff = 4;
        iy = ((b_k - 1) << 2) + 1;
        while (b_k > 0) {
          for (b_i = 0; b_i < iy; b_i += xoff) {
            temp_re_tmp = b_i + minNrowsNx;
            temp_re = fy->data[temp_re_tmp].re;
            temp_im = fy->data[temp_re_tmp].im;
            fy->data[temp_re_tmp].re = fy->data[b_i].re - fy->data[temp_re_tmp].
              re;
            fy->data[temp_re_tmp].im = fy->data[b_i].im - fy->data[temp_re_tmp].
              im;
            fy->data[b_i].re += temp_re;
            fy->data[b_i].im += temp_im;
          }

          ix = 1;
          for (ju = b_k; ju < nRowsD2; ju += b_k) {
            twid_re = costab->data[ju];
            twid_im = sintab->data[ju];
            b_i = ix;
            ihi = ix + iy;
            while (b_i < ihi) {
              temp_re_tmp = b_i + minNrowsNx;
              temp_re = twid_re * fy->data[temp_re_tmp].re - twid_im * fy->
                data[temp_re_tmp].im;
              temp_im = twid_re * fy->data[temp_re_tmp].im + twid_im * fy->
                data[temp_re_tmp].re;
              fy->data[temp_re_tmp].re = fy->data[b_i].re - temp_re;
              fy->data[temp_re_tmp].im = fy->data[b_i].im - temp_im;
              fy->data[b_i].re += temp_re;
              fy->data[b_i].im += temp_im;
              b_i += xoff;
            }

            ix++;
          }

          b_k /= 2;
          minNrowsNx = xoff;
          xoff += xoff;
          iy -= minNrowsNx;
        }

        d_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
        iy = fy->size[0];
        for (ix = 0; ix < iy; ix++) {
          twid_im = fy->data[ix].re * fv->data[ix].im + fy->data[ix].im *
            fv->data[ix].re;
          fy->data[ix].re = fy->data[ix].re * fv->data[ix].re - fy->data[ix].im *
            fv->data[ix].im;
          fy->data[ix].im = twid_im;
        }

        d_FFTImplementationCallback_r2b(fy, n2blue, costab, sintabinv, fv);
        if (fv->size[0] > 1) {
          twid_re = 1.0F / (float)fv->size[0];
          iy = fv->size[0];
          for (ix = 0; ix < iy; ix++) {
            fv->data[ix].re *= twid_re;
            fv->data[ix].im *= twid_re;
          }
        }

        minNrowsNx = 0;
        ix = (int)(float)nfft;
        iy = wwc->size[0];
        for (b_k = ix; b_k <= iy; b_k++) {
          r->data[minNrowsNx].re = wwc->data[b_k - 1].re * fv->data[b_k - 1].re
            + wwc->data[b_k - 1].im * fv->data[b_k - 1].im;
          r->data[minNrowsNx].im = wwc->data[b_k - 1].re * fv->data[b_k - 1].im
            - wwc->data[b_k - 1].im * fv->data[b_k - 1].re;
          minNrowsNx++;
        }
      }

      minNrowsNx = y->size[0];
      iy = r->size[0];
      for (ix = 0; ix < iy; ix++) {
        y->data[ix + minNrowsNx * (b_chan - 1)] = r->data[ix];
      }
    }

    emxFree_creal32_T(&r);
    emxFree_creal32_T(&fy);
    emxFree_creal32_T(&fv);
  }

  emxFree_creal32_T(&wwc);
}

void c_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
  emxArray_real32_T *costab, emxArray_real32_T *sintab, emxArray_real32_T
  *sintabinv)
{
  emxArray_real32_T *costab1q;
  float e;
  int n;
  int i;
  int nd2;
  int k;
  emxInit_real32_T(&costab1q, 2);
  e = 6.28318548F / (float)nRows;
  n = nRows / 2 / 2;
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real32_T(costab1q, i);
  costab1q->data[0] = 1.0F;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q->data[k + 1] = cosf(e * (float)(k + 1));
  }

  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q->data[k] = sinf(e * (float)(n - k));
  }

  costab1q->data[n] = 0.0F;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real32_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real32_T(sintab, i);
    costab->data[0] = 1.0F;
    sintab->data[0] = 0.0F;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real32_T(sintabinv, i);
    for (k = 0; k < n; k++) {
      sintabinv->data[k + 1] = costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv->data[k] = costab1q->data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real32_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real32_T(sintab, i);
    costab->data[0] = 1.0F;
    sintab->data[0] = 0.0F;
    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }

    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }

  emxFree_real32_T(&costab1q);
}

void c_FFTImplementationCallback_get(int nfft, boolean_T useRadix2, int *n2blue,
  int *nRows)
{
  int n;
  int pmax;
  int pmin;
  boolean_T exitg1;
  int k;
  int pow2p;
  *n2blue = 1;
  if (useRadix2) {
    *nRows = nfft;
  } else {
    if (nfft > 0) {
      n = (nfft + nfft) - 1;
      pmax = 31;
      if (n <= 1) {
        pmax = 0;
      } else {
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }

      *n2blue = 1 << pmax;
    }

    *nRows = *n2blue;
  }
}

void c_FFTImplementationCallback_r2b(const emxArray_real32_T *x, int n1_unsigned,
  const emxArray_real32_T *costab, const emxArray_real32_T *sintab,
  emxArray_creal32_T *y)
{
  int i;
  int nrows;
  unsigned int sx[5];
  int loop_ub;
  int chan;
  int b_loop_ub;
  emxArray_creal32_T *r;
  int i1;
  int c_loop_ub;
  int i2;
  int d_loop_ub;
  int i3;
  int e_loop_ub;
  int b_chan;
  int i4;
  int xoff;
  int b_i;
  int u0;
  int f_loop_ub;
  int exitg1;
  boolean_T guard1 = false;
  for (i = 0; i < 5; i++) {
    sx[i] = (unsigned int)x->size[i];
  }

  nrows = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  y->size[3] = x->size[3];
  y->size[4] = x->size[4];
  emxEnsureCapacity_creal32_T(y, i);
  if (n1_unsigned > x->size[0]) {
    loop_ub = x->size[4];
    for (i = 0; i < loop_ub; i++) {
      b_loop_ub = y->size[3];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        c_loop_ub = y->size[2];
        for (i2 = 0; i2 < c_loop_ub; i2++) {
          d_loop_ub = y->size[1];
          for (i3 = 0; i3 < d_loop_ub; i3++) {
            e_loop_ub = y->size[0];
            for (i4 = 0; i4 < e_loop_ub; i4++) {
              y->data[(((i4 + y->size[0] * i3) + y->size[0] * y->size[1] * i2) +
                       y->size[0] * y->size[1] * y->size[2] * i1) + y->size[0] *
                y->size[1] * y->size[2] * y->size[3] * i].re = 0.0F;
              y->data[(((i4 + y->size[0] * i3) + y->size[0] * y->size[1] * i2) +
                       y->size[0] * y->size[1] * y->size[2] * i1) + y->size[0] *
                y->size[1] * y->size[2] * y->size[3] * i].im = 0.0F;
            }
          }
        }
      }
    }
  }

  loop_ub = (int)sx[1] * (int)sx[2] * (int)sx[3] * (int)sx[4] - 1;

#pragma omp parallel \
 num_threads(omp_get_max_threads()) \
 private(r,b_chan,xoff,b_i,u0,f_loop_ub,exitg1)

  {
    emxInit_creal32_T(&r, 1);

#pragma omp for nowait

    for (chan = 0; chan <= loop_ub; chan++) {
      b_chan = chan + 1;
      xoff = (b_chan - 1) * nrows;
      b_i = r->size[0];
      r->size[0] = n1_unsigned;
      emxEnsureCapacity_creal32_T(r, b_i);
      if (n1_unsigned > x->size[0]) {
        b_i = r->size[0];
        r->size[0] = n1_unsigned;
        emxEnsureCapacity_creal32_T(r, b_i);
        for (b_i = 0; b_i < n1_unsigned; b_i++) {
          r->data[b_i].re = 0.0F;
          r->data[b_i].im = 0.0F;
        }
      }

      guard1 = false;
      if (n1_unsigned != 1) {
        c_FFTImplementationCallback_doH(x, xoff, r, n1_unsigned, costab, sintab);
        guard1 = true;
      } else {
        u0 = x->size[0];
        if (u0 >= 1) {
          u0 = 1;
        }

        f_loop_ub = u0 - 2;
        b_i = 0;
        do {
          if (b_i <= f_loop_ub) {
            r->data[0].re = x->data[xoff];
            r->data[0].im = 0.0F;
            exitg1 = 1;
          } else {
            r->data[0].re = x->data[xoff];
            r->data[0].im = 0.0F;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
        } else {
          guard1 = true;
        }
      }

      if (guard1) {
        u0 = y->size[0];
        xoff = r->size[0];
        for (b_i = 0; b_i < xoff; b_i++) {
          y->data[b_i + u0 * (b_chan - 1)] = r->data[b_i];
        }
      }
    }

    emxFree_creal32_T(&r);
  }
}

void d_FFTImplementationCallback_dob(const emxArray_creal32_T *x, int n2blue,
  int nfft, const emxArray_real32_T *costab, const emxArray_real32_T *sintab,
  const emxArray_real32_T *sintabinv, emxArray_creal32_T *y)
{
  int i;
  emxArray_creal32_T *wwc;
  unsigned int sx[5];
  int nInt2m1;
  int idx;
  int rt;
  int nInt2;
  int k;
  int b_y;
  int nrows;
  float nt_im;
  float nt_re;
  int chan;
  emxArray_creal32_T *fv;
  emxArray_creal32_T *fy;
  emxArray_creal32_T *r;
  int i1;
  int i2;
  int i3;
  int b_chan;
  int xoff;
  int ix;
  int minNrowsNx;
  int b_k;
  int temp_re_tmp;
  int iy;
  int ihi;
  int nRowsD2;
  int ju;
  int b_i;
  boolean_T tst;
  float temp_re;
  float temp_im;
  float twid_re;
  float twid_im;
  for (i = 0; i < 5; i++) {
    sx[i] = (unsigned int)x->size[i];
  }

  emxInit_creal32_T(&wwc, 1);
  nInt2m1 = (nfft + nfft) - 1;
  i = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal32_T(wwc, i);
  idx = nfft;
  rt = 0;
  wwc->data[nfft - 1].re = 1.0F;
  wwc->data[nfft - 1].im = 0.0F;
  nInt2 = nfft << 1;
  for (k = 0; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }

    nt_im = -3.14159274F * (float)rt / (float)nfft;
    if (nt_im == 0.0F) {
      nt_re = 1.0F;
      nt_im = 0.0F;
    } else {
      nt_re = cosf(nt_im);
      nt_im = sinf(nt_im);
    }

    wwc->data[idx - 2].re = nt_re;
    wwc->data[idx - 2].im = -nt_im;
    idx--;
  }

  idx = 0;
  i = nInt2m1 - 1;
  for (k = i; k >= nfft; k--) {
    wwc->data[k] = wwc->data[idx];
    idx++;
  }

  nrows = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  y->size[3] = x->size[3];
  y->size[4] = x->size[4];
  emxEnsureCapacity_creal32_T(y, i);
  if (nfft > x->size[0]) {
    rt = x->size[4];
    for (i = 0; i < rt; i++) {
      nInt2 = y->size[3];
      for (k = 0; k < nInt2; k++) {
        b_y = y->size[2];
        for (i1 = 0; i1 < b_y; i1++) {
          nInt2m1 = y->size[1];
          for (i2 = 0; i2 < nInt2m1; i2++) {
            idx = y->size[0];
            for (i3 = 0; i3 < idx; i3++) {
              y->data[(((i3 + y->size[0] * i2) + y->size[0] * y->size[1] * i1) +
                       y->size[0] * y->size[1] * y->size[2] * k) + y->size[0] *
                y->size[1] * y->size[2] * y->size[3] * i].re = 0.0F;
              y->data[(((i3 + y->size[0] * i2) + y->size[0] * y->size[1] * i1) +
                       y->size[0] * y->size[1] * y->size[2] * k) + y->size[0] *
                y->size[1] * y->size[2] * y->size[3] * i].im = 0.0F;
            }
          }
        }
      }
    }
  }

  rt = (int)sx[1] * (int)sx[2] * (int)sx[3] * (int)sx[4] - 1;

#pragma omp parallel \
 num_threads(omp_get_max_threads()) \
 private(fv,fy,r,b_chan,xoff,ix,minNrowsNx,b_k,temp_re_tmp,iy,ihi,nRowsD2,ju,b_i,tst,temp_re,temp_im,twid_re,twid_im)

  {
    emxInit_creal32_T(&fv, 1);
    emxInit_creal32_T(&fy, 1);
    emxInit_creal32_T(&r, 1);

#pragma omp for nowait

    for (chan = 0; chan <= rt; chan++) {
      b_chan = chan + 1;
      xoff = (b_chan - 1) * nrows;
      ix = r->size[0];
      r->size[0] = nfft;
      emxEnsureCapacity_creal32_T(r, ix);
      if (nfft > x->size[0]) {
        ix = r->size[0];
        r->size[0] = nfft;
        emxEnsureCapacity_creal32_T(r, ix);
        for (ix = 0; ix < nfft; ix++) {
          r->data[ix].re = 0.0F;
          r->data[ix].im = 0.0F;
        }
      }

      minNrowsNx = x->size[0];
      if (nfft < minNrowsNx) {
        minNrowsNx = nfft;
      }

      for (b_k = 0; b_k < minNrowsNx; b_k++) {
        temp_re_tmp = (nfft + b_k) - 1;
        r->data[b_k].re = wwc->data[temp_re_tmp].re * x->data[xoff].re +
          wwc->data[temp_re_tmp].im * x->data[xoff].im;
        r->data[b_k].im = wwc->data[temp_re_tmp].re * x->data[xoff].im -
          wwc->data[temp_re_tmp].im * x->data[xoff].re;
        xoff++;
      }

      ix = minNrowsNx + 1;
      for (b_k = ix; b_k <= nfft; b_k++) {
        r->data[b_k - 1].re = 0.0F;
        r->data[b_k - 1].im = 0.0F;
      }

      ix = fy->size[0];
      fy->size[0] = n2blue;
      emxEnsureCapacity_creal32_T(fy, ix);
      if (n2blue > r->size[0]) {
        ix = fy->size[0];
        fy->size[0] = n2blue;
        emxEnsureCapacity_creal32_T(fy, ix);
        for (ix = 0; ix < n2blue; ix++) {
          fy->data[ix].re = 0.0F;
          fy->data[ix].im = 0.0F;
        }
      }

      iy = r->size[0];
      ihi = n2blue;
      if (iy < n2blue) {
        ihi = iy;
      }

      xoff = n2blue - 2;
      nRowsD2 = n2blue / 2;
      b_k = nRowsD2 / 2;
      ix = 0;
      iy = 0;
      ju = 0;
      for (b_i = 0; b_i <= ihi - 2; b_i++) {
        fy->data[iy] = r->data[ix];
        minNrowsNx = n2blue;
        tst = true;
        while (tst) {
          minNrowsNx >>= 1;
          ju ^= minNrowsNx;
          tst = ((ju & minNrowsNx) == 0);
        }

        iy = ju;
        ix++;
      }

      fy->data[iy] = r->data[ix];
      if (n2blue > 1) {
        for (b_i = 0; b_i <= xoff; b_i += 2) {
          temp_re = fy->data[b_i + 1].re;
          temp_im = fy->data[b_i + 1].im;
          twid_re = fy->data[b_i].re;
          twid_im = fy->data[b_i].im;
          fy->data[b_i + 1].re = fy->data[b_i].re - fy->data[b_i + 1].re;
          fy->data[b_i + 1].im = fy->data[b_i].im - fy->data[b_i + 1].im;
          twid_re += temp_re;
          twid_im += temp_im;
          fy->data[b_i].re = twid_re;
          fy->data[b_i].im = twid_im;
        }
      }

      minNrowsNx = 2;
      xoff = 4;
      iy = ((b_k - 1) << 2) + 1;
      while (b_k > 0) {
        for (b_i = 0; b_i < iy; b_i += xoff) {
          temp_re_tmp = b_i + minNrowsNx;
          temp_re = fy->data[temp_re_tmp].re;
          temp_im = fy->data[temp_re_tmp].im;
          fy->data[temp_re_tmp].re = fy->data[b_i].re - fy->data[temp_re_tmp].re;
          fy->data[temp_re_tmp].im = fy->data[b_i].im - fy->data[temp_re_tmp].im;
          fy->data[b_i].re += temp_re;
          fy->data[b_i].im += temp_im;
        }

        ix = 1;
        for (ju = b_k; ju < nRowsD2; ju += b_k) {
          twid_re = costab->data[ju];
          twid_im = sintab->data[ju];
          b_i = ix;
          ihi = ix + iy;
          while (b_i < ihi) {
            temp_re_tmp = b_i + minNrowsNx;
            temp_re = twid_re * fy->data[temp_re_tmp].re - twid_im * fy->
              data[temp_re_tmp].im;
            temp_im = twid_re * fy->data[temp_re_tmp].im + twid_im * fy->
              data[temp_re_tmp].re;
            fy->data[temp_re_tmp].re = fy->data[b_i].re - temp_re;
            fy->data[temp_re_tmp].im = fy->data[b_i].im - temp_im;
            fy->data[b_i].re += temp_re;
            fy->data[b_i].im += temp_im;
            b_i += xoff;
          }

          ix++;
        }

        b_k /= 2;
        minNrowsNx = xoff;
        xoff += xoff;
        iy -= minNrowsNx;
      }

      d_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
      iy = fy->size[0];
      for (ix = 0; ix < iy; ix++) {
        twid_im = fy->data[ix].re * fv->data[ix].im + fy->data[ix].im * fv->
          data[ix].re;
        fy->data[ix].re = fy->data[ix].re * fv->data[ix].re - fy->data[ix].im *
          fv->data[ix].im;
        fy->data[ix].im = twid_im;
      }

      d_FFTImplementationCallback_r2b(fy, n2blue, costab, sintabinv, fv);
      if (fv->size[0] > 1) {
        twid_re = 1.0F / (float)fv->size[0];
        iy = fv->size[0];
        for (ix = 0; ix < iy; ix++) {
          fv->data[ix].re *= twid_re;
          fv->data[ix].im *= twid_re;
        }
      }

      minNrowsNx = 0;
      ix = (int)(float)nfft;
      iy = wwc->size[0];
      for (b_k = ix; b_k <= iy; b_k++) {
        r->data[minNrowsNx].re = wwc->data[b_k - 1].re * fv->data[b_k - 1].re +
          wwc->data[b_k - 1].im * fv->data[b_k - 1].im;
        r->data[minNrowsNx].im = wwc->data[b_k - 1].re * fv->data[b_k - 1].im -
          wwc->data[b_k - 1].im * fv->data[b_k - 1].re;
        minNrowsNx++;
      }

      minNrowsNx = y->size[0];
      iy = r->size[0];
      for (ix = 0; ix < iy; ix++) {
        y->data[ix + minNrowsNx * (b_chan - 1)] = r->data[ix];
      }
    }

    emxFree_creal32_T(&r);
    emxFree_creal32_T(&fy);
    emxFree_creal32_T(&fv);
  }

  emxFree_creal32_T(&wwc);
}

void e_FFTImplementationCallback_r2b(const emxArray_creal32_T *x, int
  n1_unsigned, const emxArray_real32_T *costab, const emxArray_real32_T *sintab,
  emxArray_creal32_T *y)
{
  int i;
  int nrows;
  unsigned int sx[5];
  int loop_ub;
  int chan;
  int b_loop_ub;
  emxArray_creal32_T *r;
  int i1;
  int c_loop_ub;
  int i2;
  int d_loop_ub;
  int i3;
  int e_loop_ub;
  int b_chan;
  int i4;
  int xoff;
  int iheight;
  int iy;
  int j;
  int nRowsD2;
  int k;
  int ju;
  int b_i;
  int iDelta2;
  boolean_T tst;
  float temp_re;
  float temp_im;
  float twid_re;
  float twid_im;
  int temp_re_tmp;
  for (i = 0; i < 5; i++) {
    sx[i] = (unsigned int)x->size[i];
  }

  nrows = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2] * y->size[3] * y->size[4];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  y->size[3] = x->size[3];
  y->size[4] = x->size[4];
  emxEnsureCapacity_creal32_T(y, i);
  if (n1_unsigned > x->size[0]) {
    loop_ub = x->size[4];
    for (i = 0; i < loop_ub; i++) {
      b_loop_ub = y->size[3];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        c_loop_ub = y->size[2];
        for (i2 = 0; i2 < c_loop_ub; i2++) {
          d_loop_ub = y->size[1];
          for (i3 = 0; i3 < d_loop_ub; i3++) {
            e_loop_ub = y->size[0];
            for (i4 = 0; i4 < e_loop_ub; i4++) {
              y->data[(((i4 + y->size[0] * i3) + y->size[0] * y->size[1] * i2) +
                       y->size[0] * y->size[1] * y->size[2] * i1) + y->size[0] *
                y->size[1] * y->size[2] * y->size[3] * i].re = 0.0F;
              y->data[(((i4 + y->size[0] * i3) + y->size[0] * y->size[1] * i2) +
                       y->size[0] * y->size[1] * y->size[2] * i1) + y->size[0] *
                y->size[1] * y->size[2] * y->size[3] * i].im = 0.0F;
            }
          }
        }
      }
    }
  }

  loop_ub = (int)sx[1] * (int)sx[2] * (int)sx[3] * (int)sx[4] - 1;

#pragma omp parallel \
 num_threads(omp_get_max_threads()) \
 private(r,b_chan,xoff,iheight,iy,j,nRowsD2,k,ju,b_i,iDelta2,tst,temp_re,temp_im,twid_re,twid_im,temp_re_tmp)

  {
    emxInit_creal32_T(&r, 1);

#pragma omp for nowait

    for (chan = 0; chan <= loop_ub; chan++) {
      b_chan = chan + 1;
      xoff = (b_chan - 1) * nrows;
      iheight = r->size[0];
      r->size[0] = n1_unsigned;
      emxEnsureCapacity_creal32_T(r, iheight);
      if (n1_unsigned > x->size[0]) {
        iheight = r->size[0];
        r->size[0] = n1_unsigned;
        emxEnsureCapacity_creal32_T(r, iheight);
        for (iheight = 0; iheight < n1_unsigned; iheight++) {
          r->data[iheight].re = 0.0F;
          r->data[iheight].im = 0.0F;
        }
      }

      iy = x->size[0];
      j = n1_unsigned;
      if (iy < n1_unsigned) {
        j = iy;
      }

      iheight = n1_unsigned - 2;
      nRowsD2 = n1_unsigned / 2;
      k = nRowsD2 / 2;
      iy = 0;
      ju = 0;
      for (b_i = 0; b_i <= j - 2; b_i++) {
        r->data[iy] = x->data[xoff];
        iDelta2 = n1_unsigned;
        tst = true;
        while (tst) {
          iDelta2 >>= 1;
          ju ^= iDelta2;
          tst = ((ju & iDelta2) == 0);
        }

        iy = ju;
        xoff++;
      }

      r->data[iy] = x->data[xoff];
      if (n1_unsigned > 1) {
        for (b_i = 0; b_i <= iheight; b_i += 2) {
          temp_re = r->data[b_i + 1].re;
          temp_im = r->data[b_i + 1].im;
          twid_re = r->data[b_i].re;
          twid_im = r->data[b_i].im;
          r->data[b_i + 1].re = r->data[b_i].re - r->data[b_i + 1].re;
          r->data[b_i + 1].im = r->data[b_i].im - r->data[b_i + 1].im;
          twid_re += temp_re;
          twid_im += temp_im;
          r->data[b_i].re = twid_re;
          r->data[b_i].im = twid_im;
        }
      }

      iy = 2;
      iDelta2 = 4;
      iheight = ((k - 1) << 2) + 1;
      while (k > 0) {
        for (b_i = 0; b_i < iheight; b_i += iDelta2) {
          temp_re_tmp = b_i + iy;
          temp_re = r->data[temp_re_tmp].re;
          temp_im = r->data[temp_re_tmp].im;
          r->data[temp_re_tmp].re = r->data[b_i].re - r->data[temp_re_tmp].re;
          r->data[temp_re_tmp].im = r->data[b_i].im - r->data[temp_re_tmp].im;
          r->data[b_i].re += temp_re;
          r->data[b_i].im += temp_im;
        }

        ju = 1;
        for (j = k; j < nRowsD2; j += k) {
          twid_re = costab->data[j];
          twid_im = sintab->data[j];
          b_i = ju;
          xoff = ju + iheight;
          while (b_i < xoff) {
            temp_re_tmp = b_i + iy;
            temp_re = twid_re * r->data[temp_re_tmp].re - twid_im * r->
              data[temp_re_tmp].im;
            temp_im = twid_re * r->data[temp_re_tmp].im + twid_im * r->
              data[temp_re_tmp].re;
            r->data[temp_re_tmp].re = r->data[b_i].re - temp_re;
            r->data[temp_re_tmp].im = r->data[b_i].im - temp_im;
            r->data[b_i].re += temp_re;
            r->data[b_i].im += temp_im;
            b_i += iDelta2;
          }

          ju++;
        }

        k /= 2;
        iy = iDelta2;
        iDelta2 += iDelta2;
        iheight -= iy;
      }

      iy = y->size[0];
      iDelta2 = r->size[0];
      for (iheight = 0; iheight < iDelta2; iheight++) {
        y->data[iheight + iy * (b_chan - 1)] = r->data[iheight];
      }
    }

    emxFree_creal32_T(&r);
  }
}

/* End of code generation (FFTImplementationCallback.c) */
