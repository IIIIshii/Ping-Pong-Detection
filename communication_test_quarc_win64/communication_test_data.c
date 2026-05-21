/*
 * communication_test_data.c
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

  /* Expression: set_other_outputs_at_start
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_in
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

  /* Expression: analog_input_maximums
   * Referenced by: '<S2>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_input_minimums
   * Referenced by: '<S2>/HIL Initialize'
   */
  -10.0,

  /* Expression: analog_output_maximums
   * Referenced by: '<S2>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_output_minimums
   * Referenced by: '<S2>/HIL Initialize'
   */
  -10.0,

  /* Expression: initial_analog_outputs
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_analog_outputs
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_frequency
   * Referenced by: '<S2>/HIL Initialize'
   */
  50.0,

  /* Expression: initial_pwm_outputs
   * Referenced by: '<S2>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_pwm_outputs
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

  /* Computed Parameter: HILInitialize_CKChannels
   * Referenced by: '<S2>/HIL Initialize'
   */
  { 0, 1, 2 },

  /* Computed Parameter: HILInitialize_DOWatchdog
   * Referenced by: '<S2>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIInitial
   * Referenced by: '<S2>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POModes
   * Referenced by: '<S2>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AIChannels
   * Referenced by: '<S2>/HIL Initialize'
   */
  { 0U, 1U },

  /* Computed Parameter: HILInitialize_AOChannels
   * Referenced by: '<S2>/HIL Initialize'
   */
  { 0U, 1U },

  /* Computed Parameter: HILInitialize_DOChannels
   * Referenced by: '<S2>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIChannels
   * Referenced by: '<S2>/HIL Initialize'
   */
  { 0U, 1U },

  /* Computed Parameter: HILInitialize_EIQuadrature
   * Referenced by: '<S2>/HIL Initialize'
   */
  4U,

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

  /* Computed Parameter: HILInitialize_CKPStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKPEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AIPStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AIPEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOPStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOPEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOReset
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOPStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOPEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_DOEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOReset
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_EIPStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_EIPEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_EIStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_EIEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POPStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POPEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POStart
   * Referenced by: '<S2>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POEnter
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POReset
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_OOReset
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOFinal
   * Referenced by: '<S2>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOInitial
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
