#include <stdio.h>

int main(void) {
	long floor = 0;
	unsigned char c = 0;
	while ((c = fgetc(stdin)) != '\n') {
		switch (c) {
		case '(':
			floor++;
			break;
		case ')':
			floor--;
			break;
		default:
			printf("Unsupported character.\n");
			break;
		}
	}
	printf("Floor to go to: %ld.\n", floor);
	return 0;
}
