#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <lvgl_input_device.h>
#include <zephyr/input/input.h>

static const struct gpio_dt_spec backlight = GPIO_DT_SPEC_GET(DT_ALIAS(backlight), gpios);
static const struct device *const touch_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_touch));

// Settings
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

// content
static uint32_t count;
char count_str[11] = {0};
const struct device *display_dev;
lv_obj_t *hello_world_label;
lv_obj_t *hello_world_button;
lv_obj_t *count_label;

static struct {
	size_t x;
	size_t y;
	bool pressed;
} touch_point;

static void touch_event_callback(struct input_event *evt, void *user_data)
{
	if (evt->code == INPUT_ABS_X) {
		touch_point.x = evt->value;
	}
	if (evt->code == INPUT_ABS_Y) {
		touch_point.y = evt->value;
	}
	if (evt->code == INPUT_BTN_TOUCH) {
		touch_point.pressed = evt->value;
	}
	if (evt->sync) {
		//k_sem_give(&sync);
	}
}
INPUT_CALLBACK_DEFINE(touch_dev, touch_event_callback, NULL);


static void lv_btn_click_callback(lv_event_t *e)
{
	ARG_UNUSED(e);

    printk("Button click\r\n");

	count = 0;
}


void init_display()
{
    printk("init display\r\n");
    const struct device *display;
    
    // Initialize the display
    display = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display)) {
        printk("Error: display not ready\r\n");
    }

    // Disable display blanking
    display_blanking_off(display);

    // activate Backlight
    if(gpio_is_ready_dt(&backlight))
    {
        gpio_pin_configure_dt(&backlight, GPIO_OUTPUT);
        gpio_pin_set_dt(&backlight, true);
    }
}

void draw_content()
{
	hello_world_button = lv_btn_create(lv_scr_act());
	lv_obj_align(hello_world_button, LV_ALIGN_CENTER, 0, -15);
	lv_obj_add_event_cb(hello_world_button, lv_btn_click_callback, LV_EVENT_CLICKED,
				    NULL);
	hello_world_label = lv_label_create(hello_world_button);

    lv_label_set_text(hello_world_label, "Hello world!");
	lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);

	count_label = lv_label_create(lv_scr_act());
	lv_obj_align(count_label, LV_ALIGN_BOTTOM_MID, 0, 0);

}

void update_display()
{
	if ((count % 10) == 0U) {
		sprintf(count_str, "%d", count/10U);
		lv_label_set_text(count_label, count_str);
	}

    printk("TOUCH %s X, Y: (%d, %d)", touch_point.pressed ? "PRESS" : "RELEASE",
			touch_point.x, touch_point.y);

	lv_task_handler();
	++count;
 	k_sleep(K_MSEC(100));
}