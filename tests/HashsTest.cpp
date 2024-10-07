#include <gtest/gtest.h>
#include <vector>
#include "../src/IHash.h"
#include "../src/Hashs/StdHash.h"
#include "../src/Hashs/DoubleStdHash.h"
#include <string>


using namespace std;

TEST(Hashs,stdHash) {
     string url = "www.example.com0";
    IHash* hash = new StdHash();  
    EXPECT_EQ((*hash)(url), std::hash<string>{}(url));
    delete hash;  
}

TEST(Hashs, DoubleStdHash) {
    string url = "www.example.com0";
    //Manually calculate the expected result based on your DoubleStdHash logic 

    size_t hashResult1 = StdHash()(url);
    string hashInput2 = to_string(hashResult1);
    size_t expectedResult = StdHash()(hashInput2);
    IHash* hash = new DoubleStdHash();
    size_t actualResult = (*hash)(url);

    EXPECT_EQ(expectedResult, actualResult);
    delete hash;
}


