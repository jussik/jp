// jp.log allows us to monitor our progress
jp.log("Start");
// "text" is the only supported mode at the moment
jp.mode = "text";
// jp.doc is what we'll be filling
jp.doc.list = [];

// jp.eof() checks to see if we've hit the end of the data file
while(!jp.eof()) {
    var row = {};

    // use jp.read to read a chunk from the file, here using a RegExp
    jp.read(/\s*/);
    if(jp.eof())
        break;

    // jp.read returns a value we can then add to jp.doc
    row.key = jp.read(/[0-9A-za-z_]+/);
    jp.read(/\s*:\s*/);
    row.value = jp.read(/[^\n]*/);

    try {
        // If a RegExp doesn't match, it throws an exception into the javascript
        jp.read(/impossibru!/);
    } catch(e) {
        // We can carry on like nothing happened
    }

    jp.doc.list.push(row);

    jp.log(row.key["%val"] + " => " + row.value["%val"]);
}

jp.log(JSON.stringify(jp.doc));
