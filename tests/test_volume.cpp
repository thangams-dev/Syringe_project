
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "volume_tracker.hpp"
class volume_test : public ::testing::Test{
    protected:
        Volumetracker volume;
};
TEST_F(volume_test, volume_zero_steps) {
    volume.update(0);
    EXPECT_FLOAT_EQ(volume.getvol(), 0.0f);
}

TEST_F(volume_test, volume_one_rev_equals_2ml) {
    volume.update(51200);
    EXPECT_FLOAT_EQ(volume.getvol(), 2.0f);
}

TEST_F(volume_test, volume_half_rev_equals_1ml) {
    volume.update(25600);
    EXPECT_FLOAT_EQ(volume.getvol(), 1.0f);
}

TEST_F(volume_test, volume_reset_clears) {
    volume.update(51200);
    volume.reset();
    EXPECT_FLOAT_EQ(volume.getvol(), 0.0f);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}