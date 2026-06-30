#include "i_uart.hpp"
#include "pump_state_machine.hpp"
#include <cstring>
#include <cstdlib>

#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#endif

// Definitions for extern globals declared in i_uart.hpp
uint8_t rx_buf[64];
char cmd_buf[32];
uint8_t vol = 0;
uint8_t cmd_time = 0;
uint8_t cmd_idx = 0;

extern commandparser parser; // defined in main.cpp

void get_val() {
    static char vol_str[4];
    static char time_str[4];
    uint8_t i = 9; // skip "setrate " (8 chars + space)
    uint8_t j = 0;

    while(cmd_buf[i] != ' ' && cmd_buf[i] != '\0') {
        vol_str[j++] = cmd_buf[i++];
    }
    vol_str[j] = '\0';
    i++;
    j = 0;

    while(cmd_buf[i] != '\n' && cmd_buf[i] != '\r' && cmd_buf[i] != '\0') {
        time_str[j++] = cmd_buf[i++];
    }
    time_str[j] = '\0';

    vol = static_cast<uint8_t>(atoi(vol_str));
    cmd_time = static_cast<uint8_t>(atoi(time_str));
}

float get_data::get_vol_ml() {
    return static_cast<float>(vol);
}

float get_data::get_time_hr() {
    return static_cast<float>(cmd_time);
}

void uart_observer::update(bool active) {
#ifndef UNIT_TEST
    if (active) {
        const char* msg = "OCCLUSION ALARM\n";
        uart_tx(uart_dev, reinterpret_cast<const uint8_t*>(msg), strlen(msg), SYS_FOREVER_US);
    }
#endif
}

#ifndef UNIT_TEST
void uart_callback(const struct device* dev,
                   struct uart_event* evt, void* user_data) {
    if(evt->type == UART_RX_RDY) {
        const uint8_t* data = evt->data.rx.buf + evt->data.rx.offset;
        size_t len = evt->data.rx.len;

        for(size_t i = 0; i < len; i++) {
            char c = static_cast<char>(data[i]);
            if(c == '\n' || c == '\r') {
                cmd_buf[cmd_idx] = '\0';
                parser.process_command(cmd_buf);
                cmd_idx = 0;
            } else {
                cmd_buf[cmd_idx++] = c;
            }
        }
    }
    if(evt->type == UART_RX_BUF_REQUEST) {
        uart_rx_buf_rsp(dev, rx_buf, sizeof(rx_buf));
    }
}
#endif