#ifndef __Div_HPP__
#define __Div_HPP__
#include "Instr.hpp"

class Div : public Instr {
	public:
		Div(unsigned int number, Argument* a1, Argument* a2);
		Div(const Div&) = delete;
		Div(Div&&) = delete;
		virtual ~Div();

		void pass1() override;
		void pass2() override;
};

#endif
