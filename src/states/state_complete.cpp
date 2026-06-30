#include "i_pump_state.hpp"
#include "pump_state_machine.hpp"  
#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#define LOG(msg) printk("%s",msg)
#else
#define LOG(msg)
#endif
void completeState::onenter()   { context->motor.stop(); LOG("complete!"); }
void completeState::start() { context->setstate(&context->primingstate); }
void completeState::stop()      { LOG("already complete"); }
void completeState::pause()     { LOG("already complete"); }
void completeState::occlusion() { LOG("already complete"); }
void completeState::complete()  { LOG("already complete"); }