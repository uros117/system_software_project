#ifndef __Jne_HPP__
#define __Jne_HPP__
#include "Instr.hpp"

class Jne : public Instr {
	public:
		Jne(unsigned int number, Argument* a1);
		Jne(const Jne&) = delete;
		Jne(Jne&&) = delete;
		virtual ~Jne();

		void pass1() override;
		void pass2() override;
};

#endif
