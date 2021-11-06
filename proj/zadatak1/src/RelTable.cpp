#include "RelTable.hpp"
#include "RelData.hpp"
#include "SymbolTable.hpp"
#include "SymbolData.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

RelTable::RelTable() : table() {

}

void RelTable::append(unsigned int offset, unsigned int type, std::string symb_name, int addend) {
    table.push_back(RelData(offset, type, symb_name, addend));
}

std::ostream& operator<<(std::ostream& out, RelTable& obj) {
    out << "RelTable: " << obj.table.size() << endl;

    if(obj.table.size() > 0) {
        out
            << left
            << setw(9)
            << "Offset"
            << left
            << setw(9)
            << "Type"
            << left
            << setw(9)
            << "Symb"
            << left
            << setw(9)
            << "Addend"
            << endl;

        for(RelData& rd : obj.table) {
            SymbolData* sd = SymbolTable::getInstance().getSymbolByName(rd.getSymbName());
            out
            << left
            << setw(9)
            << rd.getOffset()
            << left
            << setw(9)
            << rd.getType()
            << left
            << setw(9)
            << sd->getIndex()
            << left
            << setw(9)
            << rd.getAddend()
            << endl;
        }
    }
    

    return out;
}