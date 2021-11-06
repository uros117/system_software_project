#include "Iret.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"

Iret::Iret(unsigned int number) : Instr(number, 1, "iret", nullptr, nullptr) {

}

void Iret::pass1() {

}

void Iret::pass2() {
    SectionManager& sm = SectionManager::getInstance();
	SectionData* sd = sm.getCurrent();
    sd->appendData(0b00100000);
}

Iret::~Iret() {

}
