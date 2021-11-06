#ifndef __Halt_HPP__
#define __Halt_HPP__
#include "Instr.hpp"

class Halt : public Instr {
	public:
		Halt(unsigned int number);
		Halt(const Halt&) = delete;
		Halt(Halt&&) = delete;
		virtual ~Halt();

		void pass1() override;
		void pass2() override;
};

#endif
