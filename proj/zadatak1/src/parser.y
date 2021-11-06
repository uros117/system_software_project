%{
	#include <iostream>
	#include <string>
	#include <list>

	#include "util.hpp"
	#include "Line.hpp"
	#include "Instr.hpp"
	#include "Argument.hpp"

	#include "Halt.hpp"
	#include "Int.hpp"
	#include "Iret.hpp"
	#include "Call.hpp"
	#include "Ret.hpp"
	#include "Jmp.hpp"
	#include "Jeq.hpp"
	#include "Jne.hpp"
	#include "Jgt.hpp"
	#include "Push.hpp"
	#include "Pop.hpp"
	#include "Xchg.hpp"
	#include "Add.hpp"
	#include "Sub.hpp"
	#include "Mul.hpp"
	#include "Div.hpp"
	#include "Cmp.hpp"
	#include "Not.hpp"
	#include "And.hpp"
	#include "Or.hpp"
	#include "Xor.hpp"
	#include "Test.hpp"
	#include "Shl.hpp"
	#include "Shr.hpp"
	#include "Ldr.hpp"
	#include "Str.hpp"

	#include "Global.hpp"
	#include "Extern.hpp"
	#include "Section.hpp"
	#include "Word.hpp"
	#include "Skip.hpp"
	#include "Equ.hpp"
	#include "End.hpp"

	#include "Sym_lit.hpp"
	
	#include "Label.hpp"

	extern FILE *yyin;
	int yylex(void);
	void yyerror(FILE* fp, const char* msg);
	extern std::list<Line*> line_list;
	extern int yylineno;
%}

%locations

%parse-param { FILE* fp }

%union {
	int num;
	char* ident;
	Argument *arg;
	std::list<std::string>* symbs;
	std::list<Sym_lit>* sym_lits;
}

%token TOKEN_LPAR
%token TOKEN_RPAR
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_SEMI
%token TOKEN_COL
%token TOKEN_COMMA
%token TOKEN_DOT
%token TOKEN_LBRA
%token TOKEN_RBRA
%token TOKEN_PERC
%token TOKEN_ASTE
%token TOKEN_DOLL
%token TOKEN_NL

%token TOKEN_HALT
%token TOKEN_INT
%token TOKEN_IRET
%token TOKEN_CALL
%token TOKEN_RET
%token TOKEN_JMP
%token TOKEN_JEQ
%token TOKEN_JNE
%token TOKEN_JGT
%token TOKEN_PUSH
%token TOKEN_POP
%token TOKEN_XCHG
%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_CMP
%token TOKEN_NOT
%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_XOR
%token TOKEN_TEST
%token TOKEN_SHL
%token TOKEN_SHR
%token TOKEN_LDR
%token TOKEN_STR

%token TOKEN_GLOBAL
%token TOKEN_EXTERN
%token TOKEN_SECTION
%token TOKEN_WORD
%token TOKEN_SKIP
%token TOKEN_EQU
%token TOKEN_END

%token <num> TOKEN_NUM
%token <ident> TOKEN_REG
%token <ident> TOKEN_IDENT

%type <arg> arg;
%type <arg> reg_arg;
%type <symbs> sym_list;
%type <sym_lits> sym_lit_list;

%start prog

%define parse.error verbose

%%

prog
	: 
	| instr
	| direc
	| label
	| instr TOKEN_NL prog
	| direc TOKEN_NL prog
	| label TOKEN_NL prog
	| TOKEN_NL prog
	;

