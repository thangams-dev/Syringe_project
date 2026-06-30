#pragma once
#include <cstdint>
#include "i_alarm_observer.hpp"
#include "command_parser.hpp"

#ifndef UNIT_TEST
#include <zephyr/drivers/uart.h>
#endif

/// @brief UART alarm observer — sends alarm notification over UART.
class uart_observer : public AlarmObserver {
public:
    explicit uart_observer(commandparser* parser) : cmd(parser) {}
    void update(bool active) override;

private:
    commandparser* cmd;
};

extern uint8_t rx_buf[64];
extern char cmd_buf[32];
extern uint8_t vol;
extern uint8_t cmd_time;
extern uint8_t cmd_idx;

void get_val();

#ifndef UNIT_TEST
extern const struct device* uart_dev;

void uart_callback(const struct device* dev,
                   struct uart_event* evt, void* user_data);
#endif