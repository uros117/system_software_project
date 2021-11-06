#ifndef __Argument_HPP__
#define __Argument_HPP__
#include <string>

#define UPDATE_NONE                 (0x00)
#define UPDATE_PRE_DEC              (0x10)
#define UPDATE_PRE_INC              (0x20)
#define UPDATE_POST_DEC             (0x30)
#define UPDATE_POST_INC             (0x40)

#define ADDR_MODE_IMMED             (0x00)
#define ADDR_MODE_REGDIR            (0x01)
#define ADDR_MODE_REGDIR_PAYLOAD    (0x05)
#define ADDR_MODE_REGINDIR          (0x02)
#define ADDR_MODE_REGINDIR_PAYLOAD  (0x03)
#define ADDR_MODE_MEM               (0x04)

// <literal>			0
// <symbol>				1
// $<literal>			2
// $<symbol>			3
// %<symbol>			4
// <reg>				5
// [<reg>]				6
// [<reg> + <literal>]	7
// [<reg> + <symbol>]	8
//
// *<literal>			9
// *<symbol>			10
// *<reg>				11
// *[<reg>]				12
// *[<reg> + <literal>]	13
// *[<reg> + <symbol>]	14

class Argument {
	unsigned char type;
	std::string reg;
	int literal;
	std::string symbol;

	public:
		Argument(unsigned char type, std::string reg, int literal, std::string symbol);
		Argument(unsigned char type, std::string reg) : Argument(type, reg, 0, "") {};
		Argument(unsigned char type, int literal) : Argument(type, "", literal, "") {};
		Argument(unsigned char type, std::string reg, int literal) : Argument(type, reg, literal, "") {};
		Argument(unsigned char type, std::string reg, std::string symbol) : Argument( type, reg, 0, symbol) {};
		Argument(const Argument&) = delete;
		Argument(Argument&&) = delete;
		~Argument();

		int instrLength() {
			switch (this->type)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 7:
			case 8:
			case 9:
			case 10:
			case 13:
			case 14:
				return 5;
			default:
				return 3;
			}
		}

		int getRegNum() {
			if(reg == "pc")
				return 7;
			else if(reg == "psw")
				return 8;
			else if(reg == "sp")
				return 6;
			else if(reg == "r0")
				return 0;
			else if(reg == "r1")
				return 1;
			else if(reg == "r2")
				return 2;
			else if(reg == "r3")
				return 3;
			else if(reg == "r4")
				return 4;
			else if(reg == "r5")
				return 5;
			else if(reg == "r6")
				return 6;
			else if(reg == "r7")
				return 7;
			return -1;
		}

		unsigned char getType() const {
			return type;
		}
		void setType(unsigned char type) {
			this->type = type;
		}

		std::string getReg() const {
			return reg;
		}
		void setReg(std::string reg) {
			this->reg = reg;
		}

		int getLiteral() const {
			return literal;
		}
		void setLiteral(int literal) {
			this->literal = literal;
		}

		std::string getSymbol() const {
			return symbol;
		}
		void setSymbol(std::string symbol) {
			this->symbol = symbol;
		}

		friend std::ostream& operator<<(std::ostream& out, const Argument& obj);
};

#endif
