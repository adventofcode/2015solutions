#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');

// Allow us to call 'exec' on a string for its exact value, to match Operation.exec()
String.prototype.exec = function() {
    return this.valueOf();
};

re_constant = /(\d|[ ])/;

function Operation(func, re) {
    // Instance methods of Operations
    function op(line) {
        args = re.exec(line).slice(1,4);

        this.a = args[0];
        this.b = args[1];
        this.next = args[2];

        this.cache = null;

        this.exec = function(expressions) {
            // Evaluate whether the operand is a constant or another net
            if(!this.cache) {
                console.log("Evaluating net %s", this.next);
                var a = re_constant.exec(this.a) ? this.a : expressions[this.a];
                var b = re_constant.exec(this.b) ? this.b : expressions[this.b];
                this.cache = func(a.exec(expressions), b.exec(expressions));
            } 
            return this.cache;
        };
    }

    // Static Operation methods
    op.re = re;
    op.match = function(line) {
        return this.re.exec(line);
    }
    return op;
}

var Constant = new Operation(function(a, b) {
    return a;
}, /(\S+)( )-> ([^\d]+)/);

var And = new Operation(function(a, b) {
    return a & b;
}, /(\S+) AND (\S+) -> ([^\d]+)/);

var Or = new Operation(function(a, b) {
    return a | b;
}, /(\S+) OR (\S+) -> ([^\d]+)/);

var LShift = new Operation(function(a,b) {
    return a << b;
}, /(\S+) LSHIFT (\d+) -> ([^\d]+)/);

var RShift = new Operation(function(a,b) {
    return a >> b;
}, /(\S+) RSHIFT (\d+) -> ([^\d]+)/);

var Not = new Operation(function(a, b) {
    return a ^ 0xffff;
}, /NOT (\S+)( )-> ([^\d]+)/);

var operations = [Constant, And, Or, LShift, RShift, Not];

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }

    lines = data.split("\n");
    lines = lines.slice(0, lines.length - 1);   // Cut the last newline out

    connections = [];

    for(var i = 0; i < lines.length; i++) {
        line = lines[i];
        var next;
        for(var op = 0; op < operations.length; op++) {
            if(operations[op].match(line)) {
                next = new operations[op](line);
            }
        }
        if(!next) {
            console.log(line + "NOT RECOGNIZED");
        }

        console.log("Adding net %s", next.next);
        connections[next.next] = next;
    }

    console.log(connections['a'].exec(connections));
});
