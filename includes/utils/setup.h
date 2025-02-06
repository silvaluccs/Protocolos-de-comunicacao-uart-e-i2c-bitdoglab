#ifndef SETUP_H
#define SETUP_H

#include "pico/stdlib.h"

void setup_led(uint pino_led);
void setup_botoes(uint pino_botao_a, uint pino_botao_b);
void setup_matriz_leds(uint pino_matriz_leds);

#endif