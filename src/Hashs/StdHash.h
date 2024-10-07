#pragma once

#include "../IHash.h"

class StdHash : public IHash {
public:
 /*
 This method makes opeator overloading for "()"" operator
*/
    size_t operator()(const std::string& str) const override;
};