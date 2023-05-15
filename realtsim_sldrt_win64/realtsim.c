/*
 * realtsim.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "realtsim".
 *
 * Model version              : 1.35
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Thu May 11 17:31:02 2023
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "realtsim.h"
#include "rtwtypes.h"
#include "realtsim_private.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "realtsim_dt.h"

/* options for Simulink Desktop Real-Time board 0 */
static double SLDRTBoardOptions0[] = {
  0.0,
  0.0,
  0.0,
  2.0,
  0.0,
  0.0,
  0.0,
};

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 1;
const double SLDRTTimers[2] = {
  0.001, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int SLDRTBoardCount = 1;
SLDRTBOARD SLDRTBoards[1] = {
  { "National_Instruments/PCIe-6321", 4294967295U, 7, SLDRTBoardOptions0 },
};

/* Block signals (default storage) */
B_realtsim_T realtsim_B;

/* Continuous states */
X_realtsim_T realtsim_X;

/* Block states (default storage) */
DW_realtsim_T realtsim_DW;

/* Real-time model */
static RT_MODEL_realtsim_T realtsim_M_;
RT_MODEL_realtsim_T *const realtsim_M = &realtsim_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  realtsim_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  realtsim_output();
  realtsim_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  realtsim_output();
  realtsim_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void realtsim_output(void)
{
  real_T rtb_AnalogInput[2];
  real_T rtb_deg2rad;
  real_T rtb_deg2rad1;
  if (rtmIsMajorTimeStep(realtsim_M)) {
    /* set solver stop time */
    if (!(realtsim_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&realtsim_M->solverInfo,
                            ((realtsim_M->Timing.clockTickH0 + 1) *
        realtsim_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&realtsim_M->solverInfo,
                            ((realtsim_M->Timing.clockTick0 + 1) *
        realtsim_M->Timing.stepSize0 + realtsim_M->Timing.clockTickH0 *
        realtsim_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(realtsim_M)) {
    realtsim_M->Timing.t[0] = rtsiGetT(&realtsim_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(realtsim_DW.EnabledSubsystem_SubsysRanBC_g);

  /* Reset subsysRan breadcrumbs */
  srClearBC(realtsim_DW.EnabledSubsystem_SubsysRanBC);

  /* TransferFcn: '<S3>/real derivative1' */
  rtb_deg2rad1 = realtsim_P.realderivative1_C[0] *
    realtsim_X.realderivative1_CSTATE[0];
  rtb_deg2rad1 += realtsim_P.realderivative1_C[1] *
    realtsim_X.realderivative1_CSTATE[1];

  /* Gain: '<S3>/rads2rpm' */
  realtsim_B.rads2rpm = realtsim_P.rads2rpm * rtb_deg2rad1;

  /* S-Function (sldrtai): '<Root>/Analog Input' */
  /* S-Function Block: <Root>/Analog Input */
  {
    ANALOGIOPARM parm;
    parm.mode = (RANGEMODE) realtsim_P.AnalogInput_RangeMode;
    parm.rangeidx = realtsim_P.AnalogInput_VoltRange;
    RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 2, realtsim_P.AnalogInput_Channels,
                   &rtb_AnalogInput[0], &parm);
  }

  /* S-Function (sldrtei): '<Root>/Encoder Input' */
  /* S-Function Block: <Root>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 0;
    parm.infilter = realtsim_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 1, &realtsim_P.EncoderInput_Channels,
                   &rtb_deg2rad1, &parm);
  }

  /* Gain: '<S1>/Gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  realtsim_B.Gain = (rtb_AnalogInput[0] - rtb_AnalogInput[1]) * realtsim_P.V2deg;

  /* Clock: '<S4>/Clock' */
  rtb_deg2rad = realtsim_M->Timing.t[0];

  /* Logic: '<S6>/AND' incorporates:
   *  Constant: '<S6>/Lower Limit'
   *  Constant: '<S6>/Upper Limit'
   *  RelationalOperator: '<S6>/Lower Test'
   *  RelationalOperator: '<S6>/Upper Test'
   */
  realtsim_B.AND = ((realtsim_P.IntervalTest_lowlimit <= rtb_deg2rad) &&
                    (rtb_deg2rad <= realtsim_P.IntervalTest_uplimit));
  if (rtmIsMajorTimeStep(realtsim_M)) {
    /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S5>/Enable'
     */
    if (realtsim_B.AND) {
      /* DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
      realtsim_B.DiscreteTimeIntegrator =
        realtsim_DW.DiscreteTimeIntegrator_DSTATE;
      if (rtsiIsModeUpdateTimeStep(&realtsim_M->solverInfo)) {
        srUpdateBC(realtsim_DW.EnabledSubsystem_SubsysRanBC_g);
      }
    }

    /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */

    /* Step: '<Root>/Step1' */
    if (realtsim_M->Timing.t[1] < realtsim_P.Step1_Time) {
      /* Step: '<Root>/Step1' */
      realtsim_B.Step1 = realtsim_P.Step1_Y0;
    } else {
      /* Step: '<Root>/Step1' */
      realtsim_B.Step1 = realtsim_P.Step1_YFinal;
    }

    /* End of Step: '<Root>/Step1' */

    /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S2>/Enable'
     */
    if (rtsiIsModeUpdateTimeStep(&realtsim_M->solverInfo)) {
      realtsim_DW.EnabledSubsystem_MODE = (realtsim_B.Step1 > 0.0);
    }

    /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem' */
  }

  /* Sum: '<S1>/Sum' */
  realtsim_B.Sum = realtsim_B.Gain - realtsim_B.DiscreteTimeIntegrator;

  /* Gain: '<S3>/rads2rpm1' incorporates:
   *  TransferFcn: '<S3>/real derivative2'
   */
  realtsim_B.rads2rpm1 = (realtsim_P.realderivative2_C[0] *
    realtsim_X.realderivative2_CSTATE[0] + realtsim_P.realderivative2_C[1] *
    realtsim_X.realderivative2_CSTATE[1]) * realtsim_P.rads2rpm;

  /* Gain: '<Root>/pulse2deg' */
  realtsim_B.pulse2deg = realtsim_P.sens.enc.pulse2deg * rtb_deg2rad1;

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (realtsim_DW.EnabledSubsystem_MODE) {
    real_T u0_tmp;
    if (rtmIsMajorTimeStep(realtsim_M)) {
    }

    /* Step: '<Root>/Step' */
    if (realtsim_M->Timing.t[0] < realtsim_P.Step_Time) {
      rtb_deg2rad = realtsim_P.Step_Y0;
    } else {
      rtb_deg2rad = realtsim_P.Step_YFinal;
    }

    /* Gain: '<S2>/deg2rad' incorporates:
     *  Step: '<Root>/Step'
     */
    rtb_deg2rad *= realtsim_P.deg2rad;

    /* Gain: '<S2>/deg2rad1' */
    rtb_deg2rad1 = realtsim_P.deg2rad * realtsim_B.Sum;

    /* Gain: '<S2>/deg2rad2' incorporates:
     *  Gain: '<S2>/deg2rad3'
     */
    u0_tmp = realtsim_P.deg2rad * realtsim_B.pulse2deg;

    /* Sum: '<S2>/Sum4' incorporates:
     *  Gain: '<S2>/deg2rad2'
     *  Gain: '<S2>/input feedforward gain'
     *  Gain: '<S2>/rpm2rads1'
     *  Gain: '<S2>/rpm2rads2'
     *  Gain: '<S2>/state feedback gain'
     *  Gain: '<S2>/state ff gain'
     *  Sum: '<S2>/Sum1'
     *  TransferFcn: '<S2>/Transfer Fcn'
     */
    rtb_deg2rad1 = (((((realtsim_P.Nx[0] * rtb_deg2rad - rtb_deg2rad1) *
                       realtsim_P.K[0] + (realtsim_P.Nx[1] * rtb_deg2rad -
      u0_tmp) * realtsim_P.K[1]) + (realtsim_P.Nx[2] * rtb_deg2rad -
      realtsim_P.rpm2rads * realtsim_B.rads2rpm) * realtsim_P.K[2]) +
                     (realtsim_P.Nx[3] * rtb_deg2rad - realtsim_P.rpm2rads *
                      realtsim_B.rads2rpm1) * realtsim_P.K[3]) + realtsim_P.Nu *
                    rtb_deg2rad) + realtsim_P.TransferFcn_C *
      realtsim_X.TransferFcn_CSTATE;

    /* Saturate: '<S2>/ Saturation' */
    if (rtb_deg2rad1 > realtsim_P.Saturation_UpperSat) {
      /* Saturate: '<S2>/ Saturation' */
      realtsim_B.Saturation = realtsim_P.Saturation_UpperSat;
    } else if (rtb_deg2rad1 < realtsim_P.Saturation_LowerSat) {
      /* Saturate: '<S2>/ Saturation' */
      realtsim_B.Saturation = realtsim_P.Saturation_LowerSat;
    } else {
      /* Saturate: '<S2>/ Saturation' */
      realtsim_B.Saturation = rtb_deg2rad1;
    }

    /* End of Saturate: '<S2>/ Saturation' */

    /* Gain: '<S2>/Gain' incorporates:
     *  Sum: '<S2>/Sum2'
     */
    realtsim_B.Gain_p = (rtb_deg2rad - u0_tmp) * realtsim_P.Ki;
    if (rtsiIsModeUpdateTimeStep(&realtsim_M->solverInfo)) {
      srUpdateBC(realtsim_DW.EnabledSubsystem_SubsysRanBC);
    }
  }

  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem' */

  /* S-Function (sldrtao): '<Root>/Analog Output' */
  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) realtsim_P.AnalogOutput_RangeMode;
      parm.rangeidx = realtsim_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &realtsim_P.AnalogOutput_Channels, ((real_T*)
        (&realtsim_B.Saturation)), &parm);
    }
  }

  if (rtmIsMajorTimeStep(realtsim_M)) {
  }

  /* Gain: '<S3>/deg2rad1' */
  realtsim_B.deg2rad1 = realtsim_P.deg2rad * realtsim_B.pulse2deg;

  /* Gain: '<S3>/deg2rad' */
  realtsim_B.deg2rad = realtsim_P.deg2rad * realtsim_B.Sum;
}

/* Model update function */
void realtsim_update(void)
{
  if (rtmIsMajorTimeStep(realtsim_M)) {
    /* Update for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S5>/Enable'
     */
    if (realtsim_B.AND) {
      /* Update for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
      realtsim_DW.DiscreteTimeIntegrator_DSTATE +=
        realtsim_P.DiscreteTimeIntegrator_gainval * realtsim_B.Gain;
    }

    /* End of Update for SubSystem: '<S4>/Enabled Subsystem' */
  }

  if (rtmIsMajorTimeStep(realtsim_M)) {
    rt_ertODEUpdateContinuousStates(&realtsim_M->solverInfo);
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
  if (!(++realtsim_M->Timing.clockTick0)) {
    ++realtsim_M->Timing.clockTickH0;
  }

  realtsim_M->Timing.t[0] = rtsiGetSolverStopTime(&realtsim_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++realtsim_M->Timing.clockTick1)) {
      ++realtsim_M->Timing.clockTickH1;
    }

    realtsim_M->Timing.t[1] = realtsim_M->Timing.clockTick1 *
      realtsim_M->Timing.stepSize1 + realtsim_M->Timing.clockTickH1 *
      realtsim_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void realtsim_derivatives(void)
{
  XDot_realtsim_T *_rtXdot;
  _rtXdot = ((XDot_realtsim_T *) realtsim_M->derivs);

  /* Derivatives for TransferFcn: '<S3>/real derivative1' */
  _rtXdot->realderivative1_CSTATE[0] = 0.0;
  _rtXdot->realderivative1_CSTATE[0] += realtsim_P.realderivative1_A[0] *
    realtsim_X.realderivative1_CSTATE[0];
  _rtXdot->realderivative1_CSTATE[1] = 0.0;
  _rtXdot->realderivative1_CSTATE[0] += realtsim_P.realderivative1_A[1] *
    realtsim_X.realderivative1_CSTATE[1];
  _rtXdot->realderivative1_CSTATE[1] += realtsim_X.realderivative1_CSTATE[0];
  _rtXdot->realderivative1_CSTATE[0] += realtsim_B.deg2rad;

  /* Derivatives for TransferFcn: '<S3>/real derivative2' */
  _rtXdot->realderivative2_CSTATE[0] = 0.0;
  _rtXdot->realderivative2_CSTATE[0] += realtsim_P.realderivative2_A[0] *
    realtsim_X.realderivative2_CSTATE[0];
  _rtXdot->realderivative2_CSTATE[1] = 0.0;
  _rtXdot->realderivative2_CSTATE[0] += realtsim_P.realderivative2_A[1] *
    realtsim_X.realderivative2_CSTATE[1];
  _rtXdot->realderivative2_CSTATE[1] += realtsim_X.realderivative2_CSTATE[0];
  _rtXdot->realderivative2_CSTATE[0] += realtsim_B.deg2rad1;

  /* Derivatives for Enabled SubSystem: '<Root>/Enabled Subsystem' */
  if (realtsim_DW.EnabledSubsystem_MODE) {
    /* Derivatives for TransferFcn: '<S2>/Transfer Fcn' */
    _rtXdot->TransferFcn_CSTATE = 0.0;
    _rtXdot->TransferFcn_CSTATE += realtsim_P.TransferFcn_A *
      realtsim_X.TransferFcn_CSTATE;
    _rtXdot->TransferFcn_CSTATE += realtsim_B.Gain_p;
  } else {
    ((XDot_realtsim_T *) realtsim_M->derivs)->TransferFcn_CSTATE = 0.0;
  }

  /* End of Derivatives for SubSystem: '<Root>/Enabled Subsystem' */
}

/* Model initialize function */
void realtsim_initialize(void)
{
  /* Start for Enabled SubSystem: '<Root>/Enabled Subsystem' */
  realtsim_DW.EnabledSubsystem_MODE = false;

  /* End of Start for SubSystem: '<Root>/Enabled Subsystem' */

  /* Start for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) realtsim_P.AnalogOutput_RangeMode;
      parm.rangeidx = realtsim_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &realtsim_P.AnalogOutput_Channels,
                     &realtsim_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for TransferFcn: '<S3>/real derivative1' */
  realtsim_X.realderivative1_CSTATE[0] = 0.0;
  realtsim_X.realderivative1_CSTATE[1] = 0.0;

  /* InitializeConditions for S-Function (sldrtei): '<Root>/Encoder Input' */

  /* S-Function Block: <Root>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 0;
    parm.infilter = realtsim_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 1,
                   &realtsim_P.EncoderInput_Channels, NULL, &parm);
  }

  /* InitializeConditions for TransferFcn: '<S3>/real derivative2' */
  realtsim_X.realderivative2_CSTATE[0] = 0.0;
  realtsim_X.realderivative2_CSTATE[1] = 0.0;

  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
  realtsim_DW.DiscreteTimeIntegrator_DSTATE =
    realtsim_P.DiscreteTimeIntegrator_IC;

  /* SystemInitialize for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' incorporates:
   *  Outport: '<S5>/Out'
   */
  realtsim_B.DiscreteTimeIntegrator = realtsim_P.Out_Y0;

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem' */
  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn' */
  realtsim_X.TransferFcn_CSTATE = 0.0;

  /* SystemInitialize for Saturate: '<S2>/ Saturation' incorporates:
   *  Outport: '<S2>/u [V]'
   */
  realtsim_B.Saturation = realtsim_P.uV_Y0;

  /* End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem' */
}

/* Model terminate function */
void realtsim_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) realtsim_P.AnalogOutput_RangeMode;
      parm.rangeidx = realtsim_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &realtsim_P.AnalogOutput_Channels,
                     &realtsim_P.AnalogOutput_FinalValue, &parm);
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
  realtsim_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  realtsim_update();
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
  realtsim_initialize();
}

void MdlTerminate(void)
{
  realtsim_terminate();
}

/* Registration function */
RT_MODEL_realtsim_T *realtsim(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  realtsim_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)realtsim_M, 0,
                sizeof(RT_MODEL_realtsim_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&realtsim_M->solverInfo,
                          &realtsim_M->Timing.simTimeStep);
    rtsiSetTPtr(&realtsim_M->solverInfo, &rtmGetTPtr(realtsim_M));
    rtsiSetStepSizePtr(&realtsim_M->solverInfo, &realtsim_M->Timing.stepSize0);
    rtsiSetdXPtr(&realtsim_M->solverInfo, &realtsim_M->derivs);
    rtsiSetContStatesPtr(&realtsim_M->solverInfo, (real_T **)
                         &realtsim_M->contStates);
    rtsiSetNumContStatesPtr(&realtsim_M->solverInfo,
      &realtsim_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&realtsim_M->solverInfo,
      &realtsim_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&realtsim_M->solverInfo,
      &realtsim_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&realtsim_M->solverInfo,
      &realtsim_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&realtsim_M->solverInfo, (&rtmGetErrorStatus
      (realtsim_M)));
    rtsiSetRTModelPtr(&realtsim_M->solverInfo, realtsim_M);
  }

  rtsiSetSimTimeStep(&realtsim_M->solverInfo, MAJOR_TIME_STEP);
  realtsim_M->intgData.y = realtsim_M->odeY;
  realtsim_M->intgData.f[0] = realtsim_M->odeF[0];
  realtsim_M->intgData.f[1] = realtsim_M->odeF[1];
  realtsim_M->intgData.f[2] = realtsim_M->odeF[2];
  realtsim_M->contStates = ((real_T *) &realtsim_X);
  rtsiSetSolverData(&realtsim_M->solverInfo, (void *)&realtsim_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&realtsim_M->solverInfo, false);
  rtsiSetSolverName(&realtsim_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = realtsim_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "realtsim_M points to
       static memory which is guaranteed to be non-NULL" */
    realtsim_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    realtsim_M->Timing.sampleTimes = (&realtsim_M->Timing.sampleTimesArray[0]);
    realtsim_M->Timing.offsetTimes = (&realtsim_M->Timing.offsetTimesArray[0]);

    /* task periods */
    realtsim_M->Timing.sampleTimes[0] = (0.0);
    realtsim_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    realtsim_M->Timing.offsetTimes[0] = (0.0);
    realtsim_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(realtsim_M, &realtsim_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = realtsim_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    realtsim_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(realtsim_M, 9.0);
  realtsim_M->Timing.stepSize0 = 0.001;
  realtsim_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  realtsim_M->Sizes.checksums[0] = (3215892544U);
  realtsim_M->Sizes.checksums[1] = (3574296525U);
  realtsim_M->Sizes.checksums[2] = (3732778097U);
  realtsim_M->Sizes.checksums[3] = (146666970U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    realtsim_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&realtsim_DW.EnabledSubsystem_SubsysRanBC_g;
    systemRan[2] = (sysRanDType *)&realtsim_DW.EnabledSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(realtsim_M->extModeInfo,
      &realtsim_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(realtsim_M->extModeInfo, realtsim_M->Sizes.checksums);
    rteiSetTPtr(realtsim_M->extModeInfo, rtmGetTPtr(realtsim_M));
  }

  realtsim_M->solverInfoPtr = (&realtsim_M->solverInfo);
  realtsim_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&realtsim_M->solverInfo, 0.001);
  rtsiSetSolverMode(&realtsim_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  realtsim_M->blockIO = ((void *) &realtsim_B);
  (void) memset(((void *) &realtsim_B), 0,
                sizeof(B_realtsim_T));

  /* parameters */
  realtsim_M->defaultParam = ((real_T *)&realtsim_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &realtsim_X;
    realtsim_M->contStates = (x);
    (void) memset((void *)&realtsim_X, 0,
                  sizeof(X_realtsim_T));
  }

  /* states (dwork) */
  realtsim_M->dwork = ((void *) &realtsim_DW);
  (void) memset((void *)&realtsim_DW, 0,
                sizeof(DW_realtsim_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    realtsim_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 30;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  realtsim_M->Sizes.numContStates = (5);/* Number of continuous states */
  realtsim_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  realtsim_M->Sizes.numY = (0);        /* Number of model outputs */
  realtsim_M->Sizes.numU = (0);        /* Number of model inputs */
  realtsim_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  realtsim_M->Sizes.numSampTimes = (2);/* Number of sample times */
  realtsim_M->Sizes.numBlocks = (44);  /* Number of blocks */
  realtsim_M->Sizes.numBlockIO = (12); /* Number of block outputs */
  realtsim_M->Sizes.numBlockPrms = (56);/* Sum of parameter "widths" */
  return realtsim_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
