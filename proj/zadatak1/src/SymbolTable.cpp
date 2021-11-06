#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include "SymbolTable.hpp"
#include "AssemblerException.hpp"
#include "SectionManager.hpp"

using namespace std;

SymbolTable::SymbolTable() : table() {
    
}

void SymbolTable::symbolDeclare(std::string name, bool isGlobal, bool isExtern,  SectionData* section) {
    SymbolData* t = getSymbolByName(name);
    if(t != nullptr) {
       // Symbol re-declaration??? 
       throw new AssemblerException("Symbol " + name + " was redeclared!");
    }
    // everything is fine
    // declare a symbol
    
    this->symbolAdd(name, isGlobal, isExtern, section, false);
}

void SymbolTable::symbolDefine(std::string name, int offset, bool isGlobal, bool isExtern,  SectionData* section) {
    SymbolData* t = getSymbolByName(name);
    if(t != nullptr) {
        if(t->getIsExtern() == true) {
            throw new AssemblerException("Cannot define a extern symbol(" + name +")!");
        }
        if(t->getHasValue() == true) {
            // Symbol re-definition
            throw new AssemblerException("Symbol " + name + " redefinition!");
        } 
        // symbol is not extern and is not defined
        
        t->setHasValue(true);
        t->setOffset(offset);
        t->setSection(section);
        return;
    }
    // there is no previous definition or declaration
    // so add a new symbol

    this->symbolAdd(name, isGlobal, isExtern, section, true, offset);
}


SymbolData* SymbolTable::getSymbolByName(std::string name) {
    for(SymbolData& i : table) {
        if(i.getName() == name) {
            return &i;
        }
    }
    return nullptr;
}

void SymbolTable::symbolAdd(std::string name, bool isGlobal, bool isExtern, SectionData* section, bool hasValue) {
    SymbolData sd(name, isGlobal, isExtern, section, (int)this->table.size(), hasValue);
    //this->table.append(sd);
    this->table.push_back(sd);
}

void SymbolTable::symbolAdd(std::string name, bool isGlobal, bool isExtern, SectionData* section, bool hasValue, int offset) {
    SymbolData sd(name, isGlobal, isExtern, section, (int)this->table.size(), hasValue);
    sd.setOffset(offset);
    //this->table.append(sd);
    this->table.push_back(sd);
}

std::ostream& operator<<(std::ostream& out, SymbolTable& obj) {
    out << "SymbolTable: " << obj.table.size() << endl;
    out
        << left
        << setw(5)
        << "ID"
        << left
        << setw(20)
        << "Name"
        << left
        << setw(9)
        << "IsGlobal"
        << left
        << setw(9)
        << "IsExtern"
        << left
        << setw(9)
        << "Offset"
        << left
        << setw(9)
        << "Section"
        << left
        << setw(9)
        << "HasValue"
        << endl;

    for(SymbolData& sd : obj.table) {
        std::string s_name = "ERROR";
        if(sd.getSection())
            s_name = sd.getSection()->getName();
        
        out
        << left
        << setw(5)
        << sd.getIndex()
        << left
        << setw(20)
        << sd.getName()
        << left
        << setw(9)
        << sd.getIsGlobal()
        << left
        << setw(9)
        << sd.getIsExtern()
        << left
        << setw(9)
        << sd.getOffset()
        << left
        << setw(9)
        << s_name
        << left
        << setw(9)
        << sd.getHasValue()
        << endl;
    }

    return out;
}
