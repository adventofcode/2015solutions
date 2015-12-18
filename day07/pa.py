INPUT_FILENAME = 'inputb' # change this as needed
from collections import defaultdict


def _16_bit(i):
    """
    Helper method to squish a Python integer into 16 bits, truncating
    higher bits.
    """
    return i & 0xFFFF
    

class Component(object):
    """
    Base class for all electronic components.
    """
    _value = None

    @property
    def value(self):
        """
        Returns the 16 bit value of the component, evaluating it and
        traversing all inputs if necessary, and caching the results.

        
        
        Subclasses must implement evaluate(), but should use the value
        properties of its sources.
        """

        if self._value is not None:
            return self._value
        self._value = self.evaluate()
        return self._value
    
    def evaluate(self):
        """
        Every component has a 16-bit unsigned integer that it produces
        from its inputs.
        
        Inputs may be evaluated multiple times, but should cache the
        results in self.value to avoid O(N^2) (or worse) problems when
        a component with a long chain or network of subcomponents is evaluated.
        """
        raise NotImplementedError
    
    def get_source_by_name(self, name):
        """
        Digs a source wire out of the list of wires, by name.
        """
        global wires
        return wires[name]
    
    def get_or_eval(self, source):
        """
        Given a source, return either its value, if it has a static
        value, or evaluate it, possibly finding it by name if needed.
        """
        try:
            return int(source)
        except TypeError:
            # it's a component
            return source.value
        except ValueError:
            # it's a non-numeric string
            source = self.get_source_by_name(source)
            return source.value
    


class Wire(Component):
    """
    Used to represent a 16-bit bus with static inputs, or as a connection
    between one source and another component with this as a source.
    """

    def __init__(self, source=None):
        """
        Default of source = None is to allow use of defaultdict;
        evaulating a wire connected to nothing will produce an error.
        """
        self.source = source
    
    def evaluate(self):
        """
        Get the value of the source and return it, caching it.
        This could be a static input (an integer), or another
        component, which must in turn be evaluated.
        """
        return self.get_or_eval(self.source)


class AndGate(Component):
    """
    Represents an AND Gate.
    """
    def __init__(self, first, second):
        self.first = first
        self.second = second

    def evaluate(self):
        l_operand = self.get_or_eval(self.first)
        r_operand = self.get_or_eval(self.second)
        
        return _16_bit(l_operand & r_operand)


class OrGate(Component):
    """
    Represents an OR gate.
    """
    def __init__(self, first, second):
        self.first = first
        self.second = second

    def evaluate(self):
        l_operand = self.get_or_eval(self.first)
        r_operand = self.get_or_eval(self.second)
        
        return _16_bit(l_operand | r_operand)


class LshiftGate(Component):
    """
    Shifts an input left a fixed number of places.
    """
    def __init__(self, source, places):
        self.source = source
        self.places = int(places)

    def evaluate(self):
        source = self.get_or_eval(self.source)
        return _16_bit(source << self.places)
        

class RshiftGate(Component):
    """
    Shifts an input right a fixed number of places.
    """
    def __init__(self, source, places):
        self.source = source
        self.places = int(places)

    def evaluate(self):
        source = self.get_or_eval(self.source)
        return _16_bit(source >> self.places)


class NotGate(Component):
    def __init__(self, source):
        self.source = source
    
    def evaluate(self):
        source = self.get_or_eval(self.source)
        return _16_bit(~source)


def reset_components():
    """
    Removes the cached values from each component.
    Helpful for part 2, which asks to reset after changing an input.
    
    This could also be done with a deepcopy() before evaluating anything.
    """
    global wires
    for wire in wires.values():
        wire._value = None
        # also the wire's source, if a gate or another wire,
        # could also have a cached value.
        if isinstance(wire.source, Component):
            wire.source._value = None



def process_line(line):
    """
    Parses a line of input for type of Gate, inputs, and what
    wire to connect to the output.
    
    Inputs are stored as string keys to wires in the global
    wires dictionary.
    
    Output is store as a Wire in the wires dictionary; because
    wires is a defaultdict, is is possible to refer to wires
    that do not yet have inputs, such as in the following instructions:
    
    x -> y
    123 -> x
    """
    global wires
    if ' AND ' in line:
        line = line.replace('AND ', '').replace('-> ', '').strip()
        first, second, destination = line.split(' ')
        wires[destination].source = AndGate(first, second)
    elif ' OR ' in line:
        line = line.replace('OR ', '').replace('-> ', '').strip()
        first, second, destination = line.split(' ')
        wires[destination].source = OrGate(first, second)
    elif ' LSHIFT ' in line:
        line = line.replace('LSHIFT ', '').replace('-> ', '').strip()
        source, places, destination = line.split(' ')
        places = int(places)
        wires[destination].source = LshiftGate(source, places)
    elif ' RSHIFT ' in line:
        line = line.replace('RSHIFT ', '').replace('-> ', '').strip()
        source, places, destination = line.split(' ')
        places = int(places)
        wires[destination].source = RshiftGate(source, places)
    elif 'NOT ' in line:
        line = line.replace('NOT ', '').replace('-> ', '').strip()
        source, destination = line.split(' ')
        wires[destination].source = NotGate(source)
    else:
        # assignment, either a value or another wire by name
        # e.g.  123 -> q  puts 123 in wire q,
        # but   ll -> q  attaches wire ll to wire q
        value, destination = line.strip().split(' -> ')
        wires[destination].source = value


# TEST SCENARIO FROM PUZZLE DESCRIPTION
wires = defaultdict(Wire)
test_input = """123 -> x
456 -> y
x AND y -> d
x OR y -> e
x LSHIFT 2 -> f
y RSHIFT 2 -> g
NOT x -> h
NOT y -> i"""

for line in test_input.split("\n"):
    process_line(line)

results = dict()
for k, wire in wires.iteritems():
    results[k] = wire.evaluate()

assert results == {'e': 507, 'd': 72, 'g': 114, 'f': 492, 'i': 65079, 'h': 65412, 'y': 456, 'x': 123}
# END TEST


# PUZZLE INPUT
wires = defaultdict(Wire)

# Build the circuit
fh = open(INPUT_FILENAME, 'r')
for line in fh.readlines():
    process_line(line)
fh.close()

# Evaluate results for part 1
part_one_answer = wires['a'].evaluate()
print "Part one:", part_one_answer

# Evaluate results for part 2
reset_components()
wires['b'].source = part_one_answer
print "Part two:", wires['a'].evaluate()
