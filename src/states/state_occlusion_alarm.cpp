#include "i_pump_state.hpp"
#include "pump_state_machine.hpp"
#ifndef UNIT_TEST
#include <zephyr/kernel.h>
#define LOG(msg) printk("%s",msg)
#else
#define LOG(msg)
#endif
void occlusionState::onenter()   { context->motor.stop(); context->alarmmanager.notify(); LOG("occlusion!\n"); }
void occlusionState::start() { LOG("resolve occlusion first"); }
void occlusionState::stop()      { context->setstate(&context->idlestate); }
void occlusionState::pause()     { LOG("in fault state\n"); }
void occlusionState::occlusion() { LOG("already in occlusion\n"); }
void occlusionState::complete()  { LOG("already in occlusion\n"); }