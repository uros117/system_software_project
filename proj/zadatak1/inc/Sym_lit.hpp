#ifndef __Sym_lib_HPP__
#define __Sym_lib_HPP__
#include <string>

class Sym_lit {
	std::string sym;
	int lit;
	bool isSym;
public:
	Sym_lit(std::string sym);
	Sym_lit(int lit);
	void setSym(const std::string sym) {
		if(isSym)
			this->sym = sym;
	}
	std::string getSym() const {
		return sym;
	}
	void setLit(const int lit) {
		if(!isSym)
			this->lit = lit;
	}
	int getLit() const {
		return lit;
	}
	void setIsSym(const bool isSym) {
		this->isSym = isSym;
	}
	bool getIsSym() const {
		return isSym;
	}

	friend std::ostream& operator<<(std::ostream& out, const Sym_lit& obj);
};

#endif
