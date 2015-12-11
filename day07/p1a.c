#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER 80

#define WIRE_READ 1
#define WIRE_WRITE 2
#define WIRE_SAFEWRITE 4
#define WIRE_PRINT 8
#define WIRE_FREE 16

enum gates {
	NOOP,
	AND,
	OR,
	NOT,
	LSHIFT,
	RSHIFT,
	GATES_MAX
};

char *gatesStr[] = {
	"",
	"AND",
	"OR",
	"NOT",
	"LSHIFT",
	"RSHIFT",
	""
};

enum state {
	init,
	op1,
	op2,
	op3,
	through,
	dest,
	end
};

struct operand {
	enum gates op;
	uint16_t value;
};

struct operation {
	enum gates gate;
	unsigned char numVals;
	char **vals;
	char *dest;
	struct operation *next;
	struct operation *prev;
};

struct wires {
	char* name;
	uint16_t value;
	struct wires *left;
	struct wires *right;
};

struct buffer {
	char *line;
	struct buffer *next;
};

struct buffer *AddToBuff(struct buffer *, char *);
void FreeBuff(struct buffer *);

char *AddToString(char *, int *, char);
int32_t ComputeVal(struct wires *, struct operation *op);
char StrIsZero(char *);
struct operation *AddOperation(struct operation *, char *);
enum gates ComputeOperand(char *);
void OperationsToWires(struct wires *, struct operation *);
void RemoveOp(struct operation *);

void PrintWires(struct wires *);
struct wires *GetFromWire(struct wires *, char *);
void SaveToWire(struct wires *, char *, uint16_t);
void FreeWires(struct wires *);
struct wires *TraverseWire(struct wires *, char *, uint16_t, unsigned char);
struct wires *InitWire(struct wires *, char *, uint16_t);
void CleanWire(struct wires *);

int main(void)
{
	char error = 1;
	char *input;
	char c;
	int str_buff = BUFFER;
	if (!(input = calloc(BUFFER, sizeof(char)))) {
		goto freeinput;
	}
	struct wires *wire;
	if (!(wire = calloc(1, sizeof(struct wires)))) {
		goto freewire;
	}
	struct operation *operations, *curOp, *tmpOp;
	if (!(operations = calloc(1, sizeof(struct operation)))) {
		fprintf(stderr, "Can't allocate operations memory\n");
		goto freemem;
	}
	struct buffer *inBuff, *tmpBuff;
	if (!(inBuff = calloc(1, sizeof(struct buffer)))) {
		fprintf(stderr, "Can't allocate buffer memory\n");
		goto freebuff;
	}
	//printf("Starting inputting\n");
	tmpBuff = inBuff;
	while ((c = fgetc(stdin)) && !feof(stdin)) {
		//puts(input);
		if (c == '\n' || feof(stdin)) {
			tmpBuff = AddToBuff(tmpBuff, input);
			memset(input, 0, strlen(input));
		} else {
			input = AddToString(input, &str_buff, c);
		}
		//puts(input);
	}
	//printf("Starting processing\n");
	curOp = operations;
	for (tmpBuff = inBuff->next; tmpBuff; tmpBuff = tmpBuff->next) {
		tmpOp = calloc(1, sizeof(struct operation));
		curOp->next = tmpOp;
		tmpOp->prev = curOp;
		if (!(curOp = AddOperation(curOp->next, tmpBuff->line))) {
			goto freemem;
		}
	}
	//printf("Starting operating\n");
	OperationsToWires(wire, operations);
	//printf("Starting printing\n");
	PrintWires(wire);
	//printf("Starting freeing\n");
	FreeWires(wire);
	error = 0; // If executing, no memory errors.
freebuff:
	FreeBuff(inBuff);
freemem:
	free(operations);
freewire:
	free(wire);
freeinput:
	free(input);
	return error;
}

char *AddToString(char *str, int *strAllocSize, char add)
{
	if (strlen(str) + 2 >= *strAllocSize) {
		////printf("Alloc size before: %d\n", *strAllocSize);
		*strAllocSize *= 2;
		////printf("Alloc size after: %d\n", *strAllocSize);
		str = realloc(str, sizeof(char)*(*strAllocSize));
		////printf("Ended realloc\n");
	}
	if (str) {
		str[strlen(str)] = add;
		str[strlen(str)+1] = 0;
	}
	return str;
}

