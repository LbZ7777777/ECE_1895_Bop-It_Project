#ifndef SOUNDFUNCTIONS_H
#define SOUNDFUNCTIONS_H

#include <Arduino.h>

#define CS_DAC 10

void playSound(const uint8_t *sound, uint16_t length);

#endif
