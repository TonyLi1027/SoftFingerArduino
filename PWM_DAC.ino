bool val = LOW;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(13,127);
  val = digitalRead(8);
  Serial.println(val);
}
