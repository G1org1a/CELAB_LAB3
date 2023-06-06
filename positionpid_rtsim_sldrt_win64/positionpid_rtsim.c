/*
 * positionpid_rtsim.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "positionpid_rtsim".
 *
 * Model version              : 1.35
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Thu May 11 17:25:35 2023
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "positionpid_rtsim.h"
#include "rtwtypes.h"
#include "positionpid_rtsim_private.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "positionpid_rtsim_dt.h"

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
B_positionpid_rtsim_T positionpid_rtsim_B;

/* Continuous states */
X_positionpid_rtsim_T positionpid_rtsim_X;

/* Block states (default storage) */
DW_positionpid_rtsim_T positionpid_rtsim_DW;

/* Real-time model */
static RT_MODEL_positionpid_rtsim_T positionpid_rtsim_M_;
RT_MODEL_positionpid_rtsim_T *const positionpid_rtsim_M = &positionpid_rtsim_M_;

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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  positionpid_rtsim_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  positionpid_rtsim_output();
  positionpid_rtsim_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  positionpid_rtsim_output();
  positionpid_rtsim_derivatives();

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
void positionpid_rtsim_output(void)
{
  /* local block i/o variables */
  real_T rtb_AnalogInput[2];
  real_T rtb_Antiwindup;
  real_T rtb_Saturationdetection;
  real_T rtb_deg2rad;
  if (rtmIsMajorTimeStep(positionpid_rtsim_M)) {
    /* set solver stop time */
    if (!(positionpid_rtsim_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&positionpid_rtsim_M->solverInfo,
                            ((positionpid_rtsim_M->Timing.clockTickH0 + 1) *
        positionpid_rtsim_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&positionpid_rtsim_M->solverInfo,
                            ((positionpid_rtsim_M->Timing.clockTick0 + 1) *
        positionpid_rtsim_M->Timing.stepSize0 +
        positionpid_rtsim_M->Timing.clockTickH0 *
        positionpid_rtsim_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(positionpid_rtsim_M)) {
    positionpid_rtsim_M->Timing.t[0] = rtsiGetT(&positionpid_rtsim_M->solverInfo);
  }

  /* S-Function (sldrtei): '<S2>/Encoder Input' */
  /* S-Function Block: <S2>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 0;
    parm.infilter = positionpid_rtsim_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 1,
                   &positionpid_rtsim_P.EncoderInput_Channels, &rtb_deg2rad,
                   &parm);
  }

  if (rtmIsMajorTimeStep(positionpid_rtsim_M)) {
    /* S-Function (sldrtai): '<S2>/Analog Input' */
    /* S-Function Block: <S2>/Analog Input */
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) positionpid_rtsim_P.AnalogInput_RangeMode;
      parm.rangeidx = positionpid_rtsim_P.AnalogInput_VoltRange;
      RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 2,
                     positionpid_rtsim_P.AnalogInput_Channels, &rtb_AnalogInput
                     [0], &parm);
    }
  }

  /* Gain: '<Root>/pulse2deg1' */
  positionpid_rtsim_B.thl_meas = positionpid_rtsim_P.sens.enc.pulse2deg *
    rtb_deg2rad;

  /* Step: '<Root>/Step2' */
  if (positionpid_rtsim_M->Timing.t[0] < positionpid_rtsim_P.Step2_Time) {
    /* Step: '<Root>/Step2' */
    positionpid_rtsim_B.Step2 = positionpid_rtsim_P.Step2_Y0;
  } else {
    /* Step: '<Root>/Step2' */
    positionpid_rtsim_B.Step2 = positionpid_rtsim_P.Step2_YFinal;
  }

  /* End of Step: '<Root>/Step2' */
  if (rtmIsMajorTimeStep(positionpid_rtsim_M)) {
  }

  /* Gain: '<S1>/deg2rad' incorporates:
   *  Sum: '<Root>/Sum'
   */
  rtb_deg2rad = (positionpid_rtsim_B.Step2 - positionpid_rtsim_B.thl_meas) *
    positionpid_rtsim_P.deg2rad;

  /* Gain: '<S1>/Derivative gain' */
  positionpid_rtsim_B.Derivativegain = positionpid_rtsim_P.PID.Kd * rtb_deg2rad;

  /* Integrator: '<S1>/Integrator' */
  rtb_Saturationdetection = positionpid_rtsim_X.Integrator_CSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Proportional gain'
   *  TransferFcn: '<S1>/Real derivative'
   */
  rtb_Antiwindup = ((positionpid_rtsim_P.Realderivative_C *
                     positionpid_rtsim_X.Realderivative_CSTATE +
                     positionpid_rtsim_P.Realderivative_D *
                     positionpid_rtsim_B.Derivativegain) +
                    positionpid_rtsim_P.PID.Kp * rtb_deg2rad) +
    rtb_Saturationdetection;

  /* Saturate: '<S1>/Saturation detection' */
  if (rtb_Antiwindup > positionpid_rtsim_P.Saturationdetection_UpperSat) {
    rtb_Saturationdetection = positionpid_rtsim_P.Saturationdetection_UpperSat;
  } else if (rtb_Antiwindup < positionpid_rtsim_P.Saturationdetection_LowerSat)
  {
    rtb_Saturationdetection = positionpid_rtsim_P.Saturationdetection_LowerSat;
  } else {
    rtb_Saturationdetection = rtb_Antiwindup;
  }

  /* End of Saturate: '<S1>/Saturation detection' */

  /* Sum: '<S1>/Sum1' */
  positionpid_rtsim_B.Sum1 = rtb_Antiwindup - rtb_Saturationdetection;
  if (rtmIsMajorTimeStep(positionpid_rtsim_M)) {
  }

  /* ManualSwitch: '<S1>/Anti wind-up' incorporates:
   *  Gain: '<S1>/Gain2'
   */
  if (positionpid_rtsim_P.Antiwindup_CurrentSetting == 1) {
    rtb_Antiwindup = positionpid_rtsim_P.Kw * positionpid_rtsim_B.Sum1;
  } else {
    rtb_Antiwindup = 0.0;
  }

  /* Sum: '<S1>/Sum2' incorporates:
   *  Gain: '<S1>/Integral gain'
   *  ManualSwitch: '<S1>/Anti wind-up'
   */
  positionpid_rtsim_B.Sum2 = positionpid_rtsim_P.PID.Ki * rtb_deg2rad -
    rtb_Antiwindup;

  /* S-Function (sldrtao): '<S2>/Analog Output' */
  /* S-Function Block: <S2>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) positionpid_rtsim_P.AnalogOutput_RangeMode;
      parm.rangeidx = positionpid_rtsim_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &positionpid_rtsim_P.AnalogOutput_Channels, ((real_T*)
        (&rtb_Saturationdetection)), &parm);
    }
  }
}

/* Model update function */
void positionpid_rtsim_update(void)
{
  if (rtmIsMajorTimeStep(positionpid_rtsim_M)) {
    rt_ertODEUpdateContinuousStates(&positionpid_rtsim_M->solverInfo);
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
  if (!(++positionpid_rtsim_M->Timing.clockTick0)) {
    ++positionpid_rtsim_M->Timing.clockTickH0;
  }

  positionpid_rtsim_M->Timing.t[0] = rtsiGetSolverStopTime
    (&positionpid_rtsim_M->solverInfo);

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
    if (!(++positionpid_rtsim_M->Timing.clockTick1)) {
      ++positionpid_rtsim_M->Timing.clockTickH1;
    }

    positionpid_rtsim_M->Timing.t[1] = positionpid_rtsim_M->Timing.clockTick1 *
      positionpid_rtsim_M->Timing.stepSize1 +
      positionpid_rtsim_M->Timing.clockTickH1 *
      positionpid_rtsim_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void positionpid_rtsim_derivatives(void)
{
  XDot_positionpid_rtsim_T *_rtXdot;
  _rtXdot = ((XDot_positionpid_rtsim_T *) positionpid_rtsim_M->derivs);

  /* Derivatives for TransferFcn: '<S1>/Real derivative' */
  _rtXdot->Realderivative_CSTATE = positionpid_rtsim_P.Realderivative_A *
    positionpid_rtsim_X.Realderivative_CSTATE;
  _rtXdot->Realderivative_CSTATE += positionpid_rtsim_B.Derivativegain;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE = positionpid_rtsim_B.Sum2;
}

/* Model initialize function */
void positionpid_rtsim_initialize(void)
{
  /* Start for S-Function (sldrtao): '<S2>/Analog Output' */

  /* S-Function Block: <S2>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) positionpid_rtsim_P.AnalogOutput_RangeMode;
      parm.rangeidx = positionpid_rtsim_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &positionpid_rtsim_P.AnalogOutput_Channels,
                     &positionpid_rtsim_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for S-Function (sldrtei): '<S2>/Encoder Input' */

  /* S-Function Block: <S2>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 0;
    parm.infilter = positionpid_rtsim_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 1,
                   &positionpid_rtsim_P.EncoderInput_Channels, NULL, &parm);
  }

  /* InitializeConditions for TransferFcn: '<S1>/Real derivative' */
  positionpid_rtsim_X.Realderivative_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  positionpid_rtsim_X.Integrator_CSTATE = positionpid_rtsim_P.Integrator_IC;
}

/* Model terminate function */
void positionpid_rtsim_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<S2>/Analog Output' */

  /* S-Function Block: <S2>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) positionpid_rtsim_P.AnalogOutput_RangeMode;
      parm.rangeidx = positionpid_rtsim_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &positionpid_rtsim_P.AnalogOutput_Channels,
                     &positionpid_rtsim_P.AnalogOutput_FinalValue, &parm);
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
  positionpid_rtsim_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  positionpid_rtsim_update();
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
  positionpid_rtsim_initialize();
}

void MdlTerminate(void)
{
  positionpid_rtsim_terminate();
}

/* Registration function */
RT_MODEL_positionpid_rtsim_T *positionpid_rtsim(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  positionpid_rtsim_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)positionpid_rtsim_M, 0,
                sizeof(RT_MODEL_positionpid_rtsim_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&positionpid_rtsim_M->solverInfo,
                          &positionpid_rtsim_M->Timing.simTimeStep);
    rtsiSetTPtr(&positionpid_rtsim_M->solverInfo, &rtmGetTPtr
                (positionpid_rtsim_M));
    rtsiSetStepSizePtr(&positionpid_rtsim_M->solverInfo,
                       &positionpid_rtsim_M->Timing.stepSize0);
    rtsiSetdXPtr(&positionpid_rtsim_M->solverInfo, &positionpid_rtsim_M->derivs);
    rtsiSetContStatesPtr(&positionpid_rtsim_M->solverInfo, (real_T **)
                         &positionpid_rtsim_M->contStates);
    rtsiSetNumContStatesPtr(&positionpid_rtsim_M->solverInfo,
      &positionpid_rtsim_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&positionpid_rtsim_M->solverInfo,
      &positionpid_rtsim_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&positionpid_rtsim_M->solverInfo,
      &positionpid_rtsim_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&positionpid_rtsim_M->solverInfo,
      &positionpid_rtsim_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&positionpid_rtsim_M->solverInfo, (&rtmGetErrorStatus
      (positionpid_rtsim_M)));
    rtsiSetRTModelPtr(&positionpid_rtsim_M->solverInfo, positionpid_rtsim_M);
  }

  rtsiSetSimTimeStep(&positionpid_rtsim_M->solverInfo, MAJOR_TIME_STEP);
  positionpid_rtsim_M->intgData.y = positionpid_rtsim_M->odeY;
  positionpid_rtsim_M->intgData.f[0] = positionpid_rtsim_M->odeF[0];
  positionpid_rtsim_M->intgData.f[1] = positionpid_rtsim_M->odeF[1];
  positionpid_rtsim_M->intgData.f[2] = positionpid_rtsim_M->odeF[2];
  positionpid_rtsim_M->contStates = ((real_T *) &positionpid_rtsim_X);
  rtsiSetSolverData(&positionpid_rtsim_M->solverInfo, (void *)
                    &positionpid_rtsim_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&positionpid_rtsim_M->solverInfo, false);
  rtsiSetSolverName(&positionpid_rtsim_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = positionpid_rtsim_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "positionpid_rtsim_M points to
       static memory which is guaranteed to be non-NULL" */
    positionpid_rtsim_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    positionpid_rtsim_M->Timing.sampleTimes =
      (&positionpid_rtsim_M->Timing.sampleTimesArray[0]);
    positionpid_rtsim_M->Timing.offsetTimes =
      (&positionpid_rtsim_M->Timing.offsetTimesArray[0]);

    /* task periods */
    positionpid_rtsim_M->Timing.sampleTimes[0] = (0.0);
    positionpid_rtsim_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    positionpid_rtsim_M->Timing.offsetTimes[0] = (0.0);
    positionpid_rtsim_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(positionpid_rtsim_M, &positionpid_rtsim_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = positionpid_rtsim_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    positionpid_rtsim_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(positionpid_rtsim_M, 5.0);
  positionpid_rtsim_M->Timing.stepSize0 = 0.001;
  positionpid_rtsim_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  positionpid_rtsim_M->Sizes.checksums[0] = (1423480159U);
  positionpid_rtsim_M->Sizes.checksums[1] = (1610004999U);
  positionpid_rtsim_M->Sizes.checksums[2] = (2477451714U);
  positionpid_rtsim_M->Sizes.checksums[3] = (858378292U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    positionpid_rtsim_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(positionpid_rtsim_M->extModeInfo,
      &positionpid_rtsim_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(positionpid_rtsim_M->extModeInfo,
                        positionpid_rtsim_M->Sizes.checksums);
    rteiSetTPtr(positionpid_rtsim_M->extModeInfo, rtmGetTPtr(positionpid_rtsim_M));
  }

  positionpid_rtsim_M->solverInfoPtr = (&positionpid_rtsim_M->solverInfo);
  positionpid_rtsim_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&positionpid_rtsim_M->solverInfo, 0.001);
  rtsiSetSolverMode(&positionpid_rtsim_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  positionpid_rtsim_M->blockIO = ((void *) &positionpid_rtsim_B);
  (void) memset(((void *) &positionpid_rtsim_B), 0,
                sizeof(B_positionpid_rtsim_T));

  /* parameters */
  positionpid_rtsim_M->defaultParam = ((real_T *)&positionpid_rtsim_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &positionpid_rtsim_X;
    positionpid_rtsim_M->contStates = (x);
    (void) memset((void *)&positionpid_rtsim_X, 0,
                  sizeof(X_positionpid_rtsim_T));
  }

  /* states (dwork) */
  positionpid_rtsim_M->dwork = ((void *) &positionpid_rtsim_DW);
  (void) memset((void *)&positionpid_rtsim_DW, 0,
                sizeof(DW_positionpid_rtsim_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    positionpid_rtsim_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 31;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  positionpid_rtsim_M->Sizes.numContStates = (2);/* Number of continuous states */
  positionpid_rtsim_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  positionpid_rtsim_M->Sizes.numY = (0);/* Number of model outputs */
  positionpid_rtsim_M->Sizes.numU = (0);/* Number of model inputs */
  positionpid_rtsim_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  positionpid_rtsim_M->Sizes.numSampTimes = (2);/* Number of sample times */
  positionpid_rtsim_M->Sizes.numBlocks = (22);/* Number of blocks */
  positionpid_rtsim_M->Sizes.numBlockIO = (5);/* Number of block outputs */
  positionpid_rtsim_M->Sizes.numBlockPrms = (31);/* Sum of parameter "widths" */
  return positionpid_rtsim_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
