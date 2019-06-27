int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  while(i<10000){
  //Serial.println("Hello World");
  Serial.println(analogRead(A0),DEC);
  //Serial.println(analogRead(A1),DEC);
  i++;
 // }
}
