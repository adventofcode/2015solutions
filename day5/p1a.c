#include <stdio.h>
#include <string.h>
#define BUFFER 80

char strNice(char *);

int main(void)
{
	char str[BUFFER];
	unsigned long niceStrs = 0;

	while ((fgets(str, BUFFER, stdin) != NULL)) {
		strtok(str, "\n");
		niceStrs += strNice(str);
	}
	printf("Nice strings: %lu\n", niceStrs);
	return 0;
}

char strNice(char *str)
{
	unsigned char i = 0;
	char twoInRow = 0;
	unsigned char vowels = 0;
	unsigned char ruleBroken = 0;
	for ( ; i < strlen(str); i++) {
		switch (str[i]) {
		case 'a':
			ruleBroken = str[i+1] == 'b' ? 1 : ruleBroken;
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			vowels++;
			break;
		case 'c':
			ruleBroken = str[i+1] == 'd' ? 1 : ruleBroken;
			break;
		case 'p':
			ruleBroken = str[i+1] == 'q' ? 1 : ruleBroken;
			break;
		case 'x':
			ruleBroken = str[i+1] == 'y' ? 1 : ruleBroken;
			break;
		}
		twoInRow = str[i] == str[i+1] ? 1 : twoInRow;
	}
	return twoInRow && vowels >= 3 && !ruleBroken;
}
