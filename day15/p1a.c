#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum property {
	PROP_NONE,
	PROP_CALORIES,
	PROP_CAPACITY,
	PROP_DURABILITY,
	PROP_FLAVOR,
	PROP_TEXTURE
};

struct ingredient {
	char *name;
	long calories;
	long capacity;
	long durability;
	long flavor;
	long texture;
};

struct cookie {
	long capacity;
	long durability;
	long flavor;
	long texture;
};

char *AddToString(char *, long long *, char);
struct ingredient **StringToIngredient(struct ingredient **, int *, char *);
struct ingredient *GetIngredient(struct ingredient ***, int *, char *);
long long ComputeBestMix(struct ingredient **, struct cookie, int, int);
void AddValue(struct ingredient *, struct cookie *, int);
void SubtractValue(struct ingredient *, struct cookie *, int);
long long CookieValue(struct cookie *);

int main(void)
{
	long long allocSize = 80;
	char *buffer = calloc(allocSize, sizeof(char));
	struct ingredient **pantry = calloc(1, sizeof(struct ingredient));
	int numIngredients = 0;
	char c;
	struct cookie jar = {0};
	while ((c = fgetc(stdin)) && !feof(stdin)){
		if (c == '\n') {
			pantry = StringToIngredient(pantry, &numIngredients, buffer);
			memset(buffer, 0, allocSize);
		} else {
			buffer = AddToString(buffer, &allocSize, c);
		}
	}
	printf("Best score: %lld\n", ComputeBestMix(pantry, jar, numIngredients, 100));
	return 0;
}

char *AddToString(char *str, long long *strAllocSize, char add)
{
	long len = strlen(str);
	if (len + 2 >= *strAllocSize) {
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
		str[len] = add; 
		str[len+1] = 0; 
	}
	return str; 
}

struct ingredient **StringToIngredient(struct ingredient **pantry, int *numIngredients, char *str)
{
	char *name;
	long tmp;
	long flavor, durability, capacity, texture, calories;
	char *token;
	int i;
	enum property nextProc = PROP_NONE;
	struct ingredient *newbie;
	token = strtok(str, ": ");
	for (i = 0; i < 11 && token; (token = strtok(NULL, " ,.")), i++) { // Number of tokens in a line.
		if (!i) {
			name = malloc((strlen(token)+1)*sizeof(char));
			strcpy(name, token);
		} else if (nextProc == PROP_NONE) {
			switch (strlen(token)) {
			case 6: // flavor
				nextProc = PROP_FLAVOR;
				break;
			case 7: // texture
				nextProc = PROP_TEXTURE;
				break;
			case 8:
				if (!strcmp(token, "calories")) {
					nextProc = PROP_CALORIES;
				} else {
					nextProc = PROP_CAPACITY;
				}
				break;
			case 10:
				nextProc = PROP_DURABILITY;
				break;
			}
		} else {
			tmp = strtol(token, NULL, 10);
			switch (nextProc) {
			case PROP_FLAVOR:
				flavor = tmp;
				break;
			case PROP_DURABILITY:
				durability = tmp;
				break;
			case PROP_CAPACITY:
				capacity = tmp;
				break;
			case PROP_TEXTURE:
				texture = tmp;
				break;
			case PROP_CALORIES:
				calories = tmp;
			default:
				break;
			}
			nextProc = PROP_NONE;
		}
	}
	if (i == 11) {
		newbie = GetIngredient(&pantry, numIngredients, name);
		newbie->calories = calories;
		newbie->capacity = capacity;
		newbie->durability = durability;
		newbie->flavor = flavor;
		newbie->texture = texture;
	}
	return pantry;
}

struct ingredient *GetIngredient(struct ingredient ***pantry, int *numIngredients, char *name)
{
	int i;
	for (i = 0; i < *numIngredients; i++) {
		if (!(strcmp((*pantry)[i]->name, name))) {
			break;
		}
	}
	if (i == *numIngredients) {
		(*pantry) = realloc(*pantry, (*numIngredients+1)*sizeof(struct ingredient *));
		(*pantry)[i] = calloc(1, sizeof(struct ingredient));
		(*pantry)[i]->name = malloc((strlen(name)+1)*sizeof(char));
		strcpy((*pantry)[i]->name, name);
		(*numIngredients)++;
	}
	return (*pantry)[i];
}

long long ComputeBestMix(struct ingredient **pantry, struct cookie jar,
			int numLeft, int maxTsp)
{
	int myTsp;
	long long retVal = 0, tmpVal;
	if (maxTsp == 0) {
		return CookieValue(&jar);
	} else if (numLeft == 1) {
		AddValue(pantry[0], &jar, maxTsp);
		return CookieValue(&jar);
	}
	for (myTsp = maxTsp; myTsp >= 0; myTsp--) {
		AddValue(pantry[0], &jar, myTsp);
		tmpVal = ComputeBestMix(pantry+1, jar, numLeft-1, maxTsp-myTsp);
		SubtractValue(pantry[0], &jar, myTsp);
		if (tmpVal > retVal) {
			retVal = tmpVal;
		}
	}
	return retVal;
}

void AddValue(struct ingredient *pantry, struct cookie *jar, int tsp)
{
	jar->capacity += pantry->capacity*tsp;
	jar->durability += pantry->durability*tsp;
	jar->flavor += pantry->flavor*tsp;
	jar->texture += pantry->texture*tsp;
}

void SubtractValue(struct ingredient *pantry, struct cookie *jar, int tsp)
{
	jar->capacity -= pantry->capacity*tsp;
	jar->durability -= pantry->durability*tsp;
	jar->flavor -= pantry->flavor*tsp;
	jar->texture -= pantry->texture*tsp;
}

long long CookieValue(struct cookie *jar)
{
	long capacity = jar->capacity;
	long durability = jar->durability;
	long flavor =  jar->flavor;
	long texture = jar->texture;
	if (capacity < 0 || durability < 0 || flavor < 0 || texture < 0) {
		return 0;
	}
	return capacity * durability * flavor * texture;
}
