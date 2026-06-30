#include "i_pump_state.hpp"
 #include "pump_state_machine.hpp" 
#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#define LOG(msg) printk("%s",msg)
#else
#define LOG(msg)
#endif
void pausingState::onenter()   { context->motor.stop(); LOG("paused\n"); }
void pausingState::start()     { context->setstate(&context->infusingstate); }
void pausingState::stop()      { context->setstate(&context->idlestate); }
void pausingState::pause()     { LOG("already paused\n"); }
void pausingState::occlusion() { LOG("occlusion while paused\n"); }
void pausingState::complete()  { LOG("Not able to do that\n"); }