#include <gtest/gtest.h>
#include <sort_merge.h>

TEST(Fake_Check, FirstElementIsOne) {
    // test 1
    std::vector<int> x_001 = {7, 9, 2};
    std::vector<int> x_001_sorted;
    x_001_sorted = x_001;
    sort(x_001_sorted.begin(), x_001_sorted.end());
    cormen::sort_merge(&x_001);
    EXPECT_EQ(x_001_sorted, x_001);
}
