#include "Jeq.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "Argument.hpp"
#include "AssemblerException.hpp"
#include "RelTable.hpp"
#include "RelData.hpp"

Jeq::Jeq(unsigned int number, Argument* a1) : Instr(number, 3, "jeq", a1, nullptr) {
    this->setSize(a1->instrLength());
}

void Jeq::pass1() {

}

void Jeq::pass2() {
    Instr::jumpInstrPass2(0b01010001, *this);
}

Jeq::~Jeq() {

}
