#include <Adafruit_MCP4725.h> //MCP4725 library from adafruit

unsigned long previousTime;
double elapsedTime;
double error;
double lastError;
double input,output,setPoint;
int len = 1;
static uint8_t up = 0;
static uint16_t x_ref = 0;
static uint16_t y_ref = 0;
static int num_arr[10];
int tem_arr[10];
unsigned long int t = millis();
static String c_arr;
static uint8_t i = 0;
uint16_t MCP4725_value = 1000;
Adafruit_MCP4725 MCP4725;

void setup() {
  Serial.begin(9600);
  MCP4725.begin(0x60);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  MCP4725.setVoltage(1000,false);
  Setpoint = 348;
  Input = 1000;
  delay(1000);
}

double computePID(double inp){
  t = millis();
  elapsedTime = (double)(t - previousTime);
  error = setPoint - inp;
  double out = kp*error;
  lastError = error;
  previousTime = t;
  return out;
  }
void execute(){
  t = millis();
  
}

void loop() {
  
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
