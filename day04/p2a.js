#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');
var crypto = require('crypto');

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }

    var md5 = crypto.createHash('md5');

    input = data.split('\n')[0];    // Trim trailing endline

    for(x = 0; x < 1000000000; x++) {
        if(x % 100000 == 0)
            console.log("Testing hash " + x);

        if(crypto.createHash('md5').update(input + x).digest('hex').slice(0,6) == '000000') {
            console.log("Hash found!");
            console.log(x);
            return;
        }
    }
});
