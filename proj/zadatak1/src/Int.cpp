#include "Int.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "AssemblerException.hpp"

Int::Int(unsigned int number, Argument* a1) : Instr(number, 2, "int", a1, nullptr) {

}

void Int::pass1() {

}

void Int::pass2() {
    SectionManager& sm = SectionManager::getInstance();
	SectionData* sd = sm.getCurrent();
    if(getA1()->getType() == 5) {
        unsigned char rdes = (unsigned char)getA1()->getRegNum();
        sd->appendData(0b00100000);
        sd->appendData(rdes << 4 | 0x0F);
        sd->appendData(0b00000001);
    } else {
        throw new AssemblerException("Invalid address mode!");
    }
}

Int::~Int() {

}
