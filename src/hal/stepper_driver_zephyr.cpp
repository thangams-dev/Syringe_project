#include "i_stepper_driver.hpp"
#ifndef UNIT_TEST
#include <zephyr/drivers/gpio.h>
#endif

void MotorDriver::start() {
#ifndef UNIT_TEST
    gpio_pin_set_dt(&enab, 1);
#endif
    motor_running = true;
}   

void MotorDriver::stop() {
    motor_running = false;
#ifndef UNIT_TEST
    gpio_pin_set_dt(&enab, 0);
#endif
}

void MotorDriver::Setrate(float ml_per_hr) {
    
    rpm = ml_per_hr;
    float steps_min = rpm * static_cast<float>(kStepsPerRev);
    if (steps_min <= 0.0F) {
    delay = UINT32_MAX; // or trigger an alarm/error state
    return;
}
    delay = static_cast<uint32_t>(60000000.0F / steps_min);
}

void MotorDriver::reset() {
#ifndef UNIT_TEST
    gpio_pin_set_dt(&step, 0);
#endif
    step_count_ = 0;
}

uint32_t MotorDriver::getsteps() {
    return step_count_;
}