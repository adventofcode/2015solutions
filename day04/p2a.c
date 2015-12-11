#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#define BUFFER 80

char HashComplies(unsigned char*, unsigned long);

int main(void)
{
	char str[BUFFER];
	char curStr[BUFFER];
	unsigned char curLen = 0;
	unsigned long i = 1;

	printf("Enter key: ");
	fgets(str, BUFFER, stdin);
	strtok(str, "\n");
	while(1) {
		curLen = snprintf(curStr, BUFFER, "%s%lu", str, i);
		if (!HashComplies((unsigned char *)curStr, curLen)) {
			i++;
		} else {
			break;
		}
	}
	printf("First successful string: %s with %lu\n", curStr, i);
	return 0;
}

char HashComplies(unsigned char *str, unsigned long len)
{
	unsigned char hash[MD5_DIGEST_LENGTH];
	MD5(str, len, hash);
	return !hash[0] && !hash[1] && !hash[2];
}
