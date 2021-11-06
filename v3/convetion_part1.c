#include <stdio.h>

typedef struct {
	char field1;
	char field2;
	long field3;
	short field4;
	char field5;
	int field6;
	char field7;
} StructType;


void __attribute__((sysv_abi)) foo_system_v_abi(char a, StructType b, int c, StructType d, long e) {

	// a se prosledjuje kroz prvi naredni slobodan registar
	// b se prosledjuje preko stecka
	// c se prosledjuje kroz registar rsi
	// d se prosledjuje kros stack
	// e se prosledjuje kroz rdx

}

void __attribute__((ms_abi)) foo_microsoft_abi(char a, StructType b, int c, StructType d, long e) {



}

int main() {
	printf("%ld\n", sizeof(StructType));

	StructType struct_object1 = {'a', 'b', 3l, 4, 'e', 6, 'g'};
	StructType struct_object2 = {'g', 'f', 4l, 3, 'c', 2, 'a'};

	foo_system_v_abi('a', struct_object1, 3, struct_object2, 5l);
	foo_microsoft_abi('a', struct_object1, 3, struct_object2, 5l);

	return 0;
} 
