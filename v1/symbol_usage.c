#include <stdio.h>


typedef struct
{
	int a;
	int b;
} ImaginaryType;

// symboli (labele) sadrze labele nizih bajtova

extern int symbol1;
extern int *symbol2;
extern int symbol3[];
extern ImaginaryType symbol4;

int main() {
	printf("symbol1 = %d\n", symbol1);
	printf("symbol2 = %p\n", symbol2);
	printf("symbol3 = %d\n", symbol3[0]);
	printf("symbol4 = %d\n", symbol4.a);

	for(int i = 0; i < 10; i++) {
		printf("symbol3[%d] = mem[offset[symbol3]] + %d * sizeof(int) = %d\n", i, i, symbol3[i]);
	}
	
	printf("&symbol3 = offset(symbol3) = %p\n", &symbol3);
	printf("symbol4.a = mem[offset(symbol4)] = %d\n", symbol4.a);
	printf("symbol4.b  = mem[offset(symbol4) + sizeof(symbol4.a) + alignment(symbol4.b)] = %d\n", symbol4.b);
	printf("&symbol4 = offset(symbol4) = %p\n", &symbol4);
	// alignment je potreban zbog optimizacije pritupa i obavezan je!
	// u ovom slucaju nismo imali problem sa symbol file-om
	// ali su moguci

	return 0;
}
