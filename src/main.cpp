#include <cstdint>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include "i_gpio.hpp"
#include "alarm_manager.hpp"
#include "command_parser.hpp"
#include "i_alarm_observer.hpp"
#include "i_uart.hpp"
#include "i_pump_state.hpp"
#include "pump_state_machine.hpp"
#include "volume_tracker.hpp"

AlarmManager alarm;
led led_obj;
buzzer buz;
PumpStateMachine pump(alarm);
commandparser parser(&pump);
uart_observer uart_obs(&parser);
Volumetracker vol_track;

static constexpr uint32_t kStackSize = 2048;
static constexpr uint32_t kDelayTime = 100;
static constexpr uint8_t kThreadPriority = 5;

K_THREAD_STACK_DEFINE(thread1, kStackSize);
struct k_thread my_thread;

void th_fn([[maybe_unused]] void *arg1, [[maybe_unused]] void *arg2, [[maybe_unused]] void *arg3) {
    while (true) {
        if (pump.motor.motor_running) {
            gpio_pin_set_dt(&step, 1);
            k_sleep(K_USEC(pump.motor.delay.load()));
            gpio_pin_set_dt(&step, 0);
            k_sleep(K_USEC(pump.motor.delay.load()));
            pump.motor.step_count_++;
            vol_track.update(pump.motor.step_count_);
        }
        k_yield();
    }
}

int main() {
    alarm.add(&led_obj);
    alarm.add(&buz);
    alarm.add(&uart_obs);
    pump.setrate(1.0F);
    hardware_init();

    k_thread_create(&my_thread, thread1, K_THREAD_STACK_SIZEOF(thread1), th_fn,
                    nullptr, nullptr, nullptr, kThreadPriority, 0, K_NO_WAIT);
    while (true) {
        k_sleep(K_MSEC(kDelayTime));
    }
    return 0;
}