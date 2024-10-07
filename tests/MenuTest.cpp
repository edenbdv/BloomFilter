#include "Menu.h"
#include "gtest/gtest.h"
#include <sstream>

// Test Menu setURL and getUrl methods
TEST(MenuTest, SetAndGetUrlTest) {
    Menu m;
    m.setURL("www.example.com");
    EXPECT_EQ(m.getUrl(), "www.example.com");
}

// Test Menu setTask and getTask methods
TEST(MenuTest, SetAndGetTaskTest) {
    Menu m;
    m.setTask("1");
    EXPECT_EQ(m.getTask(), "1");
}

// Test Menu splitInput method
TEST(MenuTest, SplitInputTest) {
    Menu m;
    std::string input = "1 www.example.com";
    std::vector<std::string> result = m.splitInput(input);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "1");
    EXPECT_EQ(result[1], "www.example.com");
}

// Test Menu validateInput method for valid input
TEST(MenuTest, ValidateInputValidTest) {
    Menu m;
    std::vector<std::string> input = {"1", "www.example.com"};
    EXPECT_TRUE(m.validateInput(input));
}

// Test Menu validateInput method for invalid input
TEST(MenuTest, ValidateInputInvalidTest) {
    Menu m;
    std::vector<std::string> input1 = {"1"}; // Missing URL
    std::vector<std::string> input2 = {"1", "www.example.com", "extra"}; // Too many arguments
    std::vector<std::string> input3 = {"3", "www.example.com"}; // Invalid task
    EXPECT_FALSE(m.validateInput(input1));
    EXPECT_FALSE(m.validateInput(input2));
    EXPECT_FALSE(m.validateInput(input3));
}
