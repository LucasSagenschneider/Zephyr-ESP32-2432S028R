#include "display/display.h"
#include <zephyr/kernel.h>



int main(void)
{
    init_display();

    draw_content();

    while (true) {
        update_display();
    }
}