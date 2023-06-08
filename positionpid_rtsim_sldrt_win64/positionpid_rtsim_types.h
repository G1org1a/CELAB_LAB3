/*
 * positionpid_rtsim_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "positionpid_rtsim".
 *
 * Model version              : 1.37
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Thu Jun  8 14:18:20 2023
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_positionpid_rtsim_types_h_
#define RTW_HEADER_positionpid_rtsim_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_struct_3axzsN0WIOkRwSvuNnRPeF_
#define DEFINED_TYPEDEF_FOR_struct_3axzsN0WIOkRwSvuNnRPeF_

typedef struct {
  real_T Tl;
  real_T Td;
  real_T Ti;
  real_T Kp;
  real_T Kd;
  real_T Ki;
} struct_3axzsN0WIOkRwSvuNnRPeF;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_vHPMdAr9HfDgWNbG6U3SfC_
#define DEFINED_TYPEDEF_FOR_struct_vHPMdAr9HfDgWNbG6U3SfC_

typedef struct {
  real_T Rs;
} struct_vHPMdAr9HfDgWNbG6U3SfC;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_nZqFUEOh71pPhzsMP64FWD_
#define DEFINED_TYPEDEF_FOR_struct_nZqFUEOh71pPhzsMP64FWD_

typedef struct {
  real_T ppr;
  real_T pulse2deg;
  real_T pulse2rad;
  real_T deg2pulse;
  real_T rad2pulse;
} struct_nZqFUEOh71pPhzsMP64FWD;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_DqRrFctOcoTwJhkxMXTGZG_
#define DEFINED_TYPEDEF_FOR_struct_DqRrFctOcoTwJhkxMXTGZG_

typedef struct {
  real_T R;
  real_T V;
  real_T th_deg;
  real_T th;
} struct_DqRrFctOcoTwJhkxMXTGZG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_t4jfYKvXkqvqbOrnXV9flF_
#define DEFINED_TYPEDEF_FOR_struct_t4jfYKvXkqvqbOrnXV9flF_

typedef struct {
  struct_DqRrFctOcoTwJhkxMXTGZG range;
  real_T deg2V;
  real_T rad2V;
  real_T V2deg;
  real_T V2rad;
} struct_t4jfYKvXkqvqbOrnXV9flF;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_i7ZlkOl9k9qbhxQhPErSIE_
#define DEFINED_TYPEDEF_FOR_struct_i7ZlkOl9k9qbhxQhPErSIE_

typedef struct {
  real_T var;
} struct_i7ZlkOl9k9qbhxQhPErSIE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_nhbocl71hD6FRzHagkwJFB_
#define DEFINED_TYPEDEF_FOR_struct_nhbocl71hD6FRzHagkwJFB_

typedef struct {
  struct_DqRrFctOcoTwJhkxMXTGZG range;
  real_T deg2V;
  real_T rad2V;
  real_T V2deg;
  real_T V2rad;
  struct_i7ZlkOl9k9qbhxQhPErSIE noise;
} struct_nhbocl71hD6FRzHagkwJFB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_4jr0aBoeUcVnCi5PWU4anE_
#define DEFINED_TYPEDEF_FOR_struct_4jr0aBoeUcVnCi5PWU4anE_

typedef struct {
  struct_vHPMdAr9HfDgWNbG6U3SfC curr;
  struct_nZqFUEOh71pPhzsMP64FWD enc;
  struct_t4jfYKvXkqvqbOrnXV9flF pot1;
  struct_nhbocl71hD6FRzHagkwJFB pot2;
} struct_4jr0aBoeUcVnCi5PWU4anE;

#endif

/* Parameters (default storage) */
typedef struct P_positionpid_rtsim_T_ P_positionpid_rtsim_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_positionpid_rtsim_T RT_MODEL_positionpid_rtsim_T;

#endif                               /* RTW_HEADER_positionpid_rtsim_types_h_ */
