#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER 80

char strNice(char *);
int sortSet(const void *, const void *);
char hasRepeatPair(char **, unsigned int);

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
	char **sets;
	int i, j;
	char lastChar;
	char withSeparation = 0, hasRepeat = 0;
	lastChar = 0;
	unsigned char length = strlen(str)-1;
	if (!(sets = (char **) malloc(length*sizeof(char *)))) {
		fprintf(stderr, "Unable to allocate memory.\n");
	}
	for (i = 0; i < length; i++) {
		if (!(sets[i] = (char *) malloc(3*sizeof(char)))) {
			fprintf(stderr, "Unable to allocate memory.\n");
			goto freemem;
		}
	}

	for (j = 0; j < length; j++) {
		sets[j][0] = str[j];
		sets[j][1] = str[j+1];
		sets[j][2] = j;
		if (str[j+1] == lastChar) {
			withSeparation = 1;
		}
		lastChar = str[j];
	}

	hasRepeat = hasRepeatPair(sets, length);

freemem:
	while (i > 0) {
		free(sets[--i]);
	}
	free(sets);
	return withSeparation && hasRepeat;
}

char hasRepeatPair(char **sets, unsigned int length)
{
	unsigned int j, k, hasRepeat = 0;
	qsort(sets, length, sizeof(char*), sortSet);
	for (j = 0; j < length-1; j++) {
		for (k = j+1; k < length && !sortSet(&sets[j], &sets[k]) ; k++) {
			if (		sets[j][2]-1 != sets[k][2]   &&
					sets[j][2]   != sets[k][2]-1) {
				hasRepeat = 1;
			}
		}
	}
	return hasRepeat;
}

int sortSet(const void *a, const void *b)
{
	const char *valA = *(const char **)a;
	const char *valB = *(const char **)b;
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (valA[i] > valB[i]) {
			return 1;
		} else if (valA[i] < valB[i]) {
			return -1;
		}
	}
	return 0;
}
