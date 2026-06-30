#include "volume_tracker.hpp"
    auto Volumetracker::update(uint32_t steps) -> void {
        step_count = steps;
    }           
    auto Volumetracker::getvol() const ->float{
        return static_cast<float>(step_count) * (vol_per_step / static_cast<float>(steps_per_rev));
    }
    void Volumetracker::reset(){
        step_count = 0;
    }