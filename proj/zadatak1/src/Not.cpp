#include "Not.hpp"

Not::Not(unsigned int number, Argument* a1) : Instr(number, 2, "not", a1, nullptr) {

}

void Not::pass1() {

}

void Not::pass2() {
    regRegInstrPass2(0b10000000, *this);
}

Not::~Not() {

}
