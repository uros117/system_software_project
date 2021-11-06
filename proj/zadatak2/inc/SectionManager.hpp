#ifndef __SectionManager_HPP__
#define __SectionManager_HPP__
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "SectionData.hpp"

class SectionManager {
    std::list<SectionData> list;
    SectionData* currentSection;
    friend std::ostream& operator<<(std::ostream& out, SectionManager& obj);
public:
    /*static SectionManager& getInstance() {
        static SectionManager instance;
        return instance;
    }*/

    SectionManager();
    //SectionManager(const SectionManager&) = delete;
	//SectionManager(SectionManager&&) = delete;
    
    void beginSection(std::string name);
    void endSection();

    SectionData* getCurrent();

    std::list<SectionData>& getList() {
        return list;
    }
    SectionData* getSectionByName(std::string name);

    void resetLocationCounters();
    
    void writeHex(std::ostream& out);

};

#endif