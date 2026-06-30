#pragma once

class PumpStateMachine; // forward declaration only — don't also #include pump_state_machine.hpp here (circular include risk)

/// @brief Holds parsed user input (volume, time) from UART commands.
class get_data {
public:
    float get_vol_ml();
    float get_time_hr();
};

/// @brief Parses UART commands and dispatches to PumpStateMachine.
class commandparser {
    PumpStateMachine* Motor; ///< Pointer to the pump state machine.
    get_data geta;

public:
    /// @brief Constructor.
    /// @param p Pointer to PumpStateMachine.
    explicit commandparser(PumpStateMachine* p) : Motor(p) {}

    /// @brief Parses a command string and triggers pump action.
    /// @param word Null-terminated command string.
    void process_command(const char* word);

    /// @brief Alias used by tests.
    void parse(const char* word) { process_command(word); }
};