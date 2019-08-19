char c;
const size_t bufferSize = 10;
char point[bufferSize];
char test_array[] = "488, 271, 406, 314, 307, 340, 209, 344, 126, 324";
int arr[bufferSize];
char *ptr = NULL;
byte i = 0;
size_t index = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    c = Serial.read();
    point[index++] = c;
  }
  ptr = strtok(test_array, ",");//used to be point

  
  while (ptr != NULL && i < bufferSize) {
  arr[i++] = atoi(ptr);
  ptr = strtok(NULL, ",");
  }
  
  if(arr[1] == 271 && arr[0] == 498){
      digitalWrite(A0,HIGH);
      }else{
        digitalWrite(A0,LOW);
        }
  
}
