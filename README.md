#jp

Read arbitrary file formats using JS scripts.
Still early days and everything is likely to change. Implemented in C++ and uses the [V8](http://code.google.com/p/v8/) javascript engine.

## Example script file

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
    
        // jp.read returns an object we can then add to jp.doc
        // the result is in the form {"%key":resultString,"%pos",positionInFile}
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

## Example data file for above script

    key1:value1
    key2:value2
    foo:*&$

## Output from the above script and data

    Log:0:Start
    Log:11:key1 => value1
    Log:23:key2 => value2
    Log:32:foo => *%"$
    Log:33:{"list":[{"key":{"%val":"key1","%pos":0},"value":{"%val":"value1","%pos":5}},{ ... }, ... ]}
