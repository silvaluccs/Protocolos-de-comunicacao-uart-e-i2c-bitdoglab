#ifndef GERENCIAR_DISPLAY_H
#define GERENCIAR_DISPLAY_H

#include "pico/stdlib.h"
#include "ssd1306.h"

void enviar_letra_para_display(char c, ssd1306_t *ssd);
void enviar_mensagem_para_display(char *mensagem1, char *mensagem2, ssd1306_t *ssd);

#endif