#include "util.hpp"
#include "Argument.hpp"
#include "Sym_lit.hpp"
#include "Line.hpp"
#include "AssemblerException.hpp"
#include "SectionManager.hpp"
#include "SymbolTable.hpp"
#include <stdio.h>
#include <list>
#include <iterator>
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>
#include <fstream>

extern struct instr *global_prev;
extern FILE* yyin;
std::list<Line*> line_list;
long currentLine = -1;

int
main(int argc, char* argv[])
{
	std::string file_in;
	std::string file_out;
	printf("\033[1;33mOutput:\033[0m");
	if((std::string)argv[1] == "-o") {
		file_out = argv[2];
		file_in = argv[3];
		std::cout << file_in << std::endl;
	} else {
		file_in = argv[1];
		file_out = file_in;
		std::string::size_type pos = 0u;
		std::string oldStr = ".s";
		std::string newStr = ".o";
		if((pos = file_out.find(oldStr, pos)) != std::string::npos){
			file_out.replace(pos, oldStr.length(), newStr);
			pos += newStr.length();
			std::cout << file_out << std::endl;
		} else {
			std::cout << "\033[0;31mFailed to generate output file name!\033[0m" << std::endl;
			return -1;
		}
	}

	printf("\033[1;33mAsembler\033[0m\n");
	
	if(argc < 2) {
		printf("Not enought parameters.\n");
		return -1;
	}

	yyin = fopen(file_in.c_str(),"r");
	if (yyin == NULL) {
		printf("Error opening file.\n");
		return -2;
	}

	global_prev = NULL;

	if (yyparse(yyin))
		return 1;
	
	printf("\033[1;33mBEGIN Code\033[0m\n");
	for( Line* i : line_list ) {
		std::cout << *i;
	}
	printf("\033[1;33mEND Code\033[0m\n");
	
	bool isError = false;
	try {
		currentLine = -1;
		for( Line* i : line_list ) {
			currentLine = i->getNumber();
			i->pass1();
			SectionManager::getInstance().getCurrent()->incLocationCounter(i->getSize());
		}
		currentLine = -1;

		printf("\033[1;33mBEGIN Pass 1 info\033[0m\n");
		std::cout << SymbolTable::getInstance();
		std::cout << SectionManager::getInstance();
		printf("\033[1;33mEND Pass 1 info\033[0m\n");

		SectionManager::getInstance().resetLocationCounters();

		for( Line* i : line_list ) {
			currentLine = i->getNumber();
			i->pass2();
			SectionManager::getInstance().getCurrent()->incLocationCounter(i->getSize());
		}
		currentLine = -1;

		printf("\033[1;33mBEGIN Pass 2 info\033[0m\n");
		std::cout << SymbolTable::getInstance();
		std::cout << SectionManager::getInstance();
		printf("\033[1;33mEND Pass 2 info\033[0m\n");
	} catch (AssemblerException* e) {
		isError = true;
		std::cout << "\033[0;31mError occured!" << std::endl;
		if(currentLine != -1) {
			std::cout << "on line : " << std::dec << currentLine << std::hex << std::endl;
		}
		std::cout << e->what() << "\033[0m" << std::endl;
		delete e;
	}

	if(!isError) {
		std::ofstream of;
		of.open(file_out);

		if (of.is_open()) { 
			of << std::hex;
			of << SymbolTable::getInstance();
			of << SectionManager::getInstance();
			of.flush();
			of.close();
		} else {
			std::cout << "\033[0;31mError cannot open output file!\033[0m" << std::endl;
		}
	}
	
	// Clean up
	for( Line* i : line_list ) {
		delete i;
	}

	fclose(yyin);
	
	return 0;
}
