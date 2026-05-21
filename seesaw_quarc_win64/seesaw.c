/*
 * seesaw.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "seesaw".
 *
 * Model version              : 11.21
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Fri May  8 15:56:13 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "seesaw.h"
#include "rtwtypes.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "seesaw_dt.h"

/* Block states (default storage) */
DW_seesaw_T seesaw_DW;

/* Real-time model */
static RT_MODEL_seesaw_T seesaw_M_;
RT_MODEL_seesaw_T *const seesaw_M = &seesaw_M_;

/* Model output function */
void seesaw_output(void)
{
  /* (no output code required) */
}

/* Model update function */
void seesaw_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++seesaw_M->Timing.clockTick0)) {
    ++seesaw_M->Timing.clockTickH0;
  }

  seesaw_M->Timing.t[0] = seesaw_M->Timing.clockTick0 *
    seesaw_M->Timing.stepSize0 + seesaw_M->Timing.clockTickH0 *
    seesaw_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void seesaw_initialize(void)
{
}

/* Model terminate function */
void seesaw_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  seesaw_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  seesaw_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  seesaw_initialize();
}

void MdlTerminate(void)
{
  seesaw_terminate();
}

/* Registration function */
RT_MODEL_seesaw_T *seesaw(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)seesaw_M, 0,
                sizeof(RT_MODEL_seesaw_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = seesaw_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "seesaw_M points to
       static memory which is guaranteed to be non-NULL" */
    seesaw_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    seesaw_M->Timing.sampleTimes = (&seesaw_M->Timing.sampleTimesArray[0]);
    seesaw_M->Timing.offsetTimes = (&seesaw_M->Timing.offsetTimesArray[0]);

    /* task periods */
    seesaw_M->Timing.sampleTimes[0] = (0.033333333333333333);

    /* task offsets */
    seesaw_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(seesaw_M, &seesaw_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = seesaw_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    seesaw_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(seesaw_M, -1);
  seesaw_M->Timing.stepSize0 = 0.033333333333333333;

  /* External mode info */
  seesaw_M->Sizes.checksums[0] = (3263069638U);
  seesaw_M->Sizes.checksums[1] = (3582958967U);
  seesaw_M->Sizes.checksums[2] = (2230116465U);
  seesaw_M->Sizes.checksums[3] = (788239897U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    seesaw_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(seesaw_M->extModeInfo,
      &seesaw_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(seesaw_M->extModeInfo, seesaw_M->Sizes.checksums);
    rteiSetTPtr(seesaw_M->extModeInfo, rtmGetTPtr(seesaw_M));
  }

  seesaw_M->solverInfoPtr = (&seesaw_M->solverInfo);
  seesaw_M->Timing.stepSize = (0.033333333333333333);
  rtsiSetFixedStepSize(&seesaw_M->solverInfo, 0.033333333333333333);
  rtsiSetSolverMode(&seesaw_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* states (dwork) */
  seesaw_M->dwork = ((void *) &seesaw_DW);
  (void) memset((void *)&seesaw_DW, 0,
                sizeof(DW_seesaw_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    seesaw_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;
  }

  /* Initialize Sizes */
  seesaw_M->Sizes.numContStates = (0); /* Number of continuous states */
  seesaw_M->Sizes.numY = (0);          /* Number of model outputs */
  seesaw_M->Sizes.numU = (0);          /* Number of model inputs */
  seesaw_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  seesaw_M->Sizes.numSampTimes = (1);  /* Number of sample times */
  seesaw_M->Sizes.numBlocks = (1);     /* Number of blocks */
  return seesaw_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
