#include <stdio.h>

typedef struct {
	char field1;
	int field2;
	short field3;
} StructType;

// extern!!!!
// mozemo samo da pozovemo compailer ali ne i linker!!!!
extern int test(
		char rdi,
		int rsi,
		StructType rdx_rcx,
		void *r8,
		StructType stack,
		long r9);

int main() {
	StructType arg = {'a', 2, 3};

	int a = test('a', 2, arg, (void *) 4, arg, 6l);

	printf("%d\n", a);

	return 0;
}
