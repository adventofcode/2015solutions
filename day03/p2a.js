#!/usr/bin/env node
// By Garrett Greenwood
// Dec 2015
// electricexploits.net

var fs = require('fs');

function Location(x, y) {
    return {
        x: x,
        y: y,
        equals: function(loc) {
            return loc.x == this.x & loc.y == this.y;
        },
        move: function(dir) {
            switch(dir) {
                case '^': return new Location(this.x, this.y + 1);
                case '>': return new Location(this.x + 1, this.y);
                case 'v': return new Location(this.x, this.y - 1);
                case '<': return new Location(this.x - 1, this.y);
                default: return new Location(0, 0);
            }
        }
    };
}

function search(array, loc) {
    return array.filter(function(x) {
        return loc.equals(x);
    }).length;
}

fs.readFile(process.argv[2], 'utf8', function(err, data) {
    if(err) {
        console.log("Error reading file");
        return;
    }

    santa = new Location(0, 0);
    robot_santa = new Location(0, 0);

    // Need to replace this with a hashmap
    locations = [santa];

    for(var i = 0; i < data.length/2; i++) {
        santa = santa.move(data[2 * i]);
        if(!search(locations, santa)) {
            locations.push(santa);
        }
        robot_santa = robot_santa.move(data[2 * i + 1]);
        if(!search(locations, robot_santa)) {
            locations.push(robot_santa);
        }
    }
    console.log(locations.length);
});
