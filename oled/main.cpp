#include "pico/stdlib.h"
#include "OLED_Test.h"

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
    OLED_0in49_test();

    return 0;
}
