#include <HashMap.h> //hashmap library
#include <Wire.h>           //wire library
#include <Adafruit_MCP4725.h> // MCP4725 library from adafruit

const byte HASH_SIZE = 12;
char vol_byte = 0;
String vol_str = "";
Adafruit_MCP4725 MCP4725;
//storage
HashType<double, int> hashRawArray[HASH_SIZE];

HashMap<double, int>hashmap = HashMap<double, int>(hashRawArray , HASH_SIZE );

uint32_t MCP4725_value = 0;
double value = 0;

//functions of keyboard detection;
char keyPressed() {
  static char key_pressed;
  if (Serial.available() > 0) {
    key_pressed = Serial.read();
    Serial.println(key_pressed);
  }
  return key_pressed;
}

void setup() {
  // put your setup code here, to run once:
  //setup hashmap
  hashmap[0](1000, 0.43);
  hashmap[1](1100, 0.65);
  hashmap[2](1200, 0.79);
  hashmap[3](1300, 0.93);
  hashmap[4](1400, 1.08);
  hashmap[5](1500, 1.22);
  hashmap[6](1600, 1.36);
  hashmap[7](1700, 1.51);
  hashmap[8](1800, 1.65);
  hashmap[9](1900, 1.80);
  hashmap[10](2000, 1.94);
  hashmap[11](2100, 2.08);  

  Serial.begin(9600);
  MCP4725.begin(0x60);
  //Serial.println(hashmap.getIndexOf("test1"), DEC);
  //Serial.println(hashmap.getValueOf("test2"));
  pinMode(A2, OUTPUT);    // sets the digital pin 13 as output
  pinMode(A3, OUTPUT);

  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0){
    vol_byte = Serial.read();
    vol_str += vol_byte;
    if(int(vol_byte)==10){
      Serial.println("it enters here");
      value = vol_str.toDouble();
      vol_byte = 0;
      vol_str = "";
      Serial.println(value);
      //MCP4725.setVoltage(value, false);
      Serial.println(hashmap.getValueOf(value));
      }
    }
    
  

}
