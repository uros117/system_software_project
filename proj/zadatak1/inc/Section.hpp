#ifndef __Section_HPP__
#define __Section_HPP__
#include <list>
#include <string>
#include "Directive.hpp"

class Section : public Directive {
	std::string name;
	public:
		Section(unsigned int number, std::string name);
		Section(const Section&) = delete;
		Section(Section&&) = delete;
		virtual ~Section();

		void pass1() override;
		void pass2() override;

		void print(std::ostream& out) const override;
};

#endif
