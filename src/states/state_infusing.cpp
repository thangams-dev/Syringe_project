#include "i_pump_state.hpp"
 #include "pump_state_machine.hpp" 
#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#define LOG(msg) printk("%s",msg)
#else
#define LOG(msg)
#endif

void infusingState::onenter()   { context->motor.start(); LOG("infusing\n"); }
void infusingState::start()     { LOG("already infusing\n"); }
void infusingState::stop()      { context->setstate(&context->idlestate); }
void infusingState::pause()     { context->setstate(&context->pausingstate); }
void infusingState::occlusion() { context->setstate(&context->occlusionstate); }
void infusingState::complete()  { context->setstate(&context->completestate); } 