direc	: TOKEN_DOT TOKEN_GLOBAL sym_list[list]
      		{
			line_list.push_back(new Global(yylineno, $list));
		}
	| TOKEN_DOT TOKEN_EXTERN sym_list[list]
		{
			line_list.push_back(new Extern(yylineno, $list));
		}
	| TOKEN_DOT TOKEN_SECTION TOKEN_IDENT[section]
		{
			line_list.push_back(new Section(yylineno, $section));
		}
	| TOKEN_DOT TOKEN_WORD sym_lit_list[list]
		{
			line_list.push_back(new Word(yylineno, $list));
		}
	| TOKEN_DOT TOKEN_SKIP TOKEN_NUM[num]
		{
			line_list.push_back(new Skip(yylineno, $num));
		}
	| TOKEN_DOT TOKEN_EQU TOKEN_IDENT[name] TOKEN_COMMA TOKEN_NUM[num]
		{
			line_list.push_back(new Equ(yylineno, $name, $num));
			free($name);
		}
	| TOKEN_DOT TOKEN_END
		{
			line_list.push_back(new End(yylineno));
		}
	;

label	: TOKEN_IDENT[name] TOKEN_COL
      		{
			line_list.push_back(new Label(yylineno, $name));
			free($name);
		}
	;

instr	: TOKEN_HALT
		{
			line_list.push_back(new Halt(yylineno));
		}
	| TOKEN_INT reg_arg[a1]
		{
			line_list.push_back(new Int(yylineno, $a1)); 
		}
	| TOKEN_IRET
		{
			line_list.push_back(new Iret(yylineno));
		}
	| TOKEN_CALL arg[a1]
		{
			line_list.push_back(new Call(yylineno, $a1));
		}
	| TOKEN_RET
		{
			line_list.push_back(new Ret(yylineno));
		}
	| TOKEN_JMP arg[a1]
		{
			line_list.push_back(new Jmp(yylineno, $a1));
		}
	| TOKEN_JEQ arg[a1]
		{
			line_list.push_back(new Jeq(yylineno, $a1));
		}
	| TOKEN_JNE arg[a1]
		{
			line_list.push_back(new Jne(yylineno, $a1));
		}
	| TOKEN_JGT arg[a1]
		{
			line_list.push_back(new Jgt(yylineno, $a1));
		}
	| TOKEN_PUSH reg_arg[a1]
		{
			line_list.push_back(new Push(yylineno, $a1));
		}
	| TOKEN_POP reg_arg[a1]
		{
			line_list.push_back(new Pop(yylineno, $a1));
		}
	| TOKEN_XCHG reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Xchg(yylineno, $a1, $a2));
		}
	| TOKEN_ADD reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Add(yylineno, $a1, $a2));
		}
	| TOKEN_SUB reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Sub(yylineno, $a1, $a2));
		}
	| TOKEN_MUL reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Mul(yylineno, $a1, $a2));
		}
	| TOKEN_DIV reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Div(yylineno, $a1, $a2));
		}
	| TOKEN_CMP reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Cmp(yylineno, $a1, $a2));
		}
	| TOKEN_NOT reg_arg[a1]
		{
			line_list.push_back(new Not(yylineno, $a1));
		}
	| TOKEN_AND reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new And(yylineno, $a1, $a2));
		}
	| TOKEN_OR reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Or(yylineno, $a1, $a2));
		}
	| TOKEN_XOR reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Xor(yylineno, $a1, $a2));
		}
	| TOKEN_TEST reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Test(yylineno, $a1, $a2));
		}
	| TOKEN_SHL reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Shl(yylineno, $a1, $a2));
		}
	| TOKEN_SHR reg_arg[a1] TOKEN_COMMA reg_arg[a2]
		{
			line_list.push_back(new Shr(yylineno, $a1, $a2));
		}
	| TOKEN_LDR reg_arg[a1] TOKEN_COMMA arg[a2]
		{
			line_list.push_back(new Ldr(yylineno, $a1, $a2));
		}
	| TOKEN_STR reg_arg[a1] TOKEN_COMMA arg[a2]
		{
			line_list.push_back(new Str(yylineno, $a1, $a2));
		}
	;

