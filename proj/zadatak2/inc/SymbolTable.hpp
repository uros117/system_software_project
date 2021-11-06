#ifndef __SymbolTable_HPP__
#define __SymbolTable_HPP__
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "SymbolData.hpp"

class FileInfo;

class SymbolTable{
    std::vector<SymbolData> table;
    
    friend std::ostream& operator<<(std::ostream& out, SymbolTable& obj);

public:
    /*static SymbolTable& getInstance() {
        static SymbolTable instance;
        return instance;
    }
    SymbolTable(const SymbolTable&) = delete;
	SymbolTable(SymbolTable&&) = delete;*/
    SymbolTable();
    void symbolDeclare(std::string name, bool isGlobal, bool isExtern,  SectionData* section);
    void symbolDefine(std::string name, int offset, bool isGlobal, bool isExtern,  SectionData* section);
    void symbolAdd(std::string name, bool isGlobal, bool isExtern, std::string section, bool hasValue);
    void symbolAdd(std::string name, bool isGlobal, bool isExtern, std::string section, bool hasValue, int offset);
    SymbolData* getSymbolByName(std::string name);
    SymbolData* getGlobalSymbolByName(std::string name);

    std::vector<SymbolData>& getTable() {
        return table;
    }

    void linkSymbol(SymbolData& sd, FileInfo& fi);

};

#endif
