#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "command_parser.hpp"
#include "pump_state_machine.hpp"
#include "i_uart.hpp"

class command_test : public ::testing::Test{
    protected:
    AlarmManager alarm;
    PumpStateMachine pump{alarm};
    commandparser command{&pump};
};

TEST_F(command_test, command_start) {
    command.parse("start");
    EXPECT_EQ(pump.currentState, &pump.primingstate);
}

TEST_F(command_test, command_stop) {
    pump.start();
    pump.start();
    command.parse("stop");
    EXPECT_EQ(pump.currentState, &pump.idlestate);
}

TEST_F(command_test, command_pause) {
    pump.start();
    pump.start();
    command.parse("pause");
    EXPECT_EQ(pump.currentState, &pump.pausingstate);
}

TEST_F(command_test, command_setrate) {
    vol = 50;
    cmd_time = 50;
    command.parse("setrate");
    EXPECT_FLOAT_EQ(pump.motor.delay, 1.0f);
}

TEST_F(command_test, command_unknown_no_state_change) {
    command.parse("invalid");
    EXPECT_EQ(pump.currentState, &pump.idlestate);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}