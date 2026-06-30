#include "i_pump_state.hpp"
#include "pump_state_machine.hpp" 
#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#define LOG(msg) printk("%s",msg)
#else
#define LOG(msg)
#endif
void primingState::onenter()   { context->motor.start();LOG("priming\n"); }
void primingState::start()     { context->setstate(&context->infusingstate); }
void primingState::stop()      { context->setstate(&context->idlestate); LOG("stopped\n"); }
void primingState::pause()     { LOG("cannot pause priming\n"); }
void primingState::occlusion() { context->setstate(&context->occlusionstate); }
void primingState::complete()  { context->motor.stop(); }