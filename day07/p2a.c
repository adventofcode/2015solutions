#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER 80

// Used later to specify actions.
#define WIRE_READ 1
#define WIRE_WRITE 2
#define WIRE_SAFEWRITE 4
#define WIRE_PRINT 8
#define WIRE_FREE 16

// NOOP is a default value. GATES_MAX is for iteration
enum gates {
	NOOP,
	AND,
	OR,
	NOT,
	LSHIFT,
	RSHIFT,
	GATES_MAX
};

// Strings with indicies corrosponding to enum gates values.
char *gatesStr[] = {
	"",
	"AND",
	"OR",
	"NOT",
	"LSHIFT",
	"RSHIFT",
	""
};

// For basic state machine parsing of input.
enum state {
	init,
	op1,
	op2,
	op3,
	through,
	dest,
	end
};

// Probably better as a union.
struct operand {
	enum gates op;
	uint16_t value;
};

// Struct containing the instruction on a given line.
struct operation {
	enum gates gate;
	unsigned char numVals;
	char **vals;
	char *dest;
	struct operation *next;
	struct operation *prev;
};

// Wire and value, for when parsing is done.
struct wires {
	char* name;
	uint16_t value;
	struct wires *left;
	struct wires *right;
};

// Lazy man's growing char array with Easy Iteration functionality.
struct buffer {
	char *line;
	struct buffer *next;
};

// Poor man's string solution.
struct buffer *AddToBuff(struct buffer *, char *);
void FreeBuff(struct buffer *);

// Ever expanding character string.
char *AddToString(char *, int *, char);

// Relating to operations and wires.
int32_t ComputeVal(struct wires *, struct operation *op);
struct operation *AddOperation(struct operation *, char *);
enum gates ComputeOperand(char *);
void OperationsToWires(struct wires *, struct operation *);
void RemoveOp(struct operation *);

// Following 4 just wrap calls to TraverseWire
void PrintWires(struct wires *);
struct wires *GetFromWire(struct wires *, char *);
void SaveToWire(struct wires *, char *, uint16_t);
void FreeWires(struct wires *);
// All BST traversion and operation code.
struct wires *TraverseWire(struct wires *, char *, uint16_t, unsigned char);
// Simplifying allocation
struct wires *InitWire(struct wires *, char *, uint16_t);
// Simplifying frees
void CleanWire(struct wires *);

int main(void)
{
	char error = 1;
	char *input;
	char c;
	int32_t a = -1;
	struct wires *tmpWire;
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
	// Declarations done, now down to work.
	tmpBuff = inBuff;
	// Get input and store in the buffers.
	while ((c = fgetc(stdin)) && !feof(stdin)) {
		if (c == '\n' || feof(stdin)) {
			tmpBuff = AddToBuff(tmpBuff, input);
			memset(input, 0, strlen(input));
		} else {
			input = AddToString(input, &str_buff, c);
		}
	}
	// Iterate at least once over the input
	do {
		// If "a" has a value, wipe everything, give it to "b"
		if ((tmpWire = GetFromWire(wire, "a"))) {
			a = tmpWire->value;
			FreeWires(wire);
			SaveToWire(wire, "b", a);
		} else {
			a = -1; // Flag value.
		}
		curOp = operations;
		// For every buffer, parse it into struct operation.
		for (tmpBuff = inBuff->next; tmpBuff; tmpBuff = tmpBuff->next) {
			tmpOp = calloc(1, sizeof(struct operation));
			curOp->next = tmpOp;
			tmpOp->prev = curOp;
			if (!(curOp = AddOperation(curOp->next, tmpBuff->line))) {
				goto freemem;
			}
		}
		// Then put into wires.
		OperationsToWires(wire, operations);
	} while (a == -1);
	PrintWires(wire);
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
	// If too small, realloc. Then try to add "add" and '\0' to the end.
	if (strlen(str) + 2 >= *strAllocSize) {
		*strAllocSize *= 2;
		str = realloc(str, sizeof(char)*(*strAllocSize));
	}
	if (str) {
		unsigned long length = strlen(str);
		str[length] = add;
		str[length+1] = 0;
	}
	return str;
}

