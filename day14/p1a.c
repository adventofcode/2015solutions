#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct reindeer {
	char *name;
	long kmPerSec;
	long travelTime;
	long restTime;
	long travelled;
};

char *AddToString(char *, long long *, char);
long MaxDistanceAfterTime(struct reindeer **, int, long);
long DeerTravelled(struct reindeer *, long);
struct reindeer **StringToDeer(struct reindeer **, int *, char *);
struct reindeer *GetReindeer(struct reindeer ***, int *, char *);

int main(void)
{
	long long allocSize = 80;
	char *buffer = calloc(allocSize, sizeof(char));
	struct reindeer **headlights = calloc(1, sizeof(struct reindeer));
	int numDeer = 0;
	char c;
	while ((c = fgetc(stdin)) && !feof(stdin)){
		if (c == '\n') {
			headlights = StringToDeer(headlights, &numDeer, buffer);
			memset(buffer, 0, allocSize);
		} else {
			buffer = AddToString(buffer, &allocSize, c);
		}
	}
	printf("Max distance: %ld\n", MaxDistanceAfterTime(headlights, numDeer, 2503));
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

long MaxDistanceAfterTime(struct reindeer **headlights, int numDeer, long secs)
{
	long retVal = 0;
	long tmp;
	int i;
	for (i = 0; i < numDeer; i++) {
		tmp = DeerTravelled(headlights[i], secs);
		retVal = retVal > tmp ? retVal : tmp;
	}
	return retVal;
}

long DeerTravelled(struct reindeer *headlight, long secs)
{
	long secsTravelling = 0;
	long secsPerUnit = headlight->travelTime + headlight->restTime;
	secsTravelling = secs / secsPerUnit; // Integer division and truncation
	secsTravelling *= headlight->travelTime;
	secsTravelling += (secs % secsPerUnit) > headlight->travelTime ?
						headlight->travelTime :
						secs % secsPerUnit;
	return secsTravelling * headlight->kmPerSec;
}

struct reindeer **StringToDeer(struct reindeer **headlights, int *numDeer, char *str)
{
	char *tag;
	long rate;
	long flyTime;
	long restTime;
	char *token;
	int i;
	struct reindeer *deer;
	token = strtok(str, " ");
	for (i = 0; i < 15 && token; (token = strtok(NULL, " .")), i++) { // Number of tokens in a line.
		switch (i) {
		case 0:
			tag = malloc((strlen(token)+1)*sizeof(char));
			strcpy(tag, token);
			break;
		case 3:
			rate = strtol(token, NULL, 10);
			break;
		case 6:
			flyTime = strtol(token, NULL, 10);
			break;
		case 13:
			restTime = strtol(token, NULL, 10);
			break;
		case 1:  // can
		case 2:  // fly
		case 4:  // km/s
		case 5:	 // for
		case 7:  // seconds,
		case 8:	 // but
		case 9:  // then
		case 10: // must 
		case 11: // rest
		case 12: // for
		case 14: // seconds
			break;
		}
	}
	if (i == 15) {
		deer = GetReindeer(&headlights, numDeer, tag);
		deer->kmPerSec = rate;
		deer->travelTime = flyTime;
		deer->restTime = restTime;
	}
	return headlights;
}

struct reindeer *GetReindeer(struct reindeer ***deer, int *numDeer, char *name)
{
	int i;
	for (i = 0; i < *numDeer; i++) {
		if (!(strcmp((*deer)[i]->name, name))) {
			break;
		}
	}
	if (i == *numDeer) {
		(*deer) = realloc(*deer, (*numDeer+1)*sizeof(struct reindeer *));
		(*deer)[i] = calloc(1, sizeof(struct reindeer));
		(*deer)[i]->name = malloc((strlen(name)+1)*sizeof(char));
		strcpy((*deer)[i]->name, name);
		(*numDeer)++;
	}
	return (*deer)[i];
}
