
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

TEST(Input,exmaple1) {
   /* input example: 
    8 1 2
    2 www.example.com0
    false
    1 www.example.com0
    2 www.example.com0
    true true
    2 www.example.com1
    false
    2 www.example.com11
    true false
    */
    vector<IHash*> hashs;
    hashs.push_back(new StdHash()); //insert the first hash
    hashs.push_back(new DoubleStdHash()); //insert the first hash

    map<string, ICommand*> commands = createCommands(); 
    BloomFilter bloomf(8,hashs, commands);
    std::vector<std::string> blacklist;
    // 2 www.example.com0
    EXPECT_EQ("false",bloomf.getCommand("2")->execute("www.example.com0",bloomf, blacklist)); //false

    //1 www.example.com0
    bloomf.getCommand("1")->execute("www.example.com0",bloomf, blacklist); 

    //2 www.example.com0
    EXPECT_EQ("true true",bloomf.getCommand("2")->execute("www.example.com0",bloomf, blacklist)); //true true
    
    //2 www.example.com1
    EXPECT_EQ("false",bloomf.getCommand("2")->execute("www.example.com1",bloomf, blacklist)); //false

    //2 www.example.com11
    EXPECT_EQ("true false",bloomf.getCommand("2")->execute("www.example.com11",bloomf, blacklist)); //true false

}



TEST(Input,exmaple2) {
   /* input example: 
    8 1
    1 www.example.com0
    2 www.example.com0
    true true
    2 www.example.com1
    true false
*/
    vector<IHash*> hashs;
    hashs.push_back(new StdHash()); //insert the first hash
    map<string, ICommand*> commands = createCommands(); 
    BloomFilter bloomf(8,hashs, commands);
    std::vector<std::string> blacklist;
    // 1 www.example.com0
    bloomf.getCommand("1")->execute("www.example.com0",bloomf, blacklist); 
    

    //2 www.example.com0
    EXPECT_EQ("true true",bloomf.getCommand("2")->execute("www.example.com0",bloomf, blacklist)); //true true
    
    // 2 www.example.com1
    EXPECT_EQ("true false",bloomf.getCommand("2")->execute("www.example.com1",bloomf, blacklist)); //true false
}



TEST(Input,exmaple3) {
    /* input example:
    8 2
    1 www.example.com0
    2 www.example.com0
    true true
    2 www.example.com4
    true false
    */
    
    vector<IHash*> hashs;
    hashs.push_back(new DoubleStdHash()); //insert the socond hash
    map<string, ICommand*> commands = createCommands(); 
    BloomFilter bloomf(8,hashs, commands);
    std::vector<std::string> blacklist;
    // 1 www.example.com0
    bloomf.getCommand("1")->execute("www.example.com0",bloomf, blacklist); 

    //2 www.example.com0
    EXPECT_EQ("true true",bloomf.getCommand("2")->execute("www.example.com0",bloomf, blacklist)); //true true
    
    // 2 www.example.com4
    EXPECT_EQ("true false",bloomf.getCommand("2")->execute("www.example.com4",bloomf, blacklist)); //true false


}
