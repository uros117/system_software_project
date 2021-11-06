#ifndef __SymbolData_HPP__
#define __SymbolData_HPP__
#include <iostream>
#include <string>
#include "SectionData.hpp"

class SymbolData{
    std::string name;
    bool isGlobal;
    bool isExtern;
    unsigned int offset;
    SectionData* section;
    int index;
    bool hasValue;
    
public:
    SymbolData(
        std::string name,
        bool isGlobal,
        bool isExtern,
        SectionData* section,
        int index,
        bool hasValue);
        
    void setName(std::string name) {
        this->name = name;
    }
    std::string getName() const {
        return name;
    }
    void setIsGlobal(bool isGlobal) {
        this->isGlobal = isGlobal;
    }
    bool getIsGlobal() const {
        return isGlobal;
    }
    void setIsExtern(bool isExtern) {
        this->isExtern = isExtern;
    }
    bool getIsExtern() const {
        return isExtern;
    }
    void setOffset(int offset) {
        this->offset = offset;
    }
    void incOffset(int increment) {
        offset += increment;
    }
    int getOffset() const {
        return offset;
    }
    /*int getLocationCounter() const {
        return locationCounter;
    }*/
    void setSection(SectionData* section) {
        this->section = section;
    }
    SectionData* getSection() const {
        return section;
    }
    void setIndex(int index) {
        this->index = index;
    }
    int getIndex() const {
        return index;
    }
    void setHasValue(bool hasValue) {
        this->hasValue = hasValue;
    }
    bool getHasValue() const {
        return hasValue;
    }
};


#endif