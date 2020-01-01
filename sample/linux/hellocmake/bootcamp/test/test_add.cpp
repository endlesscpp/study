#include "add.h"
#include "gtest/gtest.h"

TEST(AddTest, TwoAndThree) {
    ASSERT_EQ(add(2, 3), 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
