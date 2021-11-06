#include "Cmp.hpp"

Cmp::Cmp(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "cmp", a1, a2) {

}

void Cmp::pass1() {

}

void Cmp::pass2() {
    regRegInstrPass2(0b01110100, *this);
}

Cmp::~Cmp() {

}
