#include <gtest/gtest.h>
#include <hash.h>

TEST(OpenAddressingHash, CheckDuplicate) {
    gravilet::OpenAddressingHash<std::string, std::string> a;
    a.insert("aaa", "Alice");
    a.insert("aaa", "Berta");

    // check correct overwriting the value
    EXPECT_EQ("Berta", *a.find("aaa"));
    // check that number of elements dont changet after overwriting
    EXPECT_EQ(1, a.size());
}

TEST(OpenAddressingHash, CheckDuplicate_Improved) {
    // Improved - becauseby default we use only 1st letter for hash-function
    // and we must check that 'aaa' 'abb' are still different keys
    gravilet::OpenAddressingHash<std::string, std::string> a;
    a.insert("aaa", "Alice");
    a.insert("abb", "Berta");

    EXPECT_EQ("Alice", *a.find("aaa"));
    EXPECT_EQ("Berta", *a.find("abb"));
    EXPECT_EQ(2, a.size());
}

TEST(OpenAddressingHash, CheckOverrateSizeOfCollection) {   // if still 'hash_function_divisor = 26'
    gravilet::OpenAddressingHash<std::string, std::string> a(10);     // 10 < hash_function_divisor
    a.insert("aaa", "Alice1");
    a.insert("bbb", "Berta");
    a.insert("kkk", "Alice2");      // 'a' + 10 == 'k'
    a.insert("kkk", "Alice3");
    a.insert("aaa", "Alice4");

    EXPECT_EQ("Alice4", *a.find("aaa"));
    EXPECT_EQ("Berta", *a.find("bbb"));
    EXPECT_EQ("Alice3", *a.find("kkk"));
    EXPECT_EQ(3, a.size());
}

TEST(OpenAddressingHash, CheckNotFound) {
    gravilet::OpenAddressingHash<std::string, std::string> a;
    a.insert("aaa", "Alice");
    a.insert("aaa", "Berta");

    EXPECT_EQ("Berta", *a.find("aaa"));
    EXPECT_EQ(1, a.size());

    EXPECT_EQ(nullptr, a.find("bbb"));  // == not found
}

TEST(OpenAddressingHash, CheckOperator) {
    gravilet::OpenAddressingHash<std::string, std::string> a;
    a.insert("aaa", "Alice");
    a.insert("aaa", "Berta");

    EXPECT_EQ("Berta", a["aaa"]);
    EXPECT_EQ(1, a.size());

    EXPECT_EQ("", a["bbb"]);  // == not found
}

//////////////////////////////////////////////////////////////////
////////    custom function
//////////////////////////////////////////////////////////////////
int blah_blah(std::string key, int size) {
    std::cout << "STRING BLAH" << std::endl;
    return key.size() % size;
}

int blah_blah(int key, int size) {
    std::cout << "INT BLAH" << std::endl;
    return key ^ size;
}

TEST(OpenAddressingHash, CheckDuplicate_WithCustomFunctions) {
    gravilet::OpenAddressingHash<std::string, std::string> a(10, 1, blah_blah);
    a.insert("aaa", "Alice");
    a.insert("aaa", "Berta");

    // check correct overwriting the value
    EXPECT_EQ("Berta", *a.find("aaa"));
    // check that number of elements dont changet after overwriting
    EXPECT_EQ(1, a.size());

    gravilet::OpenAddressingHash<int, std::string> b(10, 1, blah_blah);
    b.insert(17, "Alice");
    b.insert(17, "Berta");

    // check correct overwriting the value
    EXPECT_EQ("Berta", *b.find(17));
    // check that number of elements dont changet after overwriting
    EXPECT_EQ(1, b.size());
}

//////////////////////////////////////////////////////////////////
////////    functor
//////////////////////////////////////////////////////////////////
class FunctorCesar {
    int offset;
 public:
    explicit FunctorCesar(int off) : offset(off) {}
    int operator()(const int& e, int size) {
        return (e + offset) % size;
    }
    int operator()(const std::string& e, int size) {
        return (e.size() + offset) % size;
    }
};

TEST(OpenAddressingHash, CheckDuplicate_WithFunctor) {
    gravilet::OpenAddressingHash<std::string, std::string> a(10,
                                                             1,
                                                             FunctorCesar(7));
    a.insert("aaa", "Alice");
    a.insert("aaa", "Berta");

    // check correct overwriting the value
    EXPECT_EQ("Berta", *a.find("aaa"));
    // check that number of elements dont changet after overwriting
    EXPECT_EQ(1, a.size());

    gravilet::OpenAddressingHash<int, std::string> b(10, 1, blah_blah);
    b.insert(17, "Alice");
    b.insert(17, "Berta");

    // check correct overwriting the value
    EXPECT_EQ("Berta", *b.find(17));
    // check that number of elements dont changet after overwriting
    EXPECT_EQ(1, b.size());
}
