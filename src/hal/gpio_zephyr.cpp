#include "i_gpio.hpp"
#include "pump_state_machine.hpp"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(input, LOG_LEVEL_INF);

const struct device* uart_dev = DEVICE_DT_GET(DT_NODELABEL(usart1)); // single definition
    static struct gpio_callback sw1_cb_data;
    static struct gpio_callback sw2_cb_data;
extern void uart_callback(const struct device* dev, struct uart_event* evt, void* user_data);
extern PumpStateMachine pump;

void hardware_init() {

    gpio_pin_configure_dt(&led_pin, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&switch1, GPIO_INPUT | GPIO_PULL_UP);
    gpio_pin_configure_dt(&switch2, GPIO_INPUT | GPIO_PULL_UP);
    gpio_pin_configure_dt(&buzzer_pin, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&step, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&dir, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&enab, GPIO_OUTPUT_INACTIVE);

    gpio_pin_interrupt_configure_dt(&switch1, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&sw1_cb_data, sw1_isr, BIT(switch1.pin));
    gpio_add_callback(switch1.port, &sw1_cb_data);

    gpio_pin_interrupt_configure_dt(&switch2, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&sw2_cb_data, sw2_isr, BIT(switch2.pin));
    gpio_add_callback(switch2.port, &sw2_cb_data);

    uart_callback_set(uart_dev, uart_callback, nullptr);
    uart_rx_enable(uart_dev, rx_buf, sizeof(rx_buf), 100);
}

void led::update(bool active) {
#ifndef UNIT_TEST
    gpio_pin_set_dt(&led_pin, active ? 1 : 0);
#endif
}

void buzzer::update(bool active) {
#ifndef UNIT_TEST
    gpio_pin_set_dt(&buzzer_pin, active ? 1 : 0);
#endif
}
void sw1_isr(const struct device* dev, struct gpio_callback* cb, uint32_t pins) {
    pump.start();
    LOG_INF("STARTED\n");
}
void sw2_isr(const struct device* dev, struct gpio_callback* cb, uint32_t pins) {
    LOG_ERR("OCCLUSION\n");
    pump.occlusion();
}