
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
#include "TestHelpers.h"


using namespace std;
using namespace testing;


TEST(BloomFilter, GetterTests) {
    vector<IHash*> hashs = createHashFunctions();
    map<string, ICommand*> commands = createCommands();
    BloomFilter bloomf(100,hashs,commands);
    int* arrayPtr = bloomf.getArray();
    // check getArray()
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(arrayPtr[i], 0);
    }

    // check getArraySize()
    EXPECT_EQ(bloomf.getArraySize(), 100);


    // check getHashs()
    vector<IHash*> retrievedHashs = bloomf.getHashs();
    checkHashFunctions(hashs, retrievedHashs);


    // check getCommand() - Contains command
    ICommand* actual2 = bloomf.getCommand("2");
    EXPECT_TRUE(compareCommands(commands["2"],  actual2,bloomf)); 

    // check getCommand() - Add command
    ICommand* actual1 = bloomf.getCommand("1");
    EXPECT_TRUE(compareCommands(commands["1"], actual1,bloomf));

}


TEST(BloomFilter,addAndContainsUrl) {
    std::vector<std::string> blacklist;
    vector<IHash*> hashs = createHashFunctions();
    map<string, ICommand*> commands = createCommands();
    BloomFilter bloomf(80,hashs,commands);
    ICommand* addUrl = bloomf.getCommand("1");
    ICommand* containUrl = bloomf.getCommand("2");
    addUrl->execute("www.example.com0",bloomf, blacklist);
    EXPECT_EQ("true true",containUrl->execute("www.example.com0",bloomf, blacklist));
    EXPECT_EQ("false",containUrl->execute("www.example.com1",bloomf, blacklist));
}


TEST(BloomFilter,editHashs) {
    vector<IHash*> hashs = createHashFunctions();
    map<string, ICommand*> commands = createCommands();
    BloomFilter bloomf(80,hashs, commands);
    bloomf.getHashs();

   // Verify the initial set of hash functions
    vector<IHash*> actualHashs = bloomf.getHashs();
    checkHashFunctions(hashs, actualHashs);

    // Add a "new" hash function to the BloomFilter
    IHash* hashNew = new DoubleStdHash(); // h2=hash(hash())   
    bloomf.addHash(hashNew);

   // Verify the updated set of hash functions
    vector<IHash*> updatedHashs = bloomf.getHashs();
    hashs.push_back(hashNew);
    checkHashFunctions(hashs, updatedHashs);
    
    // delete the last hash we added
    bloomf.deleteHashByIndex(hashs.size()-1);

    // Verify that the last hash has been deleted
    vector<IHash*> afterDeletionHashs = bloomf.getHashs();
    hashs.pop_back();
    checkHashFunctions(hashs, afterDeletionHashs);

}

