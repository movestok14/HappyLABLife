#include "SPI.h"
#include "Phpoc.h"
 
PhpocServer server(80);
PhpocEmail email;
 
void setup() {
  Serial.begin(9600);
  while(!Serial)
    ;
 
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET | PF_LOG_APP);
  
  // set outgoing relay server and sender's e-mail address - naver
  email.setOutgoingServer("smtp.naver.com", 587);
  email.setOutgoingLogin("dhbaek2004", "**pw**"); // here
  email.setFrom("dhbaek2004@naver.com", "백대현");  // here
 
  // set receiver's e-mail address and subject
  email.setTo("dhbaek2004@naver.com", "백대현");  //here
  email.setSubject("Mail from PHPoC Shield for Arduino");
 
  // write e-mail message
  email.beginMessage();
  email.println("Hello, world!");
  email.println("I am PHPoC Shield for Arduino");
  email.println("Good bye");
  email.endMessage();
  
  // run websocket server
  server.beginWebSocket("remote_push");
 
  Serial.print("WebSocket server address : ");
  Serial.println(Phpoc.localIP());  
}
 
void loop() {
  // wait for a new client:
  PhpocClient client = server.available();
 
  if (client) {
    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
      if(thisChar == 'A') {
        Serial.println("button A press");
        // send e-mail
        if(email.send() > 0)
          Serial.println("Email send ok");
        else
          Serial.println("Email send failed");
      }
    }
  }
}
 
