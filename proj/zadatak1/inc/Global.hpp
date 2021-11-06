#ifndef __Global_HPP__
#define __Global_HPP__
#include <list>
#include <string>
#include <iostream>
#include "Directive.hpp"

class Global : public Directive {
	std::list<std::string>* sym_list;
	public:
		Global(unsigned int number, std::list<std::string>* sym_list);
		Global(const Global&) = delete;
		Global(Global&&) = delete;
		virtual ~Global();

		void pass1() override;
		void pass2() override;

		void print(std::ostream& out) const override;
};

#endif
