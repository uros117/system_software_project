#ifndef __Xchg_HPP__
#define __Xchg_HPP__
#include "Instr.hpp"

class Xchg : public Instr {
	public:
		Xchg(unsigned int number, Argument* a1, Argument* a2);
		Xchg(const Xchg&) = delete;
		Xchg(Xchg&&) = delete;
		virtual ~Xchg();

		void pass1() override;
		void pass2() override;
};

#endif
