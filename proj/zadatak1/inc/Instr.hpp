#ifndef __Instr_HPP__
#define __Instr_HPP__
#include "Line.hpp"
#include "Argument.hpp"
#include <iostream>
#include <string>
class Instr : public Line{
	std::string name;
	Argument* a1;
	Argument* a2;
	public:
		Instr(unsigned int number, unsigned int size, std::string name, Argument* a1, Argument* a2);
		Instr(const Instr&) = delete;
		Instr(Instr&&) = delete;
		virtual ~Instr();

		virtual void pass1() = 0;
		virtual void pass2() = 0;

		Argument* getA1() {
			return a1;
		}
		Argument* getA2() {
			return a2;
		}

		static void jumpInstrPass2(unsigned char byte1, Instr& i);
		static void regRegInstrPass2(unsigned char byte1, Instr& i);

		void print(std::ostream& out) const override;
};

#endif
