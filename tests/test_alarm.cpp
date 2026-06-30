#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "alarm_manager.hpp"
#include "i_uart.hpp"

class pumptest : public ::testing::Test {
protected:
    AlarmManager alarm;
};
TEST_F(pumptest, alarm_add_one_notify) {
    led l;
    alarm.add(&l);
    alarm.notify();
    EXPECT_EQ(alarm.noti_count, 1);
}

TEST_F(pumptest, alarm_add_two_notify) {
    led l;
    buzzer b;
    uart_observer u(nullptr);
    alarm.add(&l);
    alarm.add(&b);
    alarm.add(&u);
    alarm.notify();
    EXPECT_EQ(alarm.noti_count, 1);
    EXPECT_EQ(alarm.player_count, 3);
}

TEST_F(pumptest, alarm_notify_twice) {
    led l;
    alarm.add(&l);
    alarm.notify();
    alarm.notify();
    EXPECT_EQ(alarm.noti_count, 2);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}