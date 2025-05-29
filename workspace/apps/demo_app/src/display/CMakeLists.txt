# Create the library target
add_library(display STATIC display.c)

# Add the library's header file(s)
target_include_directories(display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Required to set Zephyr compile options (e.g. for ARM)
target_link_libraries(display PRIVATE zephyr_interface)
