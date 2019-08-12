#include <Wire.h>           //wire library
#include <Adafruit_MCP4725.h> // MCP4725 library from adafruit
#define analogVin A0          // Analog voltage input to A0

Adafruit_MCP4725 MCP4725;

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MCP4725.begin(0x60);
}

void loop(void) {
  // put your main code here, to run repeatedly:
  uint32_t MCP4725_value = 0;
  MCP4725.setVoltage(MCP4725_value, false);
  //Serial.println(MCP4725_value, DEC);
  //Serial.println("Flex sensor Reading: ");
  //Serial.println(analogRead(A1), DEC);
  //Serial.println("Feedback sensor Reading: ");
  Serial.println(analogRead(A2), DEC);
  
}
