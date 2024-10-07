#include <string>
#include <vector>
#include <functional>
#include <map>
#include "./IHash.h"
#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

class ICommand;  // Forward declaration
#include "ICommand.h"



using namespace std;

class BloomFilter {
public:
    // Constructor
    BloomFilter(int num, vector<IHash*> hashs,std::map<string, ICommand*> commands);

    // Member function:

    //getters

    //return the 'binary' array to outer code
    int* getArray() const;

    //return the size of the 'binary' array to outer code
    int getArraySize() const;

    //return the vector of hash function that are avaliable to the bloom filter
    vector<IHash*> getHashs() const;

    //return command by its string key to outer code
    ICommand* getCommand(const std::string& str) ;

    // adds a hash function to the vector hashs
    void addHash(IHash* hash);

    //deletes a hash from the vector based on index
    void deleteHashByIndex(size_t index);

    //destructor
    ~BloomFilter();

private:
    int* array; // Private data member - array of integers
    int arraySize;  // Size of the array
    vector<IHash*> hashs;   // Vector of hash functions for strings
    map<string, ICommand*> commands; // map for name command- the command
};
#endif
