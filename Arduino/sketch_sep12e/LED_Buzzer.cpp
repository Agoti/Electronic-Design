// Include necessary header files
#include "defs.h"
#include "param.h"
#include <Timer.h>

// Define a Timer object for controlling yellow LED blinking
Timer yellow_timer(MILLIS);

// Initialize the status of the yellow LED
int yellow_status = 1;

// Function to initialize LEDs and buzzer pins
void led_buzzer_init(){
  // Set pin modes
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Initialize yellow LED timer
  yellow_timer.start();
}

// Function to set the status of LEDs based on the provided mask
void led_set(int led_mask){

  // Set or clear red LED based on the mask
  if(led_mask & LED_RED_MASK){
    digitalWrite(LED_RED, HIGH);
  }
  else{
    digitalWrite(LED_RED, LOW);
  }

  // Set or clear white LED based on the mask
  if(led_mask & LED_WHITE_MASK){
    digitalWrite(LED_WHITE, HIGH);
  }
  else{
    digitalWrite(LED_WHITE, LOW);
  }

  // Handle yellow LED based on mask and timer threshold
  if(led_mask & LED_YELLOW_MASK){
    digitalWrite(LED_YELLOW, yellow_status ? HIGH : LOW);
    if(yellow_timer.read() > LED_YELLOW_THRESHOLD){
      yellow_timer.stop();
      yellow_status = !yellow_status;
      yellow_timer.start();
    }
  }
  else{
    digitalWrite(LED_YELLOW, LOW);
  }
}

// Function to make the buzzer produce a sound at a specified frequency
void buzzer_buzz(int freq){
  tone(BUZZER, freq); // Emit a 1kHz sound
}

// Function to silence the buzzer
void buzzer_mute(){
  noTone(BUZZER);     // Stop the buzzer sound
}
