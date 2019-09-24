#include <Adafruit_MCP4725.h> //MCP4725 library from adafruit

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

typedef struct{
  uint16_t Input;
  uint16_t x_val;
  uint16_t y_val;
}ArduinoDictionary;

const ArduinoDictionary MyDictionary[]{
  {1000, 199, 456},
  {1100, 201, 465},
  {1200, 198, 453},
  {1300, 196, 443},
  {1400, 193, 431},
  {1500, 191, 418},
  {1600, 190, 405},
  {1700, 190, 363},
  {1800, 191, 378},
  {1900, 191, 363},
  {2000, 192, 348},
  {2100, 195, 333},
  {2200, 198, 321},
  {2300, 202, 307},
  {2400, 204, 293},
  {2500, 213, 275},
  {2600, 221, 259},
  {2700, 231, 242},
  {2800, 242, 225},
  {2900, 257, 208},
  {3000, 273, 190}
};


 
void setup(){
  Serial.begin(9600);
  MCP4725.begin(0x60);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  MCP4725.setVoltage(1000, false);
  delay(1000);
}

void execute(){
   t = millis();
   if(up == 0){
   for(uint8_t i = 0; i < sizeof(MyDictionary)/sizeof(ArduinoDictionary); ++i) {
      //Serial.println(MyDictionary[i].x_val);//Prints the values: "Settings", "Ajustes" and "Paramètres"
      if(MyDictionary[i].x_val>=190 && MyDictionary[i].x_val<=191 && MyDictionary[i].y_val<=405 && MyDictionary[i].y_val>=403){
        MCP4725_value = MyDictionary[i].Input;
        x_ref = MyDictionary[i].x_val;
        y_ref = MyDictionary[i].y_val;
        break;
        }
  }
 }
  up = 1;
  MCP4725.setVoltage(MCP4725_value, false); //MCP4725_value
  while((millis() - t)<1000);
  if((num_arr[0] - x_ref)>2 && (num_arr[1] - y_ref)>2){
    MCP4725_value += 50;
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
    //delay(500);
  }
  else if(((x_ref - num_arr[0])>2 && (x_ref-num_arr[1])<=5) || ((y_ref - num_arr[1])>2 && (x_ref-num_arr[1])<=5)){
    MCP4725_value -= 50;
    digitalWrite(A1, HIGH);
    digitalWrite(A0, LOW);
    //delay(500);
  }
}
 
void loop(){

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
