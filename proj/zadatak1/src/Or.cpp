#include "Or.hpp"

Or::Or(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "or", a1, a2) {

}

void Or::pass1() {

}

void Or::pass2() {
    regRegInstrPass2(0b10000010, *this);
}

Or::~Or() {

}
