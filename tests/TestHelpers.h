#include <vector>  
#include <map>     
#include <string>  

#include "IHash.h"
#include "ICommand.h"
#include "BloomFilter.h"

// helper functions for tests: 

 // Helper function create dynamic array of hashs (corrently with 2 fucntions)
std::vector<IHash*> createHashFunctions();

// Helper function to create map of commands
std::map<std::string, ICommand*> createCommands();

// Helper function to check if two vectors of hash functions are equal
void checkHashFunctions(const std::vector<IHash*>& expected, const std::vector<IHash*>& actual);

// Helper function to compare ICommand objects based on behavior
bool compareCommands(const ICommand* expected, const ICommand* actual, BloomFilter& bloomf);


