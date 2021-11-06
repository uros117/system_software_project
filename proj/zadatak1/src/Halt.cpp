#include "Halt.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"

Halt::Halt(unsigned int number) : Instr(number, 1, "halt", nullptr, nullptr) {

}

void Halt::pass1() {

}

void Halt::pass2() {
    SectionData* sd = SectionManager::getInstance().getCurrent();
    sd->appendData(0);
}

Halt::~Halt() {

}
