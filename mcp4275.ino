/*
   Arduino Digital to Analog Coverter MCP4725 Interface code
   Library from Adafruit-MCP4725
   see text at www.theorycircuit.com
*/
#include <Wire.h>           //wire library
#include <Adafruit_MCP4725.h> // MCP4725 library from adafruit
#define analogVin A0          // Analog voltage input to A0

Adafruit_MCP4725 MCP4725;
unsigned long t = millis();
int a = 0;
void setup(void) {
  Serial.begin(9600);
  MCP4725.begin(0x60); // Default I2C Address of MCP4725 breakout board (sparkfun)
  pinMode(A2, OUTPUT);    // sets the digital pin 13 as output
  pinMode(A3, OUTPUT);

  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
}

char keyPressed() {
  static char key_pressed;
  if (Serial.available() > 0) {
    key_pressed = Serial.read();
    Serial.println(key_pressed);
  }
  return key_pressed;
}

void loop(void) {
  uint32_t MCP4725_value = 930;
  
  //float MCP4725_expected_output;
  for (MCP4725_value = 100; MCP4725_value <= 800; MCP4725_value = MCP4725_value+10) {
  MCP4725.setVoltage(MCP4725_value, false);
  Serial.println(MCP4725_value, DEC);
  
    while(millis() - t < 1000){//before the para is a<7500
    MCP4725.setVoltage(MCP4725_value, false);
    Serial.println("Flex sensor Reading:");
    Serial.println(analogRead(A1), DEC);
    Serial.println("Feedback sensor Reading:");
    Serial.println(analogRead(A0), DEC);
    if(keyPressed() == 'c'){
      break;
      }
    }
    t = millis();
  
  if (keyPressed() == 'q'){
    while (1){
      MCP4725.setVoltage(100, false);
      if(keyPressed() == 'c'){
        break;
        }
      }
    }
  }


}
