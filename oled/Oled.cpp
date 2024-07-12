#include "Oled.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

namespace
{
    constexpr uint8_t DISPLAY_OFF[] = {0xAE};
    constexpr uint8_t DISPLAY_ON[] = {0xAF};
    constexpr uint8_t COLUMN_ADDRESS[] = {0x15, 0x00, 0x3F};
    constexpr uint8_t ROW_ADDRESS[] = {0x75, 0x00, 0x7F};
    constexpr uint8_t CONTRAST[] = {0x81, 0x7F};
}

Oled::Oled(Config config) : m_config{config}
{
    /**
     * Display Byte Order
     * ------------------
     *
     *      p(0, HEIGHT - 1)            ...             p(WIDTH - 1, HEIGHT - 1)
     *      ...                                         ...
     *      p(0,0)                      ...             p(WIDTH - 1, 0)
     *
     *  - 4 bit per pixel
     *  - 2 pixel per byte
     *
     * uint8_t display_data[WIDTH * HEIGHT / 2] = {...};
     * display_data[0] = p(0, 1) << 4 | p(0, 0);
     * display_data[1] = p(0, 3) << 4 | p(0, 2);
     * ...
     * display_data[HEIGHT / 2] = p(1, 1) << 4 | p(1, 0);
     * ...
     *
     */
    for (size_t i = 0; i < m_test_image.size(); ++i)
    {
        m_test_image[i] = i % 0x10;
    }
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
    write_command(DISPLAY_OFF, sizeof(DISPLAY_OFF));
    write_command(COLUMN_ADDRESS, sizeof(COLUMN_ADDRESS));
    write_command(ROW_ADDRESS, sizeof(ROW_ADDRESS));
    write_command(CONTRAST, sizeof(CONTRAST));
    write_command(DISPLAY_ON, sizeof(DISPLAY_ON));
}

void Oled::write(const uint8_t *data, size_t size, bool is_data)
{
    gpio_put(m_config.data_command, is_data ? 1 : 0);
    gpio_put(m_config.chip_select, 0);
    spi_write_blocking(m_config.spi, data, size);
    gpio_put(m_config.chip_select, 1);
}

void Oled::write_command(const uint8_t *data, size_t size)
{
    write(data, size, false);
}

void Oled::write_data(const uint8_t *data, size_t size)
{
    write(data, size, true);
}

void Oled::show_test_image()
{
    write_data(m_test_image.data(), m_test_image.size());
}