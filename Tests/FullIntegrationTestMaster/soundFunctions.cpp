#include "soundFunctions.h"
#include <SPI.h>  // Include SPI for communication

void writeDAC(uint16_t value) {
    value &= 0x0FFF;  // Ensure it's 12-bit
    digitalWrite(CS_DAC, LOW);
    SPI.transfer((value >> 8) | 0x30);  // Command byte
    SPI.transfer(value & 0xFF);         // Data byte
    digitalWrite(CS_DAC, HIGH);
}

void playSound(const uint8_t *sound, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        uint8_t sample = pgm_read_byte(&sound[i]);  // Read sound sample from PROGMEM
        writeDAC(sample << 4);  // Convert 8-bit to 12-bit
        delayMicroseconds(125);  // Approx 8kHz sample rate
    }
}

