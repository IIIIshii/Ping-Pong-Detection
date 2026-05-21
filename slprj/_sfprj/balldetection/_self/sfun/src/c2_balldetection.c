/* Include files */

#include "balldetection_sfun.h"
#include "c2_balldetection.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static emlrtRSInfo c2_emlrtRSI = { 51, /* lineNo */
  "rgb2hsv",                           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\eml\\lib\\matlab\\images\\rgb2hsv.m"/* pathName */
};

static emlrtRSInfo c2_b_emlrtRSI = { 3,/* lineNo */
  "BallDetector/MATLAB Function",      /* fcnName */
  "#balldetection:2"                   /* pathName */
};

/* Function Declarations */
static void initialize_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void initialize_params_c2_balldetection(SFc2_balldetectionInstanceStruct *
  chartInstance);
static void mdl_start_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void mdl_terminate_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void mdl_setup_runtime_resources_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance);
static void mdl_cleanup_runtime_resources_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance);
static void enable_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void disable_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void sf_gateway_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void ext_mode_exec_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void c2_update_jit_animation_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance);
static void c2_do_animation_call_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance);
static void set_sim_state_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void initSimStructsc2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void initSubchartIOPointersc2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance);
static void c2_emlrt_marshallIn(SFc2_balldetectionInstanceStruct *chartInstance,
  const mxArray *c2_b_BW, const char_T *c2_identifier, boolean_T c2_y[921600]);
static void c2_b_emlrt_marshallIn(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  boolean_T c2_y[921600]);
static uint8_T c2_c_emlrt_marshallIn(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_balldetection, const char_T
  *c2_identifier);
static uint8_T c2_d_emlrt_marshallIn(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_slStringInitializeDynamicBuffers(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void c2_chart_data_browse_helper(SFc2_balldetectionInstanceStruct
  *chartInstance, int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T
  *c2_isValueTooBig);
static void init_dsm_address_info(SFc2_balldetectionInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc2_balldetectionInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_balldetection = 0U;
}

static void initialize_params_c2_balldetection(SFc2_balldetectionInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void mdl_start_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void mdl_terminate_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void mdl_setup_runtime_resources_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance)
{
  static const uint32_T c2_decisionTxtEndIdx = 0U;
  static const uint32_T c2_decisionTxtStartIdx = 0U;
  setDebuggerFlag(chartInstance->S, true);
  setDataBrowseFcn(chartInstance->S, (void *)&c2_chart_data_browse_helper);
  chartInstance->c2_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c2_RuntimeVar,
    &chartInstance->c2_IsDebuggerActive,
    &chartInstance->c2_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c2_mlFcnLineNumber, &chartInstance->c2_IsHeatMapPresent, 0);
  covrtCreateStateflowInstanceData(chartInstance->c2_covrtInstance, 1U, 0U, 1U,
    18U);
  covrtChartInitFcn(chartInstance->c2_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c2_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c2_decisionTxtStartIdx, &c2_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c2_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c2_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 4U, 0U, 0U,
                     "eML_blk_kernel", 0, -1, 290);
}

static void mdl_cleanup_runtime_resources_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c2_RuntimeVar);
  covrtDeleteStateflowInstanceData(chartInstance->c2_covrtInstance);
}

