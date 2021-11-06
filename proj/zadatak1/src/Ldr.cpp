#include "Ldr.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "Argument.hpp"
#include "RelTable.hpp"
#include "Instr.hpp"
#include "AssemblerException.hpp"

Ldr::Ldr(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 3, "ldr", a1, a2) {
    this->setSize(a2->instrLength());
}

void Ldr::pass1() {

}

void Ldr::pass2() {
	SectionManager& sm = SectionManager::getInstance();
	SectionData* sd = sm.getCurrent();
	sd->appendData(0b10100000);

	unsigned char c = 0b11110000;
	unsigned char m = 0b00001111;
	uint16_t temp = (uint16_t)getA2()->getLiteral();
	unsigned char tl = ((unsigned char*)&temp)[0];
	unsigned char th = ((unsigned char*)&temp)[1];
	unsigned char rdes = (unsigned char)getA1()->getRegNum();
	switch(getA2()->getType()) {
	case 0:
		// <literal>
		sd->appendData(rdes << 4);
		sd->appendData(UPDATE_NONE | ADDR_MODE_MEM);
		sd->appendData(th);
		sd->appendData(tl);
		break;
	case 1:
		// <symbol>
		sd->getRelTable().append(sd->getLocationCounter() + 3, 1, getA2()->getSymbol(), 0);
		sd->appendData(rdes << 4);
		sd->appendData(UPDATE_NONE | ADDR_MODE_MEM);
		sd->appendData(0);
		sd->appendData(0);
		break;
	case 2:
		// $<literal>
		sd->appendData(rdes << 4);
		sd->appendData(UPDATE_NONE | ADDR_MODE_IMMED);
		sd->appendData(th);
		sd->appendData(tl);
		break;
	case 3:
		// $<symbol>
		sd->getRelTable().append(sd->getLocationCounter() + 3, 3, getA2()->getSymbol(), 0);
		sd->appendData(rdes << 4);
		sd->appendData(UPDATE_NONE | ADDR_MODE_IMMED);
		sd->appendData(0);
		sd->appendData(0);
		break;
	case 4:
		// %<symbol>
		sd->getRelTable().append(sd->getLocationCounter() + 3, 4, getA2()->getSymbol(), 5);
		sd->appendData(7);// PC REL
		sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR_PAYLOAD);
		sd->appendData(0);
		sd->appendData(0);
		break;
	case 5:
		// <reg>
		sd->appendData(rdes << 4 | getA2()->getRegNum());
		sd->appendData(UPDATE_NONE | ADDR_MODE_REGDIR);
		break;
	case 6:
		// [<reg>]
		sd->appendData(rdes << 4 | getA2()->getRegNum());
		sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR);
		break;
	case 7:
		// [<reg> + <literal>]
		sd->appendData(rdes << 4 | getA2()->getRegNum());
		sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR_PAYLOAD);
		sd->appendData(th);
		sd->appendData(tl);
		break;
	case 8:
		// [<reg> + <symbol>]
		sd->getRelTable().append(sd->getLocationCounter() + 3, 8, getA2()->getSymbol(), 0);
		sd->appendData(rdes << 4 | getA2()->getRegNum());
		sd->appendData(UPDATE_NONE | ADDR_MODE_REGINDIR_PAYLOAD);
		sd->appendData(0);
		sd->appendData(0);
		break;

	default:
		throw new AssemblerException("Invalid address mode!");
		break;
	}
}

Ldr::~Ldr() {

}
