#include <gtest/gtest.h>
#include <hash.h>

TEST(OpenAddressingHash, CheckDuplicate) {
    gravilet::OpenAddressingHash a;
    a.insert("20", "aaa");
    a.insert("20", "bbb");

    EXPECT_EQ("bbb", a.find("20"));
    EXPECT_EQ(1, a.size());
}