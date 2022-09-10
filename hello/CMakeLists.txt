add_executable(hello
        hello.cpp
        )

# pull in common dependencies
target_link_libraries(hello pico_stdlib)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello)