#include "Add.hpp"

Add::Add(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "add", a1, a2) {

}

void Add::pass1() {

}

void Add::pass2() {
    regRegInstrPass2(0b01110000, *this);
}

Add::~Add() {

}