static void enable_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void sf_gateway_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  real_T c2_b_hMax;
  real_T c2_b_hMin;
  real_T c2_b_sMax;
  real_T c2_b_sMin;
  real_T c2_b_vMax;
  real_T c2_b_vMin;
  int32_T c2_i;
  int32_T c2_i1;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i2;
  int32_T c2_i20;
  int32_T c2_i21;
  int32_T c2_i22;
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i3;
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  chartInstance->c2_JITTransitionAnimation[0] = 0U;
  _sfTime_ = sf_get_time(chartInstance->S);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 6U, *chartInstance->c2_vMax);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 5U, *chartInstance->c2_vMin);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 4U, *chartInstance->c2_sMax);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 3U, *chartInstance->c2_sMin);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 2U, *chartInstance->c2_hMax);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 1U, *chartInstance->c2_hMin);
  for (c2_i = 0; c2_i < 2764800; c2_i++) {
    covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 0U, (real_T)
                      (*chartInstance->c2_RGB)[c2_i]);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_b_hMin = *chartInstance->c2_hMin;
  c2_b_hMax = *chartInstance->c2_hMax;
  c2_b_sMin = *chartInstance->c2_sMin;
  c2_b_sMax = *chartInstance->c2_sMax;
  c2_b_vMin = *chartInstance->c2_vMin;
  c2_b_vMax = *chartInstance->c2_vMax;
  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 4U, 0, 0);
  rgb2hsv_tbb_real32(&(*chartInstance->c2_RGB)[0], 921600.0,
                     &chartInstance->c2_I[0], true);
  c2_i1 = 0;
  for (c2_i2 = 0; c2_i2 < 1280; c2_i2++) {
    for (c2_i4 = 0; c2_i4 < 720; c2_i4++) {
      (*chartInstance->c2_BW)[c2_i4 + c2_i1] = ((real_T)chartInstance->
        c2_I[c2_i4 + c2_i1] >= c2_b_hMin);
    }

    c2_i1 += 720;
  }

  c2_i3 = 0;
  for (c2_i5 = 0; c2_i5 < 1280; c2_i5++) {
    for (c2_i7 = 0; c2_i7 < 720; c2_i7++) {
      chartInstance->c2_bv[c2_i7 + c2_i3] = ((real_T)chartInstance->c2_I[c2_i7 +
        c2_i3] <= c2_b_hMax);
    }

    c2_i3 += 720;
  }

  for (c2_i6 = 0; c2_i6 < 921600; c2_i6++) {
    (*chartInstance->c2_BW)[c2_i6] = ((*chartInstance->c2_BW)[c2_i6] &&
      chartInstance->c2_bv[c2_i6]);
  }

  c2_i8 = 0;
  for (c2_i9 = 0; c2_i9 < 1280; c2_i9++) {
    for (c2_i11 = 0; c2_i11 < 720; c2_i11++) {
      chartInstance->c2_bv[c2_i11 + c2_i8] = ((real_T)chartInstance->c2_I
        [(c2_i11 + c2_i8) + 921600] >= c2_b_sMin);
    }

    c2_i8 += 720;
  }

  for (c2_i10 = 0; c2_i10 < 921600; c2_i10++) {
    (*chartInstance->c2_BW)[c2_i10] = ((*chartInstance->c2_BW)[c2_i10] &&
      chartInstance->c2_bv[c2_i10]);
  }

  c2_i12 = 0;
  for (c2_i13 = 0; c2_i13 < 1280; c2_i13++) {
    for (c2_i15 = 0; c2_i15 < 720; c2_i15++) {
      chartInstance->c2_bv[c2_i15 + c2_i12] = ((real_T)chartInstance->c2_I
        [(c2_i15 + c2_i12) + 921600] <= c2_b_sMax);
    }

    c2_i12 += 720;
  }

  for (c2_i14 = 0; c2_i14 < 921600; c2_i14++) {
    (*chartInstance->c2_BW)[c2_i14] = ((*chartInstance->c2_BW)[c2_i14] &&
      chartInstance->c2_bv[c2_i14]);
  }

  c2_i16 = 0;
  for (c2_i17 = 0; c2_i17 < 1280; c2_i17++) {
    for (c2_i19 = 0; c2_i19 < 720; c2_i19++) {
      chartInstance->c2_bv[c2_i19 + c2_i16] = ((real_T)chartInstance->c2_I
        [(c2_i19 + c2_i16) + 1843200] >= c2_b_vMin);
    }

    c2_i16 += 720;
  }

  for (c2_i18 = 0; c2_i18 < 921600; c2_i18++) {
    (*chartInstance->c2_BW)[c2_i18] = ((*chartInstance->c2_BW)[c2_i18] &&
      chartInstance->c2_bv[c2_i18]);
  }

  c2_i20 = 0;
  for (c2_i21 = 0; c2_i21 < 1280; c2_i21++) {
    for (c2_i23 = 0; c2_i23 < 720; c2_i23++) {
      chartInstance->c2_bv[c2_i23 + c2_i20] = ((real_T)chartInstance->c2_I
        [(c2_i23 + c2_i20) + 1843200] <= c2_b_vMax);
    }

    c2_i20 += 720;
  }

  for (c2_i22 = 0; c2_i22 < 921600; c2_i22++) {
    (*chartInstance->c2_BW)[c2_i22] = ((*chartInstance->c2_BW)[c2_i22] &&
      chartInstance->c2_bv[c2_i22]);
  }

  c2_do_animation_call_c2_balldetection(chartInstance);
  for (c2_i24 = 0; c2_i24 < 921600; c2_i24++) {
    covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 7U, (real_T)
                      (*chartInstance->c2_BW)[c2_i24]);
  }
}

