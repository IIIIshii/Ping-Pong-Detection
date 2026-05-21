/*
 * system_step_input.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "system_step_input".
 *
 * Model version              : 11.15
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Fri May  8 18:08:54 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "system_step_input.h"
#include "rtwtypes.h"
#include "system_step_input_private.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "system_step_input_dt.h"

/* Block signals (default storage) */
B_system_step_input_T system_step_input_B;

/* Continuous states */
X_system_step_input_T system_step_input_X;

/* Block states (default storage) */
DW_system_step_input_T system_step_input_DW;

/* Real-time model */
static RT_MODEL_system_step_input_T system_step_input_M_;
RT_MODEL_system_step_input_T *const system_step_input_M = &system_step_input_M_;

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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  system_step_input_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void system_step_input_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadAnalog;
  real_T rtb_HILReadEncoder;
  real_T u0;
  if (rtmIsMajorTimeStep(system_step_input_M)) {
    /* set solver stop time */
    if (!(system_step_input_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&system_step_input_M->solverInfo,
                            ((system_step_input_M->Timing.clockTickH0 + 1) *
        system_step_input_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&system_step_input_M->solverInfo,
                            ((system_step_input_M->Timing.clockTick0 + 1) *
        system_step_input_M->Timing.stepSize0 +
        system_step_input_M->Timing.clockTickH0 *
        system_step_input_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(system_step_input_M)) {
    system_step_input_M->Timing.t[0] = rtsiGetT(&system_step_input_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(system_step_input_M)) {
    /* Gain: '<S1>/Gain' incorporates:
     *  Constant: '<Root>/reference'
     */
    system_step_input_B.Gain = system_step_input_P.Gain_Gain *
      system_step_input_P.reference_Value;
  }

  /* TransferFcn: '<S1>/Transfer Fcn' */
  system_step_input_B.TransferFcn = system_step_input_P.TransferFcn_C *
    system_step_input_X.TransferFcn_CSTATE;
  system_step_input_B.TransferFcn += system_step_input_P.TransferFcn_D *
    system_step_input_B.Gain;

  /* Gain: '<S4>/Direction Convention: (Right-Hand) system' incorporates:
   *  TransferFcn: '<S1>/Transfer Fcn1'
   */
  u0 = (system_step_input_P.TransferFcn1_C *
        system_step_input_X.TransferFcn1_CSTATE +
        system_step_input_P.TransferFcn1_D * system_step_input_B.TransferFcn) *
    system_step_input_P.DirectionConventionRightHandsys;

  /* Saturate: '<S4>/Amplifier Saturation (V)' */
  if (u0 > system_step_input_P.AmplifierSaturationV_UpperSat) {
    u0 = system_step_input_P.AmplifierSaturationV_UpperSat;
  } else if (u0 < system_step_input_P.AmplifierSaturationV_LowerSat) {
    u0 = system_step_input_P.AmplifierSaturationV_LowerSat;
  }

  /* Gain: '<S4>/Inverse Amplifier  Gain (V//V)' incorporates:
   *  Saturate: '<S4>/Amplifier Saturation (V)'
   */
  u0 *= system_step_input_P.InverseAmplifierGainVV_Gain;

  /* Saturate: '<S4>/DACB Saturation (V)' */
  if (u0 > system_step_input_P.DACBSaturationV_UpperSat) {
    /* Saturate: '<S4>/DACB Saturation (V)' */
    system_step_input_B.DACBSaturationV =
      system_step_input_P.DACBSaturationV_UpperSat;
  } else if (u0 < system_step_input_P.DACBSaturationV_LowerSat) {
    /* Saturate: '<S4>/DACB Saturation (V)' */
    system_step_input_B.DACBSaturationV =
      system_step_input_P.DACBSaturationV_LowerSat;
  } else {
    /* Saturate: '<S4>/DACB Saturation (V)' */
    system_step_input_B.DACBSaturationV = u0;
  }

  /* End of Saturate: '<S4>/DACB Saturation (V)' */
  if (rtmIsMajorTimeStep(system_step_input_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: system_step_input/SRV02 Flexible Link/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(system_step_input_DW.HILInitialize_Card,
        &system_step_input_P.HILWriteAnalog_channels, 1,
        &system_step_input_B.DACBSaturationV);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      }
    }

    /* S-Function (hil_write_digital_block): '<S2>/HIL Write Digital' incorporates:
     *  Constant: '<S2>/Enable VoltPAQ-X2,X4'
     */

    /* S-Function Block: system_step_input/SRV02 Flexible Link/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      system_step_input_DW.HILWriteDigital_Buffer[0] =
        (system_step_input_P.EnableVoltPAQX2X4_Value[0] != 0);
      system_step_input_DW.HILWriteDigital_Buffer[1] =
        (system_step_input_P.EnableVoltPAQX2X4_Value[1] != 0);
      system_step_input_DW.HILWriteDigital_Buffer[2] =
        (system_step_input_P.EnableVoltPAQX2X4_Value[2] != 0);
      system_step_input_DW.HILWriteDigital_Buffer[3] =
        (system_step_input_P.EnableVoltPAQX2X4_Value[3] != 0);
      result = hil_write_digital(system_step_input_DW.HILInitialize_Card,
        system_step_input_P.HILWriteDigital_channels, 4,
        &system_step_input_DW.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      }
    }

    /* S-Function (hil_read_analog_block): '<S2>/HIL Read Analog' */

    /* S-Function Block: system_step_input/SRV02 Flexible Link/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog(system_step_input_DW.HILInitialize_Card,
        &system_step_input_P.HILReadAnalog_channels, 1,
        &system_step_input_DW.HILReadAnalog_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      }

      rtb_HILReadAnalog = system_step_input_DW.HILReadAnalog_Buffer;
    }

    /* S-Function (hil_read_encoder_block): '<S2>/HIL Read Encoder' */

    /* S-Function Block: system_step_input/SRV02 Flexible Link/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(system_step_input_DW.HILInitialize_Card,
        &system_step_input_P.HILReadEncoder_channels, 1,
        &system_step_input_DW.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder = system_step_input_DW.HILReadEncoder_Buffer;
      }
    }
  }
}

/* Model update function */
void system_step_input_update(void)
{
  if (rtmIsMajorTimeStep(system_step_input_M)) {
    rt_ertODEUpdateContinuousStates(&system_step_input_M->solverInfo);
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
  if (!(++system_step_input_M->Timing.clockTick0)) {
    ++system_step_input_M->Timing.clockTickH0;
  }

  system_step_input_M->Timing.t[0] = rtsiGetSolverStopTime
    (&system_step_input_M->solverInfo);

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
    if (!(++system_step_input_M->Timing.clockTick1)) {
      ++system_step_input_M->Timing.clockTickH1;
    }

    system_step_input_M->Timing.t[1] = system_step_input_M->Timing.clockTick1 *
      system_step_input_M->Timing.stepSize1 +
      system_step_input_M->Timing.clockTickH1 *
      system_step_input_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void system_step_input_derivatives(void)
{
  XDot_system_step_input_T *_rtXdot;
  _rtXdot = ((XDot_system_step_input_T *) system_step_input_M->derivs);

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = system_step_input_P.TransferFcn_A *
    system_step_input_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += system_step_input_B.Gain;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = system_step_input_P.TransferFcn1_A *
    system_step_input_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += system_step_input_B.TransferFcn;
}

/* Model initialize function */
void system_step_input_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S2>/HIL Initialize' */

  /* S-Function Block: system_step_input/SRV02 Flexible Link/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &system_step_input_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (system_step_input_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal", 50);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(system_step_input_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      return;
    }

    if ((system_step_input_P.HILInitialize_AIPStart && !is_switching) ||
        (system_step_input_P.HILInitialize_AIPEnter && is_switching)) {
      system_step_input_DW.HILInitialize_AIMinimums[0] =
        (system_step_input_P.HILInitialize_AILow);
      system_step_input_DW.HILInitialize_AIMinimums[1] =
        (system_step_input_P.HILInitialize_AILow);
      system_step_input_DW.HILInitialize_AIMaximums[0] =
        system_step_input_P.HILInitialize_AIHigh;
      system_step_input_DW.HILInitialize_AIMaximums[1] =
        system_step_input_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (system_step_input_DW.HILInitialize_Card,
         system_step_input_P.HILInitialize_AIChannels, 2U,
         &system_step_input_DW.HILInitialize_AIMinimums[0],
         &system_step_input_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }

    if ((system_step_input_P.HILInitialize_AOPStart && !is_switching) ||
        (system_step_input_P.HILInitialize_AOPEnter && is_switching)) {
      system_step_input_DW.HILInitialize_AOMinimums[0] =
        (system_step_input_P.HILInitialize_AOLow);
      system_step_input_DW.HILInitialize_AOMinimums[1] =
        (system_step_input_P.HILInitialize_AOLow);
      system_step_input_DW.HILInitialize_AOMaximums[0] =
        system_step_input_P.HILInitialize_AOHigh;
      system_step_input_DW.HILInitialize_AOMaximums[1] =
        system_step_input_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (system_step_input_DW.HILInitialize_Card,
         system_step_input_P.HILInitialize_AOChannels, 2U,
         &system_step_input_DW.HILInitialize_AOMinimums[0],
         &system_step_input_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }

    if ((system_step_input_P.HILInitialize_AOStart && !is_switching) ||
        (system_step_input_P.HILInitialize_AOEnter && is_switching)) {
      system_step_input_DW.HILInitialize_AOVoltages[0] =
        system_step_input_P.HILInitialize_AOInitial;
      system_step_input_DW.HILInitialize_AOVoltages[1] =
        system_step_input_P.HILInitialize_AOInitial;
      result = hil_write_analog(system_step_input_DW.HILInitialize_Card,
        system_step_input_P.HILInitialize_AOChannels, 2U,
        &system_step_input_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }

    if (system_step_input_P.HILInitialize_AOReset) {
      system_step_input_DW.HILInitialize_AOVoltages[0] =
        system_step_input_P.HILInitialize_AOWatchdog;
      system_step_input_DW.HILInitialize_AOVoltages[1] =
        system_step_input_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (system_step_input_DW.HILInitialize_Card,
         system_step_input_P.HILInitialize_AOChannels, 2U,
         &system_step_input_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(system_step_input_DW.HILInitialize_Card,
      NULL, 0U, system_step_input_P.HILInitialize_DOChannels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(system_step_input_M, _rt_error_message);
      return;
    }

    if ((system_step_input_P.HILInitialize_DOStart && !is_switching) ||
        (system_step_input_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &system_step_input_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = system_step_input_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(system_step_input_DW.HILInitialize_Card,
        system_step_input_P.HILInitialize_DOChannels, 8U, (t_boolean *)
        &system_step_input_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }

    if (system_step_input_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &system_step_input_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOStates[i1] = system_step_input_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (system_step_input_DW.HILInitialize_Card,
         system_step_input_P.HILInitialize_DOChannels, 8U, (const
          t_digital_state *) &system_step_input_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }

    if ((system_step_input_P.HILInitialize_EIPStart && !is_switching) ||
        (system_step_input_P.HILInitialize_EIPEnter && is_switching)) {
      system_step_input_DW.HILInitialize_QuadratureModes[0] =
        system_step_input_P.HILInitialize_EIQuadrature;
      system_step_input_DW.HILInitialize_QuadratureModes[1] =
        system_step_input_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (system_step_input_DW.HILInitialize_Card,
         system_step_input_P.HILInitialize_EIChannels, 2U,
         (t_encoder_quadrature_mode *)
         &system_step_input_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }

    if ((system_step_input_P.HILInitialize_EIStart && !is_switching) ||
        (system_step_input_P.HILInitialize_EIEnter && is_switching)) {
      system_step_input_DW.HILInitialize_InitialEICounts[0] =
        system_step_input_P.HILInitialize_EIInitial;
      system_step_input_DW.HILInitialize_InitialEICounts[1] =
        system_step_input_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(system_step_input_DW.HILInitialize_Card,
        system_step_input_P.HILInitialize_EIChannels, 2U,
        &system_step_input_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn' */
  system_step_input_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1' */
  system_step_input_X.TransferFcn1_CSTATE = 0.0;
}

/* Model terminate function */
void system_step_input_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S2>/HIL Initialize' */

  /* S-Function Block: system_step_input/SRV02 Flexible Link/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(system_step_input_DW.HILInitialize_Card);
    hil_monitor_stop_all(system_step_input_DW.HILInitialize_Card);
    is_switching = false;
    if ((system_step_input_P.HILInitialize_AOTerminate && !is_switching) ||
        (system_step_input_P.HILInitialize_AOExit && is_switching)) {
      system_step_input_DW.HILInitialize_AOVoltages[0] =
        system_step_input_P.HILInitialize_AOFinal;
      system_step_input_DW.HILInitialize_AOVoltages[1] =
        system_step_input_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((system_step_input_P.HILInitialize_DOTerminate && !is_switching) ||
        (system_step_input_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &system_step_input_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = system_step_input_P.HILInitialize_DOFinal;
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
      result = hil_write(system_step_input_DW.HILInitialize_Card
                         , system_step_input_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , system_step_input_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &system_step_input_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &system_step_input_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (system_step_input_DW.HILInitialize_Card,
             system_step_input_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &system_step_input_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (system_step_input_DW.HILInitialize_Card,
             system_step_input_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &system_step_input_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(system_step_input_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(system_step_input_DW.HILInitialize_Card);
    hil_monitor_delete_all(system_step_input_DW.HILInitialize_Card);
    hil_close(system_step_input_DW.HILInitialize_Card);
    system_step_input_DW.HILInitialize_Card = NULL;
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
  system_step_input_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  system_step_input_update();
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
  system_step_input_initialize();
}

void MdlTerminate(void)
{
  system_step_input_terminate();
}

/* Registration function */
RT_MODEL_system_step_input_T *system_step_input(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)system_step_input_M, 0,
                sizeof(RT_MODEL_system_step_input_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&system_step_input_M->solverInfo,
                          &system_step_input_M->Timing.simTimeStep);
    rtsiSetTPtr(&system_step_input_M->solverInfo, &rtmGetTPtr
                (system_step_input_M));
    rtsiSetStepSizePtr(&system_step_input_M->solverInfo,
                       &system_step_input_M->Timing.stepSize0);
    rtsiSetdXPtr(&system_step_input_M->solverInfo, &system_step_input_M->derivs);
    rtsiSetContStatesPtr(&system_step_input_M->solverInfo, (real_T **)
                         &system_step_input_M->contStates);
    rtsiSetNumContStatesPtr(&system_step_input_M->solverInfo,
      &system_step_input_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&system_step_input_M->solverInfo,
      &system_step_input_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&system_step_input_M->solverInfo,
      &system_step_input_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&system_step_input_M->solverInfo,
      &system_step_input_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&system_step_input_M->solverInfo, (&rtmGetErrorStatus
      (system_step_input_M)));
    rtsiSetRTModelPtr(&system_step_input_M->solverInfo, system_step_input_M);
  }

  rtsiSetSimTimeStep(&system_step_input_M->solverInfo, MAJOR_TIME_STEP);
  system_step_input_M->intgData.f[0] = system_step_input_M->odeF[0];
  system_step_input_M->contStates = ((real_T *) &system_step_input_X);
  rtsiSetSolverData(&system_step_input_M->solverInfo, (void *)
                    &system_step_input_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&system_step_input_M->solverInfo, false);
  rtsiSetSolverName(&system_step_input_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = system_step_input_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "system_step_input_M points to
       static memory which is guaranteed to be non-NULL" */
    system_step_input_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    system_step_input_M->Timing.sampleTimes =
      (&system_step_input_M->Timing.sampleTimesArray[0]);
    system_step_input_M->Timing.offsetTimes =
      (&system_step_input_M->Timing.offsetTimesArray[0]);

    /* task periods */
    system_step_input_M->Timing.sampleTimes[0] = (0.0);
    system_step_input_M->Timing.sampleTimes[1] = (0.033333333333333333);

    /* task offsets */
    system_step_input_M->Timing.offsetTimes[0] = (0.0);
    system_step_input_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(system_step_input_M, &system_step_input_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = system_step_input_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    system_step_input_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(system_step_input_M, 70.0);
  system_step_input_M->Timing.stepSize0 = 0.033333333333333333;
  system_step_input_M->Timing.stepSize1 = 0.033333333333333333;

  /* External mode info */
  system_step_input_M->Sizes.checksums[0] = (2476734403U);
  system_step_input_M->Sizes.checksums[1] = (3128754689U);
  system_step_input_M->Sizes.checksums[2] = (1407867604U);
  system_step_input_M->Sizes.checksums[3] = (3168085007U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    system_step_input_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(system_step_input_M->extModeInfo,
      &system_step_input_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(system_step_input_M->extModeInfo,
                        system_step_input_M->Sizes.checksums);
    rteiSetTPtr(system_step_input_M->extModeInfo, rtmGetTPtr(system_step_input_M));
  }

  system_step_input_M->solverInfoPtr = (&system_step_input_M->solverInfo);
  system_step_input_M->Timing.stepSize = (0.033333333333333333);
  rtsiSetFixedStepSize(&system_step_input_M->solverInfo, 0.033333333333333333);
  rtsiSetSolverMode(&system_step_input_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  system_step_input_M->blockIO = ((void *) &system_step_input_B);
  (void) memset(((void *) &system_step_input_B), 0,
                sizeof(B_system_step_input_T));

  /* parameters */
  system_step_input_M->defaultParam = ((real_T *)&system_step_input_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &system_step_input_X;
    system_step_input_M->contStates = (x);
    (void) memset((void *)&system_step_input_X, 0,
                  sizeof(X_system_step_input_T));
  }

  /* states (dwork) */
  system_step_input_M->dwork = ((void *) &system_step_input_DW);
  (void) memset((void *)&system_step_input_DW, 0,
                sizeof(DW_system_step_input_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    system_step_input_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 21;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  system_step_input_M->Sizes.numContStates = (2);/* Number of continuous states */
  system_step_input_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  system_step_input_M->Sizes.numY = (0);/* Number of model outputs */
  system_step_input_M->Sizes.numU = (0);/* Number of model inputs */
  system_step_input_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  system_step_input_M->Sizes.numSampTimes = (2);/* Number of sample times */
  system_step_input_M->Sizes.numBlocks = (16);/* Number of blocks */
  system_step_input_M->Sizes.numBlockIO = (3);/* Number of block outputs */
  system_step_input_M->Sizes.numBlockPrms = (100);/* Sum of parameter "widths" */
  return system_step_input_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
