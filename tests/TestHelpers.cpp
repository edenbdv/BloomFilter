
#include "TestHelpers.h"
#include <gtest/gtest.h>
#include "../src/BloomFilter.h" 
#include <string>
#include <vector>
#include "../src/Hashs/StdHash.h"
#include "../src/Hashs/DoubleStdHash.h"
#include "../src/Commands/AddUrlCommand.h"
#include "../src/Commands/ContainsUrlCommand.h" 
#include "../src/IHash.h"
#include "../src/ICommand.h"

// helper functions for tests: 

 // Helper function create dynamic array of hashs (corrently with 2 fucntions)
  vector<IHash*> createHashFunctions() {
    vector<IHash*> hashs;
    hashs.push_back(new StdHash());
    hashs.push_back(new DoubleStdHash());
    return hashs;
}

// Helper function to create map of commands
std::map<string, ICommand*> createCommands() {
    std::map<string, ICommand*> commands;
    ICommand* add = new AddUrlCommand();
    commands["1"] = add;
    ICommand* contains = new ContainsUrlCommand();
    commands["2"] = contains;

    return commands;

}

// Helper function to check if two vectors of hash functions are equal
void checkHashFunctions(const  vector<IHash*>& expected,
                        const  vector<IHash*>& actual) {
    EXPECT_EQ(expected.size(), actual.size()); // Check size
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(expected[i]->operator()("test"), actual[i]->operator()("test")); // Check content
    }
}

// Helper function to compare ICommand objects based on behavior
bool compareCommands(const ICommand* expected, const ICommand* actual,BloomFilter& bloomf) {
    const std::string testUrl = "test_url";
    std::vector<std::string> blacklist;
    std::string expectedResult = expected->execute(testUrl, bloomf, blacklist);
    std::string actualResult = actual->execute(testUrl, bloomf, blacklist);
    
    return expectedResult == actualResult;
    // 1(add) : both should return true
    // 2(contains): both should return false
}

