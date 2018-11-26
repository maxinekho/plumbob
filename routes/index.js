var express = require('express');
var SerialPort = require('serialport')
// var five = require("johnny-five");
var router = express.Router();

var bodyParser = require('body-parser');
router.use(bodyParser.json());
router.use(bodyParser.urlencoded({ extended: false }));


// var board = new five.Board();
//
// board.on("ready", function() {
// console.log("Ready!");
//
// var led = new five.Led(13);
// led.blink(500);
// });

const port = new SerialPort('/dev/cu.wchusbserial14130', {
  baudRate: 9600,
  autoOpen: false
})

port.open(function (err) {
  console.log("port opened");
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
})

// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
})



/* GET home page. */
router.get('/', function(req, res, next) {
  // console.log("writing to the LED strip");
  // port.write('4'+'\n');
  res.render('mood-ring', { title: 'Mood Ring'});
});

/* POST to main page. */
router.post('/', function(req, res, next) {
  console.log("emotion change: "+ req.body.emotion);
  port.write(req.body.serialVal+'\n');
  res.status(200).end();
  // console.log("got a post request: " + JSON.parse(req.body));
})


module.exports = router;
