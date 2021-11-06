#ifndef __Str_HPP__
#define __Str_HPP__
#include "Instr.hpp"

class Str : public Instr {
	public:
		Str(unsigned int number, Argument* a1, Argument* a2);
		Str(const Str&) = delete;
		Str(Str&&) = delete;
		virtual ~Str();

		void pass1() override;
		void pass2() override;
};

#endif
