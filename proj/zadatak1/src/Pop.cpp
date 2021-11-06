#include "Pop.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "Argument.hpp"
#include "RelTable.hpp"
#include "Instr.hpp"
#include "AssemblerException.hpp"

Pop::Pop(unsigned int number, Argument* a1) : Instr(number, 3, "pop", a1, nullptr) {
    
}

void Pop::pass1() {

}

void Pop::pass2() {
    SectionManager& sm = SectionManager::getInstance();
	SectionData* sd = sm.getCurrent();
	sd->appendData(0b10100000);

	unsigned char rdes = (unsigned char)getA1()->getRegNum();
	
	sd->appendData(rdes << 4 | 6);
	sd->appendData(UPDATE_POST_INC | ADDR_MODE_REGINDIR);
}

Pop::~Pop() {

}
