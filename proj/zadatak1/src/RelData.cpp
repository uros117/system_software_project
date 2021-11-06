#include "RelData.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

RelData::RelData(
    unsigned int offset,
    unsigned int type,
    std::string symb_name,
    int addend) : 
    offset(offset),
    type(type),
    symb_name(symb_name),
    addend(addend) {
    
}

std::ostream& operator<<(std::ostream& out, RelData& obj) {
    
    return out;
}