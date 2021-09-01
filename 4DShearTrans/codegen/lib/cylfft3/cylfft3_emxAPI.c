/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cylfft3_emxAPI.c
 *
 * Code generation for function 'cylfft3_emxAPI'
 *
 */

/* Include files */
#include "cylfft3_emxAPI.h"
#include "cylfft3.h"
#include "cylfft3_emxutil.h"
#include <stdlib.h>

/* Function Definitions */
emxArray_creal32_T *emxCreateND_creal32_T(int numDimensions, const int *size)
{
  emxArray_creal32_T *emx;
  int numEl;
  int i;
  emxInit_creal32_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (creal32_T *)calloc((unsigned int)numEl, sizeof(creal32_T));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

emxArray_real32_T *emxCreateND_real32_T(int numDimensions, const int *size)
{
  emxArray_real32_T *emx;
  int numEl;
  int i;
  emxInit_real32_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (float *)calloc((unsigned int)numEl, sizeof(float));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

emxArray_creal32_T *emxCreateWrapperND_creal32_T(creal32_T *data, int
  numDimensions, const int *size)
{
  emxArray_creal32_T *emx;
  int numEl;
  int i;
  emxInit_creal32_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

emxArray_real32_T *emxCreateWrapperND_real32_T(float *data, int numDimensions,
  const int *size)
{
  emxArray_real32_T *emx;
  int numEl;
  int i;
  emxInit_real32_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

emxArray_creal32_T *emxCreateWrapper_creal32_T(creal32_T *data, int rows, int
  cols)
{
  emxArray_creal32_T *emx;
  emxInit_creal32_T(&emx, 2);
  emx->size[0] = rows;
  emx->size[1] = cols;
  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = rows * cols;
  emx->canFreeData = false;
  return emx;
}

emxArray_real32_T *emxCreateWrapper_real32_T(float *data, int rows, int cols)
{
  emxArray_real32_T *emx;
  emxInit_real32_T(&emx, 2);
  emx->size[0] = rows;
  emx->size[1] = cols;
  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = rows * cols;
  emx->canFreeData = false;
  return emx;
}

emxArray_creal32_T *emxCreate_creal32_T(int rows, int cols)
{
  emxArray_creal32_T *emx;
  int numEl;
  emxInit_creal32_T(&emx, 2);
  emx->size[0] = rows;
  numEl = rows * cols;
  emx->size[1] = cols;
  emx->data = (creal32_T *)calloc((unsigned int)numEl, sizeof(creal32_T));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

emxArray_real32_T *emxCreate_real32_T(int rows, int cols)
{
  emxArray_real32_T *emx;
  int numEl;
  emxInit_real32_T(&emx, 2);
  emx->size[0] = rows;
  numEl = rows * cols;
  emx->size[1] = cols;
  emx->data = (float *)calloc((unsigned int)numEl, sizeof(float));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

void emxDestroyArray_creal32_T(emxArray_creal32_T *emxArray)
{
  emxFree_creal32_T(&emxArray);
}

void emxDestroyArray_real32_T(emxArray_real32_T *emxArray)
{
  emxFree_real32_T(&emxArray);
}

void emxInitArray_creal32_T(emxArray_creal32_T **pEmxArray, int numDimensions)
{
  emxInit_creal32_T(pEmxArray, numDimensions);
}

void emxInitArray_real32_T(emxArray_real32_T **pEmxArray, int numDimensions)
{
  emxInit_real32_T(pEmxArray, numDimensions);
}

/* End of code generation (cylfft3_emxAPI.c) */
