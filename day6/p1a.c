#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 80
#define MAX_SIZE 1000

enum action {
	off,
	on,
	toggle
};

enum inputState {
	init,
	x1,
	y1,
	through,
	x2,
	y2,
	end
};

int main(void)
{
	unsigned char lights[MAX_SIZE][MAX_SIZE];
	unsigned int i, j, lowX, highX, lowY, highY;
	unsigned int lit;
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			lights[i][j] = 0;
		}
	}
	enum action act;
	enum inputState state;
	char str[BUFFER];
	char numIn[4];
	numIn[3] = numIn[2] = numIn[1] = numIn[0] = 0;
	unsigned char skip = 0;
	char *opt1 = "turn on", *opt2 = "turn off", *opt3 = "toggle";
	while ((fgets(str, BUFFER, stdin)) != NULL) {
		state = init;
		if (strlen(str) < strlen(opt2)) {
			fprintf(stderr, "Input string too short\n");
			continue;
		} else if (!strncmp(str, opt1, strlen(opt1))) {
			act = on;
			skip = strlen(opt1);
		} else if (!strncmp(str, opt2, strlen(opt2))) {
			act = off;
			skip = strlen(opt2);
		} else if (!strncmp(str, opt3, strlen(opt3))) {
			act = toggle;
			skip = strlen(opt3);
		} else {
			printf ("Input not recognized\n");
			continue;
		}
		for (i = skip; i < strlen(str); i++) {
			switch (str[i]) {
			case ' ':
				if (state == init) {
					j = 0;
					state = x1;
				} else if (state == y1) {
					lowY = atoi(numIn);
					j = 0;
					state = through;
				} else if (state == through) {
					state = x2;
				}// Else noop
				break;
			case ',':
				if (state == x1) {
					lowX = atoi(numIn);
					j = 0;
					state = y1;
				} else if (state == x2) {
					highX = atoi(numIn);
					j = 0;
					state = y2;
				}
				break;
			case '\n':
				if (state == y2) {
					highY = atoi(numIn);
					state = end;
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				numIn[j] = str[i];
				numIn[j+1] = 0;
				j++;
				break;
			}
		}
		printf("Acting on %d,%d -> %d,%d\n", lowX, lowY, highX, highY);
		for (i = lowX; i <= highX; i++) {
			for (j = lowY; j <= highY; j++) {
				switch (act) {
				case on:
					lights[i][j] = 1;
					break;
				case off:
					lights[i][j] = 0;
					break;
				case toggle:
					lights[i][j] = !lights[i][j];
					break;
				}
			}
		}
		printf("Processed: %s\n", str);
	}

	lit = 0;
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			lit += lights[i][j];
		}
	}
	printf("%d lights lit.\n", lit);

	return 0;
}
