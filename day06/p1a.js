#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');

var re_off = /^turn off/;
var re_on = /^turn on/;
var re_toggle = /^toggle/;

var re_numbers = /(\d+)[^\d]+?(\d+)[^\d]+?(\d+)[^\d]+?(\d+)/;

function setLights(arr, coords, value) {
    var lowX = Math.min(coords[0], coords[2]);
    var highX = Math.max(coords[0], coords[2]);
    var lowY = Math.min(coords[1], coords[3]);
    var highY = Math.max(coords[1], coords[3]);
    for(var x = lowX; x <= highX; x++) {
        for(var y = lowY; y <= highY; y++) {
            arr[x][y] = value;
        }
    }
}

function toggleLights(arr, coords) {
    var lowX = Math.min(coords[0], coords[2]);
    var highX = Math.max(coords[0], coords[2]);
    var lowY = Math.min(coords[1], coords[3]);
    var highY = Math.max(coords[1], coords[3]);
    for(var x = lowX; x <= highX; x++) {
        for(var y = lowY; y <= highY; y++) {
            arr[x][y] = !arr[x][y];
        }
    }
}

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }

    lines = data.split("\n");
    lines = lines.slice(0, lines.length - 1);   // Cut the last newline out

    // Build the array of lights
    var arr = [];
    for(var x = 0; x < 1000; x++) {
        arr.push([]);
        for(var y = 0; y < 1000; y++) {
            arr[x].push(false);
        }
    }
    console.log("Lights initialized");

    console.log("Computing inputs...");
    for(var x = 0; x < lines.length; x++) {
        var line = lines[x];
        var coords = re_numbers.exec(line).slice(1,5);
        if(re_off.exec(line)) {
            setLights(arr, coords, false);
        } else if(re_on.exec(line)) {
            setLights(arr, coords, true);
        } else if(re_toggle.exec(line)) {
            toggleLights(arr, coords);
        } else {
            console.log(line + " NOT RECOGNIZED");
        }
    }
    console.log("Computed inputs");

    var count = 0;
    console.log("Counting lights...");
    for(var x = 0; x < 1000; x++) {
        count += arr[x].reduce(function(a,b) {
            return a+b;
        });
    }
    console.log(count);
});
