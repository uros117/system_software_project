#include "End.hpp"
#include "SectionManager.hpp"

End::End(unsigned int number) : Directive(number) {
}

End::~End() {
}

void End::pass1() {
	SectionManager::getInstance().endSection();
}

void End::pass2() {
	SectionManager::getInstance().endSection();
}

void End::print(std::ostream& out) const {
	out << ".end" << std::endl;
}
