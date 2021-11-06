#ifndef __Skip_HPP__
#define __Skip_HPP__
#include <list>
#include <string>
#include "Directive.hpp"

class Skip : public Directive {
	int literal;
	public:
		Skip(unsigned int number, int literal);
		Skip(const Skip&) = delete;
		Skip(Skip&&) = delete;
		virtual ~Skip();

		void pass1() override;
		void pass2() override;

		void print(std::ostream& out) const override;
};

#endif
