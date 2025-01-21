#include "led.h"

#define UART_ID uart1
#define Baudrate 115200
#define TX 4
#define RX 5

int main()
{
    stdio_init_all();
    init_uart(UART_ID, Baudrate, TX, RX);
    sleep_ms(1000);
    LED_STRIP_t led_strip = create_led_strip(5, 13);
    clear_strip(led_strip);

    int i = 0;
    while (true)
    {
        sleep_ms(1000);
        build_strip(i, led_strip);
        print_data(UART_ID, &led_strip);
        send_strip(led_strip);
        reset_led(led_strip);
        print(UART_ID,"[+] Current Led Value: %d\r\n", i);

        i++;
        if (i >= led_strip.led_count)
        {
            i = 0;
        }

    }

    destroy_led_strip(&led_strip);

    return 0;
}
