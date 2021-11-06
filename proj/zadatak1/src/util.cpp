#include "util.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#define MAX_IDENT_SIZE 32

void error_handler(std::string msg) {
	std::cout << msg << std::endl;
	exit(0);
}

struct instr *global_prev;
int
is_register(const char *in)
{
	int last = 0;
	while (in[last+1]) last++;
	return in[0] == 'r' && in[last] == 'x';
}

/* all of these, in this case, will malloc and create
 * structures; we can do whatever we want here. Depending
 * on what you're parsing, you might even want to start
 * executing as you're parsing. */
char*
copy_str(const char *in)
{
	size_t len = strnlen(in, MAX_IDENT_SIZE);
	char* buf = (char*)malloc(len + 1);
	strncpy(buf, in, len);
	buf[len] = '\0';
	return buf;
}

struct arg*
mk_argument(char type, char *reg, int literal, char* symbol)
{
	struct arg* a = (struct arg*)malloc(sizeof(struct arg));
	a->type = type;
	a->reg  = reg;
	a->literal = literal;
	a->symbol = symbol;
	a->next = NULL;
	return a;
}

struct instr*
mk_instruction(char *name, struct arg *args)
{
	struct instr* i = (struct instr*)malloc(sizeof(struct instr));
	i->name = name;
	i->args = args;
	i->prev = global_prev;
	global_prev = i;
	return i;
}

void
print_arg(const struct arg *arg)
{
	switch (arg->type) {
		case 9:	printf("*");
		case 0:
			printf("0x%x", arg->literal);
			break;
		case 10:	printf("*");
		case 1:
			printf("%s", arg->symbol);
			break;
		case 2:
			printf("$0x%x", arg->literal);
			break;
		case 3:
			printf("$%s", arg->symbol);
			break;
		case 4:
			printf("%%%s", arg->symbol);
			break;
		case 11:	printf("*");
		case 5:
			printf("%s", arg->reg);
			break;
		case 12:	printf("*");
		case 6:
			printf("[%s]", arg->reg);
			break;
		case 13:	printf("*");
		case 7:
			printf("[%s + 0x%x]", arg->reg, arg->literal);
			break;
		case 14:	printf("*");
		case 8:
			printf("[%s + %s]", arg->reg, arg->symbol);
			break;
		default:
			break;
	}
}

/* We'll use this at the end to pretty-print our
 * 'assembly program'
 */
void
print_instrs(const struct instr *instr)
{
	if (!instr) return;

	print_instrs(instr->prev);

	if (!instr->args) {
		printf("%s;\n", instr->name);
	} else if (instr->args->next) {
		printf("%s ", instr->name);
		print_arg(instr->args);
		printf(", ");
		print_arg(instr->args->next);
		printf(";\n");
	} else  {
		printf("%s ", instr->name);
		print_arg(instr->args);
		printf(";\n");
	}
}

/* and for cleaning up at the end */
void
free_args(struct arg *args)
{
	if (!args) return;
	free_args(args->next);
	if(args->reg)
		free(args->reg);
	if(args->symbol)
		free(args->symbol);
	free(args);
}
void
free_instrs(struct instr *instr)
{
	if (!instr) return;
	free_instrs(instr->prev);
	free_args(instr->args);
	free(instr->name);
	free(instr);
}
