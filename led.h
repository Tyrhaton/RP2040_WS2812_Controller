#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"
#include "uart.h"

typedef struct
{
    int led_count;
    int gpio_pin;
    uint32_t *data;
} LED_STRIP_t;

void delay_us(double us);
void build_strip(int position, LED_STRIP_t led_strip);
void send_strip(LED_STRIP_t led_strip);
void reset_led(LED_STRIP_t led_strip);

void clear_strip(LED_STRIP_t led_strip);
LED_STRIP_t create_led_strip(int led_count, int gpio_pin);
void destroy_led_strip(LED_STRIP_t *led_strip);
void print_data(uart_inst_t *uart, LED_STRIP_t *led_strip);

#endif