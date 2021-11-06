#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include "SectionData.hpp"
#include "SectionManager.hpp"
#include "LinkerException.hpp"

SectionManager::SectionManager() : 
    list(), currentSection(nullptr) {
    //list.push_back(SectionData("UND"));
    //list.push_back(SectionData("ABS"));
}

void SectionManager::beginSection(std::string name) {
    if(currentSection != nullptr)
        endSection();
    SectionData* t = getSectionByName(name);
    if(t == nullptr) {
        list.push_back(SectionData(name));
        t = &list.back();
    } 

    currentSection = t;
    //std::cout << "Section begin : " << currentSection->getName() << std::endl;
    return;
}

void SectionManager::endSection() {
    if(currentSection == nullptr) {
        throw new LinkerException("There is no section to end!");
    }
    currentSection = nullptr;
}

SectionData* SectionManager::getCurrent() {
    if(currentSection == nullptr) {
        //std::cout << currentSection << std::endl;
        beginSection("ABS");
    }
    return currentSection;
}

SectionData* SectionManager::getSectionByName(std::string name) {
    for(SectionData& i : list) {
        if(i.getName() == name) {
            return &i;
        }
    }
    return nullptr;
}

void SectionManager::resetLocationCounters() {
    for(SectionData& sd : this->list) {
        sd.setLocationCounter(0);
    }
}

std::ostream& operator<<(std::ostream& out, SectionManager& obj) {
    out << "Sections: " << obj.list.size() << endl;
    for(SectionData& elem : obj.list) {
        out << elem;
    }
    
    return out;
}

void writeByte(std::ostream& out, unsigned char b, int i) {
    if(i % 8 == 0)
        out << setfill('0') << setw(4) << right << hex << (unsigned int)i << setfill(' ') << ": ";

    out << setfill('0') << setw(2) << right << hex << ((unsigned char)b & 0xff) << setfill(' ') << ' ';
    
    if(i % 8 == 7)
        out << endl;
}

void SectionManager::writeHex(std::ostream& out) {
    // Sort the list of sections
    list.sort();
    int i = 0;
    for(SectionData& elem : list) {
        if(elem.getOffset() / 8 != i / 8) {
            // Sections are not in the same 8 byte space
            i = elem.getOffset() / 8;
        }
        
        for(;i < elem.getOffset(); i++) {
            writeByte(out, 0, i);
        }
        
        if(elem.getData().size() > 0) {
            for(char b : elem.getData()) {
                writeByte(out, b, i);
                i++;
            }
        }
    }
}