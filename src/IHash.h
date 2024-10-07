#pragma once

#include <string>

class IHash {
public:
virtual size_t operator()(const std::string& str) const = 0;
};
