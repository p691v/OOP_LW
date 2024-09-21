#include <gtest/gtest.h>
#include "../include/divider.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(divider(1,1) == 0);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(divider(3,2) == 7);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(divider(-100,-20) == -1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}