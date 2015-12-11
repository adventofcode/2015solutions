#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 80

struct city {
	char name[BUFFER];
	struct travel *dest;
};
struct travel {
	char to[BUFFER];
	unsigned long distance;
	struct travel *dest;
};

char AddLine(struct city **, char *, unsigned int);
unsigned long GetDistance(struct city *, struct city *);
unsigned long ComputeDistance(struct city **, unsigned char);
unsigned long permutation(struct city **, int, int);
void swap(void *, void *, int);

int main(void)
{
	unsigned int numCities = 0;
	char str[BUFFER];
	struct city **cities = calloc(10, sizeof(struct city *));

	while((fgets(str, BUFFER, stdin))) {
		numCities += AddLine(cities, str, numCities);
	}
	printf("Largest distance: %lu\n", permutation(cities, 0, numCities));
	return 0;
}

char AddLine(struct city **cities, char *str, unsigned int numCities)
{
	unsigned char i = 0, j = 0;
	char retVal = 0;
	char *token = strtok(str, " ");
	struct travel *travelTo = calloc(1, sizeof(struct travel));
	struct travel *travelFrom = calloc(1, sizeof(struct travel));
	char to[BUFFER];
	char from[BUFFER];
	char *curName[2];
	curName[0] = to;
	curName[1] = from;
	struct travel *travels[2];
	travels[0] = travelTo;
	travels[1] = travelFrom;
	struct travel *curTravel;
	to[0] = 0;
	do {
		if (!(strcmp(token, "to")) || !(strcmp(token,"="))) {
			continue;
		} else if (!to[0]) {
			strcpy(curName[0], token);
			strcpy(travels[1]->to, token);
		} else if (!(travelTo->to[0])) {
			strcpy(curName[1], token);
			strcpy(travels[0]->to, token);
		} else {
			travelFrom->distance = strtol(token, NULL, 10);
			travelTo->distance = strtol(token, NULL, 10);
		}
	} while ((token = strtok(NULL, " ")));

	for (j = 0; j < 2; j++) {
		i = 0;
		while (i < numCities && cities[i] && strcmp(cities[i]->name, curName[j])) {
			i++;
		}
		if (i == numCities || !cities[i]) {
			cities[i] = calloc(1, sizeof(struct city));
			strcpy(cities[i]->name, curName[j]);
			cities[i]->dest = travels[j];
			retVal++;
			numCities++;
		} else {
			curTravel = cities[i]->dest;
			while (curTravel->dest) {
				curTravel = curTravel->dest;
			}
			curTravel->dest = travels[j];
		}
	}
	return retVal;
}

unsigned long ComputeDistance(struct city **dests, unsigned char count)
{
	unsigned long retVal = 0;
	int i = 0;
	while (i < count-1) {
		retVal += GetDistance(dests[i], dests[i+1]);
		i++;
	}
	return retVal;
}

unsigned long GetDistance(struct city *start, struct city *end)
{
	struct travel *curTrip = start->dest;
	while (strcmp(curTrip->to, end->name)) {
		curTrip = curTrip->dest;
	}
	return curTrip->distance;
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
unsigned long permutation(struct city **arr, int curr, int size)
{
	if(curr == size-1) {
		return ComputeDistance(arr, size);
	} else {
		unsigned long largestDist = 0, dist;
		int i;
		for(i=curr; i<size; i++)
		{
			if (i != curr) {
				swap(&arr[curr], &arr[i], sizeof(struct city *));
			}
			dist = permutation(arr, curr+1, size);
			if (i != curr) {
				swap(&arr[curr], &arr[i], sizeof(struct city *));
			}
			if (largestDist < dist) {
				largestDist = dist;
			}
		}
		return largestDist;
	}
}
