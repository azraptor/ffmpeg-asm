#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// Assembly functions
extern void __add_values_sse2(uint8_t *src, const uint8_t *src2);
extern void __add_values_w_sse2(int16_t *src, const int16_t *src2);
extern void __add_values_dw_sse2(int32_t *src, const int32_t *src2);
extern void __add_values_qw_sse2(int64_t *src, const int64_t *src2);

// Prints an array in a nice way
#define PRINT_ARR(A, T, S, F) {\
	putchar('[');\
	for(size_t i=0;i<S;i++) {\
		printf("%"F, A[i]); \
		if(i < S-1) fputs(", ", stdout);\
	}\
	putchar(']');\
	putchar('\n');\
}

// Testing vector functions
void test_bytes() {
	uint8_t *p1 = NULL;
	uint8_t *p2 = NULL;
	puts("!!!!BYTES VECTOR TEST!!!!");

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

	PRINT_ARR(p1, uint8_t, 16, "d");

	fputs("p2: ", stdout);
	PRINT_ARR(p2, uint8_t, 16, "d");
	
	// Call assembly function
	__add_values_sse2(p1, p2);
	puts("====RESULT====");
	fputs("p1: ", stdout);
	PRINT_ARR(p1, uint8_t, 16, "d");
}

void test_words() {
	int16_t *p1 = NULL;
	int16_t *p2 = NULL;

	puts("!!!!WORDS VECTOR TEST!!!!");

	// Populate each array
	p1 = calloc(2, 8);
	p2 = calloc(2, 8);

	p1[1] = 10;
	p2[1] = 80;

	printf("PTR SIZE: %zu\n", sizeof(p1));

	puts("====ARRAYS====");
	fputs("p1: ", stdout);
	PRINT_ARR(p1, int16_t, 8, "d");

	fputs("p2: ", stdout);
	PRINT_ARR(p2, int16_t, 8, "d");

	// Call assembly function
	__add_values_w_sse2(p1, p2);
	puts("====RESULT====");
	fputs("p1: ", stdout);
	PRINT_ARR(p1, int16_t, 8, "d");
}

void test_double_words() {
	int32_t *p1 = NULL;
	int32_t *p2 = NULL;

	puts("!!!!DOUBLE WORDS VECTOR TEST!!!!");

	// Populate each array
	p1 = calloc(4, 4);
	p2 = calloc(4, 4);

	p1[1] = 10;
	p2[1] = 80;

	printf("PTR SIZE: %zu\n", sizeof(p1));

	puts("====ARRAYS====");
	fputs("p1: ", stdout);
	PRINT_ARR(p1, int32_t, 4, "d");

	fputs("p2: ", stdout);
	PRINT_ARR(p2, int32_t, 4, "d");

	// Call assembly function
	__add_values_dw_sse2(p1, p2);
	puts("====RESULT====");
	fputs("p1: ", stdout);
	PRINT_ARR(p1, int32_t, 4, "d");
}

void test_quad_words() {
	int64_t *p1 = NULL;
	int64_t *p2 = NULL;

	puts("!!!!QUAD WORDS VECTOR TEST!!!!");

	// Populate each array
	p1 = calloc(8, 2);
	p2 = calloc(8, 2);

	p1[0] = 1L << 16L;
	p2[0] = 32L;
	p1[1] = 1L << 32L;
	p2[1] = 10L;

	printf("PTR SIZE: %zu\n", sizeof(p1));

	puts("====ARRAYS====");
	fputs("p1: ", stdout);
	PRINT_ARR(p1, int64_t, 2, "ld");

	fputs("p2: ", stdout);
	PRINT_ARR(p2, int64_t, 2, "ld");

	// Call assembly function
	__add_values_qw_sse2(p1, p2);
	puts("====RESULT====");
	fputs("p1: ", stdout);
	PRINT_ARR(p1, int64_t, 2, "ld");
}

void (*tests[4])() = {
	test_bytes,
	test_words,
	test_double_words,
	test_quad_words
};

// Run all of our tests to
// make sure vector stuff works
int main() {
#ifdef TESTS
	for(size_t i=0;i<4;i++) (*tests[i])();
#endif
}
