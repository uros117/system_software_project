#ifndef __Jgt_HPP__
#define __Jgt_HPP__
#include "Instr.hpp"

class Jgt : public Instr {
	public:
		Jgt(unsigned int number, Argument* a1);
		Jgt(const Jgt&) = delete;
		Jgt(Jgt&&) = delete;
		virtual ~Jgt();

		void pass1() override;
		void pass2() override;
};

#endif
