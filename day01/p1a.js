#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');

String.prototype.count = function(term) {
    return Array.prototype.filter.call(this, function (x) {
        return x == term;
    }).length;
}

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }
    console.log(data.count('(') - data.count(')'));
});
