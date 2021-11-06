#ifndef __RelTable_HPP__
#define __RelTable_HPP__
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "RelData.hpp"

class RelTable{
    std::vector<RelData> table;
    friend std::ostream& operator<<(std::ostream& out, RelTable& obj);

public:
    //RelTable(const RelTable&) = delete;
	//RelTable(RelTable&&) = delete;
    RelTable();
    
    void append(unsigned int offset, unsigned int type, int symb_id, int addend);
    std::vector<RelData>& getTable() {
        return table;
    }
};

#endif