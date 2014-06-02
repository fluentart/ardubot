var http 		= require('http')				//HTTP
var	url	 		= require('url')
var path 		= require('path')
var fs 			= require('fs')					//FILESYSTEM				
var util 		= require('util')

var mimeTypes = {
    "html": "text/html",
    "jpeg": "image/jpeg",
    "jpg": "image/jpeg",
    "png": "image/png",
    "js": "text/javascript",
    "css": "text/css"};

var webserver = http.createServer(function (req, res) {
	var uri = url.parse(req.url).pathname;
	var filename = path.join(process.cwd()+"/static", uri);
	console.log(uri)
	if (uri == "/") {
			var page = process.cwd()+"/static/index.htm"
			var mimeType = mimeTypes[path.extname(page).split(".")[1]]
			res.writeHead(200, {'Content-Type': mimeType})
			var fileStream = fs.createReadStream(page);
			fileStream.pipe(res);
			return;
	}
	

	//####################   STATIC FILES ################
	fs.exists(filename, function(exists) {
		if (!exists) {
			//console.log("404:"+filename);		
			res.writeHead(404, {'Content-Type': 'text/html'});
		  	res.write('error 404');
		  	res.end();
		  	return;
		} 

		var stats = fs.statSync(filename);
		//console.log("STATS: "+stats.isDirectory());

		if (stats.isDirectory()) {
			res.writeHead(200, {'Content-Type':'text/html'})
			res.write('Are you lost?')
			res.end();
		} else {
			var mimeType = mimeTypes[path.extname(filename).split(".")[1]]
			res.writeHead(200, {'Content-Type': mimeType})
			var fileStream = fs.createReadStream(filename);
			fileStream.pipe(res);	
		}		
	});	//end static server
	
})





var SerialPort = require("serialport"); //so we can access the serial port
var os = require("os");
var scraper = require('json-scrape')();


var arduino;
//LIST DEVICES
SerialPort.list( function (err, ports) {
	for (var num in ports) {
		console.log(ports[num])
		if (ports[num].manufacturer.slice[0,5] == "Arduino".slice[0,5]) {
			console.log("Arduino detected")
			arduino = new SerialPort.SerialPort(ports[num].comName, {baudrate: 115200});
			arduConnect(arduino);
		}
	}
});




var arduConnect = function (connection) {
	connection.on("data", arduDatahandler);
}

var arduDatahandler = function (data) {
	var strdata = data.toString()
	scraper.write(data); 
}

var io = require('socket.io').listen(webserver, {log: false});

io.sockets.on('connection', function (socket) {
  
  socket.on('toArdu', function (data) {
    var test = JSON.stringify(data)    
    console.log(test);
    arduino.write(test)
  });
  
});

scraper.on('data', function (cleandata) {
	console.log(cleandata)
	io.sockets.emit("ardu", {serial: cleandata})		
});


webserver.listen(8000, "127.0.0.1");




