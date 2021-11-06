#include "Sub.hpp"

Sub::Sub(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "sub", a1, a2) {

}

void Sub::pass1() {

}

void Sub::pass2() {
    regRegInstrPass2(0b01110001, *this);
}

Sub::~Sub() {

}
