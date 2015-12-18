#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }

    var floor = 0;

    for(var i = 0; i < data.length; i++) {
        if(data[i] == '(') {
            floor++;
        } else if(data[i] == ')') {
            floor--;
        }

        if(floor < 0) {
            console.log(i+1);
            return;
        }
    }

    console.log("Basement not found");
});
