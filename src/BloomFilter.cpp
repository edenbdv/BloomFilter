
#include "BloomFilter.h"
#include <iostream>
#include <string>
#include <vector>
#include "./IHash.h"
#include "./ICommand.h"
#include <map>

using namespace std;

/*
This is the constructur of BloomFilter
*/
BloomFilter::BloomFilter(int num, vector<IHash*> hashs, std::map<string, ICommand*> commands) {
    this->arraySize = num;
    this->array = new int[arraySize](); // Initialize array elements to 0
    this->hashs = hashs;
    this-> commands = commands; 
}


//Getters:

/*
This method returns the 'binary' array to outer code
*/
int* BloomFilter::getArray() const {
    return array;
}

/*
This method returns the size of the 'binary' array to outer code
*/
 int BloomFilter::getArraySize() const {
    return arraySize;
 }

/*
This method returns the vector of hash function that are avaliable to the bloom filter
*/
 vector< IHash*> BloomFilter:: getHashs() const {
    return hashs;
 }

/*
This method returns command by its string key to outer code
*/
 ICommand* BloomFilter:: getCommand(const std::string& str) {
    return commands[str];
 }


/*
This method adds a hash function to the vector hashs
*/
void BloomFilter::addHash(IHash* hash)
{
    hashs.push_back(hash);
}

/*
This method deletes a hash from the vector based on index
*/ 
void BloomFilter::deleteHashByIndex(size_t index) {
  if (index < hashs.size()) {
    hashs.erase(hashs.begin() + index);
    }
}
 

/*
This method is the destructor
*/
BloomFilter::~BloomFilter() {
    if (array){
        delete[] array; 
        array = nullptr;
    }
}

