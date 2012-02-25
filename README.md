#jp

Read arbitrary file formats using JS scripts

## Script file

	jp.log("Start");
	jp.mode = "text";
	jp.doc.list = [];
	
	while(!jp.eof()) {
	    var row = {};
	
	    jp.read(/\s*/);
	    if(jp.eof())
	        break;
	
	    row.key = jp.read(/[0-9A-za-z_]+/);
	    jp.read(/\s*:\s*/);
	    row.value = jp.read(/[^\n]*/);
	
	    try {
	        jp.read(/impossibru!/);
	    } catch(e) {
	        // We can carry on like nothing happened
	    }
	
	    jp.doc.list.push(row);
	    jp.log(row.key["%val"] + " => " + row.value["%val"]);
	}
	
	jp.log(JSON.stringify(jp.doc));
