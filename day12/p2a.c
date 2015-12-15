/**
 * STRONGLY DEPENDS ON A JSON LIBRARY
 * The nxjson library is, at time of writing, on bitbucket.
 * The link follows
 * https://bitbucket.org/yarosla/nxjson
 * The source files (nxjson.c and nxjosn.h) are necessary to compile.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nxjson.h"

char *AddToString(char *, long long *, char);
long long SumJson(const nx_json *);

int main(void)
{
	long long allocSize = 160;
	const nx_json *json;
	char c;
	char *buffer = calloc(allocSize, sizeof(char));
	while ((c = fgetc(stdin)) && !feof(stdin)) {
		buffer = AddToString(buffer, &allocSize, c);
	}
	json = nx_json_parse(buffer, NULL);
	printf("Sum: %lld\n", SumJson(json));
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

long long SumJson(const nx_json *json)
{
	long long retVal = 0;
	const nx_json *curSon = json;
	while (curSon) {
		switch (curSon->type) {
		case NX_JSON_OBJECT:
		case NX_JSON_ARRAY:
			retVal += SumJson(curSon->child);
			break;
		case NX_JSON_STRING:
			if (curSon->key && !strcmp(curSon->text_value, "red")) {
				return 0;
			}
			break;
		case NX_JSON_INTEGER:
			retVal += curSon->int_value;
			break;
		case NX_JSON_DOUBLE:
		case NX_JSON_BOOL:
		case NX_JSON_NULL:
			break;
		}
		curSon = curSon->next;
	}
	return retVal;
}
