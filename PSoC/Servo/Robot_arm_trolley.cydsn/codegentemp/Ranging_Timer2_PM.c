/*******************************************************************************
* File Name: Ranging_Timer2_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Ranging_Timer2.h"

static Ranging_Timer2_backupStruct Ranging_Timer2_backup;


/*******************************************************************************
* Function Name: Ranging_Timer2_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Ranging_Timer2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Ranging_Timer2_SaveConfig(void) 
{
    #if (!Ranging_Timer2_UsingFixedFunction)
        Ranging_Timer2_backup.TimerUdb = Ranging_Timer2_ReadCounter();
        Ranging_Timer2_backup.InterruptMaskValue = Ranging_Timer2_STATUS_MASK;
        #if (Ranging_Timer2_UsingHWCaptureCounter)
            Ranging_Timer2_backup.TimerCaptureCounter = Ranging_Timer2_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Ranging_Timer2_UDB_CONTROL_REG_REMOVED)
            Ranging_Timer2_backup.TimerControlRegister = Ranging_Timer2_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Ranging_Timer2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Ranging_Timer2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Ranging_Timer2_RestoreConfig(void) 
{   
    #if (!Ranging_Timer2_UsingFixedFunction)

        Ranging_Timer2_WriteCounter(Ranging_Timer2_backup.TimerUdb);
        Ranging_Timer2_STATUS_MASK =Ranging_Timer2_backup.InterruptMaskValue;
        #if (Ranging_Timer2_UsingHWCaptureCounter)
            Ranging_Timer2_SetCaptureCount(Ranging_Timer2_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Ranging_Timer2_UDB_CONTROL_REG_REMOVED)
            Ranging_Timer2_WriteControlRegister(Ranging_Timer2_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Ranging_Timer2_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Ranging_Timer2_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Ranging_Timer2_Sleep(void) 
{
    #if(!Ranging_Timer2_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Ranging_Timer2_CTRL_ENABLE == (Ranging_Timer2_CONTROL & Ranging_Timer2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Ranging_Timer2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Ranging_Timer2_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Ranging_Timer2_Stop();
    Ranging_Timer2_SaveConfig();
}


/*******************************************************************************
* Function Name: Ranging_Timer2_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Ranging_Timer2_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Ranging_Timer2_Wakeup(void) 
{
    Ranging_Timer2_RestoreConfig();
    #if(!Ranging_Timer2_UDB_CONTROL_REG_REMOVED)
        if(Ranging_Timer2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Ranging_Timer2_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
