#ifndef __Iret_HPP__
#define __Iret_HPP__
#include "Instr.hpp"

class Iret : public Instr {
	public:
		Iret(unsigned int number);
		Iret(const Iret&) = delete;
		Iret(Iret&&) = delete;
		virtual ~Iret();

		void pass1() override;
		void pass2() override;
};

#endif
