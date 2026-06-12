#include "machine_state.hpp"
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>

static const struct gpio_dt_spec led_pin = GPIO_DT_SPEC_GET(DT_ALIAS(led0),gpios);
static const struct gpio_dt_spec switch1 = GPIO_DT_SPEC_GET(DT_ALIAS(sw1),gpios);
static const struct gpio_dt_spec switch2 = GPIO_DT_SPEC_GET(DT_ALIAS(sw2),gpios);
static const struct gpio_dt_spec buzzer_pin = GPIO_DT_SPEC_GET(DT_ALIAS(bu),gpios);
static const struct gpio_dt_spec step = GPIO_DT_SPEC_GET(DT_ALIAS(st1),gpios);
static const struct gpio_dt_spec dir = GPIO_DT_SPEC_GET(DT_ALIAS(dir1),gpios);
static const struct device* uart = DEVICE_DT_GET(DT_ALIAS(uart0));
// before hardware_init()
static struct gpio_callback sw1_cb_data;
static struct gpio_callback sw2_cb_data;
static char rx_buf[32];
void hardware_init(){
    gpio_pin_configure_dt(&led_pin,GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&switch1, GPIO_INPUT | GPIO_PULL_UP);
    gpio_pin_configure_dt(&switch2, GPIO_INPUT | GPIO_PULL_UP);
    gpio_pin_configure_dt(&buzzer_pin,GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&step,GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&dir,GPIO_OUTPUT_INACTIVE);

gpio_pin_interrupt_configure_dt(&switch1, GPIO_INT_EDGE_TO_ACTIVE);
gpio_init_callback(&sw1_cb_data, sw1_isr, BIT(switch1.pin));
gpio_add_callback(switch1.port, &sw1_cb_data);

gpio_pin_interrupt_configure_dt(&switch2, GPIO_INT_EDGE_TO_ACTIVE);
gpio_init_callback(&sw2_cb_data, sw2_isr, BIT(switch2.pin));
gpio_add_callback(switch2.port, &sw2_cb_data);
uart_callback_set(uart, uart_callback, NULL);
uart_rx_enable(uart, rx_buf, sizeof(rx_buf), 100);
}
extern PumpStateMachine pump;
void led::update() {
        gpio_pin_set_dt(&led_pin,1);
    }
void buzzer :: update(){
        gpio_pin_set_dt(&buzzer_pin,1);
    }
void MotorDriver :: start() {
    motor_running = true;       
}
void MotorDriver::stop(){
    motor_running = false;
    gpio_pin_set_dt(&step,0);
    gpio_pin_set_dt(&dir,0);
}
void sw1_isr(const struct device* dev, struct gpio_callback*cb, uint32_t pins){
    pump.start();
}
void sw2_isr(const struct device* dev, struct gpio_callback*cb, uint32_t pins){
    pump.start();
}
extern commandparser parser;
void uart_callback(const struct device* dev,
                   struct uart_event* evt, void* user_data) {
    if(evt->type == UART_RX_RDY) {
        parser.parse((const char*)(evt->data.rx.buf + evt->data.rx.offset));
    }
}

