#include "And.hpp"

And::And(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "and", a1, a2) {

}

void And::pass1() {

}

void And::pass2() {
    regRegInstrPass2(0b10000001, *this);
}

And::~And() {

}
