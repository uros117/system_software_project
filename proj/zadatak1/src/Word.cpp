#include "Word.hpp"
#include "Sym_lit.hpp"
#include "util.hpp"
#include "SectionManager.hpp"
#include "SymbolData.hpp"
#include "SymbolTable.hpp"
#include "AssemblerException.hpp"
#include "RelData.hpp"
#include "RelTable.hpp"

Word::Word(unsigned int number, std::list<Sym_lit>* sym_list) : Directive(number), sym_list(nullptr) {
	if(sym_list == nullptr) {
		// Error
	}
	this->sym_list = sym_list;
}

Word::~Word() {
	if(sym_list)
		delete sym_list;
}

void Word::pass1() {
	SectionManager::getInstance().getCurrent()->incLocationCounter(sym_list->size() * 2);
}

void Word::pass2() {
	for(Sym_lit& elem : *sym_list) {
		if(elem.getIsSym()) {
			SymbolTable& st = SymbolTable::getInstance();
			SymbolData* syd = st.getSymbolByName(elem.getSym());
			SectionManager& sm = SectionManager::getInstance();
			SectionData* sd = sm.getCurrent();
			if(syd) {
				sd->getRelTable().append(sd->getLocationCounter(), 3, elem.getSym(), 0);
				if(syd->getHasValue()) {
					uint16_t temp = (uint16_t)syd->getOffset();
					unsigned char tl = ((unsigned char*)&temp)[0];
					unsigned char th = ((unsigned char*)&temp)[1];
					SectionManager::getInstance().getCurrent()->appendData(th);
					SectionManager::getInstance().getCurrent()->appendData(tl);
				} else {
					SectionManager::getInstance().getCurrent()->appendData(0);
					SectionManager::getInstance().getCurrent()->appendData(0);
				}
			} else throw new AssemblerException("Missing symbol: " + elem.getSym());
		} else {
			uint16_t temp = (uint16_t)elem.getLit();
			unsigned char tl = ((unsigned char*)&temp)[0];
    		unsigned char th = ((unsigned char*)&temp)[1];
			SectionManager::getInstance().getCurrent()->appendData(th);
			SectionManager::getInstance().getCurrent()->appendData(tl);
		}
		
	}
	SectionManager::getInstance().getCurrent()->incLocationCounter(sym_list->size() * 2);
}

void Word::print(std::ostream& out) const {
	out << ".word ";
	print_list(sym_list, out);
	out << std::endl;
}
