/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * permute.c
 *
 * Code generation for function 'permute'
 *
 */

/* Include files */
#include "permute.h"
#include "cylfft3.h"
#include "cylfft3_emxutil.h"

/* Function Definitions */
boolean_T nomovement(const int perm[5], const emxArray_creal32_T *a)
{
  boolean_T b;
  int plast;
  int k;
  boolean_T exitg1;
  b = true;
  if ((a->size[0] != 0) && (a->size[1] != 0) && (a->size[2] != 0) && (a->size[3]
       != 0) && (a->size[4] != 0)) {
    plast = 0;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (a->size[perm[k] - 1] != 1) {
        if (plast > perm[k]) {
          b = false;
          exitg1 = true;
        } else {
          plast = perm[k];
          k++;
        }
      } else {
        k++;
      }
    }
  }

  return b;
}

void permute(const emxArray_creal32_T *a, emxArray_creal32_T *b)
{
  static const int iv[5] = { 2, 1, 3, 4, 5 };

  int i;
  int loop_ub;
  int k;
  int b_k;
  int i1;
  int c_k;
  int i2;
  int d_k;
  int i3;
  int subsa_idx_1;
  int e_k;
  int subsa_idx_2;
  int subsa_idx_3;
  int subsa_idx_4;
  if (nomovement(iv, a)) {
    i = b->size[0] * b->size[1] * b->size[2] * b->size[3] * b->size[4];
    b->size[0] = a->size[1];
    b->size[1] = a->size[0];
    b->size[2] = a->size[2];
    b->size[3] = a->size[3];
    b->size[4] = a->size[4];
    emxEnsureCapacity_creal32_T(b, i);
    loop_ub = a->size[1] * a->size[0] * a->size[2] * a->size[3] * a->size[4];
    for (i = 0; i < loop_ub; i++) {
      b->data[i] = a->data[i];
    }
  } else {
    i = b->size[0] * b->size[1] * b->size[2] * b->size[3] * b->size[4];
    b->size[0] = a->size[1];
    b->size[1] = a->size[0];
    b->size[2] = a->size[2];
    b->size[3] = a->size[3];
    b->size[4] = a->size[4];
    emxEnsureCapacity_creal32_T(b, i);
    i = a->size[4];
    for (k = 0; k < i; k++) {
      loop_ub = a->size[3];
      for (b_k = 0; b_k < loop_ub; b_k++) {
        i1 = a->size[2];
        for (c_k = 0; c_k < i1; c_k++) {
          i2 = a->size[1];
          for (d_k = 0; d_k < i2; d_k++) {
            i3 = a->size[0];
            if (0 <= a->size[0] - 1) {
              subsa_idx_1 = d_k + 1;
              subsa_idx_2 = c_k + 1;
              subsa_idx_3 = b_k + 1;
              subsa_idx_4 = k + 1;
            }

            for (e_k = 0; e_k < i3; e_k++) {
              b->data[((((subsa_idx_1 + b->size[0] * e_k) + b->size[0] * b->
                         size[1] * (subsa_idx_2 - 1)) + b->size[0] * b->size[1] *
                        b->size[2] * (subsa_idx_3 - 1)) + b->size[0] * b->size[1]
                       * b->size[2] * b->size[3] * (subsa_idx_4 - 1)) - 1] =
                a->data[(((e_k + a->size[0] * (subsa_idx_1 - 1)) + a->size[0] *
                          a->size[1] * (subsa_idx_2 - 1)) + a->size[0] * a->
                         size[1] * a->size[2] * (subsa_idx_3 - 1)) + a->size[0] *
                a->size[1] * a->size[2] * a->size[3] * (subsa_idx_4 - 1)];
            }
          }
        }
      }
    }
  }
}

/* End of code generation (permute.c) */
