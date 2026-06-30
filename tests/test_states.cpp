#include <gtest/gtest.h>
#include "pump_state_machine.hpp"

class pump_state_test : public ::testing::Test {
protected:
    AlarmManager alarm;
    PumpStateMachine pump{alarm};
};

// ─── Initial State ────────────────────────────────────
TEST_F(pump_state_test, initial_state_is_idle) {
    EXPECT_EQ(pump.currentState, &pump.idlestate);
}

// ─── Idle ─────────────────────────────────────────────
TEST_F(pump_state_test, idle_start_goes_priming)    { pump.start();      EXPECT_EQ(pump.currentState, &pump.primingstate); }
TEST_F(pump_state_test, idle_stop_ignored)          { pump.stop();       EXPECT_EQ(pump.currentState, &pump.idlestate); }
TEST_F(pump_state_test, idle_pause_ignored)         { pump.pause();      EXPECT_EQ(pump.currentState, &pump.idlestate); }
TEST_F(pump_state_test, idle_occlusion_ignored)     { pump.occlusion();  EXPECT_EQ(pump.currentState, &pump.idlestate); }
TEST_F(pump_state_test, idle_complete_ignored)      { pump.complete();   EXPECT_EQ(pump.currentState, &pump.idlestate); }

// ─── Priming ──────────────────────────────────────────
TEST_F(pump_state_test, priming_start_goes_infusing)      { pump.start(); pump.start();      EXPECT_EQ(pump.currentState, &pump.infusingstate); }
TEST_F(pump_state_test, priming_stop_goes_idle)           { pump.start(); pump.stop();       EXPECT_EQ(pump.currentState, &pump.idlestate); }
TEST_F(pump_state_test, priming_pause_ignored)            { pump.start(); pump.pause();      EXPECT_EQ(pump.currentState, &pump.primingstate); }
TEST_F(pump_state_test, priming_occlusion_goes_occlusion) { pump.start(); pump.occlusion();  EXPECT_EQ(pump.currentState, &pump.occlusionstate); }
TEST_F(pump_state_test, priming_complete_ignored)         { pump.start(); pump.complete();   EXPECT_EQ(pump.currentState, &pump.primingstate); }

// ─── Infusing ─────────────────────────────────────────
TEST_F(pump_state_test, infusing_start_ignored)          { pump.start(); pump.start(); pump.start();      EXPECT_EQ(pump.currentState, &pump.infusingstate); }
TEST_F(pump_state_test, infusing_stop_goes_idle)         { pump.start(); pump.start(); pump.stop();       EXPECT_EQ(pump.currentState, &pump.idlestate); }
TEST_F(pump_state_test, infusing_pause_goes_pausing)     { pump.start(); pump.start(); pump.pause();      EXPECT_EQ(pump.currentState, &pump.pausingstate); }
TEST_F(pump_state_test, infusing_occlusion_goes_occlusion){ pump.start(); pump.start(); pump.occlusion(); EXPECT_EQ(pump.currentState, &pump.occlusionstate); }
TEST_F(pump_state_test, infusing_complete_goes_complete) { pump.start(); pump.start(); pump.complete();   EXPECT_EQ(pump.currentState, &pump.completestate); }

// ─── Pausing ──────────────────────────────────────────
TEST_F(pump_state_test, pausing_start_goes_infusing)  { pump.start(); pump.start(); pump.pause(); pump.start();     EXPECT_EQ(pump.currentState, &pump.infusingstate); }
TEST_F(pump_state_test, pausing_stop_goes_idle)       { pump.start(); pump.start(); pump.pause(); pump.stop();      EXPECT_EQ(pump.currentState, &pump.idlestate); }
TEST_F(pump_state_test, pausing_pause_ignored)        { pump.start(); pump.start(); pump.pause(); pump.pause();     EXPECT_EQ(pump.currentState, &pump.pausingstate); }
TEST_F(pump_state_test, pausing_occlusion_ignored)    { pump.start(); pump.start(); pump.pause(); pump.occlusion(); EXPECT_EQ(pump.currentState, &pump.pausingstate); }
TEST_F(pump_state_test, pausing_complete_ignored)     { pump.start(); pump.start(); pump.pause(); pump.complete();  EXPECT_EQ(pump.currentState, &pump.pausingstate); }

// ─── Occlusion ────────────────────────────────────────
TEST_F(pump_state_test, occlusion_stop_goes_idle)       { pump.start(); pump.start(); pump.occlusion(); pump.stop();      EXPECT_EQ(pump.currentState, &pump.idlestate); }
TEST_F(pump_state_test, occlusion_start_ignored)        { pump.start(); pump.start(); pump.occlusion(); pump.start();     EXPECT_EQ(pump.currentState, &pump.occlusionstate); }
TEST_F(pump_state_test, occlusion_pause_ignored)        { pump.start(); pump.start(); pump.occlusion(); pump.pause();     EXPECT_EQ(pump.currentState, &pump.occlusionstate); }
TEST_F(pump_state_test, occlusion_occlusion_ignored)    { pump.start(); pump.start(); pump.occlusion(); pump.occlusion(); EXPECT_EQ(pump.currentState, &pump.occlusionstate); }
TEST_F(pump_state_test, occlusion_complete_ignored)     { pump.start(); pump.start(); pump.occlusion(); pump.complete();  EXPECT_EQ(pump.currentState, &pump.occlusionstate); }

// ─── Complete ─────────────────────────────────────────
TEST_F(pump_state_test, complete_start_goes_priming)    { pump.start(); pump.start(); pump.complete(); pump.start();     EXPECT_EQ(pump.currentState, &pump.primingstate); }
TEST_F(pump_state_test, complete_stop_ignored)          { pump.start(); pump.start(); pump.complete(); pump.stop();      EXPECT_EQ(pump.currentState, &pump.completestate); }
TEST_F(pump_state_test, complete_pause_ignored)         { pump.start(); pump.start(); pump.complete(); pump.pause();     EXPECT_EQ(pump.currentState, &pump.completestate); }
TEST_F(pump_state_test, complete_occlusion_ignored)     { pump.start(); pump.start(); pump.complete(); pump.occlusion(); EXPECT_EQ(pump.currentState, &pump.completestate); }
TEST_F(pump_state_test, complete_complete_ignored)      { pump.start(); pump.start(); pump.complete(); pump.complete();  EXPECT_EQ(pump.currentState, &pump.completestate); }

// ─── Setrate ──────────────────────────────────────────
TEST_F(pump_state_test, setrate_sets_motor_delay) {
    pump.setrate(1.0f);
    EXPECT_FLOAT_EQ(pump.motor.delay, 1.0f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}