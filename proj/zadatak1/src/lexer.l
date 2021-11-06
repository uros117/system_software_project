%{
	#include <list>
	#include "Argument.hpp"
	#include "Sym_lit.hpp"
	#include "util.hpp"
	#include "parser.hpp"
%}

%option yylineno
%option noyywrap

LPAR "("
RPAR ")"
PLUS "+"
MINUS "-"
SEMI ";"
COL ":"
COMMA ","
DOT "."
LBRA "["
RBRA "]"
PERC "%"
ASTE "*"
DOLL "$"
NL [\r\n]

GLO "global"
EXT "extern"
SEC "section"
WOR "word"
SKI "skip"
EQU "equ"
END "end"

HALT "halt"
INT "int"
IRET "iret"
CALL "call"
RET "ret"
JMP "jmp"
JEQ "jeq"
JNE "jne"
JGT "jgt"
PUSH "push"
POP "pop"
XCHG "xchg"
ADD "add"
SUB "sub"
MUL "mul"
DIV "div"
CMP "cmp"
NOT "not"
AND "and"
OR "or"
XOR "xor"
TEST "test"
SHL "shl"
SHR "shr"
LDR "ldr"
STR "str"

HEX 0[Xx][0-9A-Fa-f]+
DEC [0-9]+
IDENT [A-Za-z_][A-Za-z0-9_]*
COM "#"[^\n\r]*
WS [ \t]*

REG r[0-7]|sp|pc|psw
%%

{WS}	{}
{COM}	{}
{NL}	{ return TOKEN_NL; }
{HEX}	{
		sscanf(yytext, "%x", &yylval.num);
		return TOKEN_NUM;
	}
{DEC}	{
		sscanf(yytext, "%d", &yylval.num);
		return TOKEN_NUM;
	}
{REG}	{
		yylval.ident = copy_str(yytext);
		return TOKEN_REG;
	}
{GLO}	{
		return TOKEN_GLOBAL;
	}
{EXT}	{
		return TOKEN_EXTERN;
	}
{SEC}	{
		return TOKEN_SECTION;
	}
{WOR}	{
		return TOKEN_WORD;
	}
{SKI}	{
		return TOKEN_SKIP;
	}
{EQU}	{
		return TOKEN_EQU;
	}
{END}	{
		return TOKEN_END;
	}
{HALT}	{
		return TOKEN_HALT;
	}
{INT}	{
		return TOKEN_INT;
	}
{IRET}	{
		return TOKEN_IRET;
	}
{CALL}	{
		return TOKEN_CALL;
	}
{RET}	{
		return TOKEN_RET;
	}
{JMP}	{
		return TOKEN_JMP;
	}
{JEQ}	{
		return TOKEN_JEQ;
	}
{JNE}	{
		return TOKEN_JNE;
	}
{JGT}	{
		return TOKEN_JGT;
	}
{PUSH}	{
		return TOKEN_PUSH;
	}
{POP}	{
		return TOKEN_POP;
	}
{XCHG}	{
		return TOKEN_XCHG;
	}
{ADD}	{
		return TOKEN_ADD;
	}
{SUB}	{
		return TOKEN_SUB;
	}
{MUL}	{
		return TOKEN_MUL;
	}
{DIV}	{
		return TOKEN_DIV;
	}
{CMP}	{
		return TOKEN_CMP;
	}
{NOT}	{
		return TOKEN_NOT;
	}
{AND}	{
		return TOKEN_AND;
	}
{OR}	{
		return TOKEN_OR;
	}
{XOR}	{
		return TOKEN_XOR;
	}
{TEST}	{
		return TOKEN_TEST;
	}
{SHL}	{
		return TOKEN_SHL;
	}
{SHR}	{
		return TOKEN_SHR;
	}
{LDR}	{
		return TOKEN_LDR;
	}
{STR}	{
		return TOKEN_STR;
	}
{IDENT}	{
		yylval.ident = copy_str(yytext);
		return TOKEN_IDENT;
	}
{LPAR}	{ return TOKEN_LPAR; }
{RPAR}	{ return TOKEN_RPAR; }
{PLUS}	{ return TOKEN_PLUS; }
{MINUS}	{ return TOKEN_MINUS; }
{SEMI}	{ return TOKEN_SEMI; }
{COL}	{ return TOKEN_COL; }
{COMMA} { return TOKEN_COMMA; }
{DOT}	{ return TOKEN_DOT; }
{LBRA}	{ return TOKEN_LBRA; }
{RBRA}	{ return TOKEN_RBRA; }
{PERC}	{ return TOKEN_PERC; }
{ASTE}	{ return TOKEN_ASTE; }
{DOLL}	{ return TOKEN_DOLL; }

%%
int
yyerror(FILE* fp, const char* msg)
{
    fprintf(stderr, "\033[0;31mError on line: %d\n%s\n\033[0m", yylineno, msg);// there was lexer error in the string
    return 0;
}
