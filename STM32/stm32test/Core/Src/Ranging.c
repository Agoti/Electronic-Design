/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "defs.h"
#include "param.h"

// ---------- Global Variables ----------

// Timer period and timeout flag
uint32 period1, period2;
int timeout1, timeout2;

// ---------- Common Functions --------

// Calculate the distance (millimeter) out of the count value
long long calculate_millimeter(uint32 cnt) {
    return ((long long)cnt) * SOUND_SPEED * 1000 / RANGING_CLOCK_FREQ / 2;
}

// Initialize all probes
void ranging_init() {
    ranging_init1();
    ranging_init2();
}

// ---------- Probe 1 Functions ----------

// Timeout interrupt handler
void RangingTimeoutInt1() {
    // Ranging_Timer1_STATUS; // Reset interrupt status
    timeout1 = 1; // Set timeout flag
    Ranging_Timer1_Stop(); // Stop timer
}

// Initialization
void ranging_init1() {
    period1 = Ranging_Timer1_ReadPeriod(); // Get period
    Ranging_Timer1_Clock_Start(); // Start timer clock
    Ranging_Timeout1_StartEx(RangingTimeoutInt1); // Enable interrupt
}

// Generate trigger pulse signal for probe 1
void trigger1() {
    Ranging_T1_Write(1);
    CyDelayUs(RANGING_TRIGGER);
    Ranging_T1_Write(0);
}

// Set timer value and start timer for probe 1
void startcount1() {
    Ranging_Timer1_Start();
    Ranging_Timer1_WriteCounter(period1 - 1);
}

// Stop timer for probe 1 and get timer value, return count value
uint32 endcount1() {
    uint32 cnt = Ranging_Timer1_ReadCounter();
    Ranging_Timer1_Stop();
    return period1 - 1 - cnt;
}

// Get probe 1 distance (mm)
int get_millimeter1() {
    uint32 cnt;
    int distance;
    startcount1();
    trigger1();
    // Polling
    while (Ranging_R1_Read() == 0 && timeout1 == 0);
    startcount1();
    while (Ranging_R1_Read() != 0 && timeout1 == 0);
    cnt = endcount1();
    if (timeout1 == 0) {
        distance = (int)calculate_millimeter(cnt);
    } else {
        // If timeout, return int max
        distance = L_INT_MAX;
    }
    return distance;
}

// ---------- Probe 2 Functions ----------

// Timeout interrupt handler for probe 2
void RangingTimeoutInt2() {
    // Ranging_Timer2_STATUS; // Reset interrupt status
    timeout2 = 1; // Set timeout flag
    Ranging_Timer2_Stop(); // Stop timer
}

// Initialization for probe 2
void ranging_init2() {
    period2 = Ranging_Timer2_ReadPeriod(); // Get period
    Ranging_Timer2_Clock_Start(); // Start timer clock
    Ranging_Timeout2_StartEx(RangingTimeoutInt2); // Enable interrupt
}

// Generate trigger pulse signal for probe 2
void trigger2() {
    Ranging_T2_Write(1);
    CyDelayUs(RANGING_TRIGGER);
    Ranging_T2_Write(0);
}

// Set timer value and start timer for probe 2
void startcount2() {
    Ranging_Timer2_Start();
    Ranging_Timer2_WriteCounter(period2 - 1);
}

// Stop timer for probe 2 and get timer value, return count value
uint32 endcount2() {
    uint32 cnt = Ranging_Timer2_ReadCounter();
    Ranging_Timer2_Stop();
    return period2 - 1 - cnt;
}

// Get probe 2 distance (mm)
int get_millimeter2() {
    uint32 cnt;
    int distance;
    startcount2();
    trigger2();
    // Polling
    while (Ranging_R2_Read() == 0 && timeout2 == 0);
    startcount2();
    while (Ranging_R2_Read() != 0 && timeout2 == 0);
    cnt = endcount2();
    if (timeout2 == 0) {
        distance = (int)calculate_millimeter(cnt);
    } else {
        // If timeout, return int max
        distance = L_INT_MAX;
    }
    return distance;
}

/* [] END OF FILE */
