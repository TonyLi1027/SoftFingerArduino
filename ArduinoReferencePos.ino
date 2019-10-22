#include <Adafruit_MCP4725.h> //MCP4725 library from adafruit

unsigned long int previousTime;
unsigned long int SystemTime;
double elapsedTime;
double error;
static double lastError;
static double rateError;
static double input,output;
int len = 1;
int16_t kp = 2;
int16_t kd = 0.5;
static uint8_t up = 0;
static uint16_t x_ref = 0;
static uint16_t y_ref = 0;
static int num_arr[10];
int tem_arr[10];
unsigned long int t = millis();
static String c_arr;
static uint8_t i = 0;
static double setPoint;
static uint16_t MCP4725_value = 1000;//4947.7 - setPoint*7.36;
Adafruit_MCP4725 MCP4725;

typedef struct{
  uint16_t Input;
  int16_t diff;
}ArduinoDictionary;

const ArduinoDictionary MyDictionary[]{
  {1400, -4},
  {1450, 3},
  {1500, 8},
  {1550, 16},
  {1600, 21},
  {1650, 26},
  {1700, 32},
  {1750, 36},
  {1800, 47},
  {1850, 53},
  {1900, 58},
  {1950, 66},
  {2000, 73},
  {2050, 81},
  {2100, 86},
  {2150, 92},
  {2200, 101},
  {2250, 107},
  {2300, 112},
  {2350, 122},
  {2400, 129},
  {2450, 136},
  {2500, 142},
  {2550, 150},
  {2600, 160},
  {2650, 169},
  {2700, 177},
  {2750, 187},
  {2800, 193},
  {2850, 199},
  {2900, 205},
  {2950, 215},
  {3000, 222},
  {3050, 228},
  {3100, 233},
  {3150, 242},
  {3200, 250}
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MCP4725.begin(0x60);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
//  for(uint8_t j = 0; j < sizeof(MyDictionary)/sizeof(ArduinoDictionary); ++j) {
//      //Serial.println(MyDictionary[i].x_val);//Prints the values: "Settings", "Ajustes" and "Paramètres"
//    if(MyDictionary[j].diff == 250){
//       MCP4725_value = MyDictionary[j].Input;
//       input = MyDictionary[j].Input;
//       setPoint = MyDictionary[j].diff;
//       break;
//    }
// }
  setInput(169);
  MCP4725.setVoltage(MCP4725_value,false);
  delay(1000);
}

void setInput(int Input){
  for(uint8_t j = 0; j < sizeof(MyDictionary)/sizeof(ArduinoDictionary); ++j) {
      //Serial.println(MyDictionary[i].x_val);//Prints the values: "Settings", "Ajustes" and "Paramètres"
    if(MyDictionary[j].diff == Input){
       MCP4725_value = MyDictionary[i].Input;
       input = MyDictionary[j].Input;
       setPoint = MyDictionary[j].diff;
       break;
    }else if((MyDictionary[j].diff < Input) && (MyDictionary[j+1].diff > Input)){
       MCP4725_value = MyDictionary[i].Input;
       input = MyDictionary[j].Input + (Input - MyDictionary[j].diff);
       setPoint = Input;
       break;
    }
 }  
}

double computePID(double inp, double setpoint, double kp, double kd){
  t = millis();
  elapsedTime = (double)(t - previousTime);
  error = setpoint - inp;
  rateError = (error-lastError)/elapsedTime;
  if(abs(error) > 80){
    error = 0;
    rateError = 0;
  }else if(abs(error) < 5){
    error = 0;
    rateError = 0;
  }
  double out = kp*error + kd*rateError;
  lastError = error;
  previousTime = t;
  return out;
  }

  
void execute(){
  MCP4725_value = input - computePID(num_arr[9]-num_arr[1],setPoint,kp,kd);
  MCP4725.setVoltage(MCP4725_value,false);
  i = 0;
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