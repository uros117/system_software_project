/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_INC_PARSER_HPP_INCLUDED
# define YY_YY_INC_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_LPAR = 258,
    TOKEN_RPAR = 259,
    TOKEN_PLUS = 260,
    TOKEN_MINUS = 261,
    TOKEN_SEMI = 262,
    TOKEN_COL = 263,
    TOKEN_COMMA = 264,
    TOKEN_DOT = 265,
    TOKEN_LBRA = 266,
    TOKEN_RBRA = 267,
    TOKEN_PERC = 268,
    TOKEN_ASTE = 269,
    TOKEN_DOLL = 270,
    TOKEN_NL = 271,
    TOKEN_HALT = 272,
    TOKEN_INT = 273,
    TOKEN_IRET = 274,
    TOKEN_CALL = 275,
    TOKEN_RET = 276,
    TOKEN_JMP = 277,
    TOKEN_JEQ = 278,
    TOKEN_JNE = 279,
    TOKEN_JGT = 280,
    TOKEN_PUSH = 281,
    TOKEN_POP = 282,
    TOKEN_XCHG = 283,
    TOKEN_ADD = 284,
    TOKEN_SUB = 285,
    TOKEN_MUL = 286,
    TOKEN_DIV = 287,
    TOKEN_CMP = 288,
    TOKEN_NOT = 289,
    TOKEN_AND = 290,
    TOKEN_OR = 291,
    TOKEN_XOR = 292,
    TOKEN_TEST = 293,
    TOKEN_SHL = 294,
    TOKEN_SHR = 295,
    TOKEN_LDR = 296,
    TOKEN_STR = 297,
    TOKEN_GLOBAL = 298,
    TOKEN_EXTERN = 299,
    TOKEN_SECTION = 300,
    TOKEN_WORD = 301,
    TOKEN_SKIP = 302,
    TOKEN_EQU = 303,
    TOKEN_END = 304,
    TOKEN_NUM = 305,
    TOKEN_REG = 306,
    TOKEN_IDENT = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 61 "./src/parser.y"

	int num;
	char* ident;
	Argument *arg;
	std::list<std::string>* symbs;
	std::list<Sym_lit>* sym_lits;

#line 118 "inc/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (FILE* fp);

#endif /* !YY_YY_INC_PARSER_HPP_INCLUDED  */
