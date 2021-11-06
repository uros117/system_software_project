#include "Equ.hpp"
#include <iostream>
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "AssemblerException.hpp"
#include "SymbolTable.hpp"

Equ::Equ(unsigned int number, std::string name, int literal) : Directive(number), name(""), literal(0) {
	this->name = name;
	this->literal = literal;
}

Equ::~Equ() {
}

void Equ::pass1() {
	SectionData* sd_old = SectionManager::getInstance().getCurrent();
	SectionData* sd = SectionManager::getInstance().getSectionByName("ABS");
	if(sd) {
		SymbolTable::getInstance().symbolDefine(name, literal, false, false, sd);
	} else {
		throw new AssemblerException("There is no ABS section!");
	}
	if(sd_old) {
		SectionManager::getInstance().beginSection(sd_old->getName());
	} else {
		throw new AssemblerException("Old section is null!");
	}
	
}

void Equ::pass2() {
}

void Equ::print(std::ostream& out) const {
	out << ".equ " << name << ", " << literal << std::endl;
}
