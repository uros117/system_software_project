#ifndef __Sub_HPP__
#define __Sub_HPP__
#include "Instr.hpp"

class Sub : public Instr {
	public:
		Sub(unsigned int number, Argument* a1, Argument* a2);
		Sub(const Sub&) = delete;
		Sub(Sub&&) = delete;
		virtual ~Sub();

		void pass1() override;
		void pass2() override;
};

#endif
