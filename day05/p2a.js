#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');

var reg_the_one = /(?=.*(..).*\1)(?=.*(.).\2)/;

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }

    lines = data.split("\n").slice(0,1000); // Cut the last newline out
    total = 0;

    for(var x = 0; x < lines.length; x++) {
        if(reg_the_one.exec(lines[x])) {
            total++;
        }
    }
    console.log(total);
});
