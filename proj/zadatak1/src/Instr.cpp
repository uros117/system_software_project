#include <iostream>
#include "Instr.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "AssemblerException.hpp"

Instr::Instr(unsigned int number, unsigned int size, std::string name, Argument* a1, Argument* a2) : Line(number, size) {
	this->name = name;
	this->a1 = a1;
	this->a2 = a2;
}

Instr::~Instr() {
	if (a1) delete a1;
	if (a2) delete a2;
}

void Instr::print(std::ostream& out) const {
	out << name;

	if(a1 != nullptr) {
		out << " " << *a1;
	} else {
		out << std::endl;
		return;
	}

	if(a2 != nullptr) {
		out << ", " << *a2 << std::endl;
	} else {
		out << std::endl;
	}
}

void Instr::jumpInstrPass2(unsigned char byte1, Instr& i) {
	SectionManager& sm = SectionManager::getInstance();
    SectionData* sd = sm.getCurrent();
    sd->appendData(byte1);
    unsigned char c = 0b11110000;
    unsigned char m = 0b00001111;
    uint16_t temp = (uint16_t)i.getA1()->getLiteral();
    unsigned char tl = ((unsigned char*)&temp)[0];
    unsigned char th = ((unsigned char*)&temp)[1];
    switch(i.getA1()->getType()) {
        case 0:
            // <literal>
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_IMMED);
            sd->appendData(th);
            sd->appendData(tl);
            break;
        case 1:
            // <symbol>
            sd->getRelTable().append(sd->getLocationCounter() + 3, 1, i.getA1()->getSymbol(), 0);
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_IMMED);
            sd->appendData(0);
            sd->appendData(0);
            break;
        case 4:
            // %<symbol>
            sd->getRelTable().append(sd->getLocationCounter() + 3, 4, i.getA1()->getSymbol(), 5);
            sd->appendData(0b11110111);
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGDIR_PAYLOAD);
            sd->appendData(0);
            sd->appendData(0);
            break;
        case 9:
            // *<literal>
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_MEM);
            sd->appendData(th);
            sd->appendData(tl);
            break;
        case 10:
            // *<symbol>
            sd->getRelTable().append(sd->getLocationCounter() + 3, 10, i.getA1()->getSymbol(), 0);
            sd->appendData(c);
            sd->appendData(UPDATE_NONE | ADDR_MODE_MEM);
            sd->appendData(0);
            sd->appendData(0);
            break;
        case 11:
            // *<reg>
            sd->appendData(c | (m & i.getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGDIR);
            break;
        case 12:
            // *[<reg>]
            sd->appendData(c | (m & i.getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR);
            break;
        case 13:
            // *[<reg> + <literal>]
            sd->appendData(c | (m & i.getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR_PAYLOAD);
            sd->appendData(th);
            sd->appendData(tl);
            break;
        case 14:
            // *[<reg> + <symbol>]
            sd->getRelTable().append(sd->getLocationCounter() + 3, 14, i.getA1()->getSymbol(), 0);
            sd->appendData(c | (m & i.getA1()->getRegNum()));
            sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR_PAYLOAD);
            sd->appendData(0);
            sd->appendData(0);
            break;
            
        default:
            throw new AssemblerException("Invalid address mode!");
            break;
    }

}

void Instr::regRegInstrPass2(unsigned char byte1, Instr& i) {
    SectionManager& sm = SectionManager::getInstance();
    SectionData* sd = sm.getCurrent();
    Argument* a1 = i.getA1();
    Argument* a2 = i.getA2();
    if(!a1)
        throw new AssemblerException("Instruction format is op reg reg!");
    if(!a2)
        a2 = a1;// NOT - Although it should probably be 0
    char rdes = a1->getRegNum();
    char rsrc = a2->getRegNum();
    if(rdes < 0 || rsrc < 0)
        throw new AssemblerException("Instruction format is op reg reg!");

    sd->appendData(byte1);
    sd->appendData(rdes << 4 | (rsrc & 0xF));
}
