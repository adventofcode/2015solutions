#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *GetLookAndSay(char *, long long *);
char *AddToString(char *, long long *, char, char);

int main(void)
{
	int i = 0;
	long long allocSize = 160;
	char *buffer = calloc(allocSize, sizeof(char));
	char *oldBuff;
	fgets(buffer, allocSize, stdin);
	for (i = 0; i < 50; i++) {
		oldBuff = buffer;
		buffer = GetLookAndSay(buffer, &allocSize);
		free(oldBuff);
		//printf("Buffer: %s\n", buffer);
	}
	printf("Final strlen: %lu\n", strlen(buffer));
	return 0;
}

char *GetLookAndSay(char *in, long long *strAllocSize)
{
	char curChar, curCount, tmpChar;
	int i;
	char *newStr = calloc(*strAllocSize, sizeof(char));
	curChar = *in;
	curCount = 0;
	long long endlength = strlen(in)+1;
	for (i = 0; i < endlength && curChar >= 0; i++) {
		tmpChar = *(in+i);
		//printf("Char is: %c\n", tmpChar);
		if (tmpChar != curChar || tmpChar == '\n') {
			//printf("Char change! Resetting\n");
			newStr = AddToString(newStr, strAllocSize,
					'0' + curCount, curChar);
			curCount = 0;
			curChar = tmpChar == '\n' ? -1 : tmpChar;
		}
		if (tmpChar == curChar) {
			curCount++;
		} 
	}
	return newStr;
}

char *AddToString(char *str, long long *strAllocSize, char char1, char char2)
{
	if (strlen(str) + 3 >= *strAllocSize) {
		////printf("Alloc size before: %d\n", *strAllocSize);
		*strAllocSize *= 2;
		////printf("Alloc size after: %d\n", *strAllocSize); 
		str = realloc(str, sizeof(char)*(*strAllocSize));
		if (!str) {
			fprintf(stderr, "Out of memory for string!\n");
			exit(1);
		}
		////printf("Ended realloc\n"); 
	} 
	if (str) { 
		unsigned long long len = strlen(str);
		*(str+len) = char1; 
		*(str+len+1) = char2; 
		*(str+len+2) = 0; 
	} 
	return str; 
} 

