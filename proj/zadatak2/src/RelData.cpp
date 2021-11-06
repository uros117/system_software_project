#include "RelData.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

RelData::RelData(
    unsigned int offset,
    unsigned int type,
    int symb_id,
    int addend) : 
    offset(offset),
    type(type),
    symb_id(symb_id),
    addend(addend) {
    
}

std::ostream& operator<<(std::ostream& out, RelData& obj) {
    
    return out;
}