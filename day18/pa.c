#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_X 100
#define MAX_Y 100
#define ITERATIONS 100

void CalcLife(char ***);
void BackupVals(char ***);
long SumOfLights(char ***, unsigned char);
char ShouldBeOn(char ***, int, int, unsigned char);

int main(void)
{
	char ***lights;
	char c;
	int x, y, i;
	lights = calloc(4, sizeof(char **));
	for (i = 0; i < 4; i++) {
		lights[i] = calloc(MAX_X, sizeof(char *));
		for (x = 0; x < MAX_X; x++) {
			lights[i][x] = calloc(MAX_Y, sizeof(char));
		}
	}
	x = y = 0;
	while ((c = fgetc(stdin)) && !feof(stdin)) {
		if (c == '\n') {
			x++;
			y = 0;
		}
		switch (c) {
		case '#':
			lights[2][x][y] = 1;
			lights[3][x][y++] = 1;
			break;
		case '.':
			lights[2][x][y] = 0;
			lights[3][x][y++] = 0;
			break;
		}
	}
	BackupVals(lights);
	for (i = 0; i < ITERATIONS; i++) {
		CalcLife(lights);
		BackupVals(lights);
	}
	printf("Sum after iterations: %ld\n", SumOfLights(lights, 0));
	printf("Sum if stuck corners: %ld\n", SumOfLights(lights, 1));
	return 0;
}

void CalcLife(char ***lights)
{
	int x, y;
	for (x = 0; x < MAX_X; x++) {
		for (y = 0; y < MAX_Y; y++) {
			lights[2][x][y] = ShouldBeOn(lights, x, y, 0);
			lights[3][x][y] = ShouldBeOn(lights, x, y, 1);
		}
	}
}

void BackupVals(char ***lights)
{
	int x, y;
	for (x = 0; x < MAX_X; x++) {
		for (y = 0; y < MAX_Y; y++) {
			lights[0][x][y] = lights[2][x][y];
			if ((x == 0 || x == MAX_X-1) && (y == 0 || y == MAX_Y-1)) {
				lights[1][x][y] = 1;
			} else {
				lights[1][x][y] = lights[3][x][y];
			}
		}
	}
}

long SumOfLights(char ***lights, unsigned char stuckCorner)
{
	long retVal = 0;
	int x, y;
	for (x = 0; x < MAX_X; x++) {
		for (y = 0; y < MAX_Y; y++) {
			retVal += lights[stuckCorner][x][y];
		}
	}
	return retVal;
}

char ShouldBeOn(char ***lights, int x, int y, unsigned char stuckCorner)
{
	int checkX, checkY, sum;
	int minX, minY, maxX, maxY;
	minX = (x == 0 ? x : x-1);
	maxX = (x == MAX_X-1 ? x : x+1);
	minY = (y == 0 ? y : y-1);
	maxY = (y == MAX_Y-1 ? y : y+1);
	sum = 0;
	for (checkX = minX; checkX <= maxX; checkX++) {
		for (checkY = minY; checkY <= maxY; checkY++) {
			if (checkX != x || checkY != y) {
				sum += lights[stuckCorner][checkX][checkY];
			}
		}
	}
	if (lights[stuckCorner][x][y]) {
		return (sum == 2) || (sum == 3);
	} else {
		return sum == 3;
	}
}
