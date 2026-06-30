#pragma once
#include <cstdint>
#include <atomic>
#include "i_gpio.hpp"

/// @brief Controls stepper motor hardware.
class MotorDriver {
public:
    static constexpr uint32_t kStepsPerRev = 51200U;

    std::atomic<uint32_t> step_count_{0};  ///< Current step count (atomic, shared across ISR/thread).
    std::atomic<uint32_t> delay{0};  ///< Step delay in microseconds (shared across ISR/thread).
    float rpm = 0.0F;
    bool motor_running = false;

    void start();
    void Setrate(float ml_per_hr);
    void stop();
    void reset();
    uint32_t getsteps();
};