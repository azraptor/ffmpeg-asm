#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// Assembly functions
extern void __add_values_sse2(uint8_t *src, const uint8_t *src2);

void print_arr(uint8_t *a, size_t s) {
	// Prints an array in a nice way
	putchar('[');
	for(size_t i=0;i<s;i++) {
		printf("%02u", a[i]);
		if(i < s-1) fputs(", ", stdout);
	}
	putchar(']');
	putchar('\n');
}

// Testing vector function
void test2() {
	uint8_t *p1 = NULL;
	uint8_t *p2 = NULL;

	puts("====TEST2 ====");

	// Populate each array
	p1 = calloc(16, 1);
	p2 = calloc(16, 1);

	// Set second array to single number
	memset((uint8_t*)p2, 2, 16);

	for(uint32_t i=0;i<6;i++)
		p1[i] = i % 2 == 0 ? i * 3 : i + 2;

	p1[7] = 10;
	p2[7] = 80;

	printf("PTR SIZE: %zu\n", sizeof(p1));

	puts("====ARRAYS====");
	fputs("p1: ", stdout);

	print_arr(p1, 16);

	fputs("p2: ", stdout);
	print_arr(p2, 16);
	
	// Call assembly function
	__add_values_sse2(p1, p2);
	puts("====RESULT====");
	fputs("p1: ", stdout);
	print_arr(p1, 16);
}

int main() {
#ifdef TEST2
	test2();
#endif
}
