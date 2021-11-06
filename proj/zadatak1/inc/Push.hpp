#ifndef __Push_HPP__
#define __Push_HPP__
#include "Instr.hpp"

class Push : public Instr {
	public:
		Push(unsigned int number, Argument* a1);
		Push(const Push&) = delete;
		Push(Push&&) = delete;
		virtual ~Push();

		void pass1() override;
		void pass2() override;
};

#endif
