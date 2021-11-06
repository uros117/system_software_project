#include "Push.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "Argument.hpp"
#include "RelTable.hpp"
#include "Instr.hpp"
#include "AssemblerException.hpp"

Push::Push(unsigned int number, Argument* a1) : Instr(number, 3, "push", a1, nullptr) {

}

void Push::pass1() {

}

void Push::pass2() {
    SectionManager& sm = SectionManager::getInstance();
	SectionData* sd = sm.getCurrent();
	sd->appendData(0b10110000);
    
	unsigned char rdes = (unsigned char)getA1()->getRegNum();
	
	// [<reg>]
	sd->appendData(rdes << 4 | 6);
	sd->appendData(UPDATE_PRE_DEC | ADDR_MODE_REGINDIR);
}

Push::~Push() {

}
