#include <string>
#include "Sym_lit.hpp"
#include <iostream>

Sym_lit::Sym_lit(std::string sym) : isSym(true), lit(0), sym(sym) {
}

Sym_lit::Sym_lit(int lit) : isSym(false), lit(lit), sym("") {
}
	
std::ostream& operator<<(std::ostream& out, const Sym_lit& obj) {
	if(obj.isSym) {
		out << obj.sym;
	} else {
		out << obj.lit;
	}
	return out;
}
