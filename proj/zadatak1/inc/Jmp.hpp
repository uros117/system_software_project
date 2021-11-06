#ifndef __Jmp_HPP__
#define __Jmp_HPP__
#include "Instr.hpp"

class Jmp : public Instr {
	public:
		Jmp(unsigned int number, Argument* a1);
		Jmp(const Jmp&) = delete;
		Jmp(Jmp&&) = delete;
		virtual ~Jmp();

		void pass1() override;
		void pass2() override;
};

#endif
