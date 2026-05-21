/*
 * communication_test.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "communication_test".
 *
 * Model version              : 1.3
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Fri May  8 16:00:11 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_communication_test_h_
#define RTW_HEADER_communication_test_h_
#ifndef communication_test_COMMON_INCLUDES_
#define communication_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "hil.h"
#include "quanser_messages.h"
#include "quanser_extern.h"
#endif                                 /* communication_test_COMMON_INCLUDES_ */

#include "communication_test_types.h"
#include <float.h>
#include <string.h>
#include <stddef.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Gain;                         /* '<S1>/Gain' */
  real_T TransferFcn;                  /* '<S1>/Transfer Fcn' */
  real_T DACBSaturationV;              /* '<S4>/DACB Saturation (V)' */
  real_T AmplifierGainVV;              /* '<S4>/Amplifier  Gain (V//V)' */
  real_T EncoderCalibrationradcount;
                                  /* '<S2>/Encoder Calibration  (rad//count)' */
} B_communication_test_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T HILInitialize_AOVoltages[2];  /* '<S2>/HIL Initialize' */
  real_T HILReadAnalog_Buffer;         /* '<S2>/HIL Read Analog' */
  t_card HILInitialize_Card;           /* '<S2>/HIL Initialize' */
  void *HILWriteAnalog_PWORK;          /* '<S2>/HIL Write Analog' */
  void *HILReadEncoder_PWORK;          /* '<S2>/HIL Read Encoder' */
  void *HILReadAnalog_PWORK;           /* '<S2>/HIL Read Analog' */
  void *HILWriteDigital_PWORK;         /* '<S2>/HIL Write Digital' */
  int32_T HILReadEncoder_Buffer;       /* '<S2>/HIL Read Encoder' */
  boolean_T HILInitialize_DOBits[8];   /* '<S2>/HIL Initialize' */
  t_boolean HILWriteDigital_Buffer[4]; /* '<S2>/HIL Write Digital' */
} DW_communication_test_T;

/* Continuous states (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Qs_CSTATE[2];                 /* '<Root>/Q(s)' */
} X_communication_test_T;

