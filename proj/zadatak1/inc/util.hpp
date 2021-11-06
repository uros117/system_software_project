#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#define MAX_LEN 32

#include <iostream>
#include <list>
#include <string>
#include <iterator>

// literal is always a number
// symbol is always a string 
// reg is always a astring

// <literal>		0
// <symbol>		1
// $<literal>		2
// $<symbol>		3
// %<symbol>		4
// <reg>		5
// [<reg>]		6
// [<reg> + <literal>]	7
// [<reg> + <symbol>]	8
//
// *<literal>		9
// *<symbol>		10
// *<reg>		11
// *[<reg>]		12
// *[<reg> + <literal>]	13
// *[<reg> + <symbol>]	14

struct arg {
	char type;
	char *reg;
	int literal;
	char *symbol;

	struct arg *next;
};

struct instr {
	char         *name;
	struct arg   *args;
	struct instr *prev;
};

//struct instr *global_prev;

void error_handler(std::string);

int is_register(const char*);
char* copy_str(const char*);

struct arg* mk_argument(char, char*, int, char*);
struct instr* mk_instruction(char*, struct arg*);

void print_instrs(const struct instr *);
void free_instrs(struct instr*);

template<typename T> void print_list(const std::list<T>* l, std::ostream& out ) {
	bool first = true;
	for(auto i : *l) {
		if(first == true) {
			first = false;
		} else {
			out << ", ";
		}
		out << i; 
	}
}

#endif