struct buffer *AddToBuff(struct buffer *curBuff, char *str)
{
	// Given a buffer, put the string in the next one and return the
	// next buffer.
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
	// Free every sub-buffer of topBuff.
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
	// Given operation lvalue -> rvalue
	struct operation *tmpOp, *curOp;
	int32_t val;
	while (topOp->next) {
		// While there are operations on the list
		for (curOp = topOp->next; curOp; curOp = curOp->next) {
			// And if that operation has a confirmed lvalue
			if ((val = ComputeVal(wire,curOp)) < 0) {
				continue;
			} else {
				// write lvalue to rvalue and remove operation
				// from the list.
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
	// Don't give a root node. But probably fine if you do.
	// Clear all values, introduce before and after to each other, and
	// gracefully free yourself.
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
	// Parse string into an operation tokenwise.
	char *token = malloc((strlen(input)+1)*sizeof(char));
	strcpy(token,input); // don't destroy input which strtok() can do.
	token = strtok(token," \n");
	// Make sure there is something to do.
	if (!token) {
		return curOp->prev;
	}
	unsigned char j = 0;
	// We use a state machine to parse each line.
	enum state state = init;
	enum gates gate;
	if (!(curOp->vals = calloc(3, sizeof(char *)))) {
		fprintf(stderr, "Can't allocate vals memory\n");
		return NULL;
	}
	do { // State machine.
	/** a OP b -> c
	 *  a OP -> b -- dunno if possible, but parser allows it.
	 *  OP a -> b
	 *  a -> b
	 * start -> op1 -> op2 -> op3 -> through -> dest -> end -> \
	 *            \______\______\_____/                   \____/
	 */
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
	// Ensure we got what we came for, that the state machine made it far
	// enough to be sure of success.
	if (!curOp->dest) {
		return NULL;
	}
	free(token);
	return curOp;
}

int32_t ComputeVal(struct wires *wire, struct operation *op)
{
	// Given an operation, and the wire object, see if operation may run.
	uint16_t val[3];
	uint16_t retVal = 0;
	uint16_t in;
	char *endPtr;
	struct wires *gotWire;
	unsigned int i = 0, j = 0;
	char errorFetching = 0;
	for (i = 0; i < op->numVals; i++) {
		// For each value
		in = strtol(op->vals[i], &endPtr, 10);
		// Try and parse it as a number
		if (endPtr == op->vals[i]) { // And if that doesn't work
			gotWire = GetFromWire(wire,op->vals[i]);
			if (!gotWire) { // Try the wires.
				errorFetching = 1; // but prepare for failure
			} else {
				in = gotWire->value;
			}
		}
		// Error if necessary, otherwise integer value and continue.
		if (errorFetching) {
			return -1;
		} else {
			val[j++] = in;
			val[j] = 0;
		}
	}
	switch (op->gate) { // Act on the gate, if any.
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
	case GATES_MAX: // Not possible.
		fprintf(stderr, "Operand computation went wrong.\n");
		break;
	}
	return retVal;
}

enum gates ComputeOperand(char *op)
{
	// Given a string try and compute the enum value for it.
	enum gates i;
	for (i = NOOP; i < GATES_MAX; i++) {
		if (!strcmp(op, gatesStr[i])) {
			return i;
		}
	}
	return NOOP;
}

// Next four just wrap TraverseWire calls for readability
void SaveToWire(struct wires *wire, char *index, uint16_t in_val)
{
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
	// A poor man's binary search tree. In theory I can print, read, write,
	// and free, all in the same call. Not recommended or very useful.
	// Flags choose the operation.
	struct wires *retVal, *tmp;
	char goLeft, goRight, i;
	unsigned char j;
	struct wires **direction[2]; // left or right.
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
	// Choose the next direction
	if (goLeft) {
		direction[j] = &wire->left;
		j++;
	} 
	if (goRight) {
		direction[j] = &wire->right;
		j++;
	}
	// Loop over the directions given.
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
	// Instantiate a wire with the given attributes.
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
	// Delete all attributes a wire has and free any memory.
	if (wire->name) {
		free(wire->name);
	}
	wire->value = 0;
	wire->name = NULL;
	wire->left = NULL;
	wire->right = NULL;
}
