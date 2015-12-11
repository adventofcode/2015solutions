#!/usr/bin/env node

var fs = require('fs');

function getNums(line) {
    return line.split('x').map(function(x) {
        return parseInt(x, 10);
    }).sort(function(a, b) {
        return a - b;
    });
}

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }
    lines = data.split("\n").slice(0,1000); // Cut the last newline out

    total = 0;

    for(var i = 0; i < lines.length; i++) {
        line = lines[i];
        nums = getNums(line);
        total += 2 * (nums[0] + nums[1]) + (nums[0] * nums[1] * nums[2]);
    }
    console.log(total);
});
