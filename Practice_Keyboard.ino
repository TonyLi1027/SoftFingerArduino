#define delay 5000//5s waiting time in second state

static unsigned int state; //state machine number
unsigned long timer; //check the time
static unsigned int printer;//only let serial print once
char vol_byte = 0;
String vol_str = "";
bool not_a_number = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  printer = 0;
  state = 1;
}

char keyPressed() {
  static char key_pressed;
  if (Serial.available() > 0) {
    key_pressed = Serial.read();
    Serial.println(key_pressed);
  }
  return key_pressed;
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state) {
    case 1:
      timer = 0;
      if (printer == 0) {
        Serial.print("Hello Kengyu!");
        Serial.println("Press g to go Forward");
      }
      printer = 1;
      if (keyPressed() == 'g') {
        state = 2;
      }
      timer = millis();
      break;
    case 2:
      if (printer == 1) {
        Serial.println("Let's go back, Kengyu! press b");
        printer = 2;
      }
      if (millis() - timer > delay) {
        Serial.println("it stays here");
        state = 1;
        printer = 0;
      } else if (keyPressed() == 'b') {
        state = 1;
        printer = 0;
      } else if (keyPressed() == 'd') {
        state = 3;
        printer = 2;
      }
      break;
    case 3:
      if (printer == 2) {
        Serial.println("Please enter your expected voltage");
      }
      printer = 3;
      while (Serial.available() > 0) {
        vol_byte = Serial.read();
        if ((vol_byte >= '0') && (vol_byte <= '9')) {
          vol_str += vol_byte;
        } else if ((vol_byte == '\n') && (vol_str != "")) {
          if (not_a_number) {
            Serial.println("Not a valid Number");
            state = 3;
            printer = 2;
          } else {
            state = 4;
            printer = 3;
            Serial.println("it goes here");
          }
        } else {
          not_a_number = true;
        }

      }
      break;
    //Serial.println(analogRead(A0),DEC);
    case 4:
      if (printer == 3) {
        Serial.println(analogRead(A0), DEC);
        if (keyPressed() == 'q') {
          state = 1;
          printer = 0;
        }
      }
  }

  //      printer = 3;
  //      if (keyPressed() == 'q') {
  //        state = 1;
  //        printer = 0;
  //      }


}
//char a = keyPressed();
