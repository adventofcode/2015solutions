#include <stdio.h>

unsigned long long CalcSize(unsigned int, unsigned int, unsigned int);

int main(void)
{
	unsigned long long total = 0;
	unsigned int dim[3], temp;
	char c;
	unsigned char i;
	temp = dim[0] = dim[1] = dim[2] = 0;
	while ((c = fgetc(stdin)) != EOF) {
		switch (c) {
		case '9':
		case '8':
		case '7':
		case '6':
		case '5':
		case '4':
		case '3':
		case '2':
		case '1':
		case '0':
			temp *= 10;
			temp += c-'0';
			break;
		case 'x':
		case '\n':
			for (i = 0; dim[i] != 0; i++) { ; }
			dim[i] = temp;
			temp = 0;
			break;
		default:
			printf("Unknown character: %d\n", c);
			break;
		}
		if (c == '\n') {
			total += CalcSize(dim[0], dim[1], dim[2]);
			temp = dim[0] = dim[1] = dim[2] = 0;
		}
	}
	printf("Total size: %llu\n", total);
	return 0;
}

unsigned long long CalcSize(unsigned int w, unsigned int l, unsigned int h)
{
	unsigned long long a = w*l;
	unsigned long long b = w*h;
	unsigned long long c = l*h;
	unsigned long long retVal = 2*a + 2*b + 2*c;
	unsigned long long smallest = a < b ? a : b;
	smallest = smallest < c ? smallest : c;
	retVal += smallest;
	return retVal;
}
