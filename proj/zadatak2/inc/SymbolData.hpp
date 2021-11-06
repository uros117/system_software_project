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
    std::string section;
    int index;
    bool hasValue;
    int linkedIndex;
    std::list<SymbolData*> linkedNotfyList;
    
public:
    SymbolData(
        std::string name,
        bool isGlobal,
        bool isExtern,
        std::string section,
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
    void setSection(std::string section) {
        this->section = section;
    }
    std::string getSection() const {
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

    void setLinkedIndex(int linkedIndex) {
        this->linkedIndex = linkedIndex;
    }
    int getLinkedIndex() const {
        return linkedIndex;
    }

    bool operator< (const SymbolData& e) const
    {
        return (name < e.name);
    }

    void addSymbolToNotifyWhenLinked(SymbolData* sd) {
        if(sd != nullptr) {
            linkedNotfyList.push_back(sd);
        }
    }
    void notify() {
        for(SymbolData* sd : linkedNotfyList) {
            if(sd != nullptr) {
                sd->setLinkedIndex(this->index);
            }
        }
    }
};


#endif