#include "Xchg.hpp"

Xchg::Xchg(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "xchg", a1, a2) {

}

void Xchg::pass1() {

}

void Xchg::pass2() {
    regRegInstrPass2(0b01100000, *this);
}

Xchg::~Xchg() {

}
