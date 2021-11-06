#ifndef __Test_HPP__
#define __Test_HPP__
#include "Instr.hpp"

class Test : public Instr {
	public:
		Test(unsigned int number, Argument* a1, Argument* a2);
		Test(const Test&) = delete;
		Test(Test&&) = delete;
		virtual ~Test();

		void pass1() override;
		void pass2() override;
};

#endif
