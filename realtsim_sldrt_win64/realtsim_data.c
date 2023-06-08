/*
 * realtsim_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "realtsim".
 *
 * Model version              : 1.38
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Thu Jun  8 16:29:54 2023
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "realtsim.h"

/* Block parameters (default storage) */
P_realtsim_T realtsim_P = {
  /* Variable: sens
   * Referenced by: '<Root>/pulse2deg'
   */
  {
    {
      0.5
    },

    {
      2000.0,
      0.18,
      0.0031415926535897933,
      5.5555555555555554,
      318.3098861837907
    },

    {
      {
        10000.0,
        5.0,
        345.0,
        6.0213859193804371
      },
      0.014492753623188406,
      0.83037361613162786,
      69.0,
      1.2042771838760873
    },

    {
      {
        10000.0,
        5.0,
        340.0,
        5.9341194567807207
      },
      0.014705882352941176,
      0.84258499283944588,
      68.0,
      1.1868238913561442,

      {
        3.5e-7
      }
    }
  },

  /* Variable: K
   * Referenced by: '<S2>/state feedback gain'
   */
  { 0.11253686899080279, 65.859141494106, -0.096755843140633721,
    -0.45417331778275366 },

  /* Variable: Ki
   * Referenced by: '<S2>/Gain'
   */
  0.15955065370091615,

  /* Variable: Nu
   * Referenced by: '<S2>/input feedforward gain'
   */
  0.0,

  /* Variable: Nx
   * Referenced by: '<S2>/state ff gain'
   */
  { 1.0, -0.0, -0.0, 0.0 },

  /* Variable: V2deg
   * Referenced by: '<S1>/Gain'
   */
  68.0,

  /* Variable: deg2rad
   * Referenced by:
   *   '<S2>/deg2rad'
   *   '<S2>/deg2rad1'
   *   '<S2>/deg2rad2'
   *   '<S2>/deg2rad3'
   *   '<S4>/deg2rad'
   *   '<S4>/deg2rad1'
   */
  0.017453292519943295,

  /* Variable: rads2rpm
   * Referenced by:
   *   '<S4>/rads2rpm'
   *   '<S4>/rads2rpm1'
   */
  9.5492965855137211,

  /* Variable: rpm2rads
   * Referenced by:
   *   '<S2>/rpm2rads1'
   *   '<S2>/rpm2rads2'
   */
  0.10471975511965977,

  /* Mask Parameter: AnalogOutput_FinalValue
   * Referenced by: '<S3>/Analog Output'
   */
  0.0,

  /* Mask Parameter: AnalogOutput_InitialValue
   * Referenced by: '<S3>/Analog Output'
   */
  0.0,

  /* Mask Parameter: EncoderInput_InputFilter
   * Referenced by: '<S3>/Encoder Input'
   */
  0.0,

  /* Mask Parameter: EncoderInput_MaxMissedTicks
   * Referenced by: '<S3>/Encoder Input'
   */
  10.0,

  /* Mask Parameter: AnalogInput_MaxMissedTicks
   * Referenced by: '<S3>/Analog Input'
   */
  10.0,

  /* Mask Parameter: AnalogOutput_MaxMissedTicks
   * Referenced by: '<S3>/Analog Output'
   */
  10.0,

  /* Mask Parameter: EncoderInput_YieldWhenWaiting
   * Referenced by: '<S3>/Encoder Input'
   */
  0.0,

  /* Mask Parameter: AnalogInput_YieldWhenWaiting
   * Referenced by: '<S3>/Analog Input'
   */
  0.0,

  /* Mask Parameter: AnalogOutput_YieldWhenWaiting
   * Referenced by: '<S3>/Analog Output'
   */
  0.0,

  /* Mask Parameter: IntervalTest_lowlimit
   * Referenced by: '<S7>/Lower Limit'
   */
  0.2,

  /* Mask Parameter: IntervalTest_uplimit
   * Referenced by: '<S7>/Upper Limit'
   */
  0.7,

  /* Mask Parameter: EncoderInput_Channels
   * Referenced by: '<S3>/Encoder Input'
   */
  0,

  /* Mask Parameter: AnalogInput_Channels
   * Referenced by: '<S3>/Analog Input'
   */
  { 2, 3 },

  /* Mask Parameter: AnalogOutput_Channels
   * Referenced by: '<S3>/Analog Output'
   */
  0,

  /* Mask Parameter: AnalogInput_RangeMode
   * Referenced by: '<S3>/Analog Input'
   */
  0,

  /* Mask Parameter: AnalogOutput_RangeMode
   * Referenced by: '<S3>/Analog Output'
   */
  0,

  /* Mask Parameter: AnalogInput_VoltRange
   * Referenced by: '<S3>/Analog Input'
   */
  1,

  /* Mask Parameter: AnalogOutput_VoltRange
   * Referenced by: '<S3>/Analog Output'
   */
  0,

  /* Computed Parameter: Out_Y0
   * Referenced by: '<S6>/Out'
   */
  0.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<S6>/Discrete-Time Integrator'
   */
  0.002,

  /* Expression: 0
   * Referenced by: '<S6>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: uV_Y0
   * Referenced by: '<S2>/u [V]'
   */
  0.0,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<S2>/Transfer Fcn'
   */
  -0.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<S2>/Transfer Fcn'
   */
  1.0,

  /* Expression: 12
   * Referenced by: '<S2>/ Saturation'
   */
  12.0,

  /* Expression: -12
   * Referenced by: '<S2>/ Saturation'
   */
  -12.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step2'
   */
  0.0,

  /* Expression: 50
   * Referenced by: '<Root>/Step2'
   */
  50.0,

  /* Computed Parameter: realderivative1_A
   * Referenced by: '<S4>/real derivative1'
   */
  { -444.2882938158366, -98696.044010893587 },

  /* Computed Parameter: realderivative1_C
   * Referenced by: '<S4>/real derivative1'
   */
  { 98696.044010893587, 0.0 },

  /* Computed Parameter: realderivative2_A
   * Referenced by: '<S4>/real derivative2'
   */
  { -444.2882938158366, -98696.044010893587 },

  /* Computed Parameter: realderivative2_C
   * Referenced by: '<S4>/real derivative2'
   */
  { 98696.044010893587, 0.0 },

  /* Expression: 0.53
   * Referenced by: '<Root>/Step3'
   */
  0.53,

  /* Expression: 0
   * Referenced by: '<Root>/Step3'
   */
  0.0,

  /* Expression: 50
   * Referenced by: '<Root>/Step3'
   */
  50.0
};
