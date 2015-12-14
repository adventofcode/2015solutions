#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');

var reg_vowel = /([aeiou]).*?([aeiou]).*?([aeiou])/;
var reg_double = /(.)\1/;
var reg_bad = /(ab|cd|pq|xy)/;

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }

    lines = data.split("\n").slice(0,1000); // Cut the last newline out
    total = 0;

    for(var x = 0; x < lines.length; x++) {
        line = lines[x];
        if(reg_vowel.exec(line) && reg_double.exec(line) && !reg_bad.exec(line)) {
            total++;
        }
    }

    console.log(total);

});
