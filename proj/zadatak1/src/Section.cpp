#include "Section.hpp"
#include "SectionManager.hpp"
#include "SymbolTable.hpp"
#include <iostream>

Section::Section(unsigned int number, std::string name) : Directive(number), name("") {
	this->name = name;
}

Section::~Section() {
}

void Section::pass1() {
	SectionManager& sm = SectionManager::getInstance();
	sm.beginSection(name);
	SectionData* sd = sm.getCurrent();
	SymbolTable::getInstance().symbolDeclare(name, false, false, sd);
	/*if(!SymbolTable::getInstance().getSymbolByName(name)) {
		SymbolTable::getInstance().symbolDeclare(name, false, false, sd);
	}*/
	
}

void Section::pass2() {
	SectionManager& sm = SectionManager::getInstance();
	sm.beginSection(name);
}

void Section::print(std::ostream& out) const {
	out << ".section " << name << std::endl;
}
