#pragma once

#include <string>
#include "./IHash.h"
#ifndef ICOMMAND_H
#define ICOMMAND_H
using namespace std;
class BloomFilter; // Forward declaration
#include "BloomFilter.h"

class ICommand {
public:
virtual string execute(const std::string& url, BloomFilter& bloomFilter, vector<string>& blacklist) const = 0;
};

#endif

