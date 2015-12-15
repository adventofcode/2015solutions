#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *AddToString(char *, long long *, char);

int main(void)
{
	long long allocSize = 160;
	char *token;
	long long sum = 0;
	char c;
	char *splitOn = " \nabcdefghijklmnopqrstufwxyz\"[]{},:";
	char *buffer = calloc(allocSize, sizeof(char));
	while ((c = fgetc(stdin)) && !feof(stdin)) {
		buffer = AddToString(buffer, &allocSize, c);
	}
	token = strtok(buffer, splitOn);
	if (!token) {
		return 0;
	}
	do {
		sum += strtol(token, NULL, 10);
	} while ((token = strtok(NULL, splitOn)));
	printf("Sum: %lld\n", sum);
	return 0;
}

char *AddToString(char *str, long long *strAllocSize, char add)
{
	long len = strlen(str);
	if (len + 2 >= *strAllocSize) {
		*strAllocSize *= 2;
		str = realloc(str, sizeof(char)*(*strAllocSize));
		if (!str) {
			fprintf(stderr, "Out of memory for string!\n");
			exit(1);
		}
	}
	if (str) { 
		str[len] = add; 
		str[len+1] = 0; 
	}
	return str; 
}
