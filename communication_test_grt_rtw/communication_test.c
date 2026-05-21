/*
 * communication_test.c
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

#include "communication_test.h"
#include "rtwtypes.h"
#include "communication_test_private.h"
#include <string.h>
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_communication_test_T communication_test_B;

/* Continuous states */
X_communication_test_T communication_test_X;

/* Block states (default storage) */
DW_communication_test_T communication_test_DW;

/* Real-time model */
static RT_MODEL_communication_test_T communication_test_M_;
RT_MODEL_communication_test_T *const communication_test_M =
  &communication_test_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  communication_test_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void communication_test_step(void)
{
  real_T rtb_StrainGageCalibrationradV;
  real_T u0;
  if (rtmIsMajorTimeStep(communication_test_M)) {
    /* set solver stop time */
    if (!(communication_test_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&communication_test_M->solverInfo,
                            ((communication_test_M->Timing.clockTickH0 + 1) *
        communication_test_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&communication_test_M->solverInfo,
                            ((communication_test_M->Timing.clockTick0 + 1) *
        communication_test_M->Timing.stepSize0 +
        communication_test_M->Timing.clockTickH0 *
        communication_test_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(communication_test_M)) {
    communication_test_M->Timing.t[0] = rtsiGetT
      (&communication_test_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(communication_test_M)) {
    /* Sum: '<Root>/Subtract' incorporates:
     *  Constant: '<Root>/reference'
     */
    rtb_StrainGageCalibrationradV = communication_test_P.reference_Value;

    /* Gain: '<S1>/Gain' */
    communication_test_B.Gain = communication_test_P.Gain_Gain *
      rtb_StrainGageCalibrationradV;
  }

  /* TransferFcn: '<S1>/Transfer Fcn' */
  communication_test_B.TransferFcn = communication_test_P.TransferFcn_C *
    communication_test_X.TransferFcn_CSTATE;
  communication_test_B.TransferFcn += communication_test_P.TransferFcn_D *
    communication_test_B.Gain;

  /* Gain: '<S4>/Direction Convention: (Right-Hand) system' incorporates:
   *  TransferFcn: '<S1>/Transfer Fcn1'
   */
  u0 = (communication_test_P.TransferFcn1_C *
        communication_test_X.TransferFcn1_CSTATE +
        communication_test_P.TransferFcn1_D * communication_test_B.TransferFcn) *
    communication_test_P.DirectionConventionRightHandsys;

  /* Saturate: '<S4>/Amplifier Saturation (V)' */
  if (u0 > communication_test_P.AmplifierSaturationV_UpperSat) {
    u0 = communication_test_P.AmplifierSaturationV_UpperSat;
  } else if (u0 < communication_test_P.AmplifierSaturationV_LowerSat) {
    u0 = communication_test_P.AmplifierSaturationV_LowerSat;
  }

  /* Gain: '<S4>/Inverse Amplifier  Gain (V//V)' incorporates:
   *  Saturate: '<S4>/Amplifier Saturation (V)'
   */
  u0 *= communication_test_P.InverseAmplifierGainVV_Gain;

  /* Saturate: '<S4>/DACB Saturation (V)' */
  if (u0 > communication_test_P.DACBSaturationV_UpperSat) {
    /* Saturate: '<S4>/DACB Saturation (V)' */
    communication_test_B.DACBSaturationV =
      communication_test_P.DACBSaturationV_UpperSat;
  } else if (u0 < communication_test_P.DACBSaturationV_LowerSat) {
    /* Saturate: '<S4>/DACB Saturation (V)' */
    communication_test_B.DACBSaturationV =
      communication_test_P.DACBSaturationV_LowerSat;
  } else {
    /* Saturate: '<S4>/DACB Saturation (V)' */
    communication_test_B.DACBSaturationV = u0;
  }

  /* End of Saturate: '<S4>/DACB Saturation (V)' */
  if (rtmIsMajorTimeStep(communication_test_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: communication_test/SRV02 Flexible Link/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(communication_test_DW.HILInitialize_Card,
        &communication_test_P.HILWriteAnalog_channels, 1,
        &communication_test_B.DACBSaturationV);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<S4>/Amplifier  Gain (V//V)' */
  communication_test_B.AmplifierGainVV =
    communication_test_P.AmplifierGainVV_Gain *
    communication_test_B.DACBSaturationV;
  if (rtmIsMajorTimeStep(communication_test_M)) {
    /* S-Function (hil_read_encoder_block): '<S2>/HIL Read Encoder' */

    /* S-Function Block: communication_test/SRV02 Flexible Link/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(communication_test_DW.HILInitialize_Card,
        &communication_test_P.HILReadEncoder_channels, 1,
        &communication_test_DW.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
      } else {
        rtb_StrainGageCalibrationradV =
          communication_test_DW.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<S2>/Encoder Calibration  (rad//count)' */
    communication_test_B.EncoderCalibrationradcount =
      communication_test_P.EncoderCalibrationradcount_Gain *
      rtb_StrainGageCalibrationradV;

    /* S-Function (hil_read_analog_block): '<S2>/HIL Read Analog' */

    /* S-Function Block: communication_test/SRV02 Flexible Link/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog(communication_test_DW.HILInitialize_Card,
        &communication_test_P.HILReadAnalog_channels, 1,
        &communication_test_DW.HILReadAnalog_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
      }

      rtb_StrainGageCalibrationradV = communication_test_DW.HILReadAnalog_Buffer;
    }

    /* Gain: '<S2>/Strain Gage Calibration  (rad//V)' */
    rtb_StrainGageCalibrationradV *=
      communication_test_P.StrainGageCalibrationradV_Gain;

    /* S-Function (hil_write_digital_block): '<S2>/HIL Write Digital' incorporates:
     *  Constant: '<S2>/Enable VoltPAQ-X2,X4'
     */

    /* S-Function Block: communication_test/SRV02 Flexible Link/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      communication_test_DW.HILWriteDigital_Buffer[0] =
        (communication_test_P.EnableVoltPAQX2X4_Value[0] != 0);
      communication_test_DW.HILWriteDigital_Buffer[1] =
        (communication_test_P.EnableVoltPAQX2X4_Value[1] != 0);
      communication_test_DW.HILWriteDigital_Buffer[2] =
        (communication_test_P.EnableVoltPAQX2X4_Value[2] != 0);
      communication_test_DW.HILWriteDigital_Buffer[3] =
        (communication_test_P.EnableVoltPAQX2X4_Value[3] != 0);
      result = hil_write_digital(communication_test_DW.HILInitialize_Card,
        communication_test_P.HILWriteDigital_channels, 4,
        &communication_test_DW.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
      }
    }
  }

  if (rtmIsMajorTimeStep(communication_test_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(communication_test_M->rtwLogInfo,
                        (communication_test_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(communication_test_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(communication_test_M)!=-1) &&
          !((rtmGetTFinal(communication_test_M)-
             (((communication_test_M->Timing.clockTick1+
                communication_test_M->Timing.clockTickH1* 4294967296.0)) *
              0.033333333333333333)) >
            (((communication_test_M->Timing.clockTick1+
               communication_test_M->Timing.clockTickH1* 4294967296.0)) *
             0.033333333333333333) * (DBL_EPSILON))) {
        rtmSetErrorStatus(communication_test_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&communication_test_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++communication_test_M->Timing.clockTick0)) {
      ++communication_test_M->Timing.clockTickH0;
    }

    communication_test_M->Timing.t[0] = rtsiGetSolverStopTime
      (&communication_test_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.033333333333333333s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.033333333333333333, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      communication_test_M->Timing.clockTick1++;
      if (!communication_test_M->Timing.clockTick1) {
        communication_test_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void communication_test_derivatives(void)
{
  XDot_communication_test_T *_rtXdot;
  _rtXdot = ((XDot_communication_test_T *) communication_test_M->derivs);

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = communication_test_P.TransferFcn_A *
    communication_test_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += communication_test_B.Gain;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = communication_test_P.TransferFcn1_A *
    communication_test_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += communication_test_B.TransferFcn;

  /* Derivatives for TransferFcn: '<Root>/Q(s)' */
  _rtXdot->Qs_CSTATE[0] = communication_test_P.Qs_A[0] *
    communication_test_X.Qs_CSTATE[0];
  _rtXdot->Qs_CSTATE[0] += communication_test_P.Qs_A[1] *
    communication_test_X.Qs_CSTATE[1];
  _rtXdot->Qs_CSTATE[1] = communication_test_X.Qs_CSTATE[0];
  _rtXdot->Qs_CSTATE[0] += communication_test_B.EncoderCalibrationradcount;
}

/* Model initialize function */
void communication_test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)communication_test_M, 0,
                sizeof(RT_MODEL_communication_test_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&communication_test_M->solverInfo,
                          &communication_test_M->Timing.simTimeStep);
    rtsiSetTPtr(&communication_test_M->solverInfo, &rtmGetTPtr
                (communication_test_M));
    rtsiSetStepSizePtr(&communication_test_M->solverInfo,
                       &communication_test_M->Timing.stepSize0);
    rtsiSetdXPtr(&communication_test_M->solverInfo,
                 &communication_test_M->derivs);
    rtsiSetContStatesPtr(&communication_test_M->solverInfo, (real_T **)
                         &communication_test_M->contStates);
    rtsiSetNumContStatesPtr(&communication_test_M->solverInfo,
      &communication_test_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&communication_test_M->solverInfo,
      &communication_test_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&communication_test_M->solverInfo,
      &communication_test_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&communication_test_M->solverInfo,
      &communication_test_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&communication_test_M->solverInfo, (&rtmGetErrorStatus
      (communication_test_M)));
    rtsiSetRTModelPtr(&communication_test_M->solverInfo, communication_test_M);
  }

  rtsiSetSimTimeStep(&communication_test_M->solverInfo, MAJOR_TIME_STEP);
  communication_test_M->intgData.f[0] = communication_test_M->odeF[0];
  communication_test_M->contStates = ((X_communication_test_T *)
    &communication_test_X);
  rtsiSetSolverData(&communication_test_M->solverInfo, (void *)
                    &communication_test_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&communication_test_M->solverInfo, false);
  rtsiSetSolverName(&communication_test_M->solverInfo,"ode1");
  rtmSetTPtr(communication_test_M, &communication_test_M->Timing.tArray[0]);
  rtmSetTFinal(communication_test_M, 40.0);
  communication_test_M->Timing.stepSize0 = 0.033333333333333333;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    communication_test_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(communication_test_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(communication_test_M->rtwLogInfo, (NULL));
    rtliSetLogT(communication_test_M->rtwLogInfo, "tout");
    rtliSetLogX(communication_test_M->rtwLogInfo, "");
    rtliSetLogXFinal(communication_test_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(communication_test_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(communication_test_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(communication_test_M->rtwLogInfo, 0);
    rtliSetLogDecimation(communication_test_M->rtwLogInfo, 1);
    rtliSetLogY(communication_test_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(communication_test_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(communication_test_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &communication_test_B), 0,
                sizeof(B_communication_test_T));

  /* states (continuous) */
  {
    (void) memset((void *)&communication_test_X, 0,
                  sizeof(X_communication_test_T));
  }

  /* states (dwork) */
  (void) memset((void *)&communication_test_DW, 0,
                sizeof(DW_communication_test_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(communication_test_M->rtwLogInfo, 0.0,
    rtmGetTFinal(communication_test_M), communication_test_M->Timing.stepSize0,
    (&rtmGetErrorStatus(communication_test_M)));

  /* Start for S-Function (hil_initialize_block): '<S2>/HIL Initialize' */

  /* S-Function Block: communication_test/SRV02 Flexible Link/HIL Initialize (hil_initialize_block) */
  {
    static const t_uint analog_input_channels[2U] = {
      0
      , 1
    };

    static const t_double analog_input_minimums[2U] = {
      -10.0
      , -10.0
    };

    static const t_double analog_input_maximums[2U] = {
      10.0
      , 10.0
    };

    static const t_uint analog_output_channels[2U] = {
      0
      , 1
    };

    static const t_double analog_output_minimums[2U] = {
      -10.0
      , -10.0
    };

    static const t_double analog_output_maximums[2U] = {
      10.0
      , 10.0
    };

    static const t_double initial_analog_outputs[2U] = {
      0.0
      , 0.0
    };

    static const t_uint digital_output_channels[8U] = {
      0
      , 1
      , 2
      , 3
      , 4
      , 5
      , 6
      , 7
    };

    static const t_boolean initial_digital_outputs[8U] = {
      false
      , false
      , false
      , false
      , false
      , false
      , false
      , false
    };

    static const t_uint encoder_input_channels[2U] = {
      0
      , 1
    };

    static const t_encoder_quadrature_mode encoder_quadrature[2U] = {
      ENCODER_QUADRATURE_4X
      , ENCODER_QUADRATURE_4X
    };

    static const t_int32 initial_encoder_counts[2U] = {
      0
      , 0
    };

    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &communication_test_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(communication_test_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (communication_test_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal", 50);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(communication_test_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(communication_test_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(communication_test_M, _rt_error_message);
      return;
    }

    if (!is_switching) {
      result = hil_set_analog_input_ranges
        (communication_test_DW.HILInitialize_Card, analog_input_channels, 2U,
         analog_input_minimums, analog_input_maximums);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if (!is_switching) {
      result = hil_set_analog_output_ranges
        (communication_test_DW.HILInitialize_Card, analog_output_channels, 2U,
         analog_output_minimums, analog_output_maximums);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if (!is_switching) {
      result = hil_write_analog(communication_test_DW.HILInitialize_Card,
        analog_output_channels, 2U, initial_analog_outputs);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(communication_test_DW.HILInitialize_Card,
      NULL, 0U, digital_output_channels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(communication_test_M, _rt_error_message);
      return;
    }

    if (!is_switching) {
      result = hil_write_digital(communication_test_DW.HILInitialize_Card,
        digital_output_channels, 8U, (t_boolean *) initial_digital_outputs);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if (!is_switching) {
      result = hil_set_encoder_quadrature_mode
        (communication_test_DW.HILInitialize_Card, encoder_input_channels, 2U,
         (t_encoder_quadrature_mode *) encoder_quadrature);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if (!is_switching) {
      result = hil_set_encoder_counts(communication_test_DW.HILInitialize_Card,
        encoder_input_channels, 2U, initial_encoder_counts);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn' */
  communication_test_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1' */
  communication_test_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Q(s)' */
  communication_test_X.Qs_CSTATE[0] = 0.0;
  communication_test_X.Qs_CSTATE[1] = 0.0;
}

/* Model terminate function */
void communication_test_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S2>/HIL Initialize' */

  /* S-Function Block: communication_test/SRV02 Flexible Link/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    static const t_uint analog_output_channels[2U] = {
      0
      , 1
    };

    t_uint32 num_final_digital_outputs = 0;
    static const t_uint digital_output_channels[8U] = {
      0
      , 1
      , 2
      , 3
      , 4
      , 5
      , 6
      , 7
    };

    hil_task_stop_all(communication_test_DW.HILInitialize_Card);
    hil_monitor_stop_all(communication_test_DW.HILInitialize_Card);
    is_switching = false;
    if ((communication_test_P.HILInitialize_AOTerminate && !is_switching) ||
        (communication_test_P.HILInitialize_AOExit && is_switching)) {
      communication_test_DW.HILInitialize_AOVoltages[0] =
        communication_test_P.HILInitialize_AOFinal;
      communication_test_DW.HILInitialize_AOVoltages[1] =
        communication_test_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((communication_test_P.HILInitialize_DOTerminate && !is_switching) ||
        (communication_test_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &communication_test_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = communication_test_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 8U;
    } else {
      num_final_digital_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(communication_test_DW.HILInitialize_Card
                         , analog_output_channels, num_final_analog_outputs
                         , NULL, 0
                         , digital_output_channels, num_final_digital_outputs
                         , NULL, 0
                         , &communication_test_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &communication_test_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (communication_test_DW.HILInitialize_Card, analog_output_channels,
             num_final_analog_outputs,
             &communication_test_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (communication_test_DW.HILInitialize_Card, digital_output_channels,
             num_final_digital_outputs, (t_boolean *)
             &communication_test_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(communication_test_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(communication_test_DW.HILInitialize_Card);
    hil_monitor_delete_all(communication_test_DW.HILInitialize_Card);
    hil_close(communication_test_DW.HILInitialize_Card);
    communication_test_DW.HILInitialize_Card = NULL;
  }
}
