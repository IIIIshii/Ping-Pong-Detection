/*
 * operate_flexible_link_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "operate_flexible_link".
 *
 * Model version              : 11.80
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Thu May 21 17:33:08 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int32_T),
  sizeof(t_card),
  sizeof(t_boolean),
  sizeof(uint_T),
  sizeof(char_T),
  sizeof(uchar_T),
  sizeof(time_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "physical_connection",
  "t_card",
  "t_boolean",
  "uint_T",
  "char_T",
  "uchar_T",
  "time_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&operate_flexible_link_B.HILReadEncoder), 0, 0, 15 }
  ,

  { (char_T *)(&operate_flexible_link_DW.HILInitialize_AIMinimums[0]), 0, 0, 13
  },

  { (char_T *)(&operate_flexible_link_DW.HILInitialize_Card), 15, 0, 1 },

  { (char_T *)(&operate_flexible_link_DW.HILReadEncoder_PWORK), 11, 0, 5 },

  { (char_T *)(&operate_flexible_link_DW.HILInitialize_ClockModes[0]), 6, 0, 16
  },

  { (char_T *)(&operate_flexible_link_DW.HILInitialize_DOBits[0]), 8, 0, 8 },

  { (char_T *)(&operate_flexible_link_DW.HILWriteDigital_Buffer[0]), 16, 0, 4 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&operate_flexible_link_P.HILReadEncoder_channels), 7, 0, 7 },

  { (char_T *)(&operate_flexible_link_P.HILInitialize_OOTerminate), 0, 0, 44 },

  { (char_T *)(&operate_flexible_link_P.HILInitialize_CKChannels[0]), 6, 0, 6 },

  { (char_T *)(&operate_flexible_link_P.HILInitialize_AIChannels[0]), 7, 0, 15 },

  { (char_T *)(&operate_flexible_link_P.HILInitialize_Active), 8, 0, 39 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  5U,
  rtPTransitions
};

/* [EOF] operate_flexible_link_dt.h */
