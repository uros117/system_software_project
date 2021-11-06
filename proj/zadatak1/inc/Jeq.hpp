#ifndef __Jeq_HPP__
#define __Jeq_HPP__
#include "Instr.hpp"

class Jeq : public Instr {
	public:
		Jeq(unsigned int number, Argument* a1);
		Jeq(const Jeq&) = delete;
		Jeq(Jeq&&) = delete;
		virtual ~Jeq();

		void pass1() override;
		void pass2() override;
};

#endif
