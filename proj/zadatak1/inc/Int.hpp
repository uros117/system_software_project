#ifndef __Int_HPP__
#define __Int_HPP__
#include "Instr.hpp"

class Int : public Instr {
	public:
		Int(unsigned int number, Argument* a1);
		Int(const Int&) = delete;
		Int(Int&&) = delete;
		virtual ~Int();

		void pass1() override;
		void pass2() override;
};

#endif
