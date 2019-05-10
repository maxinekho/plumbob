var express = require('express');
var SerialPort = require('serialport');
var router = express.Router();

var bodyParser = require('body-parser');
router.use(bodyParser.json());
router.use(bodyParser.urlencoded({ extended: false }));

const port = new SerialPort('/dev/cu.SLAB_USBtoUART', {
  baudRate: 9600,
  autoOpen: false
});

port.open(function (err) {
  console.log("port opened");
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
});

// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
});



/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('mood-ring', { title: 'Plumbob, IRL'});
});

/* POST to main page. */
router.post('/', function(req, res, next) {
  console.log("emotion change: "+ req.body.emotion);
  port.write(req.body.serialVal+'\n');
  res.status(200).end();
})


module.exports = router;
