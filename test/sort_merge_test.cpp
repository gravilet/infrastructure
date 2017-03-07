#include <gtest/gtest.h>
#include <sort_merge.h>

TEST(Fake_Check, FirstElementIsOne) {
    std::vector<int> x;
    x = {7, 9, 2};

    // test 1
    cormen::merge(x, 1, 1, 1);
    EXPECT_EQ(1, x[0]);
}