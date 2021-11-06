#ifndef __And_HPP__
#define __And_HPP__
#include "Instr.hpp"

class And : public Instr {
	public:
		And(unsigned int number, Argument* a1, Argument* a2);
		And(const And&) = delete;
		And(And&&) = delete;
		virtual ~And();

		void pass1() override;
		void pass2() override;
};

#endif
