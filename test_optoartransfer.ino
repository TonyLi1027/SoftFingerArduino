int len = 1;
//static char c_arr[49];
static int num_arr[10];
static int num;
static String c_arr;
static uint8_t i = 0;
static uint8_t j = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,OUTPUT);

}

void execute(){
  if(num_arr[9] == 324){
    digitalWrite(A0, HIGH);
    delay(1000);
    }
  else{
    digitalWrite(A0, LOW);
    delay(1000);
    } 
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
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
