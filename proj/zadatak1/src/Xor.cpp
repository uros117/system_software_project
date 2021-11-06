#include "Xor.hpp"

Xor::Xor(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "xor", a1, a2) {

}

void Xor::pass1() {

}

void Xor::pass2() {
    regRegInstrPass2(0b10000011, *this);
}

Xor::~Xor() {

}
