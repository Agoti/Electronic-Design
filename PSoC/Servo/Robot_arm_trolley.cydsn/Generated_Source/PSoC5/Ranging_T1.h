/*******************************************************************************
* File Name: Ranging_T1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Ranging_T1_H) /* Pins Ranging_T1_H */
#define CY_PINS_Ranging_T1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ranging_T1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ranging_T1__PORT == 15 && ((Ranging_T1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ranging_T1_Write(uint8 value);
void    Ranging_T1_SetDriveMode(uint8 mode);
uint8   Ranging_T1_ReadDataReg(void);
uint8   Ranging_T1_Read(void);
void    Ranging_T1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ranging_T1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ranging_T1_SetDriveMode() function.
     *  @{
     */
        #define Ranging_T1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ranging_T1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ranging_T1_DM_RES_UP          PIN_DM_RES_UP
        #define Ranging_T1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ranging_T1_DM_OD_LO           PIN_DM_OD_LO
        #define Ranging_T1_DM_OD_HI           PIN_DM_OD_HI
        #define Ranging_T1_DM_STRONG          PIN_DM_STRONG
        #define Ranging_T1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ranging_T1_MASK               Ranging_T1__MASK
#define Ranging_T1_SHIFT              Ranging_T1__SHIFT
#define Ranging_T1_WIDTH              1u

/* Interrupt constants */
#if defined(Ranging_T1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ranging_T1_SetInterruptMode() function.
     *  @{
     */
        #define Ranging_T1_INTR_NONE      (uint16)(0x0000u)
        #define Ranging_T1_INTR_RISING    (uint16)(0x0001u)
        #define Ranging_T1_INTR_FALLING   (uint16)(0x0002u)
        #define Ranging_T1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ranging_T1_INTR_MASK      (0x01u) 
#endif /* (Ranging_T1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ranging_T1_PS                     (* (reg8 *) Ranging_T1__PS)
/* Data Register */
#define Ranging_T1_DR                     (* (reg8 *) Ranging_T1__DR)
/* Port Number */
#define Ranging_T1_PRT_NUM                (* (reg8 *) Ranging_T1__PRT) 
/* Connect to Analog Globals */                                                  
#define Ranging_T1_AG                     (* (reg8 *) Ranging_T1__AG)                       
/* Analog MUX bux enable */
#define Ranging_T1_AMUX                   (* (reg8 *) Ranging_T1__AMUX) 
/* Bidirectional Enable */                                                        
#define Ranging_T1_BIE                    (* (reg8 *) Ranging_T1__BIE)
/* Bit-mask for Aliased Register Access */
#define Ranging_T1_BIT_MASK               (* (reg8 *) Ranging_T1__BIT_MASK)
/* Bypass Enable */
#define Ranging_T1_BYP                    (* (reg8 *) Ranging_T1__BYP)
/* Port wide control signals */                                                   
#define Ranging_T1_CTL                    (* (reg8 *) Ranging_T1__CTL)
/* Drive Modes */
#define Ranging_T1_DM0                    (* (reg8 *) Ranging_T1__DM0) 
#define Ranging_T1_DM1                    (* (reg8 *) Ranging_T1__DM1)
#define Ranging_T1_DM2                    (* (reg8 *) Ranging_T1__DM2) 
/* Input Buffer Disable Override */
#define Ranging_T1_INP_DIS                (* (reg8 *) Ranging_T1__INP_DIS)
/* LCD Common or Segment Drive */
#define Ranging_T1_LCD_COM_SEG            (* (reg8 *) Ranging_T1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ranging_T1_LCD_EN                 (* (reg8 *) Ranging_T1__LCD_EN)
/* Slew Rate Control */
#define Ranging_T1_SLW                    (* (reg8 *) Ranging_T1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ranging_T1_PRTDSI__CAPS_SEL       (* (reg8 *) Ranging_T1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ranging_T1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ranging_T1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ranging_T1_PRTDSI__OE_SEL0        (* (reg8 *) Ranging_T1__PRTDSI__OE_SEL0) 
#define Ranging_T1_PRTDSI__OE_SEL1        (* (reg8 *) Ranging_T1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ranging_T1_PRTDSI__OUT_SEL0       (* (reg8 *) Ranging_T1__PRTDSI__OUT_SEL0) 
#define Ranging_T1_PRTDSI__OUT_SEL1       (* (reg8 *) Ranging_T1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ranging_T1_PRTDSI__SYNC_OUT       (* (reg8 *) Ranging_T1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ranging_T1__SIO_CFG)
    #define Ranging_T1_SIO_HYST_EN        (* (reg8 *) Ranging_T1__SIO_HYST_EN)
    #define Ranging_T1_SIO_REG_HIFREQ     (* (reg8 *) Ranging_T1__SIO_REG_HIFREQ)
    #define Ranging_T1_SIO_CFG            (* (reg8 *) Ranging_T1__SIO_CFG)
    #define Ranging_T1_SIO_DIFF           (* (reg8 *) Ranging_T1__SIO_DIFF)
#endif /* (Ranging_T1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ranging_T1__INTSTAT)
    #define Ranging_T1_INTSTAT            (* (reg8 *) Ranging_T1__INTSTAT)
    #define Ranging_T1_SNAP               (* (reg8 *) Ranging_T1__SNAP)
    
	#define Ranging_T1_0_INTTYPE_REG 		(* (reg8 *) Ranging_T1__0__INTTYPE)
#endif /* (Ranging_T1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ranging_T1_H */


/* [] END OF FILE */