/* State derivatives (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<S1>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S1>/Transfer Fcn1' */
  real_T Qs_CSTATE[2];                 /* '<Root>/Q(s)' */
} XDot_communication_test_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<S1>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S1>/Transfer Fcn1' */
  boolean_T Qs_CSTATE[2];              /* '<Root>/Q(s)' */
} XDis_communication_test_T;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* Parameters (default storage) */
struct P_communication_test_T_ {
  uint32_T HILWriteAnalog_channels;   /* Mask Parameter: HILWriteAnalog_channels
                                       * Referenced by: '<S2>/HIL Write Analog'
                                       */
  uint32_T HILReadEncoder_channels;   /* Mask Parameter: HILReadEncoder_channels
                                       * Referenced by: '<S2>/HIL Read Encoder'
                                       */
  uint32_T HILReadAnalog_channels;     /* Mask Parameter: HILReadAnalog_channels
                                        * Referenced by: '<S2>/HIL Read Analog'
                                        */
  uint32_T HILWriteDigital_channels[4];
                                     /* Mask Parameter: HILWriteDigital_channels
                                      * Referenced by: '<S2>/HIL Write Digital'
                                      */
  real_T HILInitialize_OOTerminate;/* Expression: set_other_outputs_at_terminate
                                    * Referenced by: '<S2>/HIL Initialize'
                                    */
  real_T HILInitialize_OOExit;    /* Expression: set_other_outputs_at_switch_out
                                   * Referenced by: '<S2>/HIL Initialize'
                                   */
  real_T HILInitialize_AOFinal;        /* Expression: final_analog_outputs
                                        * Referenced by: '<S2>/HIL Initialize'
                                        */
  real_T HILInitialize_POFinal;        /* Expression: final_pwm_outputs
                                        * Referenced by: '<S2>/HIL Initialize'
                                        */
  real_T reference_Value;              /* Expression: 0.3
                                        * Referenced by: '<Root>/reference'
                                        */
  real_T Gain_Gain;                    /* Expression: -4/100
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<S1>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<S1>/Transfer Fcn'
                                        */
  real_T TransferFcn_D;                /* Computed Parameter: TransferFcn_D
                                        * Referenced by: '<S1>/Transfer Fcn'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<S1>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<S1>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_D;               /* Computed Parameter: TransferFcn1_D
                                        * Referenced by: '<S1>/Transfer Fcn1'
                                        */
  real_T DirectionConventionRightHandsys;/* Expression: -1
                                          * Referenced by: '<S4>/Direction Convention: (Right-Hand) system'
                                          */
  real_T AmplifierSaturationV_UpperSat;/* Expression: 24
                                        * Referenced by: '<S4>/Amplifier Saturation (V)'
                                        */
  real_T AmplifierSaturationV_LowerSat;/* Expression: -24
                                        * Referenced by: '<S4>/Amplifier Saturation (V)'
                                        */
  real_T InverseAmplifierGainVV_Gain;  /* Expression: 1
                                        * Referenced by: '<S4>/Inverse Amplifier  Gain (V//V)'
                                        */
  real_T DACBSaturationV_UpperSat;     /* Expression: 10
                                        * Referenced by: '<S4>/DACB Saturation (V)'
                                        */
  real_T DACBSaturationV_LowerSat;     /* Expression: -10
                                        * Referenced by: '<S4>/DACB Saturation (V)'
                                        */
  real_T AmplifierGainVV_Gain;         /* Expression: -1
                                        * Referenced by: '<S4>/Amplifier  Gain (V//V)'
                                        */
  real_T EncoderCalibrationradcount_Gain;/* Expression: 0.0015
                                          * Referenced by: '<S2>/Encoder Calibration  (rad//count)'
                                          */
  real_T StrainGageCalibrationradV_Gain;/* Expression: 0.0606
                                         * Referenced by: '<S2>/Strain Gage Calibration  (rad//V)'
                                         */
  real_T EnableVoltPAQX2X4_Value[4];   /* Expression: [1 1 1 1]
                                        * Referenced by: '<S2>/Enable VoltPAQ-X2,X4'
                                        */
  real_T Qs_A[2];                      /* Computed Parameter: Qs_A
                                        * Referenced by: '<Root>/Q(s)'
                                        */
  real_T Qs_C[2];                      /* Computed Parameter: Qs_C
                                        * Referenced by: '<Root>/Q(s)'
                                        */
  boolean_T HILInitialize_Active;    /* Computed Parameter: HILInitialize_Active
                                      * Referenced by: '<S2>/HIL Initialize'
                                      */
  boolean_T HILInitialize_AOTerminate;
                                /* Computed Parameter: HILInitialize_AOTerminate
                                 * Referenced by: '<S2>/HIL Initialize'
                                 */
  boolean_T HILInitialize_AOExit;    /* Computed Parameter: HILInitialize_AOExit
                                      * Referenced by: '<S2>/HIL Initialize'
                                      */
  boolean_T HILInitialize_DOTerminate;
                                /* Computed Parameter: HILInitialize_DOTerminate
                                 * Referenced by: '<S2>/HIL Initialize'
                                 */
  boolean_T HILInitialize_DOExit;    /* Computed Parameter: HILInitialize_DOExit
                                      * Referenced by: '<S2>/HIL Initialize'
                                      */
  boolean_T HILInitialize_POTerminate;
                                /* Computed Parameter: HILInitialize_POTerminate
                                 * Referenced by: '<S2>/HIL Initialize'
                                 */
  boolean_T HILInitialize_POExit;    /* Computed Parameter: HILInitialize_POExit
                                      * Referenced by: '<S2>/HIL Initialize'
                                      */
  boolean_T HILInitialize_DOFinal;  /* Computed Parameter: HILInitialize_DOFinal
                                     * Referenced by: '<S2>/HIL Initialize'
                                     */
  boolean_T HILWriteAnalog_Active;  /* Computed Parameter: HILWriteAnalog_Active
                                     * Referenced by: '<S2>/HIL Write Analog'
                                     */
  boolean_T HILReadEncoder_Active;  /* Computed Parameter: HILReadEncoder_Active
                                     * Referenced by: '<S2>/HIL Read Encoder'
                                     */
  boolean_T HILReadAnalog_Active;    /* Computed Parameter: HILReadAnalog_Active
                                      * Referenced by: '<S2>/HIL Read Analog'
                                      */
  boolean_T HILWriteDigital_Active;/* Computed Parameter: HILWriteDigital_Active
                                    * Referenced by: '<S2>/HIL Write Digital'
                                    */
};

/* Real-time Model Data Structure */
struct tag_RTM_communication_test_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_communication_test_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_communication_test_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][4];
  ODE1_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_communication_test_T communication_test_P;

/* Block signals (default storage) */
extern B_communication_test_T communication_test_B;

/* Continuous states (default storage) */
extern X_communication_test_T communication_test_X;

/* Block states (default storage) */
extern DW_communication_test_T communication_test_DW;

/* Model entry point functions */
extern void communication_test_initialize(void);
extern void communication_test_step(void);
extern void communication_test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_communication_test_T *const communication_test_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'communication_test'
 * '<S1>'   : 'communication_test/C(s)'
 * '<S2>'   : 'communication_test/SRV02 Flexible Link'
 * '<S3>'   : 'communication_test/UDP Read1'
 * '<S4>'   : 'communication_test/SRV02 Flexible Link/Actuator Dynamics'
 * '<S5>'   : 'communication_test/UDP Read1/UDP Read'
 */
#endif                                 /* RTW_HEADER_communication_test_h_ */
