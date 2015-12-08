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
			sum += str[0] - str[1];
		}
	}
	printf("Sum: %lu\n", sum);
	return 0;
}

unsigned char Count(char *in)
{
	int i;
	unsigned char sum = 0;
	for (i = 1; i < strlen(in)-2; i++) {
		if (in[i] == '\\') {
			switch (in[i+1]) {
			case '\\':
			case '"':
				i++;
				break;
			case 'x':
				if (in[i+3]) {
					i+= 3;
				}
			}
		}
		sum++;
	}
	return sum;
}
