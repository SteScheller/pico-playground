#include "pico/stdlib.h"
#include "OLED_Test.h"

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
    OLED_0in49_test();

    return 0;
}
