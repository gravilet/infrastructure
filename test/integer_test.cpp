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

// NOLINT
TEST(Class_integer, Test_operatorEqual) {
    gravilet::integer a(7);
    gravilet::integer b(7);
    gravilet::integer c(8);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a != b);
    /**
     * следующие 4 забракованы travis-ом - предлагает EXPECT_EQ/EXPECT_NE
     * но в таком случае бы пришлось вместо
     * EXPECT_FALSE(8 == a);   и   EXPECT_TRUE(8 != a);
     * использовать одну лишь проверку
     * EXPECT_NE(8, a);
     * и тогда operator!= остался бы не полностью протестирован
     */
    EXPECT_TRUE(7 == a);    // NOLINT
    EXPECT_FALSE(8 == a);   // NOLINT
    EXPECT_TRUE(8 != a);    // NOLINT
    EXPECT_FALSE(7 != a);   // NOLINT
    EXPECT_TRUE(7.0 == a);
    EXPECT_FALSE(8.0 == a);
    EXPECT_TRUE(8.0 != a);
    EXPECT_FALSE(7.0 != a);
    /**
     * следующие 4 забракованы travis-ом - предлагает EXPECT_EQ/EXPECT_NE
     * но я против (см. случай выше)
     */
    EXPECT_TRUE(a == 7);    // NOLINT
    EXPECT_FALSE(a == 8);   // NOLINT
    EXPECT_TRUE(a != 8);    // NOLINT
    EXPECT_FALSE(a != 7);   // NOLINT
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

    // присваивание int-ов и double-ов
    a = 11;
    b = 12.0;
    m = 13.5;
    EXPECT_EQ(11, a);
    EXPECT_EQ(12, b);
    EXPECT_EQ(13, m);

//    int z, z2;
//    z = z2 = a;
//    EXPECT_EQ(11, a);
//    EXPECT_EQ(11, z);
//    EXPECT_EQ(11, z2);
}

TEST(Class_integer, OperatorPlus) {
    gravilet::integer a(7);
    gravilet::integer b(2.0);
    gravilet::integer m;

    b = a + 1;
    int t = a + 1;
    double p = a + 1.5;
    EXPECT_EQ(7, a);
    EXPECT_EQ(8, b);
    EXPECT_EQ(8, t);
    EXPECT_EQ(8.5, p);

    // operator+ / operator+=
    b = 1 + a;
    int t_2 = 1 + a;
    double p_2 = 1.5 + a;
    EXPECT_EQ(7, a);
    EXPECT_EQ(8, b);
    EXPECT_EQ(8, t_2);
    EXPECT_EQ(8.5, p_2);
}

TEST(Class_integer, OperatorMinus) {
    gravilet::integer a(7);
    gravilet::integer b(2.0);
    gravilet::integer m;

    // operator- / operator-=
    b = a - 1;
    int t = a - 1;
    double p = a - 1.5;
    EXPECT_EQ(7, a);
    EXPECT_EQ(6, b);
    EXPECT_EQ(6, t);
    EXPECT_EQ(5.5, p);

    b = 1 - a;
    int t_2 = 1 - a;
    double p_2 = 1.5 - a;
    EXPECT_EQ(7, a);
    EXPECT_EQ(-6, b);
    EXPECT_EQ(-6, t_2);
    EXPECT_EQ(-5.5, p_2);
}
//    a*b
//    a/b




// TEST(Class_integer, Array) {
////    a = arr[i]
//    gravilet::integer i;
//    i = 1;
//    gravilet::integer arr[10] = {gravilet::integer(2), gravilet::integer(3.5)};
//
////    gravilet::integer x = arr[i];
////    int t = arr[i];
////    double p = arr[i];
//}
