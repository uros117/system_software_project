#include <string>
#include <iostream>
#include "Label.hpp"
#include "SymbolTable.hpp"
#include "SectionManager.hpp"
#include "AssemblerException.hpp"

Label::Label(unsigned int number, std::string name) : Line(number), name(name) {

}

Label::~Label() {
}

void Label::pass1() {
	SymbolTable& st = SymbolTable::getInstance();
	
	SectionData* sd = SectionManager::getInstance().getCurrent();
	if(sd){
		st.symbolDefine(name, sd->getLocationCounter(), false, false, sd);
	} else {
		sd = SectionManager::getInstance().getSectionByName("ABS");
		if(sd){
			st.symbolDefine(name, sd->getLocationCounter(), false, false, sd);
		} else {
			throw new AssemblerException("Missing ABS section!");
		}
		
	}
	
}

void Label::pass2() {
}


void Label::print(std::ostream& out) const {
	out << name << " :" << std::endl;
}
