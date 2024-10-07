#pragma once

#include "../ICommand.h"
#include "../BloomFilter.h"
using namespace std;

class ContainsUrlCommand: public ICommand {
public:
     /*
     This function checks if the url is in the "blacklist"
     */
     string execute(const std::string& url, BloomFilter& bloomFilter, vector<string>& blacklist) const override;

};
