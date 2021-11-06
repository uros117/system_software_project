#include <iostream>
#include <string>
#include "SectionData.hpp"
#include "SymbolData.hpp"

SymbolData::SymbolData(
    std::string name, 
    bool isGlobal, 
    bool isExtern,
    SectionData* section, 
    int index, 
    bool hasValue) :
    name(name),
    isGlobal(isGlobal),
    isExtern(isExtern),
    offset(0),
    section(section),
    index(index),
    hasValue(hasValue) {
    
}