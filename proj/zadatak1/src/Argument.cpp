#include <iostream>
#include "Argument.hpp"

Argument::Argument(unsigned char type, std::string reg, int literal, std::string symbol) {
	this->type = type;
	this->reg = reg;
	this->literal = literal;
	this->symbol = symbol;
}

Argument::~Argument() {

}

std::ostream& operator<<(std::ostream& out, const Argument& obj) {
	switch (obj.type) {
		case 9:	out << "*";
		case 0:
			out << std::hex << obj.literal;
			break;
		case 10: out << "*";
		case 1:
			out << obj.symbol;
			break;
		case 2:
			out << "$" << std::hex << obj.literal;
			break;
		case 3:
			out << "$" << obj.symbol;
			break;
		case 4:
			out << "%" << obj.symbol;
			break;
		case 11:	out << "*";
		case 5:
			out << obj.reg;
			break;
		case 12:	out << "*";
		case 6:
			out << "[" << obj.reg << "]";
			break;
		case 13:	out << "*";
		case 7:
			out << "[" << obj.reg << " + " << std::hex << obj.literal << "]";
			break;
		case 14:	out << "*";
		case 8:
			out << "[" << obj.reg << " + " << obj.symbol << "]";
			break;
		default:
			break;
	}
	return out;
}
