#include "pico/stdlib.h"

/*
 * Waveshare 1.5 inch OLED Pin Config:
 *
 *  4 Wire SPI
 *
 *  Pico Pin |  Signal
 *  ---------|--------------
 *      22   |  SPI0_CSn
 *      23   |  GND
 *      24   |  SPI0_SCK
 *      25   |  SPI0_TX
 *      26   |  GP20 (DC)
 *      27   |  GP21 (RST)
 *
 */

int main()
{
    const uint LED_PIN = 25;
    timer_hw->dbgpause = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true)
    {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }

    return 0;
}
