
#include "../ICommand.h"
#include "./AddUrlCommand.h"
#include "../BloomFilter.h"
using namespace std;

/*
This function checks if the url is in the "blacklist"
*/
string AddUrlCommand::execute(const std::string& url,
    BloomFilter& bloomFilter, vector<string>& blacklist) const{
    blacklist.push_back(url);
    // save getters to vars 
    int size = bloomFilter.getArraySize();
    vector< IHash*> hashs = bloomFilter.getHashs();
    int* arr = bloomFilter.getArray();

    for (int i = 0; i < hashs.size(); ++i) {
        int bit_index = hashs[i]->operator()(url) % size;
            arr[bit_index] = 1;
        }
    
    return "";
    }