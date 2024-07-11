#include <cstdio>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "Oled.h"

/*
 * Waveshare 1.5 inch OLED Pin Config:
 *
 *  4 Wire SPI
 *
 *  Pico Pin | GPIO |  Signal
 *  ---------|------|--------------
 *      22   | GP17 |  SPI0_CSn
 *      23   | ---- |  GND
 *      24   | GP18 |  SPI0_SCK
 *      25   | GP19 |  SPI0_TX
 *      26   | GP20 |  GP20 (DC)
 *      27   | GP21 |  GP21 (RST)
 *
 */

int main()
{
    timer_hw->dbgpause = 0;

    stdio_init_all();

    Oled::Config config;
    config.spi = spi0;
    config.baudrate = 1e5;
    config.reset = 21;
    config.data_command = 20;
    config.chip_select = 17;
    config.clock = 18;
    config.mosi = 19;
    Oled oled{config};

    std::printf("initializing oled\n");
    oled.init();

    constexpr uint8_t LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true)
    {
        std::printf("o");
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        std::printf(".");
        gpio_put(LED_PIN, 0);
        sleep_ms(250);

        std::printf("\nsending test image\n");
        oled.show_test_image();
    }

    return 0;
}
