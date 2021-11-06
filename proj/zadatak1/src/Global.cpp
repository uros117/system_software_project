#include <iostream>
#include "Global.hpp"
#include "util.hpp"
#include "SymbolTable.hpp"
#include "SectionManager.hpp"
#include "AssemblerException.hpp"

Global::Global(unsigned int number, std::list<std::string>* sym_list) : Directive(number), sym_list(nullptr) {
	if(sym_list == nullptr) {
		// Error
	}
	this->sym_list = sym_list;
}

Global::~Global() {
	if(sym_list)
		delete sym_list;
}

void Global::pass1() {
	SymbolTable& st = SymbolTable::getInstance();
	for(std::string i : *this->sym_list) {
		SectionData* sd = SectionManager::getInstance().getCurrent();
		if(sd){
			st.symbolDeclare(i, true, false, sd);
		} else {
			sd = SectionManager::getInstance().getSectionByName("ABS");
			if(sd){
				st.symbolDeclare(i, true, false, sd);
			} else {
				throw new AssemblerException("Missing ABS section!");
			}
			
		}
	}
}

void Global::pass2() {

}

void Global::print(std::ostream& out) const {
	out << ".global ";
	print_list(sym_list, out);
	out << std::endl;
}
