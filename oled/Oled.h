#pragma once

#include <cstdint>
#include "hardware/spi.h"

class Oled
{
public:
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

    Oled(Config config);

    void init();

private:
    void write_config_register(uint8_t reg);

    Config m_config;
};