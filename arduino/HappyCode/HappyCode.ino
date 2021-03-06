#include <SPI.h>
#include <Phpoc.h>
PhpocEmail email;

int ledPin = 13;                // 출력할 핀번호
int inputPin = 2;               // 움직임 감지 센서 출력 핀번호
int pirState = LOW;             // we start, assuming no motion detected
int val = LOW;                    // 움직임 센서에 상태를 저장하기 위한 variable
int sensorPin = 0;// 사운드 센서를 0번핀에 연결합니다.
const int button1Pin = 4; //버튼센서 4번

 
void setup() {
  pinMode(ledPin, OUTPUT);      // led 출력 -> 13 번으로
  pinMode(inputPin, INPUT);     // '동작감지센서' 2번 핀 인풋으로 선언
  pinMode(8, INPUT); // '조도센서'8번 핀으로 데이터를 값을 받습니다.
  pinMode(button1Pin, INPUT); //'버튼센서' 4번 핀을 입력 핀으로 설정합니다.

  Serial.begin(9600); // 시리얼 포트 9600을 사용하겠다
//--- 메일링부분----
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET | PF_LOG_APP);
  pinMode(A0, INPUT);
}
 
void loop(){
   val = digitalRead(inputPin);  // 동작감지 센서 인풋 값을 저장
  int svalue = analogRead(sensorPin); // 사운드 센서로부터 센서값을 읽어 들입니다.계속읽기
//  Serial.println(svalue);//센서값을 시리얼 모니터로 출력하여 현재 센서값을 보여줍니다.
//  Serial.println(digitalRead(8));
  int button1State=digitalRead(button1Pin); //버튼상태 저장

  if(button1State == LOW){
 // Serial.println(button1State);
  }//버튼동작부

  
  if (val == HIGH) {            // 인풋 값이 높은지 확인
    if((digitalRead(8) == 0) || (button1State == 0) || (svalue>1000)){
       digitalWrite(ledPin, HIGH);  // led를 켜기

       //---이메일전송부---
       {
       email.setOutgoingServer("smtp.gmail.com", 587);
       email.setOutgoingLogin("its319hun", "****");
       email.setFrom("its319hun@gmail.com", "hun");
       email.setTo("***@naver.com", "HUN");
       email.setSubject("or Happy_LAB_Life! [#905]");  // Mail Subject
       
       // -----메일 내용------
       email.beginMessage();
       email.println("Hello, world!");
       email.println("!!!Warning!!!!");
       email.println("Professor has been detected!!!!");
       email.endMessage();
       //-메일발송실패시-
       if (email.send() > 0)  // Send Email
       Serial.println("Your Mail has been sent successfully");
       else
       Serial.println("Your Mail is not sent");
       }
       }
       
      if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!"); // 나중에 라즈베리파이에서 받을 값
   
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
