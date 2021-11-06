#ifndef __Ldr_HPP__
#define __Ldr_HPP__
#include "Instr.hpp"

class Ldr : public Instr {
	public:
		Ldr(unsigned int number, Argument* a1, Argument* a2);
		Ldr(const Ldr&) = delete;
		Ldr(Ldr&&) = delete;
		virtual ~Ldr();

		void pass1() override;
		void pass2() override;
};

#endif
