#include <stdio.h>

int main(void) {
	long floor = 0;
	unsigned long pos = 0;
	unsigned char c = 0;
	while ((c = fgetc(stdin)) != '\n') {
		pos++;
		switch (c) {
		case '(':
			floor++;
			break;
		case ')':
			floor--;
			break;
		default:
			puts("Unsupported character.\n");
			break;
		}
		if (floor == -1) {
			printf("Position: %lu.\n", pos);
			break;
		}
	}
	return (pos == 0);
}
