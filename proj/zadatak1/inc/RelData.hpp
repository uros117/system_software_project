#ifndef __RelData_HPP__
#define __RelData_HPP__
#include <iostream>
#include <string>
#include <list>
#include <vector>

class RelData{
    unsigned int offset;
    unsigned int type;
    std::string symb_name;
    int addend;

    friend std::ostream& operator<<(std::ostream& out, RelData& obj);

public:
    //RelTable(const RelTable&) = delete;
	//RelTable(RelTable&&) = delete;
    RelData(unsigned int offset, unsigned int type, std::string symb_name, int addend);
    
    void setOffset(unsigned int offset) {
        this->offset = offset;
    }
    unsigned int getOffset() const {
        return offset;
    }

    void setType(unsigned int type) {
        this->type = type;
    }
    unsigned int getType() const {
        return type;
    }

    void setSymbName(std::string symb_name) {
        this->symb_name = symb_name;
    }
    std::string getSymbName() const {
        return symb_name;
    }

    void setAddend(unsigned int addend) {
        this->addend = addend;
    }
    unsigned int getAddend() const {
        return addend;
    }
};

#endif