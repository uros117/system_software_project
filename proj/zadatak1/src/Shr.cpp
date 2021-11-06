#include "Shr.hpp"

Shr::Shr(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "shr", a1, a2) {

}

void Shr::pass1() {

}

void Shr::pass2() {
    regRegInstrPass2(0b10010001, *this);
}

Shr::~Shr() {

}
