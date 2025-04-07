#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include "pico/stdlib.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/adc.h"

void adc_1_task(void *p) {

    adc_init();

    adc_gpio_init(27);


    adc_gpio_init(26);

    // Fator de conversão:
    // 12 bits => 2^12 = 4096
    // Faixa total de 0 a 3,3 V
    const float conversion_factor = 3.3f / (1 << 12);

    while (1) {
        adc_select_input(1);
        uint16_t result1 = adc_read();
        printf("voltage 1: %f V\n", result1 * conversion_factor);

    
        adc_select_input(0);
        uint16_t result2 = adc_read();
        printf("voltage 2: %f V\n", result2 * conversion_factor);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main() {
    stdio_init_all();
    printf("Start RTOS \n");


    xTaskCreate(adc_1_task, "ADC_Task", 4096, NULL, 1, NULL);

   
    vTaskStartScheduler();

    while (true) {
        
    }
}
