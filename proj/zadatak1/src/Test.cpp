#include "Test.hpp"

Test::Test(unsigned int number, Argument* a1, Argument* a2) : Instr(number, 2, "test", a1, a2) {

}

void Test::pass1() {

}

void Test::pass2() {
    regRegInstrPass2(0b10000100, *this);
}

Test::~Test() {

}
