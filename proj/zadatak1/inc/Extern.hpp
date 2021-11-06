#ifndef __Extern_HPP__
#define __Extern_HPP__
#include <list>
#include <string>
#include "Directive.hpp"

class Extern : public Directive {
	std::list<std::string>* sym_list;
	public:
		Extern(unsigned int number, std::list<std::string>* sym_list);
		Extern(const Extern&) = delete;
		Extern(Extern&&) = delete;
		virtual ~Extern();

		void pass1() override;
		void pass2() override;

		void print(std::ostream& out) const override;
};

#endif
