#ifndef __FileInfo_HPP__
#define __FileInfo_HPP__
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "SectionManager.hpp"
#include "SymbolTable.hpp"

class FileInfo{
    SectionManager sm;
    SymbolTable st;
    std::string filename;

    friend std::ostream& operator<<(std::ostream& out, FileInfo& obj);
    friend std::istream& operator>>(std::istream& in, FileInfo& obj);

public:
    FileInfo();
    FileInfo(std::string fileinfo);

    void setSM(SectionManager&& sm) {
        this-> sm = sm;
    }
    SectionManager& getSM() {
        return sm;
    }

    void setST(SymbolTable&& st) {
        this-> st = st;
    }
    SymbolTable& getST() {
        return st;
    }

    void setFilename(std::string filename) {
        this->filename = filename;
    }
    std::string getFilename() const {
        return filename;
    }

};

#endif