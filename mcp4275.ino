/*
 * Arduino Digital to Analog Coverter MCP4725 Interface code
 * Library from Adafruit-MCP4725
 * see text at www.theorycircuit.com
 */
#include <Wire.h>           //wire library
#include <Adafruit_MCP4725.h> // MCP4725 library from adafruit
#define analogVin A0          // Analog voltage input to A0

Adafruit_MCP4725 MCP4725; 

void setup(void) {
  Serial.begin(9600);
  MCP4725.begin(0x60); // Default I2C Address of MCP4725 breakout board (sparkfun)   
  pinMode(A2, OUTPUT);    // sets the digital pin 13 as output
  pinMode(A3, OUTPUT);

  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
}

void loop(void) {
  
    uint32_t MCP4725_value = 3000;
    int adcValueRead = 0;
    float voltageRead = 0;
    
    float MCP4725_expected_output;
    
      MCP4725_expected_output = (5.0/4096.0) * MCP4725_value;
      MCP4725.setVoltage(MCP4725_value, false);
      //delay(250);
      adcValueRead = analogRead(analogVin);
      voltageRead = (adcValueRead * 5.0 )/ 1024.0;
      
//      Serial.print("MCP4725 Value: ");
//      Serial.print(MCP4725_value);
////      
//      Serial.print("\tExpected Voltage: ");
//      Serial.print(MCP4725_expected_output,3);
//      
      Serial.print("\tArduino ADC Value: ");
      Serial.println(adcValueRead);

    //  Serial.print("\tClock Signal: ");
    //  Serial.println(analogRead(A5));
      Serial.print("\tArduino Voltage: ");      
      Serial.println(voltageRead,3);      
        
}
