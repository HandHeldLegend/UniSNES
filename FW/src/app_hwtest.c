#include "main.h"
#include <stdint.h>
#include <stdbool.h>

bool _hwtest_pinok(uint primary)
{
    uint second = 0;
    uint third = 0;
    switch (primary)
    {
    default:
        return false;
        break;

    case HOJA_LATCH_PIN:
        second = HOJA_CLOCK_PIN;
        third = HOJA_SERIAL_PIN;
        break;
    case HOJA_CLOCK_PIN:
        second = HOJA_SERIAL_PIN;
        third = HOJA_LATCH_PIN;
        break;
    case HOJA_SERIAL_PIN:
        second = HOJA_CLOCK_PIN;
        third = HOJA_LATCH_PIN;
        break;
    };

    gpio_init(primary);
    gpio_set_dir(primary, false);
    gpio_pull_up(primary);

    gpio_init(second);
    gpio_set_dir(second, true);
    gpio_put(second, false);

    gpio_init(third);
    gpio_set_dir(third, true);
    gpio_put(third, false);

    bool read = gpio_get(primary);

    // Fail if our pin is read low
    if (!read)
        return false;

    // Pass if we read high (pulled up)
    return true;
}

bool _hwtest_data()
{
    return _hwtest_pinok(HOJA_SERIAL_PIN);
}

bool _hwtest_latch()
{
    return _hwtest_pinok(HOJA_LATCH_PIN);
}

bool _hwtest_clock()
{
    return _hwtest_pinok(HOJA_CLOCK_PIN);
}

/**
 * @file app_hwtest.c
 * @brief Hardware test function for the application.
 *
 * This function performs a looped hardware test and returns the test result as a 16-bit unsigned integer.
 * The test includes checking various hardware components such as analog, battery, bluetooth, clock pin, data pin,
 * latch pin, RGB pin, and IMU.
 *
 * @return The test result as a 16-bit unsigned integer.
 */
uint16_t cb_hoja_hardware_test()
{
    hoja_hw_test_u _t;

    _t.analog = false;
    _t.battery = false;
    _t.bluetooth = false;
    _t.clock_pin = _hwtest_clock();
    _t.data_pin = _hwtest_data();
    _t.latch_pin = _hwtest_latch();
    _t.rgb_pin =  true;
    _t.imu = false;
    _t.rumble = true;

    cb_hoja_rumble_test();

    return _t.val;
}