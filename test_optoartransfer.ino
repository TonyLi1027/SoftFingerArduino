
#include <Adafruit_MCP4725.h> //MCP4725 library from adafruit

int len = 1;
static uint8_t up = 1;
static int num_arr[10];
unsigned long int t = millis();
static String c_arr;
static uint8_t i = 0;
uint16_t MCP4725_value = 1000;
Adafruit_MCP4725 MCP4725;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MCP4725.begin(0x60); //Default I2C address of MCP4725 breakout board;
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(A6,OUTPUT);
  pinMode(A7,OUTPUT);
  pinMode(A8,OUTPUT);
  pinMode(A9,OUTPUT);
}

void execute(){
  if(num_arr[0] - 143 <= 1){
    digitalWrite(A0, HIGH);
    }
  else{
    digitalWrite(A0, LOW);
    }
  if(num_arr[1] - 374 <= 3){
    digitalWrite(A1, HIGH);
    }
  else{
    digitalWrite(A1, LOW);
    }
  if(num_arr[2] - 229 <= 1){
    digitalWrite(A2, HIGH);
    }
  else{
    digitalWrite(A2, LOW);
    } 
  //clear the num_array
  i = 0;
  memset(num_arr, 0, sizeof(num_arr));
}

void loop() {
  // put your main code here, to run repeatedly:
  //MCP4725_value = 1000;
  
  if(millis() - t < 1000){
   MCP4725.setVoltage(MCP4725_value, false);
  }
  else if (millis() - t > 1000){
    t = millis();
    if(up == 1){
     MCP4725_value += 100;
    }
    else{
     MCP4725_value -= 100;
    }
  }
  if (MCP4725_value == 1000){
    up = 1;
  }
  else if(MCP4725_value == 3500){
    up = 0;
  }

  // check series
  if(Serial.available())
 {
   char c = Serial.read();
   //start the packet of the data;
   if (c == '['){
    len = 0;
    }
   //end of the packet of the data;
    else if(c == ']'){
     //record the last data;
     num_arr[i] = c_arr.toInt();
     c_arr = "";
     i = i + 1;
     //execute;
     execute();
     len = 1; 
    }
    else if (c == ',' && len == 0){
      //change the char to int and store them for every ','
      num_arr[i] = c_arr.toInt();
      c_arr = "";
      i = i + 1;
    }
    else if(len == 0){
      //store the chars
      c_arr += c;
    } 
 }

 }
