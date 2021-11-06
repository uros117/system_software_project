#include "Ret.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"

Ret::Ret(unsigned int number) : Instr(number, 1, "ret", nullptr, nullptr) {

}

void Ret::pass1() {

}

void Ret::pass2() {
    SectionManager& sm = SectionManager::getInstance();
	SectionData* sd = sm.getCurrent();
    sd->appendData(0b01000000);
}

Ret::~Ret() {

}
