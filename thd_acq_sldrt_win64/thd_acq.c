/*
 * thd_acq.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "thd_acq".
 *
 * Model version              : 1.38
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Thu Jun  8 13:41:57 2023
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "thd_acq.h"
#include "rtwtypes.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "thd_acq_dt.h"

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

const real_T thd_acq_RGND = 0.0;       /* real_T ground */

/* Block signals (default storage) */
B_thd_acq_T thd_acq_B;

/* Block states (default storage) */
DW_thd_acq_T thd_acq_DW;

/* Real-time model */
static RT_MODEL_thd_acq_T thd_acq_M_;
RT_MODEL_thd_acq_T *const thd_acq_M = &thd_acq_M_;

/* Model output function */
void thd_acq_output(void)
{
  /* local block i/o variables */
  real_T rtb_EncoderInput;
  real_T rtb_AnalogInput[2];
  real_T rtb_Clock;

  /* Reset subsysRan breadcrumbs */
  srClearBC(thd_acq_DW.EnabledSubsystem_SubsysRanBC);

  /* S-Function (sldrtai): '<Root>/Analog Input' */
  /* S-Function Block: <Root>/Analog Input */
  {
    ANALOGIOPARM parm;
    parm.mode = (RANGEMODE) thd_acq_P.AnalogInput_RangeMode;
    parm.rangeidx = thd_acq_P.AnalogInput_VoltRange;
    RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 2, thd_acq_P.AnalogInput_Channels,
                   &rtb_AnalogInput[0], &parm);
  }

  /* S-Function (sldrtei): '<Root>/Encoder Input' */
  /* S-Function Block: <Root>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 0;
    parm.infilter = thd_acq_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 1, &thd_acq_P.EncoderInput_Channels,
                   &rtb_EncoderInput, &parm);
  }

  /* Gain: '<S1>/Gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  thd_acq_B.Gain = (rtb_AnalogInput[0] - rtb_AnalogInput[1]) * thd_acq_P.V2deg;

  /* Clock: '<S2>/Clock' */
  rtb_Clock = thd_acq_M->Timing.t[0];

  /* Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  /* Logic: '<S4>/AND' incorporates:
   *  Constant: '<S4>/Lower Limit'
   *  Constant: '<S4>/Upper Limit'
   *  RelationalOperator: '<S4>/Lower Test'
   *  RelationalOperator: '<S4>/Upper Test'
   */
  if ((thd_acq_P.IntervalTest_lowlimit <= rtb_Clock) && (rtb_Clock <=
       thd_acq_P.IntervalTest_uplimit)) {
    thd_acq_DW.EnabledSubsystem_MODE = true;

    /* DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
    thd_acq_B.DiscreteTimeIntegrator = thd_acq_DW.DiscreteTimeIntegrator_DSTATE;
    srUpdateBC(thd_acq_DW.EnabledSubsystem_SubsysRanBC);
  } else {
    thd_acq_DW.EnabledSubsystem_MODE = false;
  }

  /* End of Logic: '<S4>/AND' */
  /* End of Outputs for SubSystem: '<S2>/Enabled Subsystem' */

  /* Sum: '<S1>/Sum' */
  thd_acq_B.Sum = thd_acq_B.Gain - thd_acq_B.DiscreteTimeIntegrator;

  /* S-Function (sldrtao): '<Root>/Analog Output' */
  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) thd_acq_P.AnalogOutput_RangeMode;
      parm.rangeidx = thd_acq_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &thd_acq_P.AnalogOutput_Channels, ((real_T*) (((const
        real_T*) &thd_acq_RGND))), &parm);
    }
  }
}

/* Model update function */
void thd_acq_update(void)
{
  /* Update for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (thd_acq_DW.EnabledSubsystem_MODE) {
    /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
    thd_acq_DW.DiscreteTimeIntegrator_DSTATE +=
      thd_acq_P.DiscreteTimeIntegrator_gainval * thd_acq_B.Gain;
  }

  /* End of Update for SubSystem: '<S2>/Enabled Subsystem' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++thd_acq_M->Timing.clockTick0)) {
    ++thd_acq_M->Timing.clockTickH0;
  }

  thd_acq_M->Timing.t[0] = thd_acq_M->Timing.clockTick0 *
    thd_acq_M->Timing.stepSize0 + thd_acq_M->Timing.clockTickH0 *
    thd_acq_M->Timing.stepSize0 * 4294967296.0;

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
    if (!(++thd_acq_M->Timing.clockTick1)) {
      ++thd_acq_M->Timing.clockTickH1;
    }

    thd_acq_M->Timing.t[1] = thd_acq_M->Timing.clockTick1 *
      thd_acq_M->Timing.stepSize1 + thd_acq_M->Timing.clockTickH1 *
      thd_acq_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void thd_acq_initialize(void)
{
  /* Start for Enabled SubSystem: '<S2>/Enabled Subsystem' */
  thd_acq_DW.EnabledSubsystem_MODE = false;

  /* End of Start for SubSystem: '<S2>/Enabled Subsystem' */

  /* Start for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) thd_acq_P.AnalogOutput_RangeMode;
      parm.rangeidx = thd_acq_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &thd_acq_P.AnalogOutput_Channels,
                     &thd_acq_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for S-Function (sldrtei): '<Root>/Encoder Input' */

  /* S-Function Block: <Root>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 0;
    parm.infilter = thd_acq_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 1, &thd_acq_P.EncoderInput_Channels,
                   NULL, &parm);
  }

  /* SystemInitialize for Enabled SubSystem: '<S2>/Enabled Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  thd_acq_DW.DiscreteTimeIntegrator_DSTATE = thd_acq_P.DiscreteTimeIntegrator_IC;

  /* SystemInitialize for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' incorporates:
   *  Outport: '<S3>/Out'
   */
  thd_acq_B.DiscreteTimeIntegrator = thd_acq_P.Out_Y0;

  /* End of SystemInitialize for SubSystem: '<S2>/Enabled Subsystem' */
}

