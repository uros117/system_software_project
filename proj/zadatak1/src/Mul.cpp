#include "Mul.hpp"

Mul::Mul(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "mul", a1, a2) {

}

void Mul::pass1() {

}

void Mul::pass2() {
    regRegInstrPass2(0b01110010, *this);
}

Mul::~Mul() {

}
