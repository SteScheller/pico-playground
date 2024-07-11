#include "Oled.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

Oled::Oled(Config config) : m_config{config}
{
}

void Oled::init()
{
    // SPI config
    spi_init(m_config.spi, 100000);
    gpio_set_function(m_config.clock, GPIO_FUNC_SPI);
    gpio_set_function(m_config.mosi, GPIO_FUNC_SPI);
    gpio_set_function(m_config.chip_select, GPIO_FUNC_SPI);

    // GPIO config
    gpio_init(m_config.reset);
    gpio_init(m_config.data_command);
    gpio_set_dir(m_config.reset, GPIO_OUT);
    gpio_set_dir(m_config.data_command, GPIO_OUT);

    // reset oled
    gpio_put(m_config.reset, 1);
    sleep_ms(100);
    gpio_put(m_config.reset, 0);
    sleep_ms(100);
    gpio_put(m_config.reset, 1);
    sleep_ms(100);

    // oled controller config
    write_config_register(0xAE); /*display off*/

    write_config_register(0x00); /*set lower column address*/
    write_config_register(0x12); /*set higher column address*/

    write_config_register(0x00); /*set display start line*/

    write_config_register(0xB0); /*set page address*/

    write_config_register(0x81); /*contract control*/
    write_config_register(0x4f); /*128*/

    write_config_register(0xA0); /*set segment remap*/

    write_config_register(0xA6); /*normal / reverse*/

    write_config_register(0xA8); /*multiplex ratio*/
    write_config_register(0x1F); /*duty = 1/32*/

    write_config_register(0xC8); /*Com scan direction*/

    write_config_register(0xD3); /*set display offset*/
    write_config_register(0x00);

    write_config_register(0x20);
    write_config_register(0x01); /*set Vertical Addressing Mode*/

    write_config_register(0xD5); /*set osc division*/
    write_config_register(0x80);

    write_config_register(0xD9); /*set pre-charge period*/
    write_config_register(0xf1);

    write_config_register(0xDA); /*set COM pins*/
    write_config_register(0x12);

    write_config_register(0xdb); /*set vcomh*/
    write_config_register(0x40);

    write_config_register(0x8d); /*set charge pump enable*/
    write_config_register(0x14);

    write_config_register(0xAF); /*display ON*/
}

void Oled::write_config_register(uint8_t reg)
{
    gpio_put(m_config.data_command, 0);
    gpio_put(m_config.chip_select, 0);
    spi_write_blocking(m_config.spi, &reg, 1);
    gpio_put(m_config.chip_select, 1);
}

void Oled::write_data(uint8_t data)
{
    gpio_put(m_config.data_command, 1);
    gpio_put(m_config.chip_select, 0);
    spi_write_blocking(m_config.spi, &data, 1);
    gpio_put(m_config.chip_select, 1);
}

void Oled::show_test_image()
{
    static constexpr uint8_t TEST_BYTE{0xF0};

    write_config_register(0x22);
    write_config_register(0x00);
    write_config_register(0x03);
    write_config_register(0x21);
    write_config_register(0x20);
    write_config_register(0x5f);

    for (size_t i = 0; i < (WIDTH * HEIGHT / 2); ++i)
    {
        write_data(TEST_BYTE);
    }
}