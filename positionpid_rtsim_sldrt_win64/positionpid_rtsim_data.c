/*
 * positionpid_rtsim_data.c
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

#include "positionpid_rtsim.h"

/* Block parameters (default storage) */
P_positionpid_rtsim_T positionpid_rtsim_P = {
  /* Variable: sens
   * Referenced by: '<Root>/pulse2deg1'
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

  /* Variable: PID
   * Referenced by:
   *   '<S1>/Derivative gain'
   *   '<S1>/Integral gain'
   *   '<S1>/Proportional gain'
   */
  {
    0.010139285364260639,
    0.066700700651598319,
    0.66700700651598321,
    10.521909242711375,
    0.701818718681377,
    15.774810669037917
  },

  /* Variable: Kw
   * Referenced by: '<S1>/Gain2'
   */
  5.882352941176471,

  /* Variable: deg2rad
   * Referenced by: '<S1>/deg2rad'
   */
  0.017453292519943295,

  /* Mask Parameter: AnalogOutput_FinalValue
   * Referenced by: '<S2>/Analog Output'
   */
  0.0,

  /* Mask Parameter: AnalogOutput_InitialValue
   * Referenced by: '<S2>/Analog Output'
   */
  0.0,

  /* Mask Parameter: EncoderInput_InputFilter
   * Referenced by: '<S2>/Encoder Input'
   */
  0.0,

  /* Mask Parameter: EncoderInput_MaxMissedTicks
   * Referenced by: '<S2>/Encoder Input'
   */
  10.0,

  /* Mask Parameter: AnalogInput_MaxMissedTicks
   * Referenced by: '<S2>/Analog Input'
   */
  10.0,

  /* Mask Parameter: AnalogOutput_MaxMissedTicks
   * Referenced by: '<S2>/Analog Output'
   */
  10.0,

  /* Mask Parameter: EncoderInput_YieldWhenWaiting
   * Referenced by: '<S2>/Encoder Input'
   */
  0.0,

  /* Mask Parameter: AnalogInput_YieldWhenWaiting
   * Referenced by: '<S2>/Analog Input'
   */
  0.0,

  /* Mask Parameter: AnalogOutput_YieldWhenWaiting
   * Referenced by: '<S2>/Analog Output'
   */
  0.0,

  /* Mask Parameter: EncoderInput_Channels
   * Referenced by: '<S2>/Encoder Input'
   */
  0,

  /* Mask Parameter: AnalogInput_Channels
   * Referenced by: '<S2>/Analog Input'
   */
  { 0, 1 },

  /* Mask Parameter: AnalogOutput_Channels
   * Referenced by: '<S2>/Analog Output'
   */
  0,

  /* Mask Parameter: AnalogInput_RangeMode
   * Referenced by: '<S2>/Analog Input'
   */
  0,

  /* Mask Parameter: AnalogOutput_RangeMode
   * Referenced by: '<S2>/Analog Output'
   */
  0,

  /* Mask Parameter: AnalogInput_VoltRange
   * Referenced by: '<S2>/Analog Input'
   */
  0,

  /* Mask Parameter: AnalogOutput_VoltRange
   * Referenced by: '<S2>/Analog Output'
   */
  0,

  /* Expression: 1
   * Referenced by: '<Root>/Step2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step2'
   */
  0.0,

  /* Expression: 120
   * Referenced by: '<Root>/Step2'
   */
  120.0,

  /* Computed Parameter: Realderivative_A
   * Referenced by: '<S1>/Real derivative'
   */
  -98.6262802627925,

  /* Computed Parameter: Realderivative_C
   * Referenced by: '<S1>/Real derivative'
   */
  -9727.1431584748952,

  /* Computed Parameter: Realderivative_D
   * Referenced by: '<S1>/Real derivative'
   */
  98.6262802627925,

  /* Expression: 0
   * Referenced by: '<S1>/Integrator'
   */
  0.0,

  /* Expression: 10
   * Referenced by: '<S1>/Saturation detection'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S1>/Saturation detection'
   */
  -10.0,

  /* Computed Parameter: Antiwindup_CurrentSetting
   * Referenced by: '<S1>/Anti wind-up'
   */
  1U
};