static void ext_mode_exec_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_update_jit_animation_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_do_animation_call_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance)
{
  sfDoAnimationWrapper(chartInstance->S, false, true);
  sfDoAnimationWrapper(chartInstance->S, false, false);
}

static const mxArray *get_sim_state_c2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance)
{
  const mxArray *c2_b_y = NULL;
  const mxArray *c2_c_y = NULL;
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", *chartInstance->c2_BW, 11, 0U, 1U,
    0U, 2, 720, 1280), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y",
    &chartInstance->c2_is_active_c2_balldetection, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  int32_T c2_i;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "BW",
                      chartInstance->c2_b_bv);
  for (c2_i = 0; c2_i < 921600; c2_i++) {
    (*chartInstance->c2_BW)[c2_i] = chartInstance->c2_b_bv[c2_i];
  }

  chartInstance->c2_is_active_c2_balldetection = c2_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_balldetection");
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

static void initSimStructsc2_balldetection(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void initSubchartIOPointersc2_balldetection
  (SFc2_balldetectionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

const mxArray *sf_c2_balldetection_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static void c2_emlrt_marshallIn(SFc2_balldetectionInstanceStruct *chartInstance,
  const mxArray *c2_b_BW, const char_T *c2_identifier, boolean_T c2_y[921600])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char_T *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_BW), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_BW);
}

static void c2_b_emlrt_marshallIn(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  boolean_T c2_y[921600])
{
  int32_T c2_i;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), chartInstance->c2_c_bv, 1, 11, 0U,
                1, 0U, 2, 720, 1280);
  for (c2_i = 0; c2_i < 921600; c2_i++) {
    c2_y[c2_i] = chartInstance->c2_c_bv[c2_i];
  }

  sf_mex_destroy(&c2_u);
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_balldetection, const char_T
  *c2_identifier)
{
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  c2_thisId.fIdentifier = (const char_T *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_balldetection), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_balldetection);
  return c2_y;
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_balldetectionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_b_u;
  uint8_T c2_y;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b_u, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_b_u;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_slStringInitializeDynamicBuffers(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_chart_data_browse_helper(SFc2_balldetectionInstanceStruct
  *chartInstance, int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T
  *c2_isValueTooBig)
{
  real_T c2_d;
  real_T c2_d1;
  real_T c2_d2;
  real_T c2_d3;
  real_T c2_d4;
  real_T c2_d5;
  *c2_mxData = NULL;
  *c2_mxData = NULL;
  *c2_isValueTooBig = 0U;
  switch (c2_ssIdNumber) {
   case 4U:
    *c2_isValueTooBig = 1U;
    break;

   case 5U:
    *c2_isValueTooBig = 1U;
    break;

   case 6U:
    c2_d = *chartInstance->c2_hMin;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d, 0, 0U, 0U, 0U, 0),
                  false);
    break;

   case 7U:
    c2_d1 = *chartInstance->c2_hMax;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d1, 0, 0U, 0U, 0U, 0),
                  false);
    break;

   case 8U:
    c2_d2 = *chartInstance->c2_sMin;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d2, 0, 0U, 0U, 0U, 0),
                  false);
    break;

   case 9U:
    c2_d3 = *chartInstance->c2_sMax;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d3, 0, 0U, 0U, 0U, 0),
                  false);
    break;

   case 10U:
    c2_d4 = *chartInstance->c2_vMin;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d4, 0, 0U, 0U, 0U, 0),
                  false);
    break;

   case 11U:
    c2_d5 = *chartInstance->c2_vMax;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d5, 0, 0U, 0U, 0U, 0),
                  false);
    break;
  }
}

