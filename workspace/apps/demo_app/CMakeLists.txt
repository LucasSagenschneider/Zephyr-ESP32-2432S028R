cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(demo_display)

# Include the display
add_subdirectory(src/display)

target_sources(app PRIVATE src/main.c)

# Link the say_hello library to the application
target_link_libraries(app PRIVATE display)
