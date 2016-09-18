var SerialPort = require("serialport");
var port = new SerialPort("COM3", {
  baudRate: 9600,
});

var express = require('express')
var app = express()
 
var time = 0
var numDigits = 0
var literalTime = ""
 
app.get('/', function (req, res) {
  res.send(time.toString())
})
 
app.listen(3000)

function reverse(s) {
  return s.split('').reverse().join('');
}

function resetValues() {
    numDigits = 0
    literalTime = ""
}

port.on('data', function (data) {
  if (data == -2) {
      // Reset
      resetValues()
      time = 0
  }
  else if (data == -1) {
      // Submit
      time = 0
      if (literalTime != "") {
          literalTime = reverse(literalTime)
          time += parseInt(literalTime.substring(0, 1))
          if (numDigits >= 2) {
              time += parseInt(literalTime.substring(1, 2))*10
          }
          if (numDigits >= 3) {
              time += parseInt(literalTime.substring(2, 3))*60
          }
          if (numDigits >= 4) {
              time += parseInt(literalTime.substring(3, 4))*60
          }
      }
      console.log("Submitted: " + time)
      resetValues()
  }
  else if (numDigits < 5 && data >= 0 && data <= 9) {
    literalTime += data.toString()
    numDigits++;
    console.log("Data: " + data);
    console.log("Time: " + literalTime)
  }
  
});