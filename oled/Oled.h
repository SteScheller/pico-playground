#pragma once

#include <cstdint>
#include <array>
#include "hardware/spi.h"

class Oled
{
public:
    inline static constexpr size_t WIDTH = 128;
    inline static constexpr size_t HEIGHT = 128;

    struct Config
    {
        using pinNr_t = uint8_t;
        using baudrate_t = uint32_t;

        spi_inst_t *spi;
        baudrate_t baudrate;

        pinNr_t reset;
        pinNr_t data_command;
        pinNr_t chip_select;
        pinNr_t clock;
        pinNr_t mosi;
    };

    using image_data_t = std::array<uint8_t, WIDTH * HEIGHT / 2>;

    Oled(Config config);

    void init();
    void show_test_image();

private:
    void write(const uint8_t *data, size_t size, bool is_data);
    void write_command(const uint8_t *data, size_t size);
    void write_data(const uint8_t *data, size_t size);

    Config m_config;
    image_data_t m_test_image;
};