#ifndef __Not_HPP__
#define __Not_HPP__
#include "Instr.hpp"

class Not : public Instr {
	public:
		Not(unsigned int number, Argument* a1);
		Not(const Not&) = delete;
		Not(Not&&) = delete;
		virtual ~Not();

		void pass1() override;
		void pass2() override;
};

#endif
