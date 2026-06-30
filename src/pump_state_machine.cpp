
#include "pump_state_machine.hpp"
    void PumpStateMachine::setstate(pumpState* newState){
        currentState =  newState;
        currentState->setcontext(this);
        currentState->onenter();
    }
    void PumpStateMachine::stop()const{
        currentState->stop();
    }
    void PumpStateMachine::pause()const{
        currentState->pause();
    }
    void PumpStateMachine::occlusion()const{
        currentState->occlusion();
    }
    void PumpStateMachine::start()const{
        currentState->start();
    }
    void PumpStateMachine::complete()const{
        currentState->complete();
    }
    void PumpStateMachine::setrate(float ml_per_hour){
        motor.Setrate(ml_per_hour);
    }