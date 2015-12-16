#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_SUES 501

enum property {
	PROP_NONE,
	PROP_AKITAS,
	PROP_CARS,
	PROP_CATS,
	PROP_CHILDREN,
	PROP_GOLDFISH,
	PROP_PERFUMES,
	PROP_POMERANIANS,
	PROP_SAMOYEDS,
	PROP_SUE,
	PROP_TREES,
	PROP_VIZSLAS,
	PROP_MAX
};

struct sue {
	long props[PROP_MAX];
};

char *AddToString(char *, long long *, char);
void StringToIngredient(struct sue **, char *);
long MatchSues(struct sue **);

int main(void)
{
	long long allocSize = 80;
	char *buffer = calloc(allocSize, sizeof(char));
	struct sue **boys = malloc(NUM_SUES*sizeof(struct sue *));
	char c;
	int i;
	for (i = 0; i < NUM_SUES; i++) {
		boys[i] = malloc(sizeof(struct sue));
	}
	// Hardcoded goal
	boys[0]->props[PROP_NONE] = -1;
	boys[0]->props[PROP_AKITAS] = 0;
	boys[0]->props[PROP_CARS] = 2;
	boys[0]->props[PROP_CATS] = 7;
	boys[0]->props[PROP_CHILDREN] = 3;
	boys[0]->props[PROP_GOLDFISH] = 5;
	boys[0]->props[PROP_PERFUMES] = 1;
	boys[0]->props[PROP_POMERANIANS] = 3;
	boys[0]->props[PROP_SAMOYEDS] = 2;
	boys[0]->props[PROP_SUE] = 0;
	boys[0]->props[PROP_TREES] = 3;
	boys[0]->props[PROP_VIZSLAS] = 0;
	while ((c = fgetc(stdin)) && !feof(stdin)){
		if (c == '\n') {
			StringToIngredient(boys, buffer);
			memset(buffer, 0, allocSize);
		} else {
			buffer = AddToString(buffer, &allocSize, c);
		}
	}
	printf("Matching Sue: %ld\n", MatchSues(boys));
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

void StringToIngredient(struct sue **boys, char *str)
{
	long props[PROP_MAX];
	char *token;
	int i;
	enum property nextProc = PROP_NONE;
	for (i = 0; i < PROP_MAX; i++) {
		props[i] = -1;
	}
	token = strtok(str, ": ");
	for (; token; (token = strtok(NULL, " :,."))) {
		if (nextProc == PROP_NONE) {
			if (!strcmp(token, "children")) {
				nextProc = PROP_CHILDREN;
			} else if (!strcmp(token, "cats")) {
				nextProc = PROP_CATS;
			} else if (!strcmp(token, "samoyeds")) {
				nextProc = PROP_SAMOYEDS;
			} else if (!strcmp(token, "pomeranians")) {
				nextProc = PROP_POMERANIANS;
			} else if (!strcmp(token, "akitas")) {
				nextProc = PROP_AKITAS;
			} else if (!strcmp(token, "vizslas")) {
				nextProc = PROP_VIZSLAS;
			} else if (!strcmp(token, "goldfish")) {
				nextProc = PROP_GOLDFISH;
			} else if (!strcmp(token, "trees")) {
				nextProc = PROP_TREES;
			} else if (!strcmp(token, "cars")) {
				nextProc = PROP_CARS;
			} else if (!strcmp(token, "perfumes")) {
				nextProc = PROP_PERFUMES;
			} else if (!strcmp(token, "Sue")) {
				nextProc = PROP_SUE;
			}
		} else {
			props[nextProc] = strtol(token, NULL, 10);
			nextProc = PROP_NONE;
		}
	}
	for(i = 0; i < PROP_MAX; i++) {
		boys[props[PROP_SUE]]->props[i] = props[i];
	}
}

long MatchSues(struct sue **boys)
{
	int i = 0;
	int sue = 1;
	char found = 0;
	long target, source;
	for (sue = 1; !found && sue <= 500; sue++) {
		found = 1;
		for (i = 1; i < PROP_MAX; i++) {
			if (i == PROP_SUE) {
				continue;
			}
			if (boys[sue]->props[i] == -1) {
				continue;
			} else {
				source = boys[sue]->props[i];
				target = boys[0]->props[i];
				switch (i) {
				case PROP_CATS:
				case PROP_TREES:
					found = source > target;
					break;
				case PROP_POMERANIANS:
				case PROP_GOLDFISH:
					found = source < target;
					break;
				default:
					found = source == target;
					break;
				}
				if (!found) {
					break;
				}
			}
		}
	}
	return sue <= 500 ? sue-1 : 501;
}