struct buffer *AddToBuff(struct buffer *curBuff, char *str)
{
	unsigned long len = strlen(str);
	while (curBuff->next) {
		curBuff = curBuff->next;
	}
	curBuff->next = calloc(1,sizeof(struct buffer));
	curBuff->next->line = malloc((len+1)*sizeof(char));
	strcpy(curBuff->next->line,str);
	return curBuff->next;
}

void FreeBuff(struct buffer *topBuff)
{
	struct buffer *curBuff, *tmpBuff;
	curBuff = topBuff;
	while (curBuff) {
		tmpBuff = curBuff->next;
		free(curBuff);
		curBuff=tmpBuff;
	}
}

void OperationsToWires(struct wires *wire, struct operation *topOp)
{
	struct operation *tmpOp, *curOp;
	int32_t val;
	while (topOp->next) {
		for (curOp = topOp->next; curOp; curOp = curOp->next) {
			if ((val = ComputeVal(wire,curOp)) < 0) {
				////printf("Couldn't find a value for %s\n", wire->name);
				continue;
			} else {
				SaveToWire(wire, curOp->dest, val);
				tmpOp = curOp->prev;
				RemoveOp(curOp);
				curOp = tmpOp;
			}
		}
	}
}

void RemoveOp(struct operation *op)
{
	// Don't give a root node.
	if (op->vals) {
		if (op->vals[0]) {
			free(op->vals[0]);
		}
		if (op->vals[1]) {
			free(op->vals[1]);
		}
		if (op->vals[2]) {
			free(op->vals[2]);
		}
		free(op->vals);
	}
	if (op->dest) {
		free(op->dest);
	}
	if (op->prev) {
		op->prev->next = op->next;
	}
	if (op->next) {
		op->next->prev = op->prev;
	}
	op->next = NULL;
	op->prev = NULL;
	op->dest = NULL;
	op->vals = NULL;
	free(op);
}

struct operation *AddOperation(struct operation *curOp, char *input)
{
	char *token = malloc((strlen(input)+1)*sizeof(char));
	strcpy(token,input);
	token = strtok(token," \n");
	if (!token) {
		return curOp->prev;
	}
	unsigned char j = 0;
	enum state state = init;
	enum gates gate;
	if (!(curOp->vals = calloc(3, sizeof(char *)))) {
		fprintf(stderr, "Can't allocate vals memory\n");
		return NULL;
	}
	do {
		if (!strcmp(token,"->") && state != end) {
			state = through;
		}
		if (state < through) {
			state++;
			if ((gate = ComputeOperand(token))) {
				curOp->gate = gate;
				continue;
			}
			curOp->vals[j] = calloc(strlen(token)+1,sizeof(char));
			if (!curOp->vals[j]) {
				fprintf(stderr, "Can't allocate vals[] memory\n");
				return NULL;
			}
			strcpy(curOp->vals[j++],token);
			////printf("Added token to op: %s\n", token);
			curOp->numVals = j;
		} else if (state == through) {
			state = dest;
		} else if (state == dest) {
			curOp->dest = calloc(strlen(token)+1,sizeof(char));
			if (!curOp->dest) {
				fprintf(stderr, "Can't allocate dest memory\n");
				return NULL;
			}
			strcpy(curOp->dest,token);
			state = end;
		} 
	} while ((token = strtok(NULL," \n")) != NULL);
	if (!curOp->dest) {
		return NULL;
	}
	free(token);
	return curOp;
}

