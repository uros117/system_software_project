#ifndef __Pop_HPP__
#define __Pop_HPP__
#include "Instr.hpp"

class Pop : public Instr {
	public:
		Pop(unsigned int number, Argument* a1);
		Pop(const Pop&) = delete;
		Pop(Pop&&) = delete;
		virtual ~Pop();

		void pass1() override;
		void pass2() override;
};

#endif
