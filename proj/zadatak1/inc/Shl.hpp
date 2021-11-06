#ifndef __Shl_HPP__
#define __Shl_HPP__
#include "Instr.hpp"

class Shl : public Instr {
	public:
		Shl(unsigned int number, Argument* a1, Argument* a2);
		Shl(const Shl&) = delete;
		Shl(Shl&&) = delete;
		virtual ~Shl();

		void pass1() override;
		void pass2() override;
};

#endif
