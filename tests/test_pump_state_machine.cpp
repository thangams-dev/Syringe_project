#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "pump_state_machine.hpp"
#include "i_pump_state.hpp"
class pump_state_machine_test : public ::testing::Test{
    protected:
    AlarmManager alarm;
    PumpStateMachine pump{alarm};
};
TEST_F(pump_state_machine_test,initialstate_as_idle){
    EXPECT_EQ(pump.currentState,&pump.idlestate);
}
TEST_F(pump_state_machine_test, start_goes_to_priming) {
    pump.start();
    EXPECT_EQ(pump.currentState, &pump.primingstate);
}

TEST_F(pump_state_machine_test, priming_start_goes_to_infusing) {
    pump.start();  // idle → priming
    pump.start();  // priming → infusing
    EXPECT_EQ(pump.currentState, &pump.infusingstate);
}

TEST_F(pump_state_machine_test, infusing_pause_goes_to_pausing) {
    pump.start();
    pump.start();
    pump.pause();
    EXPECT_EQ(pump.currentState, &pump.pausingstate);
}

TEST_F(pump_state_machine_test, infusing_occlusion_goes_to_occlusion) {
    pump.start();
    pump.start();
    pump.occlusion();
    EXPECT_EQ(pump.currentState, &pump.occlusionstate);
}

TEST_F(pump_state_machine_test, infusing_complete_goes_to_complete) {
    pump.start();
    pump.start();
    pump.complete();
    EXPECT_EQ(pump.currentState, &pump.completestate);
}

TEST_F(pump_state_machine_test, pausing_start_goes_to_infusing) {
    pump.start();
    pump.start();
    pump.pause();
    pump.start();
    EXPECT_EQ(pump.currentState, &pump.infusingstate);
}

TEST_F(pump_state_machine_test, pausing_stop_goes_to_idle) {
    pump.start();
    pump.start();
    pump.pause();
    pump.stop();
    EXPECT_EQ(pump.currentState, &pump.idlestate);
}

TEST_F(pump_state_machine_test, occlusion_stop_goes_to_idle) {
    pump.start();
    pump.start();
    pump.occlusion();
    pump.stop();
    EXPECT_EQ(pump.currentState, &pump.idlestate);
}

TEST_F(pump_state_machine_test, complete_start_goes_to_priming) {
    pump.start();
    pump.start();
    pump.complete();
    pump.start();
    EXPECT_EQ(pump.currentState, &pump.primingstate);
}

TEST_F(pump_state_machine_test, setrate_sets_motor_delay) {
    pump.setrate(1.0f);
    EXPECT_FLOAT_EQ(pump.motor.delay, 1.0f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}