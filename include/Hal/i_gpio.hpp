#pragma once
#include "i_alarm_observer.hpp"
#include "i_uart.hpp"

#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>


static const struct gpio_dt_spec led_pin = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec switch1 = GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios);
static const struct gpio_dt_spec switch2 = GPIO_DT_SPEC_GET(DT_ALIAS(sw2), gpios);
static const struct gpio_dt_spec buzzer_pin = GPIO_DT_SPEC_GET(DT_ALIAS(bu), gpios);
static const struct gpio_dt_spec step = GPIO_DT_SPEC_GET(DT_ALIAS(st1), gpios);
static const struct gpio_dt_spec dir = GPIO_DT_SPEC_GET(DT_ALIAS(dir1), gpios);
static const struct gpio_dt_spec enab = GPIO_DT_SPEC_GET(DT_ALIAS(enab1),gpios);
extern const struct device* uart_dev; // defined once in gpio_zephyr.cpp

/// @brief Initializes all hardware peripherals.
void hardware_init();

/// @brief ISR for switch 1.
/// @param dev GPIO device.
/// @param cb Callback struct.
/// @param pins Triggered pins.
void sw1_isr(const struct device* dev, struct gpio_callback* cb, uint32_t pins);

/// @brief ISR for switch 2.
/// @param dev GPIO device.
/// @param cb Callback struct.
/// @param pins Triggered pins.
void sw2_isr(const struct device* dev, struct gpio_callback* cb, uint32_t pins);
#endif