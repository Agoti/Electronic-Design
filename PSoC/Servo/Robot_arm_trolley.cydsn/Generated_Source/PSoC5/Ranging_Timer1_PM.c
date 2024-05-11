/*******************************************************************************
* File Name: Ranging_Timer1_PM.c
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

#include "Ranging_Timer1.h"

static Ranging_Timer1_backupStruct Ranging_Timer1_backup;


/*******************************************************************************
* Function Name: Ranging_Timer1_SaveConfig
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
*  Ranging_Timer1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Ranging_Timer1_SaveConfig(void) 
{
    #if (!Ranging_Timer1_UsingFixedFunction)
        Ranging_Timer1_backup.TimerUdb = Ranging_Timer1_ReadCounter();
        Ranging_Timer1_backup.InterruptMaskValue = Ranging_Timer1_STATUS_MASK;
        #if (Ranging_Timer1_UsingHWCaptureCounter)
            Ranging_Timer1_backup.TimerCaptureCounter = Ranging_Timer1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Ranging_Timer1_UDB_CONTROL_REG_REMOVED)
            Ranging_Timer1_backup.TimerControlRegister = Ranging_Timer1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Ranging_Timer1_RestoreConfig
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
*  Ranging_Timer1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Ranging_Timer1_RestoreConfig(void) 
{   
    #if (!Ranging_Timer1_UsingFixedFunction)

        Ranging_Timer1_WriteCounter(Ranging_Timer1_backup.TimerUdb);
        Ranging_Timer1_STATUS_MASK =Ranging_Timer1_backup.InterruptMaskValue;
        #if (Ranging_Timer1_UsingHWCaptureCounter)
            Ranging_Timer1_SetCaptureCount(Ranging_Timer1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Ranging_Timer1_UDB_CONTROL_REG_REMOVED)
            Ranging_Timer1_WriteControlRegister(Ranging_Timer1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Ranging_Timer1_Sleep
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
*  Ranging_Timer1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Ranging_Timer1_Sleep(void) 
{
    #if(!Ranging_Timer1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Ranging_Timer1_CTRL_ENABLE == (Ranging_Timer1_CONTROL & Ranging_Timer1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Ranging_Timer1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Ranging_Timer1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Ranging_Timer1_Stop();
    Ranging_Timer1_SaveConfig();
}


/*******************************************************************************
* Function Name: Ranging_Timer1_Wakeup
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
*  Ranging_Timer1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Ranging_Timer1_Wakeup(void) 
{
    Ranging_Timer1_RestoreConfig();
    #if(!Ranging_Timer1_UDB_CONTROL_REG_REMOVED)
        if(Ranging_Timer1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Ranging_Timer1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
