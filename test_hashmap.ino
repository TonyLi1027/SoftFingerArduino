#include <HashMap.h>

const byte HASH_SIZE = 5;
//storage
HashType<char*,int> hashRawArray[HASH_SIZE];

HashMap<char*, int>hashmap = HashMap<char*, int>(hashRawArray , HASH_SIZE );

void setup() {
  // put your setup code here, to run once:
  //setup hashmap
  hashmap[0]("test1", 18);
  hashmap[1]("test2", 200);
  hashmap[2]("test3", 1234);

  Serial.begin(9600);
  Serial.println(hashmap.getIndexOf("test1"), DEC);
  Serial.println(hashmap.getValueOf("test2"));
}

void loop() {
  // put your main code here, to run repeatedly:

}
