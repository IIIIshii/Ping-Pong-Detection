/*
 * communication_test_data.c
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

/* Block parameters (default storage) */
P_communication_test_T communication_test_P = {
  /* Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S2>/HIL Write Analog'
   */
  0U,

  /* Mask Parameter: HILReadEncoder_channels
   * Referenced by: '<S2>/HIL Read Encoder'
   */
  0U,

  /* Mask Parameter: HILReadAnalog_channels
   * Referenced by: '<S2>/HIL Read Analog'
   */
  0U,

  /* Mask Parameter: HILWriteDigital_channels
   * Referenced by: '<S2>/HIL Write Digital'
   */
  { 0U, 1U, 2U, 3U },

  /* Expression: set_other_outputs_at_terminate
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_out
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: final_analog_outputs
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: final_pwm_outputs
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: 0.3
   * Referenced by: '<Root>/reference'
   */
  0.3,

  /* Expression: -4/100
   * Referenced by: '<S1>/Gain'
   */
  -0.04,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<S1>/Transfer Fcn'
   */
  -15.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<S1>/Transfer Fcn'
   */
  -735.0,

  /* Computed Parameter: TransferFcn_D
   * Referenced by: '<S1>/Transfer Fcn'
   */
  50.0,

  /* Computed Parameter: TransferFcn1_A
   * Referenced by: '<S1>/Transfer Fcn1'
   */
  -15.0,

  /* Computed Parameter: TransferFcn1_C
   * Referenced by: '<S1>/Transfer Fcn1'
   */
  -735.0,

  /* Computed Parameter: TransferFcn1_D
   * Referenced by: '<S1>/Transfer Fcn1'
   */
  50.0,

  /* Expression: -1
   * Referenced by: '<S4>/Direction Convention: (Right-Hand) system'
   */
  -1.0,

  /* Expression: 24
   * Referenced by: '<S4>/Amplifier Saturation (V)'
   */
  24.0,

  /* Expression: -24
   * Referenced by: '<S4>/Amplifier Saturation (V)'
   */
  -24.0,

  /* Expression: 1
   * Referenced by: '<S4>/Inverse Amplifier  Gain (V//V)'
   */
  1.0,

  /* Expression: 10
   * Referenced by: '<S4>/DACB Saturation (V)'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S4>/DACB Saturation (V)'
   */
  -10.0,

  /* Expression: -1
   * Referenced by: '<S4>/Amplifier  Gain (V//V)'
   */
  -1.0,

  /* Expression: 0.0015
   * Referenced by: '<S2>/Encoder Calibration  (rad//count)'
   */
  0.0015,

  /* Expression: 0.0606
   * Referenced by: '<S2>/Strain Gage Calibration  (rad//V)'
   */
  0.0606,

  /* Expression: [1 1 1 1]
   * Referenced by: '<S2>/Enable VoltPAQ-X2,X4'
   */
  { 1.0, 1.0, 1.0, 1.0 },

  /* Computed Parameter: Qs_A
   * Referenced by: '<Root>/Q(s)'
   */
  { -0.0, -0.0 },

  /* Computed Parameter: Qs_C
   * Referenced by: '<Root>/Q(s)'
   */
  { 0.0, 12.258312499999999 },

  /* Computed Parameter: HILInitialize_Active
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOTerminate
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOExit
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOTerminate
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_DOExit
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POTerminate
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POExit
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOFinal
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILWriteAnalog_Active
   * Referenced by: '<S2>/HIL Write Analog'
   */
  false,

  /* Computed Parameter: HILReadEncoder_Active
   * Referenced by: '<S2>/HIL Read Encoder'
   */
  true,

  /* Computed Parameter: HILReadAnalog_Active
   * Referenced by: '<S2>/HIL Read Analog'
   */
  true,

  /* Computed Parameter: HILWriteDigital_Active
   * Referenced by: '<S2>/HIL Write Digital'
   */
  false
};
