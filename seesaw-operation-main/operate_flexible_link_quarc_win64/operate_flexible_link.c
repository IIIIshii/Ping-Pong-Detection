/*
 * operate_flexible_link.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "operate_flexible_link".
 *
 * Model version              : 11.150
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Fri May 22 18:19:13 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "operate_flexible_link.h"
#include "rtwtypes.h"
#include <math.h>
#include "operate_flexible_link_private.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "operate_flexible_link_dt.h"

/* Named constants for MATLAB Function: '<Root>/MATLAB Function' */
#define operate_flexible_lin_CALL_EVENT (-1)

/* Block signals (default storage) */
B_operate_flexible_link_T operate_flexible_link_B;

/* Continuous states */
X_operate_flexible_link_T operate_flexible_link_X;

/* Block states (default storage) */
DW_operate_flexible_link_T operate_flexible_link_DW;

/* Real-time model */
static RT_MODEL_operate_flexible_lin_T operate_flexible_link_M_;
RT_MODEL_operate_flexible_lin_T *const operate_flexible_link_M =
  &operate_flexible_link_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 * 0 - success
 * 1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

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
  int_T nXc = 8;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  operate_flexible_link_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void operate_flexible_link_output(void)
{
  real_T u0;
  real_T u1;
  real_T u2;
  if (rtmIsMajorTimeStep(operate_flexible_link_M)) {
    /* set solver stop time */
    if (!(operate_flexible_link_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&operate_flexible_link_M->solverInfo,
                            ((operate_flexible_link_M->Timing.clockTickH0 + 1) *
        operate_flexible_link_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&operate_flexible_link_M->solverInfo,
                            ((operate_flexible_link_M->Timing.clockTick0 + 1) *
        operate_flexible_link_M->Timing.stepSize0 +
        operate_flexible_link_M->Timing.clockTickH0 *
        operate_flexible_link_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(operate_flexible_link_M)) {
    operate_flexible_link_M->Timing.t[0] = rtsiGetT
      (&operate_flexible_link_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(operate_flexible_link_M)) {
    /* S-Function (hil_read_encoder_block): '<S4>/HIL Read Encoder' */

    /* S-Function Block: operate_flexible_link/SRV02 Flexible Link/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder
        (operate_flexible_link_DW.HILInitialize_Card,
         &operate_flexible_link_P.HILReadEncoder_channels, 1,
         &operate_flexible_link_DW.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      } else {
        operate_flexible_link_B.HILReadEncoder =
          operate_flexible_link_DW.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<S4>/Encoder Calibration  (rad//count)' */
    operate_flexible_link_B.EncoderCalibrationradcount =
      operate_flexible_link_P.EncoderCalibrationradcount_Gain *
      operate_flexible_link_B.HILReadEncoder;

    /* Constant: '<Root>/pos' */
    operate_flexible_link_B.pos = operate_flexible_link_P.pos_Value;

    /* Sum: '<Root>/Subtract' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    operate_flexible_link_B.Subtract = operate_flexible_link_P.Constant2_Value -
      operate_flexible_link_B.pos;

    /* Gain: '<Root>/Gain4' */
    operate_flexible_link_B.Gain4 = operate_flexible_link_P.Gain4_Gain *
      operate_flexible_link_B.Subtract;
  }

  /* TransferFcn: '<Root>/Transfer Fcn1' */
  operate_flexible_link_B.TransferFcn1 = operate_flexible_link_P.TransferFcn1_C *
    operate_flexible_link_X.TransferFcn1_CSTATE;
  operate_flexible_link_B.TransferFcn1 += operate_flexible_link_P.TransferFcn1_D
    * operate_flexible_link_B.Gain4;

  /* Gain: '<Root>/Gain3' */
  operate_flexible_link_B.Gain3 = operate_flexible_link_P.Gain3_Gain *
    operate_flexible_link_B.TransferFcn1;

  /* TransferFcn: '<Root>/Transfer Fcn3' */
  operate_flexible_link_B.TransferFcn3 = operate_flexible_link_P.TransferFcn3_C *
    operate_flexible_link_X.TransferFcn3_CSTATE;
  operate_flexible_link_B.TransferFcn3 += operate_flexible_link_P.TransferFcn3_D
    * operate_flexible_link_B.Gain3;

  /* Gain: '<Root>/Gain5' */
  operate_flexible_link_B.Gain5 = operate_flexible_link_P.Gain5_Gain *
    operate_flexible_link_B.TransferFcn1;

  /* MATLAB Function: '<Root>/MATLAB Function' */
  operate_flexible_link_DW.sfEvent = operate_flexible_lin_CALL_EVENT;
  if ((operate_flexible_link_B.TransferFcn3 * operate_flexible_link_B.Gain5 >
       0.0) && (fabs(operate_flexible_link_B.TransferFcn3) >= fabs
                (operate_flexible_link_B.Gain5))) {
    operate_flexible_link_B.y_c = operate_flexible_link_B.Gain5;
  } else {
    operate_flexible_link_B.y_c = operate_flexible_link_B.TransferFcn3;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* Sum: '<Root>/Subtract1' */
  operate_flexible_link_B.Subtract1 = operate_flexible_link_B.y_c -
    operate_flexible_link_B.EncoderCalibrationradcount;

  /* Gain: '<Root>/Gain2' */
  operate_flexible_link_B.Gain2 = operate_flexible_link_P.Gain2_Gain *
    operate_flexible_link_B.Subtract1;

  /* Gain: '<S5>/Direction Convention: (Right-Hand) system' */
  operate_flexible_link_B.DirectionConventionRightHandsys =
    operate_flexible_link_P.DirectionConventionRightHandsys *
    operate_flexible_link_B.Gain2;

  /* Saturate: '<S5>/Amplifier Saturation (V)' */
  u0 = operate_flexible_link_B.DirectionConventionRightHandsys;
  u1 = operate_flexible_link_P.AmplifierSaturationV_LowerSat;
  u2 = operate_flexible_link_P.AmplifierSaturationV_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<S5>/Amplifier Saturation (V)' */
    operate_flexible_link_B.AmplifierSaturationV = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S5>/Amplifier Saturation (V)' */
    operate_flexible_link_B.AmplifierSaturationV = u1;
  } else {
    /* Saturate: '<S5>/Amplifier Saturation (V)' */
    operate_flexible_link_B.AmplifierSaturationV = u0;
  }

  /* End of Saturate: '<S5>/Amplifier Saturation (V)' */

  /* Gain: '<S5>/Inverse Amplifier  Gain (V//V)' */
  operate_flexible_link_B.InverseAmplifierGainVV =
    operate_flexible_link_P.InverseAmplifierGainVV_Gain *
    operate_flexible_link_B.AmplifierSaturationV;

  /* Saturate: '<S5>/DACB Saturation (V)' */
  u0 = operate_flexible_link_B.InverseAmplifierGainVV;
  u1 = operate_flexible_link_P.DACBSaturationV_LowerSat;
  u2 = operate_flexible_link_P.DACBSaturationV_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<S5>/DACB Saturation (V)' */
    operate_flexible_link_B.DACBSaturationV = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S5>/DACB Saturation (V)' */
    operate_flexible_link_B.DACBSaturationV = u1;
  } else {
    /* Saturate: '<S5>/DACB Saturation (V)' */
    operate_flexible_link_B.DACBSaturationV = u0;
  }

  /* End of Saturate: '<S5>/DACB Saturation (V)' */
  if (rtmIsMajorTimeStep(operate_flexible_link_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: operate_flexible_link/SRV02 Flexible Link/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(operate_flexible_link_DW.HILInitialize_Card,
        &operate_flexible_link_P.HILWriteAnalog_channels, 1,
        &operate_flexible_link_B.DACBSaturationV);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      }
    }

    /* S-Function (hil_write_digital_block): '<S4>/HIL Write Digital' incorporates:
     *  Constant: '<S4>/Enable VoltPAQ-X2,X4'
     */

    /* S-Function Block: operate_flexible_link/SRV02 Flexible Link/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      operate_flexible_link_DW.HILWriteDigital_Buffer[0] =
        (operate_flexible_link_P.EnableVoltPAQX2X4_Value[0] != 0);
      operate_flexible_link_DW.HILWriteDigital_Buffer[1] =
        (operate_flexible_link_P.EnableVoltPAQX2X4_Value[1] != 0);
      operate_flexible_link_DW.HILWriteDigital_Buffer[2] =
        (operate_flexible_link_P.EnableVoltPAQX2X4_Value[2] != 0);
      operate_flexible_link_DW.HILWriteDigital_Buffer[3] =
        (operate_flexible_link_P.EnableVoltPAQX2X4_Value[3] != 0);
      result = hil_write_digital(operate_flexible_link_DW.HILInitialize_Card,
        operate_flexible_link_P.HILWriteDigital_channels, 4,
        &operate_flexible_link_DW.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      }
    }

    /* S-Function (hil_read_analog_block): '<S4>/HIL Read Analog' */

    /* S-Function Block: operate_flexible_link/SRV02 Flexible Link/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog
        (operate_flexible_link_DW.HILInitialize_Card,
         &operate_flexible_link_P.HILReadAnalog_channels, 1,
         &operate_flexible_link_DW.HILReadAnalog_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      }

      operate_flexible_link_B.HILReadAnalog =
        operate_flexible_link_DW.HILReadAnalog_Buffer;
    }

    /* ToFile: '<Root>/To File' */
    {
      if (!(++operate_flexible_link_DW.ToFile_IWORK.Decimation % 1) &&
          (operate_flexible_link_DW.ToFile_IWORK.Count * (1 + 1)) + 1 <
          100000000 ) {
        FILE *fp = (FILE *) operate_flexible_link_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          operate_flexible_link_DW.ToFile_IWORK.Decimation = 0;
          u[0] = operate_flexible_link_M->Timing.t[1];
          u[1] = operate_flexible_link_B.pos;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(operate_flexible_link_M,
                              "Error writing to MAT-file result.mat");
            return;
          }

          if (((++operate_flexible_link_DW.ToFile_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file result.mat.\n");
          }
        }
      }
    }
  }

  /* Step: '<Root>/Step' */
  u0 = operate_flexible_link_M->Timing.t[0];
  if (u0 < operate_flexible_link_P.Step_Time) {
    /* Step: '<Root>/Step' */
    operate_flexible_link_B.Step = operate_flexible_link_P.Step_Y0;
  } else {
    /* Step: '<Root>/Step' */
    operate_flexible_link_B.Step = operate_flexible_link_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Gain: '<Root>/Gain1' */
  operate_flexible_link_B.Gain1 = operate_flexible_link_P.Gain1_Gain *
    operate_flexible_link_B.Step;

  /* TransferFcn: '<Root>/Transfer Fcn2' */
  operate_flexible_link_B.TransferFcn2 = operate_flexible_link_P.TransferFcn2_C *
    operate_flexible_link_X.TransferFcn2_CSTATE;
  if (rtmIsMajorTimeStep(operate_flexible_link_M)) {
    /* Gain: '<S1>/Gain' */
    operate_flexible_link_B.Gain = operate_flexible_link_P.Gain_Gain * 0.0;

    /* Gain: '<S1>/Gain1' */
    operate_flexible_link_B.Gain1_p = operate_flexible_link_P.Gain1_Gain_b *
      operate_flexible_link_B.Gain;
  }

  /* TransferFcn: '<S1>/Transfer Fcn' */
  operate_flexible_link_B.TransferFcn = operate_flexible_link_P.TransferFcn_C *
    operate_flexible_link_X.TransferFcn_CSTATE;
  operate_flexible_link_B.TransferFcn += operate_flexible_link_P.TransferFcn_D *
    operate_flexible_link_B.Gain1_p;

  /* TransferFcn: '<S1>/Transfer Fcn1' */
  operate_flexible_link_B.TransferFcn1_d =
    operate_flexible_link_P.TransferFcn1_C_c *
    operate_flexible_link_X.TransferFcn1_CSTATE_f;
  operate_flexible_link_B.TransferFcn1_d +=
    operate_flexible_link_P.TransferFcn1_D_i *
    operate_flexible_link_B.TransferFcn;

  /* TransferFcn: '<S1>/Transfer Fcn2' */
  operate_flexible_link_B.TransferFcn2_i =
    operate_flexible_link_P.TransferFcn2_C_m *
    operate_flexible_link_X.TransferFcn2_CSTATE_k;

  /* TransferFcn: '<Root>/Q(s)' */
  operate_flexible_link_B.y = operate_flexible_link_P.Qs_C[0] *
    operate_flexible_link_X.Qs_CSTATE[0];
  operate_flexible_link_B.y += operate_flexible_link_P.Qs_C[1] *
    operate_flexible_link_X.Qs_CSTATE[1];
}

/* Model update function */
void operate_flexible_link_update(void)
{
  if (rtmIsMajorTimeStep(operate_flexible_link_M)) {
    rt_ertODEUpdateContinuousStates(&operate_flexible_link_M->solverInfo);
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
  if (!(++operate_flexible_link_M->Timing.clockTick0)) {
    ++operate_flexible_link_M->Timing.clockTickH0;
  }

  operate_flexible_link_M->Timing.t[0] = rtsiGetSolverStopTime
    (&operate_flexible_link_M->solverInfo);

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
    if (!(++operate_flexible_link_M->Timing.clockTick1)) {
      ++operate_flexible_link_M->Timing.clockTickH1;
    }

    operate_flexible_link_M->Timing.t[1] =
      operate_flexible_link_M->Timing.clockTick1 *
      operate_flexible_link_M->Timing.stepSize1 +
      operate_flexible_link_M->Timing.clockTickH1 *
      operate_flexible_link_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void operate_flexible_link_derivatives(void)
{
  XDot_operate_flexible_link_T *_rtXdot;
  _rtXdot = ((XDot_operate_flexible_link_T *) operate_flexible_link_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = operate_flexible_link_P.TransferFcn1_A *
    operate_flexible_link_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += operate_flexible_link_B.Gain4;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn3' */
  _rtXdot->TransferFcn3_CSTATE = operate_flexible_link_P.TransferFcn3_A *
    operate_flexible_link_X.TransferFcn3_CSTATE;
  _rtXdot->TransferFcn3_CSTATE += operate_flexible_link_B.Gain3;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE = operate_flexible_link_P.TransferFcn2_A *
    operate_flexible_link_X.TransferFcn2_CSTATE;
  _rtXdot->TransferFcn2_CSTATE += operate_flexible_link_B.Gain1;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = operate_flexible_link_P.TransferFcn_A *
    operate_flexible_link_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += operate_flexible_link_B.Gain1_p;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE_f = operate_flexible_link_P.TransferFcn1_A_p *
    operate_flexible_link_X.TransferFcn1_CSTATE_f;
  _rtXdot->TransferFcn1_CSTATE_f += operate_flexible_link_B.TransferFcn;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE_k = operate_flexible_link_P.TransferFcn2_A_b *
    operate_flexible_link_X.TransferFcn2_CSTATE_k;
  _rtXdot->TransferFcn2_CSTATE_k += operate_flexible_link_B.TransferFcn1_d;

  /* Derivatives for TransferFcn: '<Root>/Q(s)' */
  _rtXdot->Qs_CSTATE[0] = operate_flexible_link_P.Qs_A[0] *
    operate_flexible_link_X.Qs_CSTATE[0];
  _rtXdot->Qs_CSTATE[0] += operate_flexible_link_P.Qs_A[1] *
    operate_flexible_link_X.Qs_CSTATE[1];
  _rtXdot->Qs_CSTATE[1] = operate_flexible_link_X.Qs_CSTATE[0];
}

/* Model initialize function */
void operate_flexible_link_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S4>/HIL Initialize' */

  /* S-Function Block: operate_flexible_link/SRV02 Flexible Link/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0",
                      &operate_flexible_link_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (operate_flexible_link_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal", 50);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(operate_flexible_link_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      return;
    }

    if ((operate_flexible_link_P.HILInitialize_AIPStart && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_AIPEnter && is_switching)) {
      operate_flexible_link_DW.HILInitialize_AIMinimums[0] =
        (operate_flexible_link_P.HILInitialize_AILow);
      operate_flexible_link_DW.HILInitialize_AIMinimums[1] =
        (operate_flexible_link_P.HILInitialize_AILow);
      operate_flexible_link_DW.HILInitialize_AIMaximums[0] =
        operate_flexible_link_P.HILInitialize_AIHigh;
      operate_flexible_link_DW.HILInitialize_AIMaximums[1] =
        operate_flexible_link_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (operate_flexible_link_DW.HILInitialize_Card,
         operate_flexible_link_P.HILInitialize_AIChannels, 2U,
         &operate_flexible_link_DW.HILInitialize_AIMinimums[0],
         &operate_flexible_link_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }

    if ((operate_flexible_link_P.HILInitialize_AOPStart && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_AOPEnter && is_switching)) {
      operate_flexible_link_DW.HILInitialize_AOMinimums[0] =
        (operate_flexible_link_P.HILInitialize_AOLow);
      operate_flexible_link_DW.HILInitialize_AOMinimums[1] =
        (operate_flexible_link_P.HILInitialize_AOLow);
      operate_flexible_link_DW.HILInitialize_AOMaximums[0] =
        operate_flexible_link_P.HILInitialize_AOHigh;
      operate_flexible_link_DW.HILInitialize_AOMaximums[1] =
        operate_flexible_link_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (operate_flexible_link_DW.HILInitialize_Card,
         operate_flexible_link_P.HILInitialize_AOChannels, 2U,
         &operate_flexible_link_DW.HILInitialize_AOMinimums[0],
         &operate_flexible_link_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }

    if ((operate_flexible_link_P.HILInitialize_AOStart && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_AOEnter && is_switching)) {
      operate_flexible_link_DW.HILInitialize_AOVoltages[0] =
        operate_flexible_link_P.HILInitialize_AOInitial;
      operate_flexible_link_DW.HILInitialize_AOVoltages[1] =
        operate_flexible_link_P.HILInitialize_AOInitial;
      result = hil_write_analog(operate_flexible_link_DW.HILInitialize_Card,
        operate_flexible_link_P.HILInitialize_AOChannels, 2U,
        &operate_flexible_link_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }

    if (operate_flexible_link_P.HILInitialize_AOReset) {
      operate_flexible_link_DW.HILInitialize_AOVoltages[0] =
        operate_flexible_link_P.HILInitialize_AOWatchdog;
      operate_flexible_link_DW.HILInitialize_AOVoltages[1] =
        operate_flexible_link_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (operate_flexible_link_DW.HILInitialize_Card,
         operate_flexible_link_P.HILInitialize_AOChannels, 2U,
         &operate_flexible_link_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (operate_flexible_link_DW.HILInitialize_Card, NULL, 0U,
       operate_flexible_link_P.HILInitialize_DOChannels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
      return;
    }

    if ((operate_flexible_link_P.HILInitialize_DOStart && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &operate_flexible_link_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = operate_flexible_link_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(operate_flexible_link_DW.HILInitialize_Card,
        operate_flexible_link_P.HILInitialize_DOChannels, 8U, (t_boolean *)
        &operate_flexible_link_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }

    if (operate_flexible_link_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &operate_flexible_link_DW.HILInitialize_DOStates
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOStates[i1] = operate_flexible_link_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (operate_flexible_link_DW.HILInitialize_Card,
         operate_flexible_link_P.HILInitialize_DOChannels, 8U, (const
          t_digital_state *) &operate_flexible_link_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }

    if ((operate_flexible_link_P.HILInitialize_EIPStart && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_EIPEnter && is_switching)) {
      operate_flexible_link_DW.HILInitialize_QuadratureModes[0] =
        operate_flexible_link_P.HILInitialize_EIQuadrature;
      operate_flexible_link_DW.HILInitialize_QuadratureModes[1] =
        operate_flexible_link_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (operate_flexible_link_DW.HILInitialize_Card,
         operate_flexible_link_P.HILInitialize_EIChannels, 2U,
         (t_encoder_quadrature_mode *)
         &operate_flexible_link_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }

    if ((operate_flexible_link_P.HILInitialize_EIStart && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_EIEnter && is_switching)) {
      operate_flexible_link_DW.HILInitialize_InitialEICounts[0] =
        operate_flexible_link_P.HILInitialize_EIInitial;
      operate_flexible_link_DW.HILInitialize_InitialEICounts[1] =
        operate_flexible_link_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts
        (operate_flexible_link_DW.HILInitialize_Card,
         operate_flexible_link_P.HILInitialize_EIChannels, 2U,
         &operate_flexible_link_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "result.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(operate_flexible_link_M,
                        "Error creating .mat file result.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "result")) {
      rtmSetErrorStatus(operate_flexible_link_M,
                        "Error writing mat file header to file result.mat");
      return;
    }

    operate_flexible_link_DW.ToFile_IWORK.Count = 0;
    operate_flexible_link_DW.ToFile_IWORK.Decimation = -1;
    operate_flexible_link_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  operate_flexible_link_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  operate_flexible_link_X.TransferFcn3_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn2' */
  operate_flexible_link_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn' */
  operate_flexible_link_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn1' */
  operate_flexible_link_X.TransferFcn1_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  operate_flexible_link_X.TransferFcn2_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Q(s)' */
  operate_flexible_link_X.Qs_CSTATE[0] = 0.0;
  operate_flexible_link_X.Qs_CSTATE[1] = 0.0;

  /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function' */
  operate_flexible_link_DW.sfEvent = operate_flexible_lin_CALL_EVENT;
  operate_flexible_link_DW.is_active_c2_operate_flexible_l = 0U;
}

/* Model terminate function */
void operate_flexible_link_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S4>/HIL Initialize' */

  /* S-Function Block: operate_flexible_link/SRV02 Flexible Link/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(operate_flexible_link_DW.HILInitialize_Card);
    hil_monitor_stop_all(operate_flexible_link_DW.HILInitialize_Card);
    is_switching = false;
    if ((operate_flexible_link_P.HILInitialize_AOTerminate && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_AOExit && is_switching)) {
      operate_flexible_link_DW.HILInitialize_AOVoltages[0] =
        operate_flexible_link_P.HILInitialize_AOFinal;
      operate_flexible_link_DW.HILInitialize_AOVoltages[1] =
        operate_flexible_link_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((operate_flexible_link_P.HILInitialize_DOTerminate && !is_switching) ||
        (operate_flexible_link_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &operate_flexible_link_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = operate_flexible_link_P.HILInitialize_DOFinal;
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
      result = hil_write(operate_flexible_link_DW.HILInitialize_Card
                         , operate_flexible_link_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , operate_flexible_link_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &operate_flexible_link_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &operate_flexible_link_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (operate_flexible_link_DW.HILInitialize_Card,
             operate_flexible_link_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &operate_flexible_link_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (operate_flexible_link_DW.HILInitialize_Card,
             operate_flexible_link_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &operate_flexible_link_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(operate_flexible_link_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(operate_flexible_link_DW.HILInitialize_Card);
    hil_monitor_delete_all(operate_flexible_link_DW.HILInitialize_Card);
    hil_close(operate_flexible_link_DW.HILInitialize_Card);
    operate_flexible_link_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) operate_flexible_link_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "result.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(operate_flexible_link_M,
                          "Error closing MAT-file result.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(operate_flexible_link_M,
                          "Error reopening MAT-file result.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           operate_flexible_link_DW.ToFile_IWORK.Count, "result")) {
        rtmSetErrorStatus(operate_flexible_link_M,
                          "Error writing header for result to MAT-file result.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(operate_flexible_link_M,
                          "Error closing MAT-file result.mat");
        return;
      }

      operate_flexible_link_DW.ToFile_PWORK.FilePtr = (NULL);
    }
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
  operate_flexible_link_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  operate_flexible_link_update();
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
  operate_flexible_link_initialize();
}

void MdlTerminate(void)
{
  operate_flexible_link_terminate();
}

/* Registration function */
RT_MODEL_operate_flexible_lin_T *operate_flexible_link(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)operate_flexible_link_M, 0,
                sizeof(RT_MODEL_operate_flexible_lin_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&operate_flexible_link_M->solverInfo,
                          &operate_flexible_link_M->Timing.simTimeStep);
    rtsiSetTPtr(&operate_flexible_link_M->solverInfo, &rtmGetTPtr
                (operate_flexible_link_M));
    rtsiSetStepSizePtr(&operate_flexible_link_M->solverInfo,
                       &operate_flexible_link_M->Timing.stepSize0);
    rtsiSetdXPtr(&operate_flexible_link_M->solverInfo,
                 &operate_flexible_link_M->derivs);
    rtsiSetContStatesPtr(&operate_flexible_link_M->solverInfo, (real_T **)
                         &operate_flexible_link_M->contStates);
    rtsiSetNumContStatesPtr(&operate_flexible_link_M->solverInfo,
      &operate_flexible_link_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&operate_flexible_link_M->solverInfo,
      &operate_flexible_link_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&operate_flexible_link_M->solverInfo,
      &operate_flexible_link_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&operate_flexible_link_M->solverInfo,
      &operate_flexible_link_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&operate_flexible_link_M->solverInfo,
                          (&rtmGetErrorStatus(operate_flexible_link_M)));
    rtsiSetRTModelPtr(&operate_flexible_link_M->solverInfo,
                      operate_flexible_link_M);
  }

  rtsiSetSimTimeStep(&operate_flexible_link_M->solverInfo, MAJOR_TIME_STEP);
  operate_flexible_link_M->intgData.f[0] = operate_flexible_link_M->odeF[0];
  operate_flexible_link_M->contStates = ((real_T *) &operate_flexible_link_X);
  rtsiSetSolverData(&operate_flexible_link_M->solverInfo, (void *)
                    &operate_flexible_link_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&operate_flexible_link_M->solverInfo,
    false);
  rtsiSetSolverName(&operate_flexible_link_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = operate_flexible_link_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "operate_flexible_link_M points to
       static memory which is guaranteed to be non-NULL" */
    operate_flexible_link_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    operate_flexible_link_M->Timing.sampleTimes =
      (&operate_flexible_link_M->Timing.sampleTimesArray[0]);
    operate_flexible_link_M->Timing.offsetTimes =
      (&operate_flexible_link_M->Timing.offsetTimesArray[0]);

    /* task periods */
    operate_flexible_link_M->Timing.sampleTimes[0] = (0.0);
    operate_flexible_link_M->Timing.sampleTimes[1] = (0.033333333333333333);

    /* task offsets */
    operate_flexible_link_M->Timing.offsetTimes[0] = (0.0);
    operate_flexible_link_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(operate_flexible_link_M, &operate_flexible_link_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = operate_flexible_link_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    operate_flexible_link_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(operate_flexible_link_M, 100.0);
  operate_flexible_link_M->Timing.stepSize0 = 0.033333333333333333;
  operate_flexible_link_M->Timing.stepSize1 = 0.033333333333333333;

  /* External mode info */
  operate_flexible_link_M->Sizes.checksums[0] = (3006166320U);
  operate_flexible_link_M->Sizes.checksums[1] = (4290889423U);
  operate_flexible_link_M->Sizes.checksums[2] = (1722106711U);
  operate_flexible_link_M->Sizes.checksums[3] = (848651695U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    operate_flexible_link_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(operate_flexible_link_M->extModeInfo,
      &operate_flexible_link_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(operate_flexible_link_M->extModeInfo,
                        operate_flexible_link_M->Sizes.checksums);
    rteiSetTPtr(operate_flexible_link_M->extModeInfo, rtmGetTPtr
                (operate_flexible_link_M));
  }

  operate_flexible_link_M->solverInfoPtr = (&operate_flexible_link_M->solverInfo);
  operate_flexible_link_M->Timing.stepSize = (0.033333333333333333);
  rtsiSetFixedStepSize(&operate_flexible_link_M->solverInfo,
                       0.033333333333333333);
  rtsiSetSolverMode(&operate_flexible_link_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  operate_flexible_link_M->blockIO = ((void *) &operate_flexible_link_B);

  {
    operate_flexible_link_B.HILReadEncoder = 0.0;
    operate_flexible_link_B.EncoderCalibrationradcount = 0.0;
    operate_flexible_link_B.pos = 0.0;
    operate_flexible_link_B.Subtract = 0.0;
    operate_flexible_link_B.Gain4 = 0.0;
    operate_flexible_link_B.TransferFcn1 = 0.0;
    operate_flexible_link_B.Gain3 = 0.0;
    operate_flexible_link_B.TransferFcn3 = 0.0;
    operate_flexible_link_B.Gain5 = 0.0;
    operate_flexible_link_B.Subtract1 = 0.0;
    operate_flexible_link_B.Gain2 = 0.0;
    operate_flexible_link_B.DirectionConventionRightHandsys = 0.0;
    operate_flexible_link_B.AmplifierSaturationV = 0.0;
    operate_flexible_link_B.InverseAmplifierGainVV = 0.0;
    operate_flexible_link_B.DACBSaturationV = 0.0;
    operate_flexible_link_B.HILReadAnalog = 0.0;
    operate_flexible_link_B.Step = 0.0;
    operate_flexible_link_B.Gain1 = 0.0;
    operate_flexible_link_B.TransferFcn2 = 0.0;
    operate_flexible_link_B.Gain = 0.0;
    operate_flexible_link_B.Gain1_p = 0.0;
    operate_flexible_link_B.TransferFcn = 0.0;
    operate_flexible_link_B.TransferFcn1_d = 0.0;
    operate_flexible_link_B.TransferFcn2_i = 0.0;
    operate_flexible_link_B.y = 0.0;
    operate_flexible_link_B.y_c = 0.0;
  }

  /* parameters */
  operate_flexible_link_M->defaultParam = ((real_T *)&operate_flexible_link_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &operate_flexible_link_X;
    operate_flexible_link_M->contStates = (x);
    (void) memset((void *)&operate_flexible_link_X, 0,
                  sizeof(X_operate_flexible_link_T));
  }

  /* states (dwork) */
  operate_flexible_link_M->dwork = ((void *) &operate_flexible_link_DW);
  (void) memset((void *)&operate_flexible_link_DW, 0,
                sizeof(DW_operate_flexible_link_T));
  operate_flexible_link_DW.HILInitialize_AIMinimums[0] = 0.0;
  operate_flexible_link_DW.HILInitialize_AIMinimums[1] = 0.0;
  operate_flexible_link_DW.HILInitialize_AIMaximums[0] = 0.0;
  operate_flexible_link_DW.HILInitialize_AIMaximums[1] = 0.0;
  operate_flexible_link_DW.HILInitialize_AOMinimums[0] = 0.0;
  operate_flexible_link_DW.HILInitialize_AOMinimums[1] = 0.0;
  operate_flexible_link_DW.HILInitialize_AOMaximums[0] = 0.0;
  operate_flexible_link_DW.HILInitialize_AOMaximums[1] = 0.0;
  operate_flexible_link_DW.HILInitialize_AOVoltages[0] = 0.0;
  operate_flexible_link_DW.HILInitialize_AOVoltages[1] = 0.0;
  operate_flexible_link_DW.HILInitialize_FilterFrequency[0] = 0.0;
  operate_flexible_link_DW.HILInitialize_FilterFrequency[1] = 0.0;
  operate_flexible_link_DW.HILReadAnalog_Buffer = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    operate_flexible_link_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 21;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  operate_flexible_link_M->Sizes.numContStates = (8);/* Number of continuous states */
  operate_flexible_link_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  operate_flexible_link_M->Sizes.numY = (0);/* Number of model outputs */
  operate_flexible_link_M->Sizes.numU = (0);/* Number of model inputs */
  operate_flexible_link_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  operate_flexible_link_M->Sizes.numSampTimes = (2);/* Number of sample times */
  operate_flexible_link_M->Sizes.numBlocks = (34);/* Number of blocks */
  operate_flexible_link_M->Sizes.numBlockIO = (26);/* Number of block outputs */
  operate_flexible_link_M->Sizes.numBlockPrms = (125);/* Sum of parameter "widths" */
  return operate_flexible_link_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
