#ifndef __Mul_HPP__
#define __Mul_HPP__
#include "Instr.hpp"

class Mul : public Instr {
	public:
		Mul(unsigned int number, Argument* a1, Argument* a2);
		Mul(const Mul&) = delete;
		Mul(Mul&&) = delete;
		virtual ~Mul();

		void pass1() override;
		void pass2() override;
};

#endif
