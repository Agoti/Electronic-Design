/*******************************************************************************
* File Name: Ranging_Timeout1.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Ranging_Timeout1_H)
#define CY_ISR_Ranging_Timeout1_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Ranging_Timeout1_Start(void);
void Ranging_Timeout1_StartEx(cyisraddress address);
void Ranging_Timeout1_Stop(void);

CY_ISR_PROTO(Ranging_Timeout1_Interrupt);

void Ranging_Timeout1_SetVector(cyisraddress address);
cyisraddress Ranging_Timeout1_GetVector(void);

void Ranging_Timeout1_SetPriority(uint8 priority);
uint8 Ranging_Timeout1_GetPriority(void);

void Ranging_Timeout1_Enable(void);
uint8 Ranging_Timeout1_GetState(void);
void Ranging_Timeout1_Disable(void);

void Ranging_Timeout1_SetPending(void);
void Ranging_Timeout1_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Ranging_Timeout1 ISR. */
#define Ranging_Timeout1_INTC_VECTOR            ((reg32 *) Ranging_Timeout1__INTC_VECT)

/* Address of the Ranging_Timeout1 ISR priority. */
#define Ranging_Timeout1_INTC_PRIOR             ((reg8 *) Ranging_Timeout1__INTC_PRIOR_REG)

/* Priority of the Ranging_Timeout1 interrupt. */
#define Ranging_Timeout1_INTC_PRIOR_NUMBER      Ranging_Timeout1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Ranging_Timeout1 interrupt. */
#define Ranging_Timeout1_INTC_SET_EN            ((reg32 *) Ranging_Timeout1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Ranging_Timeout1 interrupt. */
#define Ranging_Timeout1_INTC_CLR_EN            ((reg32 *) Ranging_Timeout1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Ranging_Timeout1 interrupt state to pending. */
#define Ranging_Timeout1_INTC_SET_PD            ((reg32 *) Ranging_Timeout1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Ranging_Timeout1 interrupt. */
#define Ranging_Timeout1_INTC_CLR_PD            ((reg32 *) Ranging_Timeout1__INTC_CLR_PD_REG)


#endif /* CY_ISR_Ranging_Timeout1_H */


/* [] END OF FILE */
