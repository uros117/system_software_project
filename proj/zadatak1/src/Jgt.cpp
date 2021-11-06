#include "Jgt.hpp"

Jgt::Jgt(unsigned int number, Argument* a1) : Instr(number, 3, "jgt", a1, nullptr) {
    this->setSize(a1->instrLength());
}

void Jgt::pass1() {

}

void Jgt::pass2() {
    Instr::jumpInstrPass2(0b01010011, *this);
}

Jgt::~Jgt() {

}
