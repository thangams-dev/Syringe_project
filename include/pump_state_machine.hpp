#pragma once
#include "alarm_manager.hpp"
#include "i_pump_state.hpp"
#include "i_stepper_driver.hpp"

/// @brief Manages pump states using the State pattern.
class PumpStateMachine {
public:
    pumpState* currentState; ///< Active state.
    MotorDriver motor;       ///< Motor driver instance.
    AlarmManager& alarmmanager; ///< Reference to alarm manager.

    idleState idlestate;
    primingState primingstate;
    pausingState pausingstate;
    completeState completestate;
    occlusionState occlusionstate;
    infusingState infusingstate;

    explicit PumpStateMachine(AlarmManager& alarm) : alarmmanager(alarm) {
        currentState = &idlestate;
        currentState->setcontext(this);
    }

    void setstate(pumpState* newState);
    void stop() const;
    void pause() const;
    void occlusion() const;
    void start() const;
    void complete() const;

    /// @brief Sets infusion rate.
    /// @param ml_per_hour Flow rate in mL/hr.
    void setrate(float ml_per_hour);
};