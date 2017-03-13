#include <gtest/gtest.h>
#include <hash.h>

TEST(OpenAddressingHash, CheckDuplicate) {
    gravilet::OpenAddressingHash a;
    a.insert("aaa", "Alice");
    a.insert("aaa", "Berta");

    // check correct overwriting the value
    EXPECT_EQ("Berta", a.find("aaa"));
    // check that number of elements dont changet after overwriting
    EXPECT_EQ(1, a.size());
}

TEST(OpenAddressingHash, CheckOverrateSizeOfCollection) {   // if still 'hash_function_divisor = 26'
    gravilet::OpenAddressingHash a(10); // 10 < hash_function_divisor
    a.insert("aaa", "Alice1");
    a.insert("bbb", "Berta");
    a.insert("kkk", "Alice2");  // 'a' + 10 == 'k'
    a.insert("kkk", "Alice3");
    a.insert("aaa", "Alice4");

    EXPECT_EQ("Alice4", a.find("aaa"));
    EXPECT_EQ("Berta", a.find("bbb"));
    EXPECT_EQ("Alice3", a.find("kkk"));
    EXPECT_EQ(3, a.size());
}
