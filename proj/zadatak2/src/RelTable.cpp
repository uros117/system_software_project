#include "RelTable.hpp"
#include "RelData.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

RelTable::RelTable() : table() {

}

void RelTable::append(unsigned int offset, unsigned int type, int symb_id, int addend) {
    table.push_back(RelData(offset, type, symb_id, addend));
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
            << setw(20)
            << "Symb_name"
            << left
            << setw(9)
            << "Addend"
            << endl;

        for(RelData& rd : obj.table) {
            out
            << left
            << setw(9)
            << rd.getOffset()
            << left
            << setw(9)
            << rd.getType()
            << left
            << setw(20)
            << rd.getSymbID()
            << left
            << setw(9)
            << rd.getAddend()
            << endl;
        }
    }
    

    return out;
}