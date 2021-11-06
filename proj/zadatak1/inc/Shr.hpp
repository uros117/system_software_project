#ifndef __Shr_HPP__
#define __Shr_HPP__
#include "Instr.hpp"

class Shr : public Instr {
	public:
		Shr(unsigned int number, Argument* a1, Argument* a2);
		Shr(const Shr&) = delete;
		Shr(Shr&&) = delete;
		virtual ~Shr();

		void pass1() override;
		void pass2() override;
};

#endif