static void init_dsm_address_info(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_balldetectionInstanceStruct
  *chartInstance)
{
  chartInstance->c2_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_RGB = (real32_T (*)[2764800])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_BW = (boolean_T (*)[921600])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_hMin = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_hMax = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_sMin = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_sMax = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_vMin = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_vMax = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c2_balldetection_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2998961644U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(965922033U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3256466778U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3119874533U);
}

mxArray *sf_c2_balldetection_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,1);
  mxSetCell(mxcell3p, 0, mxCreateString(
             "images.internal.coder.buildable.Rgb2hsvBuildable"));
  return(mxcell3p);
}

mxArray *sf_c2_balldetection_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("rgb2hsv_tbb_real32");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_balldetection_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_balldetection(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiD+wcjAwAakOYCYiQECWKF8RqgYI1ycBS6uAMQllQWpIPHiomTPFCCdl5gL5ie"
    "WVnjmpeWDzbdgQJjPhsV8RiTzOaHiEPDBnjL9Ig4g/QZI+lkI+E8AyHMKh4QLLHzIt1/BgTL9EP"
    "sDCLhfCsX9EH5mcXxicklmWWp8slF8UmJOTkpqSSpQID8PYS4IAABl0xpC"
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_balldetection_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "s7mLjO7AD93zaDryItuemrF";
}

