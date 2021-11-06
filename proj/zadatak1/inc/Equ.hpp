#ifndef __Equ_HPP__
#define __Equ_HPP__
#include <list>
#include <string>
#include "Directive.hpp"

class Equ : public Directive {
	std::string name;
	int literal;
	public:
		Equ(unsigned int number, std::string name, int literal);
		Equ(const Equ&) = delete;
		Equ(Equ&&) = delete;
		virtual ~Equ();

		void pass1() override;
		void pass2() override;

		void print(std::ostream& out) const override;
};

#endif
