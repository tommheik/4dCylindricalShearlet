/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "cylfft3.h"
#include "cylfft3_emxAPI.h"
#include "cylfft3_terminate.h"

/* Function Declarations */
static float argInit_real32_T(void);
static emxArray_real32_T *c_argInit_UnboundedxUnboundedxU(void);
static void main_cylfft3(void);

/* Function Definitions */
static float argInit_real32_T(void)
{
  return 0.0F;
}

static emxArray_real32_T *c_argInit_UnboundedxUnboundedxU(void)
{
  emxArray_real32_T *result;
  static const int iv[5] = { 2, 2, 2, 2, 2 };

  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real32_T(5, iv);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      for (idx2 = 0; idx2 < result->size[2U]; idx2++) {
        for (idx3 = 0; idx3 < result->size[3U]; idx3++) {
          for (idx4 = 0; idx4 < result->size[4U]; idx4++) {
            /* Set the value of the array element.
               Change this value to the value that the application requires. */
            result->data[(((idx0 + result->size[0] * idx1) + result->size[0] *
                           result->size[1] * idx2) + result->size[0] *
                          result->size[1] * result->size[2] * idx3) +
              result->size[0] * result->size[1] * result->size[2] * result->
              size[3] * idx4] = argInit_real32_T();
          }
        }
      }
    }
  }

  return result;
}

static void main_cylfft3(void)
{
  emxArray_creal32_T *F;
  emxArray_real32_T *f;
  emxInitArray_creal32_T(&F, 5);

  /* Initialize function 'cylfft3' input arguments. */
  /* Initialize function input argument 'f'. */
  f = c_argInit_UnboundedxUnboundedxU();

  /* Call the entry-point 'cylfft3'. */
  cylfft3(f, F);
  emxDestroyArray_creal32_T(F);
  emxDestroyArray_real32_T(f);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_cylfft3();

  /* Terminate the application.
     You do not need to do this more than one time. */
  cylfft3_terminate();
  return 0;
}

/* End of code generation (main.c) */
