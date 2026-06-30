#pragma once

class PumpStateMachine;

/// @brief Abstract base class for pump states (State pattern).
class pumpState {
public:
    virtual ~pumpState() = default;
    PumpStateMachine* context; ///< Pointer to the state machine context.

    /// @brief Sets the state machine context.
    /// @param obj Pointer to PumpStateMachine.
    void setcontext(PumpStateMachine* obj) { context = obj; }

    virtual void onenter() = 0;    ///< Called on state entry.
    virtual void start() = 0;      ///< Handle start event.
    virtual void stop() = 0;       ///< Handle stop event.
    virtual void pause() = 0;      ///< Handle pause event.
    virtual void occlusion() = 0;  ///< Handle occlusion event.
    virtual void complete() = 0;   ///< Handle complete event.
};

/// @brief Idle state.
class idleState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};

/// @brief Priming state.
class primingState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};

/// @brief Infusing state.
class infusingState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};

/// @brief Pausing state.
class pausingState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};

/// @brief Occlusion alarm state.
class occlusionState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};

/// @brief Complete state.
class completeState : public pumpState {
public:
    void onenter() override;
    void start() override;
    void stop() override;
    void pause() override;
    void occlusion() override;
    void complete() override;
};