static void sf_opaque_initialize_c2_balldetection(void *chartInstanceVar)
{
  initialize_params_c2_balldetection((SFc2_balldetectionInstanceStruct*)
    chartInstanceVar);
  initialize_c2_balldetection((SFc2_balldetectionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_balldetection(void *chartInstanceVar)
{
  enable_c2_balldetection((SFc2_balldetectionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_balldetection(void *chartInstanceVar)
{
  disable_c2_balldetection((SFc2_balldetectionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_balldetection(void *chartInstanceVar)
{
  sf_gateway_c2_balldetection((SFc2_balldetectionInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_balldetection(SimStruct* S)
{
  return get_sim_state_c2_balldetection((SFc2_balldetectionInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_balldetection(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c2_balldetection((SFc2_balldetectionInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c2_balldetection(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_balldetectionInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_balldetection_optimization_info();
    }

    mdl_cleanup_runtime_resources_c2_balldetection
      ((SFc2_balldetectionInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c2_balldetection(void *chartInstanceVar)
{
  mdl_start_c2_balldetection((SFc2_balldetectionInstanceStruct*)
    chartInstanceVar);
  if (chartInstanceVar) {
    sf_reset_warnings_ChartRunTimeInfo(((SFc2_balldetectionInstanceStruct*)
      chartInstanceVar)->S);
  }
}

static void sf_opaque_mdl_terminate_c2_balldetection(void *chartInstanceVar)
{
  mdl_terminate_c2_balldetection((SFc2_balldetectionInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_balldetection(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  sf_warn_if_symbolic_dimension_param_changed(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_balldetection((SFc2_balldetectionInstanceStruct*)
      sf_get_chart_instance_ptr(S));
    initSubchartIOPointersc2_balldetection((SFc2_balldetectionInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c2_balldetection_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [22] = {
    "eNrtWNuO20QYnkTLllWhWgkkxAqpveQSUYmChMpuThCUZaM6u5W4YDWxf8dDxmN3DtlNxUPwEKi",
    "qxPsgLhFPwGW54x/bSVMnJJ5ElBZhyesde775D/P9hwmpdU8JXrfw/vF9Qvbx+SbedZJfbxTj2s",
    "Kdv98jnxfjH24S4icBjEB4JgzZNXG7hIn7VNJYEfdL0BgegEq40SwRXREm1bFMhCBB+LhAmkjtJ",
    "Fex2HAmxh0jfCtZPYyYH3lRYnjQwAVpcCb49O/kpkb3UWKLSfB1ByDQkUzMKOpwOlrvBamvmhH4",
    "Y2ViZ18p0J5Jranq1HDNUg7ta/C7QmmKXlAb7PU01dDU125OtvYqb4ZO4pQzKqr7OqLKgxTZoeE",
    "8DfDvmdHovUpYP6JSNyCiE1A9Ns6kJwIqSWcKZw+ZoDqRjPJ2zJt2tYr29jnaeIohwV33CO1tSK",
    "DjNGFCOwaE10E/twUdcmjB0Iwc5XrwyNhouGBwBdJtf8NmMgFJR3Am3HTO9qh9nZFyHksVsZrFc",
    "EHliY/cVRC45Q0MOuVRpCMMcBknLGQu7qqBZBPkhmuu69rw3yrXmThnv9oKm8ltT8CZV3O5HV80",
    "KefKDTtI0h5MgGfyW1TTLbC5fAewUiwYJMgOm20cM5YRDCOhwDYTEbDqrJyUUFlh+waLVAU4i20",
    "YQIBunqs+X2hTHBmlk7iJKafV61WUt4ztCg0ypD5UrjGSMgWocMYrR7kBUzaQEI1e0pmVlVfIY3",
    "ArKFGhEa2rRI7Rx67F7LmvbCS4oSEYYWLWkCW5NrL7gnJTUedYjTB+kB7nCrOsm1zE2vjZCuxTP",
    "4LAVk7G4RTzLC5QdYuVLfknaO2E6WkLlC9ZWjWSDCZ0LLrWS4NpCudiLJIr0ZFJ7BWd1xpeAWDW",
    "oFIwMWpgCZfTDipfTWsJjwZZdndtcqyfqeZ0aLnxJQishtZW2zVQH6OqLbBFRoV2wXrsMTYxQjG",
    "lsVBP81Kf1z3bvx+T5/373or+/XChfz8sbv/jyyESOZjR0q7z0cI6b1U4B8zkr8ORJRyZ42bPDx",
    "fwtRVyycLTzv90Yf5B/cX5N0ry6rN3+bXkr7dL8vZK+P3CX7//dh4e/Tx+58n4u08e/PTLn2W7y",
    "3rUlvSoZf9b3NO623nrVjH+YNY3zbP0ZCmR2blfbeDDeyU+2LG6F/e+P7t30vrs7mPaktOuNhDL",
    "Trbes9p6feslfWfv79heDYM4ywnS7wbFuc2OqcnPE+X93N/gj4MFXhHyxxe74d89Lu/j3gb7DnH",
    "UePgif7eXf+d4N3wuv79B/6PSfh9lvfsltRkaLsuZYDk+t+W5K468ZNzrouf/fvnn7atS725sid",
    "tWHnnJuF3tc63jr/v8dXWDlOYfvsJ2rMv3Lv3cq2bXr8Stz7pdjO/Pf0doRowHK04yxWc8bISrv",
    "v5H+P3M0X+zvrJt/Vf84Pzt3RNB+RSPLvnRsHjdl/Z3w/knCVStPh/+G/Wk6rnqoBTfduxFLNSX",
    "X3e9HfunvwBuoxmn",
    ""
  };

  static char newstr [1517] = "";
  newstr[0] = '\0';
  for (i = 0; i < 22; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c2_balldetection(SimStruct *S)
{
  const char* newstr = sf_c2_balldetection_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(1716904162U));
  ssSetChecksum1(S,(325823258U));
  ssSetChecksum2(S,(912157606U));
  ssSetChecksum3(S,(4191593554U));
}

static void mdlRTW_c2_balldetection(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c2_balldetection(SimStruct *S)
{
  SFc2_balldetectionInstanceStruct *chartInstance;
  chartInstance = (SFc2_balldetectionInstanceStruct *)utMalloc(sizeof
    (SFc2_balldetectionInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_balldetectionInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_balldetection;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_balldetection;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c2_balldetection;
  chartInstance->chartInfo.mdlTerminate =
    sf_opaque_mdl_terminate_c2_balldetection;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c2_balldetection;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_balldetection;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_balldetection;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_balldetection;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_balldetection;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_balldetection;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_balldetection;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_balldetection;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0,
    chartInstance->c2_JITStateAnimation,
    chartInstance->c2_JITTransitionAnimation);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c2_balldetection(chartInstance);
}

void c2_balldetection_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c2_balldetection(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_balldetection(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_balldetection(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_balldetection_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