sym_list: TOKEN_IDENT[name]
		{
			std::list<std::string>* temp = new std::list<std::string>();
			temp->push_front($name);
			free($name);
			$$ = temp;
		}
	| TOKEN_IDENT[name] TOKEN_COMMA sym_list
		{
			std::list<std::string>* temp = $3;
			temp->push_front($name);
			free($name);
			$$ = temp;
		}
	;

sym_lit_list	: TOKEN_NUM[num]
			{
				Sym_lit t($num);
				std::list<Sym_lit>* temp = new std::list<Sym_lit>();
				temp->push_front(t);
				$$ = temp;
			}
	     	| TOKEN_IDENT[sym]
			{
				std::list<Sym_lit>* temp = new std::list<Sym_lit>();
				temp->push_front(Sym_lit($sym));
				free($sym);
				$$ = temp;
			}
		| TOKEN_NUM[num] TOKEN_COMMA sym_lit_list[list]
			{
				Sym_lit t($num);
				std::list<Sym_lit>* temp = $list;
				temp->push_front(t);
				$$ = temp;
			}
		| TOKEN_IDENT[sym] TOKEN_COMMA sym_lit_list[list]
			{
				Sym_lit t($sym);
				std::list<Sym_lit>* temp = $list;
				temp->push_front(t);
				free($sym);
				$$ = temp;
			}
		;

arg
	: TOKEN_NUM
		{
			$$ = new Argument(0, "", $1, "");
		}
	| TOKEN_IDENT 
		{
			$$ = new Argument(1, "", 0, $1);
			free($1);
		}
	| TOKEN_DOLL TOKEN_NUM
		{
			$$ = new Argument(2, "", $2, "");
		}
	| TOKEN_DOLL TOKEN_IDENT
		{
			$$ = new Argument(3, "", 0, $2);
			free($2);
		}
	| TOKEN_PERC TOKEN_IDENT
		{
			$$ = new Argument(4, "", 0, $2);
			free($2);
		}
	| reg_arg
		{
			$$ = $1;
		}
	| TOKEN_LBRA TOKEN_REG TOKEN_RBRA
		{
			$$ = new Argument(6, $2, 0, "");
			free($2);
		}
	| TOKEN_LBRA TOKEN_REG TOKEN_PLUS TOKEN_NUM TOKEN_RBRA
		{
			$$ = new Argument(7, $2, $4, "");
			free($2);
		}
	| TOKEN_LBRA TOKEN_REG TOKEN_PLUS TOKEN_IDENT TOKEN_RBRA
		{
			$$ = new Argument(8, $2, 0, $4);
			free($4);
		}
	| TOKEN_ASTE TOKEN_NUM
		{
			$$ = new Argument(9, "", $2, "");
		}
	| TOKEN_ASTE TOKEN_IDENT
		{
			$$ = new Argument(10, "", 0, $2);
			free($2);
		}
	| TOKEN_ASTE TOKEN_REG
		{
			$$ = new Argument(11, $2, 0, "");
			free($2);
		}
	| TOKEN_ASTE TOKEN_LBRA TOKEN_REG TOKEN_RBRA
		{
			$$ = new Argument(12, $3, 0, "");
			free($3);
		}
	| TOKEN_ASTE TOKEN_LBRA TOKEN_REG TOKEN_PLUS TOKEN_NUM TOKEN_RBRA
		{
			$$ = new Argument(13, $3, $5, "");
			free($3);
		}
	| TOKEN_ASTE TOKEN_LBRA TOKEN_REG TOKEN_PLUS TOKEN_IDENT TOKEN_RBRA
		{
			$$ = new Argument(14, $3, 0, $5);
			free($3);
			free($5);
		}
	;

reg_arg	: TOKEN_REG
		{
			$$ = new Argument(5, $1, 0, "");
			free($1);
		}
	;

/*
rname
	: TOKEN_IDENT
	{
		if (!is_register($1)) {
			fprintf(stderr, "bad register name: %s\n", $1);
			return 0;
		}
		$$ = $1;
	}
  ;
*/

%%
