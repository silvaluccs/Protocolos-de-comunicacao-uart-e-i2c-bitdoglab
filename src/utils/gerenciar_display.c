#include "pico/stdlib.h"
#include "ssd1306.h"
#include "matriz_leds.h"
#include "gerenciar_display.h"

const uint r = 5, b = 5, g = 5; // valores de r, g e b para a matriz de leds

/*
* Função para enviar um caracter para o display
*/
void enviar_letra_para_display(char c, ssd1306_t *ssd) {

    if (c >= '0' && c <= '9') {
        desenhar_numero_na_matriz_de_leds(r, g, b, c);
    }

    ssd1306_fill(ssd, false); // Limpa o display
    ssd1306_draw_char(ssd, c, 60, 30);
    ssd1306_send_data(ssd); // Atualiza o display

}

/*
* Função para enviar uma string para o display
*/
void enviar_mensagem_para_display(char *mensagem1, char *mensagem2, ssd1306_t *ssd) {

    ssd1306_fill(ssd, false); // Limpa o display
    ssd1306_draw_string(ssd, mensagem1, 20, 30); 
    ssd1306_draw_string(ssd, mensagem2, 20, 40);
    ssd1306_send_data(ssd); // Atualiza o display


}