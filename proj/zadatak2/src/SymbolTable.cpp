#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include "SymbolTable.hpp"
#include "LinkerException.hpp"
#include "SectionManager.hpp"
#include "FileInfo.hpp"

using namespace std;

SymbolTable::SymbolTable() : table() {
    
}

void SymbolTable::symbolDeclare(std::string name, bool isGlobal, bool isExtern,  SectionData* section) {
    SymbolData* t = getSymbolByName(name);
    if(t != nullptr) {
       // Symbol re-declaration??? 
       throw new LinkerException("Symbol " + name + " was redeclared!");
    }
    // everything is fine
    // declare a symbol
    
    this->symbolAdd(name, isGlobal, isExtern, section->getName(), false);
}

void SymbolTable::symbolDefine(std::string name, int offset, bool isGlobal, bool isExtern,  SectionData* section) {
    SymbolData* t = getSymbolByName(name);
    if(t != nullptr) {
        if(t->getIsExtern() == true) {
            throw new LinkerException("Cannot define a extern symbol(" + name +")!");
        }
        if(t->getHasValue() == true) {
            // Symbol re-definition
            throw new LinkerException("Symbol " + name + " redefinition!");
        } 
        // symbol is not extern and is not defined
        
        t->setHasValue(true);
        t->setOffset(offset);
        return;
    }
    // there is no previous definition or declaration
    // so add a new symbol

    this->symbolAdd(name, isGlobal, isExtern, section->getName(), true, offset);
}


SymbolData* SymbolTable::getSymbolByName(std::string name) {
    for(SymbolData& i : table) {
        if(i.getName() == name) {
            return &i;
        }
    }
    return nullptr;
}

SymbolData* SymbolTable::getGlobalSymbolByName(std::string name) {
    for(SymbolData& i : table) {
        if(i.getName() == name && i.getIsGlobal()) {
            return &i;
        }
    }
    return nullptr;
}

void SymbolTable::symbolAdd(std::string name, bool isGlobal, bool isExtern, std::string section, bool hasValue) {
    SymbolData sd(name, isGlobal, isExtern, section, (int)this->table.size(), hasValue);
    //this->table.append(sd);
    this->table.push_back(sd);
}

void SymbolTable::symbolAdd(std::string name, bool isGlobal, bool isExtern, std::string section, bool hasValue, int offset) {
    SymbolData sd(name, isGlobal, isExtern, section, (int)this->table.size(), hasValue);
    sd.setOffset(offset);
    //this->table.append(sd);
    this->table.push_back(sd);
}

void SymbolTable::linkSymbol(SymbolData& sd, FileInfo& fi) {
    if(sd.getIsGlobal() || (sd.getName() == sd.getSection())) {
        // The symbol is global, extern or a section
        if(sd.getHasValue()) {
            // Symbol is (global) defined
            SymbolData* found = getGlobalSymbolByName(sd.getName());
            if(found) {
                // There is another symbol with the same name
                if(found->getHasValue()) {
                    // The symbol is already defined (global)
                    throw new LinkerException("Multiple definitions of symbol " + sd.getName() + "!");
                }
                // The symbol is undefined, so define it
                found->setHasValue(true);
                found->setSection(sd.getSection());
                found->setOffset(sd.getOffset());
                sd.setLinkedIndex(found->getIndex());
            } else {
                // There is no symbol with the same name in the table
                sd.setLinkedIndex(table.size());
                symbolAdd(sd.getName(), sd.getIsGlobal(), sd.getIsExtern(), sd.getSection(), sd.getHasValue());
            }
        } else {
            // Symbos is (extern) undefined
            SymbolData* found = getGlobalSymbolByName(sd.getName());
            if(found) {
                // There is already a symbol with the same name
                sd.setLinkedIndex(found->getIndex());
            } else {
                // There is no symbol with the same name in the table
                sd.setLinkedIndex(table.size());
                symbolAdd(sd.getName(), sd.getIsGlobal(), sd.getIsExtern(), sd.getSection(), sd.getHasValue());
            }
        }
    } else {
        // The symbol is local
        SectionData* section = fi.getSM().getSectionByName(sd.getSection());
               
        sd.setOffset(sd.getOffset() + section->getOffset());
        sd.setLinkedIndex(table.size());
        
        symbolAdd(sd.getName(), sd.getIsGlobal(), sd.getIsExtern(), sd.getSection(), sd.getHasValue(), sd.getOffset());
    }
    
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
        
        s_name = sd.getSection();
        
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
