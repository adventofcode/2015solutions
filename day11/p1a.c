#include <stdio.h>
#include <string.h> 

#define BUFFER 80

int ContainsRow(char *, unsigned long);
int NoConfusing(char *, unsigned long);
int TwoPair(char *, unsigned long);
void IncrementString(char *, unsigned long);

int main(void)
{
	char input[BUFFER];
	unsigned long len;
	fgets(input, BUFFER, stdin);
	strtok(input, "\n");
	len = strlen(input);
	while (!NoConfusing(input, len) || !ContainsRow(input, len) ||
			!TwoPair(input, len)) {
		IncrementString(input, len);
	}
	printf("Next possible password: %s\n", input);
	return 0;
}

int ContainsRow(char *str, unsigned long len)
{
	int i;
	for (i = 0; i < len-3; i++) {
		if (str[i]+1 == str[i+1] && str[i]+2 == str[i+2]) {
			return 1;
		}
	}
	return 0;
}

int NoConfusing(char *str, unsigned long len)
{
	int i;
	for (i = 0; i < len; i++) {
		switch (str[i]) {
		case 'i':
		case 'o':
		case 'l':
			return 0;
		}
	}
	return 1;
}

int TwoPair(char *str, unsigned long len)
{
	int pairs = 0;
	int i;
	for (i = 0; i < len-1; i++) {
		if (str[i] == str[i+1]) {
			pairs++;
			i++;
		}
	}
	return (pairs >= 2);
}

void IncrementString(char *str, unsigned long len)
{
	int i;
	for (i = len-1; i > 0; i--) {
		if (str[i] >= 'z') {
			str[i-1]++;
			str[i] = 'a';
			if (!(str[i-1] > 'z')) {
				return;
			}
		} else {
			str[i]++;
			return;
		}
	}
}