int32_t ComputeVal(struct wires *wire, struct operation *op)
{
	uint16_t val[3];
	uint16_t retVal = 0;
	uint16_t in;
	char *endPtr;
	struct wires *gotWire;
	unsigned int i = 0, j = 0;
	char errorFetching = 0;
	for (i = 0; i < op->numVals; i++) {
		in = strtol(op->vals[i], &endPtr, 10);
		if (endPtr == op->vals[i]) {
			gotWire = GetFromWire(wire,op->vals[i]);
			if (!gotWire) {
				////printf("Null wire returned\n");
				errorFetching = 1;
			} else {
				in = gotWire->value;
			}
		}
		if (errorFetching) {
			return -1;
		} else {
			val[j++] = in;
			val[j] = 0;
		}
	}
	switch (op->gate) {
	case AND:
		retVal = val[0] & val[1];
		break;
	case OR:
		retVal = val[0] | val[1];
		break;
	case NOT:
		retVal = ~val[0];
		break;
	case LSHIFT:
		retVal = val[0] << val[1];
		break;
	case RSHIFT:
		retVal = val[0] >> val[1];
		break;
	case NOOP:
		retVal = val[0];
		break;
	case GATES_MAX:
		fprintf(stderr, "Operand computation went wrong.\n");
		break;
	}
	return retVal;
}

enum gates ComputeOperand(char *op)
{
	enum gates i;
	for (i = NOOP; i < GATES_MAX; i++) {
		if (!strcmp(op, gatesStr[i])) {
			return i;
		}
	}
	return NOOP;
}

char StrIsZero(char *str)
{
	unsigned int i;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] != '0') {
			return 0;
		}
	}
	return 1;
}

void SaveToWire(struct wires *wire, char *index, uint16_t in_val)
{
	////printf("Saved %s: %d.\n", index, in_val);
	TraverseWire(wire, index, in_val, WIRE_SAFEWRITE);
}

struct wires *GetFromWire(struct wires *wire, char *index)
{
	return TraverseWire(wire, index,  0, WIRE_READ);
}

void PrintWires(struct wires *wire)
{
	TraverseWire(wire, NULL, 0, WIRE_PRINT);
}

void FreeWires(struct wires *wire)
{
	TraverseWire(wire, NULL, 0, WIRE_FREE);
	CleanWire(wire);
}

struct wires *TraverseWire(struct wires *wire, char *index,
		uint16_t val, unsigned char flags)
{
	struct wires *retVal, *tmp;
	char goLeft, goRight, i;
	unsigned char j;
	struct wires **direction[2];
	memset(direction,0,sizeof(direction));
	goLeft = goRight = 0;
	retVal = NULL;
	if (flags & WIRE_PRINT) {
		if (wire->name) {
			printf("%s: %d\n", wire->name, wire->value);
		}
	}
	if (flags & (WIRE_PRINT | WIRE_FREE)) {
		goLeft = goRight = 1;
	}
	if (wire->name && index) {
		i = strcmp(index, wire->name);
		if (i < 0) {
			goLeft = 1;
		} else if (i > 0) {
			goRight = 1;
		} else if (!i && (flags & WIRE_READ)) {
			retVal = wire;
		} else if (!i && (flags & WIRE_WRITE) && !(flags & WIRE_SAFEWRITE)) {
			wire->value = val;
		}
	} else if (!wire->name && index && (flags & (WIRE_WRITE | WIRE_SAFEWRITE))) {
		if (!InitWire(wire, index, val)) {
			return 0;
		}
	}
	j = 0;
	if (goLeft) {
		direction[j] = &wire->left;
		j++;
	} 
	if (goRight) {
		direction[j] = &wire->right;
		j++;
	}
	while (j > 0) {
		j--;
		if (*direction[j]) {
			tmp = TraverseWire(*direction[j], index, val, flags);
			retVal = tmp ? tmp : retVal;
		} else if (flags & (WIRE_WRITE | WIRE_SAFEWRITE)) {
			*direction[j] = calloc(1, sizeof(struct wires));
			if (!(*direction[j]) | !InitWire(*direction[j], index, val)) {
				return 0;
			}
		}
		if (*direction[j] && (flags & WIRE_FREE)) {
			CleanWire(*direction[j]);
			free(*direction[j]);
		}
	}
	return retVal;
}

struct wires *InitWire(struct wires *wire, char *name, uint16_t val)
{
	wire->name = malloc((strlen(name)+1)*sizeof(char));
	if (!wire->name) {
		fprintf(stderr, "Could not allocate memory for wire string.\n");
		return 0;
	}
	strcpy(wire->name, name);
	wire->value = val;
	return wire;
}

void CleanWire(struct wires *wire)
{
	if (wire->name) {
		free(wire->name);
	}
	wire->value = 0;
	wire->name = NULL;
	wire->left = NULL;
	wire->right = NULL;
}
