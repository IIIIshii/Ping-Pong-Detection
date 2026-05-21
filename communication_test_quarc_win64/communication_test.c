/*
 * communication_test.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "communication_test".
 *
 * Model version              : 1.4
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Fri May  8 16:19:48 2026
 *
 * Target selection: quarc_win64.tlc
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
#include "communication_test_dt.h"

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
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  communication_test_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  communication_test_output();
  communication_test_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  communication_test_output();
  communication_test_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  communication_test_output();
  communication_test_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void communication_test_output(void)
{
  real_T rtb_HILReadAnalog;
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
    rtb_HILReadAnalog = communication_test_P.reference_Value;

    /* Gain: '<S1>/Gain' */
    communication_test_B.Gain = communication_test_P.Gain_Gain *
      rtb_HILReadAnalog;
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
        rtb_HILReadAnalog = communication_test_DW.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<S2>/Encoder Calibration  (rad//count)' */
    communication_test_B.EncoderCalibrationradcount =
      communication_test_P.EncoderCalibrationradcount_Gain * rtb_HILReadAnalog;

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

      rtb_HILReadAnalog = communication_test_DW.HILReadAnalog_Buffer;
    }

    /* Gain: '<S2>/Strain Gage Calibration  (rad//V)' */
    communication_test_B.StrainGageCalibrationradV =
      communication_test_P.StrainGageCalibrationradV_Gain * rtb_HILReadAnalog;

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
}

