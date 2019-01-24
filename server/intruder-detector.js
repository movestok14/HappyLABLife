const { StringDecoder } = require('string_decoder')
const nodemailer = require('nodemailer')
const moment = require('moment')
const Raspistill = require('node-raspistill').Raspistill
const transporter = nodemailer.createTransport({
  service: 'gmail',
  auth: {
    type: 'OAuth2',
    user: 'its319hun@gmail.com',
    clientId: '~~~~~',
    clientSecret: '~~~~',
    refreshToken: '~~~~~'
  }
})

const camera = new Raspistill({
  width: 800,
  height: 600,
  outputDir: '/home/pi/Desktop/intruder-detect/public'
})


const SerialPort = require('serialport')
const port = new SerialPort('/dev/ttyACM0',{
  baudRate: 9600,
})
const Readline = SerialPort.parsers.Readline;
const parser = port.pipe(new Readline({ delimiter: '\r\n' }));
const decoder = new StringDecoder('utf8')




let attachments = []
let interval = null

console.log('Intruder detect started') //
parser.on('data', (data) => {
  const input = decoder.write(data)
  if (input === 'Motion detected!' && !interval) {
    console.log('Intruder detected')
    interval = setInterval(() => {
      camera.takePhoto().then((photo) => { 
        const image = photo.toString('base64')
        const imageBase64 = 'data:image/jpeg;base64,' + image
        attachments.push({
          path: imageBase64,
        })
      }).catch((e) => {})
    }, 700)
  } else if(input === 'Motion ended!') {
    if(interval) {
      clearInterval(interval);
      interval = null
    }
    
    
    if(attachments.length > 0) {
      const mailOptions = {
        from: 'its319hun@gmail.com', // sender address
        to: '~~~@gmail.com', // receivers
        subject: 'intruder detected', // Subject
        html: moment().format("MMM Do YY"),// text
        attachments: attachments
      };
      transporter.sendMail(mailOptions, function (err, info) {
        if (err)
          console.log(err)
        else
          console.log('sending email with ' + attachments.length + ' photos')
      });
      attachments = []
    }
  }
})

