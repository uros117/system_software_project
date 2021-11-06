#include "Jmp.hpp"
#include "Instr.hpp"

Jmp::Jmp(unsigned int number, Argument* a1) : Instr(number, 3, "jmp", a1, nullptr) {
    this->setSize(a1->instrLength());
}

void Jmp::pass1() {

}

void Jmp::pass2() {
	Instr::jumpInstrPass2(0b01010000, *this);
}

Jmp::~Jmp() {

}
