#ifndef __Call_HPP__
#define __Call_HPP__
#include "Instr.hpp"

class Call : public Instr {
	public:
		Call(unsigned int number, Argument* a1);
		Call(const Call&) = delete;
		Call(Call&&) = delete;
		virtual ~Call();

		void pass1() override;
		void pass2() override;
};

#endif
