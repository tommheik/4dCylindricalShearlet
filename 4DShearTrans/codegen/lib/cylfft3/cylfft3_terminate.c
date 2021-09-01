/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cylfft3_terminate.c
 *
 * Code generation for function 'cylfft3_terminate'
 *
 */

/* Include files */
#include "cylfft3_terminate.h"
#include "cylfft3.h"
#include "cylfft3_data.h"

/* Function Definitions */
void cylfft3_terminate(void)
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
  isInitialized_cylfft3 = false;
}

/* End of code generation (cylfft3_terminate.c) */
