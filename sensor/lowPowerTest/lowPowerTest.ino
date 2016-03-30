#include <LowPower.h>
const int XBee_wake = 9; // Arduino pin used to sleep the XBee
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  // wake up the XBee
pinMode(XBee_wake, OUTPUT);
digitalWrite(XBee_wake, LOW);
delay(15);

   Serial.print("test!");
   Serial.flush();

// put the XBee to sleep
pinMode(XBee_wake, INPUT); // put pin in a high impedence state
digitalWrite(XBee_wake, HIGH);
delay(5000);


}
