#include "Shl.hpp"

Shl::Shl(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "shl", a1, a2) {

}

void Shl::pass1() {
    
}

void Shl::pass2() {
    regRegInstrPass2(0b10010000, *this);
}

Shl::~Shl() {

}
