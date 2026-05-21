#ifndef __c2_balldetection_h__
#define __c2_balldetection_h__

/* Forward Declarations */
#ifndef typedef_c2_cell_0
#define typedef_c2_cell_0

typedef struct c2_tag_lfyg79q6Kpk0jaJgYJuk8C c2_cell_0;

#endif                                 /* typedef_c2_cell_0 */

#ifndef typedef_c2_cell_wrap_1
#define typedef_c2_cell_wrap_1

typedef struct c2_tag_uwJsGEKtvfiUxcdf0z0AYH c2_cell_wrap_1;

#endif                                 /* typedef_c2_cell_wrap_1 */

#ifndef typedef_c2_s_WSTEAPgNJmllMDXoFTifcF
#define typedef_c2_s_WSTEAPgNJmllMDXoFTifcF

typedef struct c2_tag_WSTEAPgNJmllMDXoFTifcF c2_s_WSTEAPgNJmllMDXoFTifcF;

#endif                                 /* typedef_c2_s_WSTEAPgNJmllMDXoFTifcF */

#ifndef typedef_c2_s_MY3jsqmREaTzOC09vCGedD
#define typedef_c2_s_MY3jsqmREaTzOC09vCGedD

typedef struct c2_tag_MY3jsqmREaTzOC09vCGedD c2_s_MY3jsqmREaTzOC09vCGedD;

#endif                                 /* typedef_c2_s_MY3jsqmREaTzOC09vCGedD */

/* Type Definitions */
#ifndef struct_c2_tag_lfyg79q6Kpk0jaJgYJuk8C
#define struct_c2_tag_lfyg79q6Kpk0jaJgYJuk8C

struct c2_tag_lfyg79q6Kpk0jaJgYJuk8C
{
  char_T f1[5];
  char_T f2[6];
  char_T f3[6];
  char_T f4[6];
};

#endif                                 /* struct_c2_tag_lfyg79q6Kpk0jaJgYJuk8C */

#ifndef typedef_c2_cell_0
#define typedef_c2_cell_0

typedef struct c2_tag_lfyg79q6Kpk0jaJgYJuk8C c2_cell_0;

#endif                                 /* typedef_c2_cell_0 */

#ifndef struct_c2_tag_uwJsGEKtvfiUxcdf0z0AYH
#define struct_c2_tag_uwJsGEKtvfiUxcdf0z0AYH

struct c2_tag_uwJsGEKtvfiUxcdf0z0AYH
{
  char_T f1[4];
};

#endif                                 /* struct_c2_tag_uwJsGEKtvfiUxcdf0z0AYH */

#ifndef typedef_c2_cell_wrap_1
#define typedef_c2_cell_wrap_1

typedef struct c2_tag_uwJsGEKtvfiUxcdf0z0AYH c2_cell_wrap_1;

#endif                                 /* typedef_c2_cell_wrap_1 */

#ifndef struct_c2_tag_WSTEAPgNJmllMDXoFTifcF
#define struct_c2_tag_WSTEAPgNJmllMDXoFTifcF

struct c2_tag_WSTEAPgNJmllMDXoFTifcF
{
  c2_cell_0 _data;
};

#endif                                 /* struct_c2_tag_WSTEAPgNJmllMDXoFTifcF */

#ifndef typedef_c2_s_WSTEAPgNJmllMDXoFTifcF
#define typedef_c2_s_WSTEAPgNJmllMDXoFTifcF

typedef struct c2_tag_WSTEAPgNJmllMDXoFTifcF c2_s_WSTEAPgNJmllMDXoFTifcF;

#endif                                 /* typedef_c2_s_WSTEAPgNJmllMDXoFTifcF */

#ifndef struct_c2_tag_MY3jsqmREaTzOC09vCGedD
#define struct_c2_tag_MY3jsqmREaTzOC09vCGedD

struct c2_tag_MY3jsqmREaTzOC09vCGedD
{
  c2_cell_wrap_1 _data;
};

#endif                                 /* struct_c2_tag_MY3jsqmREaTzOC09vCGedD */

#ifndef typedef_c2_s_MY3jsqmREaTzOC09vCGedD
#define typedef_c2_s_MY3jsqmREaTzOC09vCGedD

typedef struct c2_tag_MY3jsqmREaTzOC09vCGedD c2_s_MY3jsqmREaTzOC09vCGedD;

#endif                                 /* typedef_c2_s_MY3jsqmREaTzOC09vCGedD */

#ifndef typedef_SFc2_balldetectionInstanceStruct
#define typedef_SFc2_balldetectionInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_balldetection;
  uint8_T c2_JITStateAnimation[1];
  uint8_T c2_JITTransitionAnimation[1];
  int32_T c2_IsDebuggerActive;
  int32_T c2_IsSequenceViewerPresent;
  int32_T c2_SequenceViewerOptimization;
  int32_T c2_IsHeatMapPresent;
  void *c2_RuntimeVar;
  uint32_T c2_mlFcnLineNumber;
  void *c2_fcnDataPtrs[9];
  char_T *c2_dataNames[9];
  uint32_T c2_numFcnVars;
  uint32_T c2_ssIds[9];
  uint32_T c2_statuses[9];
  void *c2_outMexFcns[9];
  void *c2_inMexFcns[9];
  real32_T c2_I[2764800];
  boolean_T c2_bv[921600];
  boolean_T c2_b_bv[921600];
  boolean_T c2_c_bv[921600];
  CovrtStateflowInstance *c2_covrtInstance;
  void *c2_fEmlrtCtx;
  real32_T (*c2_RGB)[2764800];
  boolean_T (*c2_BW)[921600];
  real_T *c2_hMin;
  real_T *c2_hMax;
  real_T *c2_sMin;
  real_T *c2_sMax;
  real_T *c2_vMin;
  real_T *c2_vMax;
} SFc2_balldetectionInstanceStruct;

#endif                                 /* typedef_SFc2_balldetectionInstanceStruct */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_balldetection_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_balldetection_get_check_sum(mxArray *plhs[]);
extern void c2_balldetection_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
