#include "../ICommand.h"
#include "ContainsUrlCommand.h"
#include "../BloomFilter.h"
using namespace std;

/*
This function checks if the url is in the "blacklist"
*/
string ContainsUrlCommand::execute(const std::string& url,
    BloomFilter& bloomFilter, vector<string>& blacklist) const{
    // save getters to vars 
    int size = bloomFilter.getArraySize();
    vector< IHash*> hashs = bloomFilter.getHashs();
    int* arr = bloomFilter.getArray();

    // checks if the url in the blacklist
     for (int i = 0; i < hashs.size(); ++i) {
            int bit_index = hashs[i]->operator()(url) % size;
            if (arr[bit_index] == 0) {
                return "false";
            }
        }
        for (const std::string& element : blacklist) {
            if (element == url) {
                return "true true";
            }   
        }
    return "true false";
 }
