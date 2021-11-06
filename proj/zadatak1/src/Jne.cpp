#include "Jne.hpp"

Jne::Jne(unsigned int number, Argument* a1) : Instr(number, 3, "jne", a1, nullptr) {
    this->setSize(a1->instrLength());
}

void Jne::pass1() {

}

void Jne::pass2() {
    Instr::jumpInstrPass2(0b01010010, *this);
}

Jne::~Jne() {

}