/* Model update function */
void communication_test_update(void)
{
  if (rtmIsMajorTimeStep(communication_test_M)) {
    rt_ertODEUpdateContinuousStates(&communication_test_M->solverInfo);
  }

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
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++communication_test_M->Timing.clockTick1)) {
      ++communication_test_M->Timing.clockTickH1;
    }

    communication_test_M->Timing.t[1] = communication_test_M->Timing.clockTick1 *
      communication_test_M->Timing.stepSize1 +
      communication_test_M->Timing.clockTickH1 *
      communication_test_M->Timing.stepSize1 * 4294967296.0;
  }
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
  /* Start for S-Function (hil_initialize_block): '<S2>/HIL Initialize' */

  /* S-Function Block: communication_test/SRV02 Flexible Link/HIL Initialize (hil_initialize_block) */
  {
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

    if ((communication_test_P.HILInitialize_AIPStart && !is_switching) ||
        (communication_test_P.HILInitialize_AIPEnter && is_switching)) {
      communication_test_DW.HILInitialize_AIMinimums[0] =
        (communication_test_P.HILInitialize_AILow);
      communication_test_DW.HILInitialize_AIMinimums[1] =
        (communication_test_P.HILInitialize_AILow);
      communication_test_DW.HILInitialize_AIMaximums[0] =
        communication_test_P.HILInitialize_AIHigh;
      communication_test_DW.HILInitialize_AIMaximums[1] =
        communication_test_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (communication_test_DW.HILInitialize_Card,
         communication_test_P.HILInitialize_AIChannels, 2U,
         &communication_test_DW.HILInitialize_AIMinimums[0],
         &communication_test_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if ((communication_test_P.HILInitialize_AOPStart && !is_switching) ||
        (communication_test_P.HILInitialize_AOPEnter && is_switching)) {
      communication_test_DW.HILInitialize_AOMinimums[0] =
        (communication_test_P.HILInitialize_AOLow);
      communication_test_DW.HILInitialize_AOMinimums[1] =
        (communication_test_P.HILInitialize_AOLow);
      communication_test_DW.HILInitialize_AOMaximums[0] =
        communication_test_P.HILInitialize_AOHigh;
      communication_test_DW.HILInitialize_AOMaximums[1] =
        communication_test_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (communication_test_DW.HILInitialize_Card,
         communication_test_P.HILInitialize_AOChannels, 2U,
         &communication_test_DW.HILInitialize_AOMinimums[0],
         &communication_test_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if ((communication_test_P.HILInitialize_AOStart && !is_switching) ||
        (communication_test_P.HILInitialize_AOEnter && is_switching)) {
      communication_test_DW.HILInitialize_AOVoltages[0] =
        communication_test_P.HILInitialize_AOInitial;
      communication_test_DW.HILInitialize_AOVoltages[1] =
        communication_test_P.HILInitialize_AOInitial;
      result = hil_write_analog(communication_test_DW.HILInitialize_Card,
        communication_test_P.HILInitialize_AOChannels, 2U,
        &communication_test_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if (communication_test_P.HILInitialize_AOReset) {
      communication_test_DW.HILInitialize_AOVoltages[0] =
        communication_test_P.HILInitialize_AOWatchdog;
      communication_test_DW.HILInitialize_AOVoltages[1] =
        communication_test_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (communication_test_DW.HILInitialize_Card,
         communication_test_P.HILInitialize_AOChannels, 2U,
         &communication_test_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(communication_test_DW.HILInitialize_Card,
      NULL, 0U, communication_test_P.HILInitialize_DOChannels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(communication_test_M, _rt_error_message);
      return;
    }

    if ((communication_test_P.HILInitialize_DOStart && !is_switching) ||
        (communication_test_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &communication_test_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = communication_test_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(communication_test_DW.HILInitialize_Card,
        communication_test_P.HILInitialize_DOChannels, 8U, (t_boolean *)
        &communication_test_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if (communication_test_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &communication_test_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOStates[i1] = communication_test_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (communication_test_DW.HILInitialize_Card,
         communication_test_P.HILInitialize_DOChannels, 8U, (const
          t_digital_state *) &communication_test_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if ((communication_test_P.HILInitialize_EIPStart && !is_switching) ||
        (communication_test_P.HILInitialize_EIPEnter && is_switching)) {
      communication_test_DW.HILInitialize_QuadratureModes[0] =
        communication_test_P.HILInitialize_EIQuadrature;
      communication_test_DW.HILInitialize_QuadratureModes[1] =
        communication_test_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (communication_test_DW.HILInitialize_Card,
         communication_test_P.HILInitialize_EIChannels, 2U,
         (t_encoder_quadrature_mode *)
         &communication_test_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(communication_test_M, _rt_error_message);
        return;
      }
    }

    if ((communication_test_P.HILInitialize_EIStart && !is_switching) ||
        (communication_test_P.HILInitialize_EIEnter && is_switching)) {
      communication_test_DW.HILInitialize_InitialEICounts[0] =
        communication_test_P.HILInitialize_EIInitial;
      communication_test_DW.HILInitialize_InitialEICounts[1] =
        communication_test_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(communication_test_DW.HILInitialize_Card,
        communication_test_P.HILInitialize_EIChannels, 2U,
        &communication_test_DW.HILInitialize_InitialEICounts[0]);
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
    t_uint32 num_final_digital_outputs = 0;
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
                         , communication_test_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , communication_test_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
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
            (communication_test_DW.HILInitialize_Card,
             communication_test_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &communication_test_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (communication_test_DW.HILInitialize_Card,
             communication_test_P.HILInitialize_DOChannels,
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

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  communication_test_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  communication_test_update();
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
  communication_test_initialize();
}

void MdlTerminate(void)
{
  communication_test_terminate();
}

/* Registration function */
RT_MODEL_communication_test_T *communication_test(void)
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
  communication_test_M->intgData.y = communication_test_M->odeY;
  communication_test_M->intgData.f[0] = communication_test_M->odeF[0];
  communication_test_M->intgData.f[1] = communication_test_M->odeF[1];
  communication_test_M->intgData.f[2] = communication_test_M->odeF[2];
  communication_test_M->intgData.f[3] = communication_test_M->odeF[3];
  communication_test_M->contStates = ((real_T *) &communication_test_X);
  rtsiSetSolverData(&communication_test_M->solverInfo, (void *)
                    &communication_test_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&communication_test_M->solverInfo, false);
  rtsiSetSolverName(&communication_test_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = communication_test_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "communication_test_M points to
       static memory which is guaranteed to be non-NULL" */
    communication_test_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    communication_test_M->Timing.sampleTimes =
      (&communication_test_M->Timing.sampleTimesArray[0]);
    communication_test_M->Timing.offsetTimes =
      (&communication_test_M->Timing.offsetTimesArray[0]);

    /* task periods */
    communication_test_M->Timing.sampleTimes[0] = (0.0);
    communication_test_M->Timing.sampleTimes[1] = (0.033333333333333333);

    /* task offsets */
    communication_test_M->Timing.offsetTimes[0] = (0.0);
    communication_test_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(communication_test_M, &communication_test_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = communication_test_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    communication_test_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(communication_test_M, 40.0);
  communication_test_M->Timing.stepSize0 = 0.033333333333333333;
  communication_test_M->Timing.stepSize1 = 0.033333333333333333;

  /* External mode info */
  communication_test_M->Sizes.checksums[0] = (1624698350U);
  communication_test_M->Sizes.checksums[1] = (3284039564U);
  communication_test_M->Sizes.checksums[2] = (1076341121U);
  communication_test_M->Sizes.checksums[3] = (3870894U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    communication_test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(communication_test_M->extModeInfo,
      &communication_test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(communication_test_M->extModeInfo,
                        communication_test_M->Sizes.checksums);
    rteiSetTPtr(communication_test_M->extModeInfo, rtmGetTPtr
                (communication_test_M));
  }

  communication_test_M->solverInfoPtr = (&communication_test_M->solverInfo);
  communication_test_M->Timing.stepSize = (0.033333333333333333);
  rtsiSetFixedStepSize(&communication_test_M->solverInfo, 0.033333333333333333);
  rtsiSetSolverMode(&communication_test_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  communication_test_M->blockIO = ((void *) &communication_test_B);
  (void) memset(((void *) &communication_test_B), 0,
                sizeof(B_communication_test_T));

  /* parameters */
  communication_test_M->defaultParam = ((real_T *)&communication_test_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &communication_test_X;
    communication_test_M->contStates = (x);
    (void) memset((void *)&communication_test_X, 0,
                  sizeof(X_communication_test_T));
  }

  /* states (dwork) */
  communication_test_M->dwork = ((void *) &communication_test_DW);
  (void) memset((void *)&communication_test_DW, 0,
                sizeof(DW_communication_test_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    communication_test_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 21;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  communication_test_M->Sizes.numContStates = (4);/* Number of continuous states */
  communication_test_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  communication_test_M->Sizes.numY = (0);/* Number of model outputs */
  communication_test_M->Sizes.numU = (0);/* Number of model inputs */
  communication_test_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  communication_test_M->Sizes.numSampTimes = (2);/* Number of sample times */
  communication_test_M->Sizes.numBlocks = (23);/* Number of blocks */
  communication_test_M->Sizes.numBlockIO = (6);/* Number of block outputs */
  communication_test_M->Sizes.numBlockPrms = (107);/* Sum of parameter "widths" */
  return communication_test_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
