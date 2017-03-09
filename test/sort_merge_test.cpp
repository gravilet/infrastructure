#include <gtest/gtest.h>
#include <sort_merge.h>

//TEST(Sort_Merge, Simple_Check) {
//    // test 1
//    std::vector<int> x_001 = {7, 9, 2};
//    cormen::sort_merge(&x_001);
//    EXPECT_EQ(std::vector<int>({2, 7, 9}), x_001);
//}

TEST(Sort_Merge, Simple_Check_001) {
    std::vector<int> x_001 = {7, 9, 2};
    std::vector<int> x_001_expected = x_001;
    sort(x_001_expected.begin(), x_001_expected.end());

    cormen::sort_merge(&x_001);
    EXPECT_EQ(x_001_expected, x_001);
}

TEST(Sort_Merge, Simple_Check_002_odd) {
    std::vector<int> x_001 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> x_001_expected = x_001;
    sort(x_001_expected.begin(), x_001_expected.end());

    cormen::sort_merge(&x_001);
    EXPECT_EQ(x_001_expected, x_001);
}

TEST(Sort_Merge, Simple_Check_002_even) {
    std::vector<int> x_001 = {9, 8, 7, 6, 5, 4, 3, 2, 1, -8};
    std::vector<int> x_001_expected = x_001;
    sort(x_001_expected.begin(), x_001_expected.end());

    cormen::sort_merge(&x_001);
    EXPECT_EQ(x_001_expected, x_001);
}

TEST(Sort_Merge, Simple_Check_003_pow2) {
    std::vector<int> x_001 = {9, 8, 7, 6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, 0, 0};
    std::vector<int> x_001_expected = x_001;
    sort(x_001_expected.begin(), x_001_expected.end());

    cormen::sort_merge(&x_001);
    EXPECT_EQ(x_001_expected, x_001);
}