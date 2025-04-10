#include "FreeRTOS.h"
#include "task.h"
#include "comm_external.h"
#include "tusb.h"
#include "pico/stdlib.h"
#include "rick_roll.h"
#include <stdlib.h>

#define MIN_DELAY 50
#define MAX_DELAY 100

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

int random_between(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void setup_uart() {
    uart_init(uart0, 115200);  // Initialize UART0 with 115200 baud rate
    gpio_set_function(0, GPIO_FUNC_UART);  // TX pin
    gpio_set_function(1, GPIO_FUNC_UART);  // RX pin
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_putc(uart0, *str++);
    }
}

void led_on(void)
{
    gpio_put(LED_PIN, 1); 
}

void led_off(void)
{
    gpio_put(LED_PIN, 0);
}

void run_script(const char** script) {

    setup_uart();

    for (int i = 0; script[i] != NULL; i++) {
        uart_send_string(script[i]);

        const char* line = script[i];

        if (strncmp(line, "DELAY ", 6) == 0) {
            int delay_ms = atoi(line + 6);
            vTaskDelay(pdMS_TO_TICKS(delay_ms));
        }
        else if (strncmp(line, "STRING ", 7) == 0) {
            const char* text = line + 7;

            for (int c = 0; text[c] != '\0'; c++) {
                send_char_as_key(text[c]);
                int delay = random_between(MIN_DELAY, MAX_DELAY);
                led_on();
                vTaskDelay(pdMS_TO_TICKS(delay));
                led_off();
            }
        }
        else if (strcmp(line, "ENTER") == 0) {
            send_key(HID_KEY_ENTER, 0);
        }
        else if (strcmp(line, "TAB") == 0) {
            send_key(HID_KEY_TAB, 0);
        }
        else if (strcmp(line, "LGUI") == 0) {
            send_key(0, KEYBOARD_MODIFIER_LEFTGUI);
        }
        else {
            // Unknown command - could log or ignore
        }

        led_on();
        vTaskDelay(pdMS_TO_TICKS(50)); // brief pause between commands
        led_off();
    }
}

void runner_init(void)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void runner_task(void *pvParameters)
{
    runner_init();

    run_script(rick_roll_payload);

    while (true)
    {
        // TODO: add some code to save data to sd maybe
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

