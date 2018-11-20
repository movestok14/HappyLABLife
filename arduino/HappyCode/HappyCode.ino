int ledPin = 13;                // 출력할 핀번호
int inputPin = 2;               // 움직임 감지 센서 출력 핀번호
int ledState = LOW;             // Led 동작 저장
int val = 0;                    // 움직임 센서에 상태를 저장하기 위한 variable
 
void setup() {
  pinMode(ledPin, OUTPUT);      // 출력 -> 13 번
  pinMode(inputPin, INPUT);     // 센서 인풋 선언
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);  // 인풋 값을 저장
  if (val == HIGH) {            // 인풋 값이 높은지 확인
    digitalWrite(ledPin, HIGH);  // led On
    if (ledState == LOW) {
      Serial.println("Motion detected!"); // 센서 동작상태 출력
      ledState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // LED끄기
    if (ledState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      ledState = LOW;
    }
  }
}
