#ifndef __Add_HPP__
#define __Add_HPP__
#include "Instr.hpp"

class Add : public Instr {
	public:
		Add(unsigned int number, Argument* a1, Argument* a2);
		Add(const Add&) = delete;
		Add(Add&&) = delete;
		virtual ~Add();

		void pass1() override;
		void pass2() override;
};

#endif
