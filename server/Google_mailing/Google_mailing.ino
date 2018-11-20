#include <Phpoc.h>

PhpocEmail email;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET | PF_LOG_APP);
  //Phpoc.begin();

  Serial.println("Sending email to gmail relay server");


  email.setOutgoingServer("smtp.gmail.com", 587);
  email.setOutgoingLogin("its319hun", "**PW**");

  email.setFrom("its319hun@gmail.com", "hun");
  email.setTo("**email**@naver.com", "HUN");
  email.setSubject("For Happy_LAB_Life!");

  email.beginMessage();
  email.println("Hello, world!");
  email.println("!!!Warning!!!!");
  email.println("Professor has been detected!!!!");
  email.endMessage();

  if(email.send() > 0)
    Serial.println("Email send ok");
  else
    Serial.println("Email send failed");
}

void loop() {
}
