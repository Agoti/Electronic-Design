/*******************************************************************************
* File Name: Ranging_Timer2.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_Ranging_Timer2_H)
#define CY_TIMER_Ranging_Timer2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Ranging_Timer2_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define Ranging_Timer2_Resolution                 32u
#define Ranging_Timer2_UsingFixedFunction         0u
#define Ranging_Timer2_UsingHWCaptureCounter      0u
#define Ranging_Timer2_SoftwareCaptureMode        0u
#define Ranging_Timer2_SoftwareTriggerMode        0u
#define Ranging_Timer2_UsingHWEnable              0u
#define Ranging_Timer2_EnableTriggerMode          0u
#define Ranging_Timer2_InterruptOnCaptureCount    0u
#define Ranging_Timer2_RunModeUsed                0u
#define Ranging_Timer2_ControlRegRemoved          0u

#if defined(Ranging_Timer2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define Ranging_Timer2_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (Ranging_Timer2_UsingFixedFunction)
    #define Ranging_Timer2_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define Ranging_Timer2_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End Ranging_Timer2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!Ranging_Timer2_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (Ranging_Timer2_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!Ranging_Timer2_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}Ranging_Timer2_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    Ranging_Timer2_Start(void) ;
void    Ranging_Timer2_Stop(void) ;

void    Ranging_Timer2_SetInterruptMode(uint8 interruptMode) ;
uint8   Ranging_Timer2_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define Ranging_Timer2_GetInterruptSource() Ranging_Timer2_ReadStatusRegister()

#if(!Ranging_Timer2_UDB_CONTROL_REG_REMOVED)
    uint8   Ranging_Timer2_ReadControlRegister(void) ;
    void    Ranging_Timer2_WriteControlRegister(uint8 control) ;
#endif /* (!Ranging_Timer2_UDB_CONTROL_REG_REMOVED) */

uint32  Ranging_Timer2_ReadPeriod(void) ;
void    Ranging_Timer2_WritePeriod(uint32 period) ;
uint32  Ranging_Timer2_ReadCounter(void) ;
void    Ranging_Timer2_WriteCounter(uint32 counter) ;
uint32  Ranging_Timer2_ReadCapture(void) ;
void    Ranging_Timer2_SoftwareCapture(void) ;

#if(!Ranging_Timer2_UsingFixedFunction) /* UDB Prototypes */
    #if (Ranging_Timer2_SoftwareCaptureMode)
        void    Ranging_Timer2_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!Ranging_Timer2_UsingFixedFunction) */

    #if (Ranging_Timer2_SoftwareTriggerMode)
        void    Ranging_Timer2_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (Ranging_Timer2_SoftwareTriggerMode) */

    #if (Ranging_Timer2_EnableTriggerMode)
        void    Ranging_Timer2_EnableTrigger(void) ;
        void    Ranging_Timer2_DisableTrigger(void) ;
    #endif /* (Ranging_Timer2_EnableTriggerMode) */


    #if(Ranging_Timer2_InterruptOnCaptureCount)
        void    Ranging_Timer2_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (Ranging_Timer2_InterruptOnCaptureCount) */

    #if (Ranging_Timer2_UsingHWCaptureCounter)
        void    Ranging_Timer2_SetCaptureCount(uint8 captureCount) ;
        uint8   Ranging_Timer2_ReadCaptureCount(void) ;
    #endif /* (Ranging_Timer2_UsingHWCaptureCounter) */

    void Ranging_Timer2_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void Ranging_Timer2_Init(void)          ;
