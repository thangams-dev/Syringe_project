#pragma once

/// @brief Abstract base class for alarm observers.
class AlarmObserver {
public:
    virtual ~AlarmObserver() = default;
    /// @brief Called when alarm state changes.
    /// @param active True if alarm is active, false if cleared.
    virtual void update(bool active) = 0;
};

/// @brief LED alarm observer.
class led : public AlarmObserver {
public:
    void update(bool active) override;
};

/// @brief Buzzer alarm observer.
class buzzer : public AlarmObserver {
public:
    void update(bool active) override;
};