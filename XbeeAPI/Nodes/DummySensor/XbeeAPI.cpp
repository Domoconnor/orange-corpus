#include <XbeeAPI.h>

XbeeAPI xbee(&Serial, 0, "test");
int inRange = 8; 
int notInRange = 7; 

void setup() {
  Serial.begin(9600);
  pinMode(inRange, OUTPUT);
  pinMode(notInRange, OUTPUT);
}

void loop() {
  delay(1000);
  uint8_t res = xbee.sendMessage("HB#:test");
  Serial.print("Response: '");
  Serial.print(res);
  Serial.print("'");
  if(!res){
      digitalWrite(inRange, HIGH); 
      digitalWrite(notInRange, LOW);  
  }else{
      digitalWrite(inRange, LOW); 
      digitalWrite(notInRange, HIGH);  
  }
}