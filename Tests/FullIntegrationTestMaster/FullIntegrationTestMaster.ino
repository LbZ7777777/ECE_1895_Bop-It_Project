#include <SPI.h>
#include "soundFunctions.h"
#include "roar.h"
#include "tap.h"
#include "jump.h"

#define CS_DAC 10  // Chip Select pin for MCP4921 DAC
#define MIC_PIN 2 
#define JUMP_PIN 5
#define START_PIN 6
#define TAP_PIN 7

bool gameStarted = false;
bool pressJump = false;
bool pressTap = false;
bool pressRoar = false;

unsigned long lastInterruptTime = 0;  // Store the last interrupt time
unsigned long debounceDelay = 200;    // Minimum delay between interrupts (in milliseconds)

char jump[] = "000";
char tap[] = "001";
char roar[] = "010";
char enemy[] = "011";
char jumpFailed[] = "100";
char tapFailed[] = "101";
char roarFailed[] = "110";
char start[] = "111";

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
    //Touchscreen Tapped Pin from Slave Setup
    pinMode(TAP_PIN, INPUT_PULLUP);
}

void loop() {
    //Start Game Logic
    if (digitalRead(START_PIN) == LOW){
      gameStarted = true;
      Serial.println(start);
    }

    //Jump Logic
    if (digitalRead(JUMP_PIN) == LOW){
      if (gameStarted == true){
        if (pressJump == false){
          Serial.println(jumpFailed);
        }else{
          Serial.println(jump);
        }
        playSound(jumpSound, sizeof(jumpSound));
      }
    }

    //Tap Logic
    if (digitalRead(TAP_PIN) == LOW){
      if (gameStarted == true){
        if (pressTap == false){
          Serial.println(tapFailed);
        }else{
          Serial.println(tap);
        }
        playSound(tapSound, sizeof(tapSound));
      }
    }
}

//Microphone aka Sound Sensor Logic
void soundDetected(){
    unsigned long interruptTime = millis();
    if (gameStarted){
      // Check if enough time has passed since the last interrupt
      if (interruptTime - lastInterruptTime > debounceDelay) {
        if (pressRoar == false){
          Serial.println(roarFailed);
        }else{
          Serial.println(roar);
        }
        playSound(roarSound, sizeof(roarSound));
        lastInterruptTime = interruptTime;  // Update the last interrupt time
      }
    }
}


