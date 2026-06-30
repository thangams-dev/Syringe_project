#pragma once
#include <cstdint>
#include <array>
#include "i_alarm_observer.hpp"

class AlarmManager {
public:
    static constexpr uint8_t size = 3U;
    std::array<AlarmObserver*, size> indication;
    uint16_t player_count = 0;
    uint16_t noti_count = 0;
    bool alarm_active_ = false; ///< Current alarm state.

    void add(AlarmObserver* observer);
    void notify();

    /// @brief Sets the alarm state and notifies observers.
    void set_active(bool active);
};