#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person {
	char *name;
	struct animosity *likes;
	struct person *next;
};

struct animosity {
	char *towards;
	long amount;
	struct animosity *next;
};

char *AddToString(char *, long long *, char);
struct person **StringToAnimosity(struct person **, int *, char *);
struct person *GetPerson(struct person ***, int *, char *);
void swap(void *, void *, int);
long permutation(struct person **, int, int);
long ComputeDistance(struct person **, unsigned char);
long GetDistance(struct person *, struct person *);

int main(void)
{
	long long allocSize = 80;
	char *buffer = calloc(allocSize, sizeof(char));
	struct person **people = calloc(1, sizeof(struct person));
	int numPeople = 0;
	char c;
	while ((c = fgetc(stdin)) && !feof(stdin)){
		if (c == '\n') {
			people = StringToAnimosity(people, &numPeople, buffer);
			memset(buffer, 0, allocSize);
		} else {
			buffer = AddToString(buffer, &allocSize, c);
		}
	}
	GetPerson(&people, &numPeople, "me");
	printf("Max happiness: %ld\n", permutation(people, 0, numPeople));
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

struct person **StringToAnimosity(struct person **people, int *numPeople, char *str)
{
	char *feeler, *feelest;
	int sign;
	long happiness;
	char *token;
	int i;
	struct animosity *newFeels = calloc(1, sizeof(struct animosity));
	struct animosity *myFeels;
	struct person *myguy;
	token = strtok(str, " ");
	for (i = 0; i < 11 && token; (token = strtok(NULL, " .")), i++) { // Number of tokens in a line.
		switch (i) {
		case 0:
			feeler = malloc((strlen(token)+1)*sizeof(char));
			strcpy(feeler, token);
			break;
		case 2:
			if (!(strcmp(token, "gain"))) {
				sign = 1;
			} else {
				sign = -1;
			}
			break;
		case 3:
			happiness = strtol(token, NULL, 10);
			break;
		case 10:
			feelest = malloc((strlen(token)+1)*sizeof(char));
			strcpy(feelest, token);
			break;
		case 1: // would
		case 4: // happiness
		case 5: // units
		case 6: // by
		case 7: // sitting
		case 8: // next
		case 9: // to
			break;
		}
	}
	if (i == 11) {
		newFeels->towards = feelest;
		newFeels->amount = happiness*sign;
		myguy = GetPerson(&people, numPeople, feeler);
		myFeels = myguy->likes;
		if (!myFeels) {
			myguy->likes = newFeels;
		} else {
			while (myFeels->next) {
				myFeels = myFeels->next;
			}
			myFeels->next = newFeels;
		}
	}
	return people;
}

struct person *GetPerson(struct person ***people, int *numPeople, char *name)
{
	int i;
	for (i = 0; i < *numPeople; i++) {
		if (!(strcmp((*people)[i]->name, name))) {
			break;
		}
	}
	if (i == *numPeople) {
		(*people) = realloc(*people, (*numPeople+1)*sizeof(struct person *));
		(*people)[i] = calloc(1, sizeof(struct person));
		(*people)[i]->name = malloc((strlen(name)+1)*sizeof(char));
		strcpy((*people)[i]->name, name);
		(*numPeople)++;
	}
	return (*people)[i];
}

// Thank you, internet, for the initial code.
void swap(void *first, void *second, int width)
{
	void *p = malloc(width);

	memcpy(p,first,width);
	memcpy(first,second,width);
	memcpy(second,p,width);

	free(p);
}

/* arr is the string, curr is the current index to start permutation from and size is sizeof the arr */
long permutation(struct person **arr, int curr, int size)
{
	if(curr == size-1) {
		return ComputeDistance(arr, size);
	} else {
		long largestDist = 0, dist;
		int i;
		for(i=curr; i<size; i++)
		{
			if (i != curr) {
				swap(&arr[curr], &arr[i], sizeof(struct person *));
			}
			dist = permutation(arr, curr+1, size);
			if (i != curr) {
				swap(&arr[curr], &arr[i], sizeof(struct person *));
			}
			if (largestDist < dist) {
				largestDist = dist;
			}
		}
		return largestDist;
	}
}

long ComputeDistance(struct person **company, unsigned char count)
{
	long retVal = 0;
	int i = 0;
	while (i < count-1) {
		retVal += GetDistance(company[i], company[i+1]);
		i++;
	}
	retVal += GetDistance(company[i], company[0]);
	return retVal;
}

long GetDistance(struct person *first, struct person *second)
{
	struct animosity *firstAnimosity = first->likes;
	struct animosity *secondAnimosity = second->likes;
	long firstRet, secondRet;
	while (secondAnimosity && strcmp(secondAnimosity->towards, first->name)) {
		secondAnimosity = secondAnimosity->next;
	}
	while (firstAnimosity && strcmp(firstAnimosity->towards, second->name)) {
		firstAnimosity = firstAnimosity->next;
	}
	firstRet = firstAnimosity ? firstAnimosity->amount : 0;
	secondRet = secondAnimosity ? secondAnimosity->amount : 0;
	return (firstRet + secondRet);
}
