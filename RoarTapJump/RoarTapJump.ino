#include <SPI.h>
#include "soundFunctions.h"
#include "roar.h"
#include "tap.h"
#include "jump.h"

#define CS_DAC 10  // Chip Select pin for MCP4921 DAC

void setup() {
    pinMode(CS_DAC, OUTPUT);  // Set DAC CS pin as output
    SPI.begin();  // Initialize SPI for DAC
}

void loop() {
    playSound(roarSound, sizeof(roarSound));  // Play the "roar" sound
    delay(1000);  // Wait before playing again
    playSound(tapSound, sizeof(tapSound));
    delay(1000);
    playSound(jumpSound, sizeof(jumpSound));
    delay(1000);
}