void Ranging_Timer2_Enable(void)        ;
void Ranging_Timer2_SaveConfig(void)    ;
void Ranging_Timer2_RestoreConfig(void) ;
void Ranging_Timer2_Sleep(void)         ;
void Ranging_Timer2_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define Ranging_Timer2__B_TIMER__CM_NONE 0
#define Ranging_Timer2__B_TIMER__CM_RISINGEDGE 1
#define Ranging_Timer2__B_TIMER__CM_FALLINGEDGE 2
#define Ranging_Timer2__B_TIMER__CM_EITHEREDGE 3
#define Ranging_Timer2__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define Ranging_Timer2__B_TIMER__TM_NONE 0x00u
#define Ranging_Timer2__B_TIMER__TM_RISINGEDGE 0x04u
#define Ranging_Timer2__B_TIMER__TM_FALLINGEDGE 0x08u
#define Ranging_Timer2__B_TIMER__TM_EITHEREDGE 0x0Cu
#define Ranging_Timer2__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define Ranging_Timer2_INIT_PERIOD             99998u
#define Ranging_Timer2_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << Ranging_Timer2_CTRL_CAP_MODE_SHIFT))
#define Ranging_Timer2_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << Ranging_Timer2_CTRL_TRIG_MODE_SHIFT))
#if (Ranging_Timer2_UsingFixedFunction)
    #define Ranging_Timer2_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << Ranging_Timer2_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << Ranging_Timer2_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define Ranging_Timer2_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << Ranging_Timer2_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Ranging_Timer2_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Ranging_Timer2_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (Ranging_Timer2_UsingFixedFunction) */
