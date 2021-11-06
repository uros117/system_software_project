#include "Skip.hpp"
#include "SectionManager.hpp"

Skip::Skip(unsigned int number, int literal) : Directive(number), literal(0) {
	this->literal = literal;
}

Skip::~Skip() {
}

void Skip::pass1() {
	SectionManager::getInstance().getCurrent()->incLocationCounter(literal);
}

void Skip::pass2() {
	for(int i = 0; i < literal; i++) {
		SectionManager::getInstance().getCurrent()->appendData(0);
	}
	SectionManager::getInstance().getCurrent()->incLocationCounter(literal);
}

void Skip::print(std::ostream& out) const {
	out << ".skip " << literal << std::endl;
}
