#ifndef __LINE_HPP__
#define __LINE_HPP__
#include <iostream>

class Line {
	public:
		Line(unsigned int number);
		Line(unsigned int number, unsigned int size);
		Line(const Line&) = delete;
		Line(Line&&) = delete;
		virtual ~Line();

		virtual void pass1() = 0;
		virtual void pass2() = 0;
		
		unsigned int getNumber() const {
			return number;
		}
		unsigned int setNumber(unsigned int number) {
			this->number = number;
		}
		
		unsigned int getSize() const {
			return size;
		}
		unsigned int setSize(unsigned int size) {
			this->size = size;
		}

		virtual void print(std::ostream& out) const = 0;

		friend std::ostream& operator<<(std::ostream& out, const Line& line);
	private:
		unsigned int number;
		unsigned int size;

};

#endif
