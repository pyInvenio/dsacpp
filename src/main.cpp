#include <gtest/gtest.h>
#include "../include/datastructures/map.h" 

class MapTest : public ::testing::Test {
protected:
    Map<int, std::string> intStringMap;
    Map<std::string, int> stringIntMap;
};

TEST_F(MapTest, AddAndFind) {
    intStringMap.add(1, "one");
    EXPECT_TRUE(intStringMap.find(1));
    EXPECT_FALSE(intStringMap.find(2));
}

TEST_F(MapTest, AddAndGet) {
    intStringMap.add(1, "one");
    EXPECT_EQ("one", *intStringMap.get(1));
    EXPECT_EQ(nullptr, intStringMap.get(2));
}

TEST_F(MapTest, AddDuplicate) {
    intStringMap.add(1, "one");
    EXPECT_THROW(intStringMap.add(1, "uno"), std::runtime_error);
}

TEST_F(MapTest, SetExisting) {
    intStringMap.add(1, "one");
    intStringMap.set(1, "uno");
    EXPECT_EQ("uno", *intStringMap.get(1));
}

TEST_F(MapTest, SetNonExisting) {
    intStringMap.set(1, "one");
    EXPECT_EQ("one", *intStringMap.get(1));
}

TEST_F(MapTest, Remove) {
    intStringMap.add(1, "one");
    intStringMap.remove(1);
    EXPECT_FALSE(intStringMap.find(1));
}

TEST_F(MapTest, Expansion) {
    for (int i = 0; i < 10; ++i) {
        intStringMap.add(i, std::to_string(i));
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(intStringMap.find(i));
        EXPECT_EQ(std::to_string(i), *intStringMap.get(i));
    }
}

TEST_F(MapTest, MoveSemantics) {
    std::string longString = "This is a long string to test move semantics";
    stringIntMap.add(std::move(longString), 1);
    EXPECT_TRUE(stringIntMap.find("This is a long string to test move semantics"));
    EXPECT_TRUE(longString.empty()); // The string should have been moved
}

TEST_F(MapTest, GetKeysAndValues) {
    intStringMap.add(1, "one");
    intStringMap.add(2, "two");
    
    const int* keys = intStringMap.getKeys();
    const std::string* values = intStringMap.getValues();
    
    // Note: This test assumes a specific order, which might not always be guaranteed
    // in a hash-based data structure. Adjust as necessary.
    EXPECT_TRUE((keys[0] == 1 && keys[1] == 2) || (keys[0] == 2 && keys[1] == 1));
    EXPECT_TRUE((values[0] == "one" && values[1] == "two") || (values[0] == "two" && values[1] == "one"));
}

int main(int argc, char **argv) {
  
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}