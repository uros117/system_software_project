#include <iostream>
#include "Line.hpp"


Line::Line(unsigned int number) : number(number), size(0) {
	
}

Line::Line(unsigned int number, unsigned int size) : number(number), size(size) {
}

Line::~Line() {

}

std::ostream& operator<<(std::ostream& out, const Line& line) {
	line.print(out);
	return out;
}
