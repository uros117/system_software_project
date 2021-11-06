#ifndef __Cmp_HPP__
#define __Cmp_HPP__
#include "Instr.hpp"

class Cmp : public Instr {
	public:
		Cmp(unsigned int number, Argument* a1, Argument* a2);
		Cmp(const Cmp&) = delete;
		Cmp(Cmp&&) = delete;
		virtual ~Cmp();

		void pass1() override;
		void pass2() override;
};

#endif