#define Ranging_Timer2_INIT_CAPTURE_COUNT      (2u)
#define Ranging_Timer2_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << Ranging_Timer2_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (Ranging_Timer2_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define Ranging_Timer2_STATUS         (*(reg8 *) Ranging_Timer2_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define Ranging_Timer2_STATUS_MASK    (*(reg8 *) Ranging_Timer2_TimerHW__SR0 )
    #define Ranging_Timer2_CONTROL        (*(reg8 *) Ranging_Timer2_TimerHW__CFG0)
    #define Ranging_Timer2_CONTROL2       (*(reg8 *) Ranging_Timer2_TimerHW__CFG1)
    #define Ranging_Timer2_CONTROL2_PTR   ( (reg8 *) Ranging_Timer2_TimerHW__CFG1)
    #define Ranging_Timer2_RT1            (*(reg8 *) Ranging_Timer2_TimerHW__RT1)
    #define Ranging_Timer2_RT1_PTR        ( (reg8 *) Ranging_Timer2_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define Ranging_Timer2_CONTROL3       (*(reg8 *) Ranging_Timer2_TimerHW__CFG2)
        #define Ranging_Timer2_CONTROL3_PTR   ( (reg8 *) Ranging_Timer2_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Ranging_Timer2_GLOBAL_ENABLE  (*(reg8 *) Ranging_Timer2_TimerHW__PM_ACT_CFG)
    #define Ranging_Timer2_GLOBAL_STBY_ENABLE  (*(reg8 *) Ranging_Timer2_TimerHW__PM_STBY_CFG)

    #define Ranging_Timer2_CAPTURE_LSB         (* (reg16 *) Ranging_Timer2_TimerHW__CAP0 )
    #define Ranging_Timer2_CAPTURE_LSB_PTR       ((reg16 *) Ranging_Timer2_TimerHW__CAP0 )
    #define Ranging_Timer2_PERIOD_LSB          (* (reg16 *) Ranging_Timer2_TimerHW__PER0 )
    #define Ranging_Timer2_PERIOD_LSB_PTR        ((reg16 *) Ranging_Timer2_TimerHW__PER0 )
    #define Ranging_Timer2_COUNTER_LSB         (* (reg16 *) Ranging_Timer2_TimerHW__CNT_CMP0 )
    #define Ranging_Timer2_COUNTER_LSB_PTR       ((reg16 *) Ranging_Timer2_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define Ranging_Timer2_BLOCK_EN_MASK                     Ranging_Timer2_TimerHW__PM_ACT_MSK
    #define Ranging_Timer2_BLOCK_STBY_EN_MASK                Ranging_Timer2_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define Ranging_Timer2_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define Ranging_Timer2_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define Ranging_Timer2_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define Ranging_Timer2_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define Ranging_Timer2_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define Ranging_Timer2_CTRL_ENABLE                        ((uint8)((uint8)0x01u << Ranging_Timer2_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Ranging_Timer2_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define Ranging_Timer2_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << Ranging_Timer2_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define Ranging_Timer2_CTRL_MODE_SHIFT                 0x01u
        #define Ranging_Timer2_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << Ranging_Timer2_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define Ranging_Timer2_CTRL_RCOD_SHIFT        0x02u
        #define Ranging_Timer2_CTRL_ENBL_SHIFT        0x00u
        #define Ranging_Timer2_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define Ranging_Timer2_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << Ranging_Timer2_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define Ranging_Timer2_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << Ranging_Timer2_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define Ranging_Timer2_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << Ranging_Timer2_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define Ranging_Timer2_CTRL_RCOD       ((uint8)((uint8)0x03u << Ranging_Timer2_CTRL_RCOD_SHIFT))
        #define Ranging_Timer2_CTRL_ENBL       ((uint8)((uint8)0x80u << Ranging_Timer2_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define Ranging_Timer2_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define Ranging_Timer2_RT1_MASK                        ((uint8)((uint8)0x03u << Ranging_Timer2_RT1_SHIFT))
    #define Ranging_Timer2_SYNC                            ((uint8)((uint8)0x03u << Ranging_Timer2_RT1_SHIFT))
    #define Ranging_Timer2_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define Ranging_Timer2_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << Ranging_Timer2_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define Ranging_Timer2_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << Ranging_Timer2_SYNCDSI_SHIFT))

    #define Ranging_Timer2_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << Ranging_Timer2_CTRL_MODE_SHIFT))
    #define Ranging_Timer2_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << Ranging_Timer2_CTRL_MODE_SHIFT))
    #define Ranging_Timer2_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << Ranging_Timer2_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Ranging_Timer2_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Ranging_Timer2_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Ranging_Timer2_STATUS_TC_INT_MASK_SHIFT        (Ranging_Timer2_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Ranging_Timer2_STATUS_CAPTURE_INT_MASK_SHIFT   (Ranging_Timer2_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define Ranging_Timer2_STATUS_TC                       ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_TC_SHIFT))
    #define Ranging_Timer2_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define Ranging_Timer2_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define Ranging_Timer2_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define Ranging_Timer2_STATUS              (* (reg8 *) Ranging_Timer2_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define Ranging_Timer2_STATUS_MASK         (* (reg8 *) Ranging_Timer2_TimerUDB_rstSts_stsreg__MASK_REG)
    #define Ranging_Timer2_STATUS_AUX_CTRL     (* (reg8 *) Ranging_Timer2_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define Ranging_Timer2_CONTROL             (* (reg8 *) Ranging_Timer2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(Ranging_Timer2_Resolution <= 8u) /* 8-bit Timer */
        #define Ranging_Timer2_CAPTURE_LSB         (* (reg8 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Ranging_Timer2_CAPTURE_LSB_PTR       ((reg8 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Ranging_Timer2_PERIOD_LSB          (* (reg8 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Ranging_Timer2_PERIOD_LSB_PTR        ((reg8 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Ranging_Timer2_COUNTER_LSB         (* (reg8 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define Ranging_Timer2_COUNTER_LSB_PTR       ((reg8 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(Ranging_Timer2_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define Ranging_Timer2_CAPTURE_LSB         (* (reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Ranging_Timer2_CAPTURE_LSB_PTR       ((reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Ranging_Timer2_PERIOD_LSB          (* (reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Ranging_Timer2_PERIOD_LSB_PTR        ((reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Ranging_Timer2_COUNTER_LSB         (* (reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define Ranging_Timer2_COUNTER_LSB_PTR       ((reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define Ranging_Timer2_CAPTURE_LSB         (* (reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define Ranging_Timer2_CAPTURE_LSB_PTR       ((reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define Ranging_Timer2_PERIOD_LSB          (* (reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define Ranging_Timer2_PERIOD_LSB_PTR        ((reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define Ranging_Timer2_COUNTER_LSB         (* (reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define Ranging_Timer2_COUNTER_LSB_PTR       ((reg16 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(Ranging_Timer2_Resolution <= 24u)/* 24-bit Timer */
        #define Ranging_Timer2_CAPTURE_LSB         (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Ranging_Timer2_CAPTURE_LSB_PTR       ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Ranging_Timer2_PERIOD_LSB          (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Ranging_Timer2_PERIOD_LSB_PTR        ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Ranging_Timer2_COUNTER_LSB         (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define Ranging_Timer2_COUNTER_LSB_PTR       ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define Ranging_Timer2_CAPTURE_LSB         (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Ranging_Timer2_CAPTURE_LSB_PTR       ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Ranging_Timer2_PERIOD_LSB          (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Ranging_Timer2_PERIOD_LSB_PTR        ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Ranging_Timer2_COUNTER_LSB         (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define Ranging_Timer2_COUNTER_LSB_PTR       ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define Ranging_Timer2_CAPTURE_LSB         (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define Ranging_Timer2_CAPTURE_LSB_PTR       ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define Ranging_Timer2_PERIOD_LSB          (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define Ranging_Timer2_PERIOD_LSB_PTR        ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define Ranging_Timer2_COUNTER_LSB         (* (reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define Ranging_Timer2_COUNTER_LSB_PTR       ((reg32 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define Ranging_Timer2_COUNTER_LSB_PTR_8BIT       ((reg8 *) Ranging_Timer2_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (Ranging_Timer2_UsingHWCaptureCounter)
        #define Ranging_Timer2_CAP_COUNT              (*(reg8 *) Ranging_Timer2_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Ranging_Timer2_CAP_COUNT_PTR          ( (reg8 *) Ranging_Timer2_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Ranging_Timer2_CAPTURE_COUNT_CTRL     (*(reg8 *) Ranging_Timer2_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define Ranging_Timer2_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) Ranging_Timer2_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (Ranging_Timer2_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define Ranging_Timer2_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define Ranging_Timer2_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define Ranging_Timer2_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define Ranging_Timer2_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define Ranging_Timer2_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define Ranging_Timer2_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << Ranging_Timer2_CTRL_INTCNT_SHIFT))
    #define Ranging_Timer2_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << Ranging_Timer2_CTRL_TRIG_MODE_SHIFT))
    #define Ranging_Timer2_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << Ranging_Timer2_CTRL_TRIG_EN_SHIFT))
    #define Ranging_Timer2_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << Ranging_Timer2_CTRL_CAP_MODE_SHIFT))
    #define Ranging_Timer2_CTRL_ENABLE                    ((uint8)((uint8)0x01u << Ranging_Timer2_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define Ranging_Timer2_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define Ranging_Timer2_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define Ranging_Timer2_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define Ranging_Timer2_STATUS_TC_INT_MASK_SHIFT       Ranging_Timer2_STATUS_TC_SHIFT
    #define Ranging_Timer2_STATUS_CAPTURE_INT_MASK_SHIFT  Ranging_Timer2_STATUS_CAPTURE_SHIFT
    #define Ranging_Timer2_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define Ranging_Timer2_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define Ranging_Timer2_STATUS_FIFOFULL_INT_MASK_SHIFT Ranging_Timer2_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define Ranging_Timer2_STATUS_TC                      ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define Ranging_Timer2_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Ranging_Timer2_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Ranging_Timer2_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define Ranging_Timer2_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define Ranging_Timer2_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Ranging_Timer2_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << Ranging_Timer2_STATUS_FIFOFULL_SHIFT))

    #define Ranging_Timer2_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define Ranging_Timer2_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define Ranging_Timer2_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define Ranging_Timer2_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define Ranging_Timer2_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define Ranging_Timer2_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_Ranging_Timer2_H */


/* [] END OF FILE */
