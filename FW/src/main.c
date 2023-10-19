#include "hoja_includes.h"
#include "main.h"

void _gpio_put_od(uint gpio, bool level)
{
    // Unused
}

void cb_hoja_set_uart_enabled(bool enable)
{
    // Unused
}

void cb_hoja_set_bluetooth_enabled(bool enable)
{
    // Unused
}

button_remap_s user_map = {
    .dpad_up = MAPCODE_DUP,
    .dpad_down = MAPCODE_DDOWN,
    .dpad_left = MAPCODE_DLEFT,
    .dpad_right = MAPCODE_DRIGHT,

    .button_a = MAPCODE_B_A,
    .button_b = MAPCODE_B_B,
    .button_x = MAPCODE_B_X,
    .button_y = MAPCODE_B_Y,

    .trigger_l = MAPCODE_T_ZL,
    .trigger_r = MAPCODE_T_ZR,
    .trigger_zl = MAPCODE_T_L,
    .trigger_zr = MAPCODE_T_R,

    .button_plus = MAPCODE_B_PLUS,
    .button_minus = MAPCODE_B_MINUS,
    .button_stick_left = MAPCODE_B_STICKL,
    .button_stick_right = MAPCODE_B_STICKR,
};

void cb_hoja_hardware_setup()
{
    // Set up GPIO for input buttons
    hoja_setup_gpio_button(PGPIO_BTN_A);
    hoja_setup_gpio_button(PGPIO_BTN_B);
    hoja_setup_gpio_button(PGPIO_BTN_X);
    hoja_setup_gpio_button(PGPIO_BTN_Y);

    hoja_setup_gpio_button(PGPIO_BTN_DUP);
    hoja_setup_gpio_button(PGPIO_BTN_DDOWN);
    hoja_setup_gpio_button(PGPIO_BTN_DLEFT);
    hoja_setup_gpio_button(PGPIO_BTN_DRIGHT);

    hoja_setup_gpio_button(PGPIO_BTN_SELECT);
    hoja_setup_gpio_button(PGPIO_BTN_START);
    hoja_setup_gpio_button(PGPIO_BTN_L);
    hoja_setup_gpio_button(PGPIO_BTN_R);
}

void cb_hoja_read_buttons(button_data_s *data)
{
    data->button_a  = !gpio_get(PGPIO_BTN_A);
    data->button_b  = !gpio_get(PGPIO_BTN_B);
    data->button_x  = !gpio_get(PGPIO_BTN_X);
    data->button_y  = !gpio_get(PGPIO_BTN_Y);

    data->dpad_left     = !gpio_get(PGPIO_BTN_DLEFT);
    data->dpad_right    = !gpio_get(PGPIO_BTN_DRIGHT);
    data->dpad_down     = !gpio_get(PGPIO_BTN_DDOWN);
    data->dpad_up       = !gpio_get(PGPIO_BTN_DUP);

    data->trigger_l       = !gpio_get(PGPIO_BTN_L);
    data->trigger_r       = !gpio_get(PGPIO_BTN_R);
    data->button_plus     = !gpio_get(PGPIO_BTN_START);
    data->button_minus    = !gpio_get(PGPIO_BTN_SELECT);
}

void cb_hoja_read_analog(a_data_s *data)
{
    // Convert data
    data->lx = 128<<4;
    data->ly = 128<<4;
    data->rx = 128<<4;
    data->ry = 128<<4;
}

void cb_hoja_task_1_hook(uint32_t timestamp)
{
    //app_rumble_task(timestamp);
}

int main()
{
    stdio_init_all();
    sleep_ms(100);

    printf("UniSNES Started.\n");

    cb_hoja_hardware_setup();

    button_data_s tmp = {0};
    cb_hoja_read_buttons(&tmp);

    if(tmp.button_minus)
    {
        reset_usb_boot(0, 0);
    }

    hoja_config_t _config = {
        .input_method   = INPUT_METHOD_USB,
        .input_mode     = INPUT_MODE_LOAD,
    };
    hoja_init(&_config);
}
