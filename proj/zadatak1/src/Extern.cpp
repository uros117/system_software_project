#include "Extern.hpp"
#include "util.hpp"
#include "SymbolTable.hpp"
#include "SectionManager.hpp"
#include "SectionData.hpp"
#include "AssemblerException.hpp"

Extern::Extern(unsigned int number, std::list<std::string>* sym_list) : Directive(number), sym_list(nullptr) {
	if(sym_list == nullptr) {
		// Error
	}
	this-> sym_list = sym_list;
}

Extern::~Extern() {
	if(sym_list)
		delete sym_list;
}

void Extern::pass1() {
	SymbolTable& st = SymbolTable::getInstance();
	for(std::string i : *this->sym_list) {
		SectionData* sd = SectionManager::getInstance().getSectionByName("UND");
		if(sd){
			st.symbolDeclare(i, true, true, sd);
		} else {
			throw new AssemblerException("Missing UND section!");
		}
	}

}

void Extern::pass2() {

}

void Extern::print(std::ostream& out) const {
	out << ".extern ";
	print_list(sym_list, out);
	out << std::endl;
}
