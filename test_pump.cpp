
#include <gtest/gtest.h>
#include "pump_state_machine.hpp"
#include "volume_tracker.hpp"
class pumptest : public testing::Test{
    protected:
    AlarmManager alarm;
    PumpStateMachine pump{alarm};
    Volumetracker volume;
    commandparser command{&pump};
};
TEST_F(pumptest, prime_s){
    pump.start();
    EXPECT_EQ(pump.currentState,&pump.primingstate);
}
TEST_F(pumptest, infus_s){
    pump.start();
    pump.start();
    EXPECT_EQ(pump.currentState,&pump.infusingstate);
}
TEST_F(pumptest, pause_s){
    pump.start();
    pump.start();
    pump.pause();
    EXPECT_EQ(pump.currentState,&pump.pausingstate);
}
TEST_F(pumptest, idle_s){
    pump.start();
    pump.start();
    pump.occlusion();
    pump.stop();
    EXPECT_EQ(pump.currentState,&pump.idlestate);
}
TEST_F(pumptest, volume_track_2ml){
    volume.update(51200);
    EXPECT_FLOAT_EQ(volume.getvol(),2.0f);
}
TEST_F(pumptest, volume_track_1ml){
    volume.update(25600);
    EXPECT_FLOAT_EQ(volume.getvol(),1.0f);
}
TEST_F(pumptest, alam_count){
    led l;
    buzzer b;
    alarm.add(&l);
    alarm.add(&b);
    alarm.notify();
    EXPECT_EQ(alarm.noti_count,1);
}
TEST_F(pumptest, command_start){
    command.parse("start");
    EXPECT_EQ(pump.currentState, &pump.primingstate);
}
TEST_F(pumptest, command_stop){
    pump.start();
    pump.start();
    command.parse("stop");
    EXPECT_EQ(pump.currentState, &pump.idlestate);
}
TEST_F(pumptest, command_pause){
    pump.start();
    pump.start();
    command.parse("pause");
    EXPECT_EQ(pump.currentState, &pump.pausingstate);
}
TEST_F(pumptest, command_set_rate){
    command.parse("setrate");
 EXPECT_NEAR(pump.motor.delay, 140.625f, 0.01f);  // allow 0.01 tolerance
}
TEST_F(pumptest, wrongcmd){
    command.parse("wer");
    EXPECT_EQ(pump.currentState, &pump.idlestate);
}
int main(int argc, char** argv) {   
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}