int sensorPin = 0;// 사운드 센서를 0번핀에 연결합니다.
int ledPin = 11;// LED를 11번핀에 연결합니다.
void setup() {
  pinMode(ledPin,OUTPUT);// ledPin을 출력으로 설정합니다.
  Serial.begin(9600);
}
void loop() {
  int value = analogRead(sensorPin); // 사운드 센서값을 읽기.
  int intensity = map(value,19,250,0,200);// 읽어들인 값으로 LED의 밝기를 구하고, LED의 밝기를 새로고침 합니다.
  
  analogWrite(ledPin, intensity);
  delay(10);//10ms 동안 대기
   Serial.println(value);//센서값을 시리얼 모니터로 출력하여 현재 센서값을 보여줍니다.
   delay(100);//100ms 동안 대기
}
