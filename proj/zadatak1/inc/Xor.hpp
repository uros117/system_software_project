#ifndef __Xor_HPP__
#define __Xor_HPP__
#include "Instr.hpp"

class Xor : public Instr {
	public:
		Xor(unsigned int number, Argument* a1, Argument* a2);
		Xor(const Xor&) = delete;
		Xor(Xor&&) = delete;
		virtual ~Xor();

		void pass1() override;
		void pass2() override;
};

#endif
