#include <SPI.h>
#include "soundFunctions.h"
#include "roar.h"
#include "tap.h"
#include "jump.h"

#define CS_DAC 10  // Chip Select pin for MCP4921 DAC
#define MIC_PIN 2 
#define JUMP_PIN 5
#define START_PIN 6

unsigned long lastInterruptTime = 0;  // Store the last interrupt time
unsigned long debounceDelay = 200;    // Minimum delay between interrupts (in milliseconds)

void setup() {
    //Digital Audio Converter Setup
    pinMode(CS_DAC, OUTPUT);  // Set DAC CS pin as output
    SPI.begin();  // Initialize SPI for DAC
    //Sound Sensor Setup
    pinMode(MIC_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(MIC_PIN), soundDetected, RISING);
    //Slave setup
    Serial.begin(9600);
    //Jump Button Setup
    pinMode(JUMP_PIN, INPUT_PULLUP);
    //Start Button Setup
    pinMode(START_PIN, INPUT_PULLUP);
}

void loop() {
    //Start Game Logic
    if (digitalRead(START_PIN) == LOW){
      gameStarted = true;
    }
    
    //Jump Logic
    if (digitalRead(JUMP_PIN) == LOW){
      if (gameStarted == true){
        playSound(jumpSound, sizeof(jumpSound));
      }
    }

    //Tap Logic
    if (digitalRead(TAP_PIN) == LOW){
        if (gameStarted == true){
            playSound(tapSound, sizeof(tapSound));
        }
    }

    //Microphone aka Sound Sensor Logic
    void soundDetected(){
        unsigned long interruptTime = millis();
        if (gameStarted){
            // Check if enough time has passed since the last interrupt
            if (interruptTime - lastInterruptTime > debounceDelay) {
                playSound(roarSound, sizeof(roarSound));
                lastInterruptTime = interruptTime;  // Update the last interrupt time
            }
        }
    }
}