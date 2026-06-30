#include "i_alarm_observer.hpp"
#include "i_stepper_driver.hpp"

void led::update(){}

void buzzer::update(){}

void uart_observer::update() {}

void MotorDriver::start(){
    motor_running = true;
}
void MotorDriver::stop(){
    motor_running = false;
}
void MotorDriver::reset(){
    step_count_ = 0;
}
uint32_t MotorDriver::getsteps(){
    return step_count_;
}
void MotorDriver::Setrate(float ml){
    delay = ml;
}