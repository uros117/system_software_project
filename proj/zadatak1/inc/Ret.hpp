#ifndef __Ret_HPP__
#define __Ret_HPP__
#include "Instr.hpp"

class Ret : public Instr {
	public:
		Ret(unsigned int number);
		Ret(const Ret&) = delete;
		Ret(Ret&&) = delete;
		virtual ~Ret();

		void pass1() override;
		void pass2() override;
};

#endif
