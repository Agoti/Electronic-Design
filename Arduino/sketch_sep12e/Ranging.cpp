
#include "defs.h"
#include "param.h"
#include <Timer.h>

// ---------- Global Variables ----------

// Timer period and timeout flag
Timer timer1(MICROS);
Timer timer2(MICROS);
// int timeout1, timeout2;

// ---------- Common Functions --------

// Calculate the distance (millimeter) out of the count value
long long calculate_millimeter(uint32_t cnt) {
    return ((long long)cnt) * SOUND_SPEED * 1000 / RANGING_CLOCK_FREQ / 2;
}

// Initialize all probes
void ranging_init() {
    ranging_init1();
    ranging_init2();
}

// ---------- Probe 1 Functions ----------

// Initialization
void ranging_init1() {
    pinMode(RANGING_T1_PIN, OUTPUT);
    pinMode(RANGING_R1_PIN, INPUT);
}

// Generate trigger pulse signal for probe 1
void trigger1() {
    digitalWrite(RANGING_T1_PIN, HIGH);
    delayMicroseconds(RANGING_TRIGGER);
    digitalWrite(RANGING_T1_PIN, LOW);
}

// Get probe 1 distance (mm)
int get_millimeter1() {
    uint32_t begin, end;
    int distance;
    trigger1();
    // Polling
    timer1.start();
    while (digitalRead(RANGING_R1_PIN) == LOW && timer1.read() <= RANGING_TIMEOUT);
    begin = timer1.read();
    while (digitalRead(RANGING_R1_PIN) == HIGH && timer1.read() <= RANGING_TIMEOUT);
    end = timer1.read();
    timer1.stop();
    distance = (int)calculate_millimeter(end - begin);

    return distance;
}

// ---------- Probe 2 Functions ----------


// Initialization for probe 2
void ranging_init2() {
    pinMode(RANGING_T2_PIN, OUTPUT);
    pinMode(RANGING_R2_PIN, INPUT);
}

// Generate trigger pulse signal for probe 2
void trigger2() {
    digitalWrite(RANGING_T2_PIN, HIGH);
    delayMicroseconds(RANGING_TRIGGER);
    digitalWrite(RANGING_T2_PIN, LOW);
}

// Get probe 2 distance (mm)
int get_millimeter2() {
    uint32_t begin, end;
    int distance;
    trigger2();
    // Polling
    timer2.start();
    while (digitalRead(RANGING_R2_PIN) == LOW && timer2.read() <= RANGING_TIMEOUT);
    begin = timer2.read();
    while (digitalRead(RANGING_R2_PIN) == HIGH && timer2.read() <= RANGING_TIMEOUT);
    end = timer2.read();
    timer2.stop();
    distance = (int)calculate_millimeter(end - begin);

    return distance;
}

