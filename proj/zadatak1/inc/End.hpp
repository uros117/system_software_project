#ifndef __End_HPP__
#define __End_HPP__
#include <list>
#include <string>
#include "Directive.hpp"

class End : public Directive {
	public:
		End(unsigned int number);
		End(const End&) = delete;
		End(End&&) = delete;
		virtual ~End();

		void pass1() override;
		void pass2() override;

		void print(std::ostream& out) const override;
};

#endif
