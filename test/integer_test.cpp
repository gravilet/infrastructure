#include <gtest/gtest.h>
#include <integer.h>

/**
 * intresting trick :
 * std::ostringstream os;
 * MyObject a;
 * ... do something with a ...
 * os << a;     // must have "MyObject::operator<<"
 * EXPECT_EQ("...", os.str());
 */

TEST(Class_integer, Test_operatorEqual) {
    gravilet::integer a(7);
    gravilet::integer b(7);
    gravilet::integer c(8);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(7 == a);
    EXPECT_FALSE(8 == a);
    EXPECT_TRUE(8 != a);
    EXPECT_FALSE(7 != a);
    EXPECT_TRUE(7.0 == a);
    EXPECT_FALSE(8.0 == a);
    EXPECT_TRUE(8.0 != a);
    EXPECT_FALSE(7.0 != a);
    EXPECT_TRUE(a == 7);
    EXPECT_FALSE(a == 8);
    EXPECT_TRUE(a != 8);
    EXPECT_FALSE(a != 7);
    EXPECT_TRUE(a == 7.0);
    EXPECT_FALSE(a == 8.0);
    EXPECT_TRUE(a != 8.0);
    EXPECT_FALSE(a != 7.0);
}

TEST(Class_integer, CommonTests) {
    gravilet::integer a(7);
    gravilet::integer b(2.0);
    gravilet::integer m;

    m = a + b;
    EXPECT_EQ(9, m);
    EXPECT_EQ(7, a);
    EXPECT_EQ(2, b);
}
