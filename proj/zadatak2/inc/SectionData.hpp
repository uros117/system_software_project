#ifndef __SectionData_HPP__
#define __SectionData_HPP__
#include <iostream>
#include <string>
#include <vector>
#include "RelTable.hpp"

class SectionData {
    int offset;
    std::string name;
    int locationCounter;
    std::vector<char> data;
    RelTable reltable;
    bool isPositioned;

    friend std::ostream& operator<<(std::ostream& out, SectionData& obj);
public:
    SectionData(std::string name);

    void setOffset(unsigned int offset) {
        this->offset = offset;
    }
    int getOffset() const {
        return offset;
    }
    void incOffset(int increment) {
        offset += increment;
    }

    std::string getName() const {
        return name;
    }
    void setName(std::string name) {
        this->name = name;
    }

    void setLocationCounter(int locationCounter) {
        this->locationCounter = locationCounter;
    }
    int getLocationCounter() {
        return locationCounter;
    }
    void incLocationCounter(int increment) {
        locationCounter += increment;
    }

    void setData(std::vector<char> data) {
        this->data = data;
    }
    std::vector<char>& getData() {
        return data;
    
    }
    void appendData(char b) {
        this->data.push_back(b);
    }
    void appendData() {
        this->data.push_back(0);
    }

    void setRelTable(RelTable& reltable) {
        this->reltable = reltable;
    }
    RelTable& getRelTable() {
        return reltable;
    }

    void setIsPositioned(bool b) {
        this->isPositioned = b;
    }
    bool getIsPositioned() const {
        return isPositioned;
    }

    bool operator< (const SectionData& e) const
    {
        return (offset < e.offset);
    }
    
    void writeHex(std::ostream& out);

};

#endif