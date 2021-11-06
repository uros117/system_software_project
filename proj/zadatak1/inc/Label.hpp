#ifndef __Label_HPP__
#define __Label_HPP__
#include <string>
#include <iostream>
#include "Line.hpp"

class Label : public Line {
	std::string name;
	public:
		Label(unsigned int number, std::string name);
		Label(const Label&) = delete;
		Label(Label&&) = delete;
		virtual ~Label();

		void pass1() override;
		void pass2() override;

		void setName(std::string name) {
			this->name = name;
		}
		std::string getName() const {
			return name;
		}
		
		void print(std::ostream& out) const override;
};

#endif
