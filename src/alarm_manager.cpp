#include "alarm_manager.hpp"

void AlarmManager::add(AlarmObserver* observer) {
    indication[player_count] = observer;
    player_count++;
}

void AlarmManager::notify() {
    for (uint16_t i = 0; i < player_count; i++) {
        indication[i]->update(alarm_active_);
    }
    noti_count++;
}

void AlarmManager::set_active(bool active) {
    alarm_active_ = active;
    notify();
}