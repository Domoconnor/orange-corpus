#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// for next time - try disabling top lines of code

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

#define MAX_SERVER_WAIT 5000 //in millis

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ400);

int delayVal = 10000; // delay for half a second

int clockValues[24];

char term = '!';

int x = 0;

int y = 0;

//ms for an hour - if you want to make the clock wait an hour, use this variable in your delay
#define hour 3600000

//ms for five minutes - if you want to make the clock wait five minutes, use this variable in your delay
#define five 300000

//ms for a minute - if you want to make the clock wait one minute, use this variable in your delay
#define one 60000

#define BUF_SIZE 100

char buffer[BUF_SIZE];

void setup() {
  // put your setup code here, to run once:
  strip.setBrightness(40);
  strip.begin();
  strip.show();
  Serial1.begin(9600);
  Serial.begin(9600);

  delay(2000);
}

char readBlocking() {
  while (!Serial1.available());
  return Serial1.read();
}

boolean doRead() {

  while (Serial1.available()) Serial1.read();

  int i = 0;
  //Whilst still waiting for data, send requests until it is available
  //or 10 requests have been exceeded.
  while (!Serial1.available() && i < 10) {
    Serial1.write('R');
    Serial1.write(':');
    Serial1.write('!');
    Serial1.flush();
    delay(50);
    i++;
  }
  unsigned long start = millis();
  while (!Serial1.available()) {
    if (millis() - start > MAX_SERVER_WAIT)
      return false;
  }

  int c;
  while ( (c = readBlocking()) != '?') Serial.print(c);
  Serial.println(); Serial.flush();

  for (int i = 0; i < 24; i++) {
    int index = 0;
    while (index < BUF_SIZE) {
      buffer[index] = readBlocking();

      if (buffer[index] == ',') {
        buffer[index] = '\0';
        clockValues[i] = atoi(buffer);
        break; //break while
      } else if (buffer[index] == '!') {
        buffer[index] = '\0';
        clockValues[i] = atoi(buffer);
        for (int j = i + 1; j < 24; j++) clockValues[j] = -1;
        return true;
      } else if(isnan(buffer[index])){
          //if the received data is not a number, return false 
          //doRead() has failed
         return false;         
        } 
        else{
        index++;
      }
    }
  }
  return true;
}

void loop() {

  //begins by starting the white initialisation LEDs
  initialisationLeds();

  if (doRead()) {
    //Run the green accept LEDs
    acceptLeds();
  } else {
    //Run the red rejection LEDs
    rejectionLeds();
    return;
  }
  for (int i = 1; i < 24; i++) {
    if (setHourColour(clockValues[i], i) == false) {
      return;
    }
    delay(one);
  }
  delay(2000);
}

/*
   Method to set each individual LED to a colour dependent upon
   The corresponding Decibel reading for that timeslot.
*/
boolean setHourColour(int value, int pixel) {

  if (value > -1) {
    value = value / 10;
  }

  switch (value) {
    //Case for future value which has not yet been sent
    case -1:
      delay(10000);
      return false;
    case -2:
      //Case for the hub rejecting the data request sent by the clock
      delay(1000);
      rejectionLeds();
      return false;
    case -3:
      //Case for the hub being unable to interact with the server
      nullServerLeds();
      return false;
    case 0:
      strip.setPixelColor(pixel, 0, 200, 51); //blue green
      strip.show();
      break;
    case 1:
      strip.setPixelColor(pixel, 0, 255, 0); //light green
      strip.show();
      break;
    case 2:
      strip.setPixelColor(pixel, 100, 255, 0); //green/yellow
      strip.show();
      break;
    case 3:
      strip.setPixelColor(pixel, 100, 150, 0); //yellow
      strip.show();
      break;
    case 4:
      strip.setPixelColor(pixel, 100, 170, 0); //vibrant yellow
      strip.show();
      break;
    case 5:
      strip.setPixelColor(pixel, 100, 100, 0); //yellow - orange
      strip.show();
      break;
    case 6:
      strip.setPixelColor(pixel, 140, 100, 0); // orange
      strip.show();
      break;
    case 7:
      strip.setPixelColor(pixel, 240, 100, 0); // orange-red
      strip.show();
      break;
    case 8:
      strip.setPixelColor(pixel, 255, 40, 0); // red
      strip.show();
      break;
    case 9:
      strip.setPixelColor(pixel, 255, 10, 0); // vibrant red
      strip.show();
      break;
    case 10:
      strip.setPixelColor(pixel, 255, 0, 0); //very vibrant red
      strip.show();
      break;
  }

}

void initialisationLeds() {
  int i = 0;
  while (i < 5) {
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, 255, 204, 153);
      strip.show();
      delay(50);
    }
    strip.clear();
    i++;
  }

}

void rejectionLeds() {
  int i = 0;
  while (i < 5) {
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, 255, 0, 0);
      strip.show();
      delay(50);
    }
    strip.clear();
    i++;
  }

}

void acceptLeds() {
  int i = 0;
  while (i < 5) {
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, 0, 255, 0);
      strip.show();
      delay(50);
    }
    i++;
  }


}

void nullServerLeds() {
  int i = 0;
  while (i < 3) {
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, 0, 0, 255);
      strip.show();
      delay(50);
    }
    strip.clear();
    i++;
  }
}
