#include "../IHash.h"
#include "StdHash.h"
#include "DoubleStdHash.h" 

using namespace std;

 /*
 This method makes opeator overloading for "()"" operator
*/
size_t DoubleStdHash:: operator()(const string& str) const {
    //Perform the first hash
    size_t hashResult1 = StdHash()(str);

    //Convert the result to a string and perform the second hash
    string hashInput2 = to_string(hashResult1);
    size_t hashResult2 = StdHash()(hashInput2);

    return hashResult2;
}
