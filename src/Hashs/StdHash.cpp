#include "../IHash.h"
#include "StdHash.h"

using namespace std;

 /*
 This method makes opeator overloading for "()"" operator
*/
size_t StdHash::operator()(const string& str) const {
    return std::hash<std::string>{}(str);
}