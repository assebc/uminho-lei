// gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O ficha3.c -lm

#include <stdio.h>
#include <assert.h>

int main() {
	
    int r, h, d, s;
    // r - denotes for pattern row
    // h - denotes for pattern height
    // d - denotes for digits
    // s - denotes for space

	assert(scanf("%d", &h) == 1);

	for(r = 1; r <= h - 1; r++) {
		printf("\t");
		for(d = 1; d <= r; d++)
			printf("%d ", d);
		for(s = 1; s <= 2 * (h - r); s++)
			printf("  ");
		putchar('\b');
		for(d = r; d >= 1; d--)
			printf(" %d", d);
		putchar('\n');
	}

	for(r = h; r >= 1; r--) {
		printf("\t");
		for(d = 1; d <= r; d++)
			printf("%d ", d);
		for(s = 1; s <= 2 * (h - r); s++)
			printf("  ");
		putchar('\b');
		for(d = r; d >= 1; d--)
			printf(" %d", d);
		putchar('\n');
	}
    
    return 0;
}

