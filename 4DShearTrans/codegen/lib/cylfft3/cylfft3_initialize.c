/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cylfft3_initialize.c
 *
 * Code generation for function 'cylfft3_initialize'
 *
 */

/* Include files */
#include "cylfft3_initialize.h"
#include "cylfft3.h"
#include "cylfft3_data.h"

/* Function Definitions */
void cylfft3_initialize(void)
{
  omp_init_nest_lock(&emlrtNestLockGlobal);
  isInitialized_cylfft3 = true;
}

/* End of code generation (cylfft3_initialize.c) */
