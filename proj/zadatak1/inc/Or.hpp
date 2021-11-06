#ifndef __Or_HPP__
#define __Or_HPP__
#include "Instr.hpp"

class Or : public Instr {
	public:
		Or(unsigned int number, Argument* a1, Argument* a2);
		Or(const Or&) = delete;
		Or(Or&&) = delete;
		virtual ~Or();

		void pass1() override;
		void pass2() override;
};

#endif
