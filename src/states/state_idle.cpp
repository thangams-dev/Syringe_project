#include "i_pump_state.hpp"
 #include "pump_state_machine.hpp" 
#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#define LOG(msg) printk("%s",msg)
#else
#define LOG(msg)
#endif
void idleState::onenter()    { LOG("idle state\n"); }
void idleState::start()      { context->setstate(&context->primingstate); LOG("starting prime\n"); }
void idleState::stop()       { LOG("already idle\n"); }
void idleState::pause()      { LOG("not started\n"); }
void idleState::occlusion()  { LOG("occlusion ignored\n"); }
void idleState::complete()   { LOG("not started\n"); }