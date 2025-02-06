#include "pico/stdlib.h"
#include <stdio.h>
#include "ws2812.pio.h" // biblioteca para usar ws2812
#include "matriz_leds.h"
#include "setup.h"
#include "debouce.h"
#include "hardware/timer.h"
#include "pico/bootrom.h"

const uint pino_led_azul = 12; // pino do led azul
const uint pino_led_verde = 11;
const uint pino_botao_a = 5; // pino do botao A
const uint pino_botao_b = 6; // pino do botao B
const uint pino_matriz_leds = 7; // pino da matriz de leds

uint32_t ultimo_tempo = 0;

bool repeating_timer_callback(struct repeating_timer *t);

void gpio_irq_handler(uint gpio, uint32_t events); // prototipo da função para tratar a interrupção dos botoes


int main() {

    stdio_init_all();

    setup_led(pino_led_azul);
    setup_led(pino_led_verde);

    setup_botoes(pino_botao_a, pino_botao_b); // inicializando os botoes
    setup_matriz_leds(pino_matriz_leds);  // inicializando a matriz de leds


    // timer para verificar se tem letra nova
    struct repeating_timer timer;
    add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);

    // definindo uma interrupção para os botoes na borda de descida
    gpio_set_irq_enabled_with_callback(pino_botao_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // botao A
    gpio_set_irq_enabled_with_callback(pino_botao_b, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // botao B

    
    while (true) {
        tight_loop_contents();  // Mantém o sistema ativo sem busy-waiting
     }


}

bool repeating_timer_callback(struct repeating_timer *t) {

    int c = getchar_timeout_us(0);  // Verifica se há um caractere disponível (timeout de 0 us)
    if (c == PICO_ERROR_TIMEOUT) {
        return true;  // Nenhum caractere disponível, mantém o timer rodando
    }

    printf("Recebido o caractere: %c.\n", (char)c);
    return true;
}



/*

* Função para interrupção dos botoes
*/
void gpio_irq_handler(uint gpio, uint32_t events) {


    if (!(debouce(&ultimo_tempo))) { // fazendo o debouce dos botoes
        return;
    }

    uint pino_led = gpio == pino_botao_a ? pino_led_verde : pino_led_azul; // selecionando o pino do led
    
    bool proximo_estado_led = !(gpio_get(pino_led)); // trocando o estado
    gpio_put(pino_led, proximo_estado_led);

    printf("O Led %s está %s.\n", pino_led == pino_led_verde ? "Verde" : "Azul", 
            proximo_estado_led == true ? "ON" : "OFF"); // mensagem informativa

    return;
}


