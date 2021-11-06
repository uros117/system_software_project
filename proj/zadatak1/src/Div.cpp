#include "Div.hpp"

Div::Div(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 4, "div", a1, a2) {

}

void Div::pass1() {

}

void Div::pass2() {
    regRegInstrPass2(0b01110011, *this);
}

Div::~Div() {

}
