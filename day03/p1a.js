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

    cur = new Location(0, 0);

    locations = [cur];

    for(var i = 0; i < data.length; i++) {
        cur = cur.move(data[i]);
        if(!search(locations, cur)) {
            locations.push(cur);
        }
    }
    console.log(locations.length);
});
