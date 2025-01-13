#include "led.h"

void delay_us(double us)
{
    if (us <= 0)
        return;
    uint32_t cycles = (uint32_t)((us * 125) - 3);
    if (cycles > 0)
    {
        busy_wait_at_least_cycles(cycles);
    }
}

void build_strip(int position, LED_STRIP_t led_strip)
{
    for (int i = 0; i < led_strip.led_count; i++)
    {
        if (i == position)
        {
            led_strip.data[i] = 0x00F;
        }
        else
        {
            led_strip.data[i] = 0x000;
        }
    }
}

void send_strip(LED_STRIP_t led_strip)
{
    
    for (int i = 0; i < led_strip.led_count; i++)
    {
        uint32_t color = led_strip.data[i];
        for (int bit = 23; bit >= 0; bit--)
        {
            bool bit_value = (color >> bit) & 1;
            if (bit_value)
            {
                gpio_put(led_strip.gpio_pin, 1);
                delay_us(0.8);
                gpio_put(led_strip.gpio_pin, 0);
                delay_us(0.45);
            }
            else
            {
                gpio_put(led_strip.gpio_pin, 1);
                delay_us(0.4);
                gpio_put(led_strip.gpio_pin, 0);
                delay_us(0.85);
            }
        }
    }
}
void reset_led(LED_STRIP_t led_strip)
{
    gpio_put(led_strip.gpio_pin, 0);
    delay_us(100);
}
void clear_strip(LED_STRIP_t led_strip)
{
    for (int i = 0; i < led_strip.led_count; i++)
    {
        led_strip.data[i] = 0x000000; // Zet alle LEDs uit
    }
    send_strip(led_strip);
    reset_led(led_strip);
}

LED_STRIP_t create_led_strip(int led_count, int gpio_pin)
{
    LED_STRIP_t led_strip;
    led_strip.led_count = led_count;
    led_strip.gpio_pin = gpio_pin;
    led_strip.data = (uint32_t *)malloc(led_count * sizeof(uint32_t));
    clear_strip(led_strip);

    if (led_strip.data == NULL)
    {
        print(uart1,"Memory allocation failed\n");
        exit(1);
    }
    
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_OUT);

    for (int i = 0; i < led_strip.led_count; i++)
    {
        led_strip.data[i] = 0x000;
    }
    reset_led(led_strip);

    return led_strip;
}

void destroy_led_strip(LED_STRIP_t *led_strip)
{
    free(led_strip->data);
    led_strip->data = NULL;
}

