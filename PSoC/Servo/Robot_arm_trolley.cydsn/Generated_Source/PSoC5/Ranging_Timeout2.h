/*******************************************************************************
* File Name: Ranging_Timeout2.h
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
#if !defined(CY_ISR_Ranging_Timeout2_H)
#define CY_ISR_Ranging_Timeout2_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Ranging_Timeout2_Start(void);
void Ranging_Timeout2_StartEx(cyisraddress address);
void Ranging_Timeout2_Stop(void);

CY_ISR_PROTO(Ranging_Timeout2_Interrupt);

void Ranging_Timeout2_SetVector(cyisraddress address);
cyisraddress Ranging_Timeout2_GetVector(void);

void Ranging_Timeout2_SetPriority(uint8 priority);
uint8 Ranging_Timeout2_GetPriority(void);

void Ranging_Timeout2_Enable(void);
uint8 Ranging_Timeout2_GetState(void);
void Ranging_Timeout2_Disable(void);

void Ranging_Timeout2_SetPending(void);
void Ranging_Timeout2_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Ranging_Timeout2 ISR. */
#define Ranging_Timeout2_INTC_VECTOR            ((reg32 *) Ranging_Timeout2__INTC_VECT)

/* Address of the Ranging_Timeout2 ISR priority. */
#define Ranging_Timeout2_INTC_PRIOR             ((reg8 *) Ranging_Timeout2__INTC_PRIOR_REG)

/* Priority of the Ranging_Timeout2 interrupt. */
#define Ranging_Timeout2_INTC_PRIOR_NUMBER      Ranging_Timeout2__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Ranging_Timeout2 interrupt. */
#define Ranging_Timeout2_INTC_SET_EN            ((reg32 *) Ranging_Timeout2__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Ranging_Timeout2 interrupt. */
#define Ranging_Timeout2_INTC_CLR_EN            ((reg32 *) Ranging_Timeout2__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Ranging_Timeout2 interrupt state to pending. */
#define Ranging_Timeout2_INTC_SET_PD            ((reg32 *) Ranging_Timeout2__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Ranging_Timeout2 interrupt. */
#define Ranging_Timeout2_INTC_CLR_PD            ((reg32 *) Ranging_Timeout2__INTC_CLR_PD_REG)


#endif /* CY_ISR_Ranging_Timeout2_H */


/* [] END OF FILE */
