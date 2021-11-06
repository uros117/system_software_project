#ifndef __Word_HPP__
#define __Word_HPP__
#include <list>
#include <string>
#include "Directive.hpp"
#include "Sym_lit.hpp"

class Word : public Directive {
	std::list<Sym_lit>* sym_list;
	public:
		Word(unsigned int number, std::list<Sym_lit>* sym_list);
		Word(const Word&) = delete;
		Word(Word&&) = delete;
		virtual ~Word();

		void pass1() override;
		void pass2() override;

		void print(std::ostream& out) const override;
};

#endif
