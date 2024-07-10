add_executable(oled
    main.cpp
    ImageData.c
    ImageData.h
    OLED_0in49_test.c
    OLED_0in49.c
    OLED_Test.h
)

# include libs
add_subdirectory(./lib/Config)
add_subdirectory(./lib/OLED)
add_subdirectory(./lib/Fonts)
add_subdirectory(./lib/GUI)
include_directories(./lib/Config)
include_directories(./lib/Fonts)
include_directories(./lib/GUI)
include_directories(./lib/OLED)

# pull in common dependencies
target_link_libraries(oled 
    pico_stdlib 
    examples 
    Config 
    GUI 
    Fonts 
    OLED 
    hardware_spi 
    hardware_i2c 
    hardware_pwm 
    hardware_adc
)

# pico config
pico_set_program_name(oled "oled")
pico_set_program_version(oled "0.1")

pico_enable_stdio_uart(oled 1)
pico_enable_stdio_usb(oled 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(oled)