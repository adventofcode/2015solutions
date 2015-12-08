#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER 240

unsigned char Count(char *);

int main(void)
{
	char input[BUFFER];
	unsigned int str[2];
	unsigned long sum = 0;
	while((fgets(input, BUFFER, stdin))) {
		if ((str[0] = strlen(input)-1)) {
			str[1] = Count(input);
			printf("strFull: %u, strPrint: %u\n", str[0], str[1]);
			sum += str[1] - str[0];
		}
	}
	printf("Sum: %lu\n", sum);
	return 0;
}

unsigned char Count(char *in)
{
	int i;
	unsigned char sum = 1;
	for (i = 0; i < strlen(in); i++) {
		switch (in[i]) {
		case '\\':
		case '"':
			sum++;
			break;
		}
		sum++;
	}
	return sum;
}
