#include "pico/stdlib.h"
#include <stdio.h>
#include "ws2812.pio.h" // biblioteca para usar ws2812
#include "matriz_leds.h"
#include "setup.h"

int main() {

    stdio_init_all();

    while (true) {
        printf("Hello World.\n");
        sleep_ms(500);
    }


}