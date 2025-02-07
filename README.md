# README: Projeto de Comunicação UART e I2C com Raspberry Pi Pico

## Visão Geral
Este projeto implementa comunicação UART e controle de dispositivos usando temporizadores e interrupções no Raspberry Pi Pico. Ele gerencia LEDs, botões, uma matriz de LEDs WS2812 e um display OLED SSD1306. O código foi desenvolvido utilizando o Pico SDK e bibliotecas personalizadas.

---

## Link para Vídeo explicativo
https://drive.google.com/file/d/1qvOz4A8bj2q8VHl887kKzWfe00EghB7G/view?usp=sharing
---

## Funcionalidades
- Controle de LEDs (azul e verde) através de botões.
- Display de caracteres recebidos via UART no display OLED.
- Utilização de temporizador repetitivo para verificar entradas seriais.
- Tratamento de interrupções GPIO com debounce para evitar leituras incorretas dos botões.
- Gerenciamento de uma matriz de LEDs.

---

## Estrutura do Código
### Arquivo Principal: `main.c`

### Inicialização
```c
int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    setup_led(pino_led_azul);
    setup_led(pino_led_verde);
    setup_botoes(pino_botao_a, pino_botao_b);
    setup_matriz_leds(pino_matriz_leds);
    setup_display();
    init_display(&ssd);

    struct repeating_timer timer;
    add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);

    gpio_set_irq_enabled_with_callback(pino_botao_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(pino_botao_b, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        tight_loop_contents();
    }
}
```
**Descrição:**
- Inicializa LEDs, botões, matriz de LEDs e o display.
- Configura um temporizador que verifica se há novos caracteres recebidos via UART a cada 100 ms.
- Define interrupções para os botões para alternar o estado dos LEDs.

---

### Função do Temporizador
```c
bool repeating_timer_callback(struct repeating_timer *t) {
    int c = getchar_timeout_us(0);
    if (c == PICO_ERROR_TIMEOUT) {
        return true;
    }
    printf("Recebido o caractere: %c.\n", (char)c);
    enviar_letra_para_display((char)c, &ssd);
    return true;
}
```
**Descrição:**
- Verifica se há um caractere disponível na entrada UART.
- Se um caractere for recebido, ele é exibido no display OLED.

---

### Função de Interrupção dos Botões
```c
void gpio_irq_handler(uint gpio, uint32_t events) {
    if (!(debouce(&ultimo_tempo))) {
        return;
    }
    uint pino_led = gpio == pino_botao_a ? pino_led_verde : pino_led_azul;
    bool proximo_estado_led = !(gpio_get(pino_led));
    gpio_put(pino_led, proximo_estado_led);
    printf("%s %s\n", pino_led == pino_led_verde ? "LED VERDE" : "LED AZUL", proximo_estado_led ? "LIGADO" : "DESLIGADO");
}
```
**Descrição:**
- Trata as interrupções dos botões.
- Utiliza debounce para evitar múltiplas leituras.
- Alterna o estado do LED correspondente ao botão pressionado.

---

## Uso de Temporizadores
- O temporizador repetitivo (`add_repeating_timer_ms`) verifica se há novos dados na UART a cada 100 ms.
- Isso permite evitar o uso de polling constante, melhorando a eficiência do sistema.

## Uso de Interrupções
- As interrupções dos botões são configuradas para a borda de descida (GPIO_IRQ_EDGE_FALL).
- A função de interrupção (`gpio_irq_handler`) garante resposta rápida e debounce.

---

## Como Compilar e Executar
1. Certifique-se de ter o Pico SDK configurado.
2. Compile o projeto com o CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Envie o arquivo binário gerado para o Raspberry Pi Pico.

---

## Bibliotecas Utilizadas
- **pico/stdlib.h**: Funções padrão do Raspberry Pi Pico.
- **hardware/timer.h**: Manipulação de temporizadores.
- **hardware/i2c.h**: Comunicação I2C.
- **ssd1306.h**: Controle do display OLED SSD1306.

---

## Contato
Para dúvidas ou contribuições, entre em contato com o autor.


