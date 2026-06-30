#pragma once
#include <cstdint>

/// @brief Tracks infused volume based on motor steps.
class Volumetracker {
public:
    uint32_t step_count = 0;          ///< Current step count.
    uint16_t steps_per_rev = 51200;   ///< Steps per motor revolution.
    float vol_per_step = 2.0F;        ///< Volume per step in mL.

    /// @brief Updates step count.
    /// @param steps Current step value.
    void update(uint32_t steps);

    /// @brief Returns total infused volume in mL.
    /// @return Volume in mL.
    float getvol() const;

    /// @brief Resets step count to zero.
    void reset();
};