/* Model terminate function */
void thd_acq_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) thd_acq_P.AnalogOutput_RangeMode;
      parm.rangeidx = thd_acq_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &thd_acq_P.AnalogOutput_Channels,
                     &thd_acq_P.AnalogOutput_FinalValue, &parm);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  thd_acq_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  thd_acq_update();
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
  thd_acq_initialize();
}

void MdlTerminate(void)
{
  thd_acq_terminate();
}

/* Registration function */
RT_MODEL_thd_acq_T *thd_acq(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  thd_acq_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)thd_acq_M, 0,
                sizeof(RT_MODEL_thd_acq_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&thd_acq_M->solverInfo, &thd_acq_M->Timing.simTimeStep);
    rtsiSetTPtr(&thd_acq_M->solverInfo, &rtmGetTPtr(thd_acq_M));
    rtsiSetStepSizePtr(&thd_acq_M->solverInfo, &thd_acq_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&thd_acq_M->solverInfo, (&rtmGetErrorStatus(thd_acq_M)));
    rtsiSetRTModelPtr(&thd_acq_M->solverInfo, thd_acq_M);
  }

  rtsiSetSimTimeStep(&thd_acq_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&thd_acq_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = thd_acq_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "thd_acq_M points to
       static memory which is guaranteed to be non-NULL" */
    thd_acq_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    thd_acq_M->Timing.sampleTimes = (&thd_acq_M->Timing.sampleTimesArray[0]);
    thd_acq_M->Timing.offsetTimes = (&thd_acq_M->Timing.offsetTimesArray[0]);

    /* task periods */
    thd_acq_M->Timing.sampleTimes[0] = (0.0);
    thd_acq_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    thd_acq_M->Timing.offsetTimes[0] = (0.0);
    thd_acq_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(thd_acq_M, &thd_acq_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = thd_acq_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    thd_acq_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(thd_acq_M, 100.0);
  thd_acq_M->Timing.stepSize0 = 0.001;
  thd_acq_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  thd_acq_M->Sizes.checksums[0] = (3259231536U);
  thd_acq_M->Sizes.checksums[1] = (1687406623U);
  thd_acq_M->Sizes.checksums[2] = (2033774276U);
  thd_acq_M->Sizes.checksums[3] = (378203794U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    thd_acq_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&thd_acq_DW.EnabledSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(thd_acq_M->extModeInfo,
      &thd_acq_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(thd_acq_M->extModeInfo, thd_acq_M->Sizes.checksums);
    rteiSetTPtr(thd_acq_M->extModeInfo, rtmGetTPtr(thd_acq_M));
  }

  thd_acq_M->solverInfoPtr = (&thd_acq_M->solverInfo);
  thd_acq_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&thd_acq_M->solverInfo, 0.001);
  rtsiSetSolverMode(&thd_acq_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  thd_acq_M->blockIO = ((void *) &thd_acq_B);
  (void) memset(((void *) &thd_acq_B), 0,
                sizeof(B_thd_acq_T));

  /* parameters */
  thd_acq_M->defaultParam = ((real_T *)&thd_acq_P);

  /* states (dwork) */
  thd_acq_M->dwork = ((void *) &thd_acq_DW);
  (void) memset((void *)&thd_acq_DW, 0,
                sizeof(DW_thd_acq_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    thd_acq_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 23;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  thd_acq_M->Sizes.numContStates = (0);/* Number of continuous states */
  thd_acq_M->Sizes.numY = (0);         /* Number of model outputs */
  thd_acq_M->Sizes.numU = (0);         /* Number of model inputs */
  thd_acq_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  thd_acq_M->Sizes.numSampTimes = (2); /* Number of sample times */
  thd_acq_M->Sizes.numBlocks = (16);   /* Number of blocks */
  thd_acq_M->Sizes.numBlockIO = (4);   /* Number of block outputs */
  thd_acq_M->Sizes.numBlockPrms = (23);/* Sum of parameter "widths" */
  return thd_acq_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
