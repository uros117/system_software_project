#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "util.hpp"
#include "SectionData.hpp"
#include "SectionManager.hpp"
#include "AssemblerException.hpp"

SectionManager::SectionManager() : 
    list(), currentSection(nullptr) {
    list.push_back(SectionData("UND"));
    list.push_back(SectionData("ABS"));
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
        throw new AssemblerException("There is no section to end!");
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