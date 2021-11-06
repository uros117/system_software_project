#ifndef __Directive_HPP__
#define __Directive_HPP__
#include "Line.hpp"

class Directive : public Line {
	public:
		Directive(unsigned int number);
		Directive(const Directive&) = delete;
		Directive(Directive&&) = delete;
		virtual ~Directive();
};

#endif
