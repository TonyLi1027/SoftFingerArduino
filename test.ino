char c;
String point;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    c = Serial.read();
    point += c;
  }
  if(point == "[(488, 271), (406, 314), (307, 340), (209, 344), (126, 324)]"){
      digitalWrite(A0,HIGH);
      }else{
        digitalWrite(A0,LOW);
        }
}
