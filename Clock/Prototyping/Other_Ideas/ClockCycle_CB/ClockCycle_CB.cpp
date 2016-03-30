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

#define BUF_SIZE 100

char buffer[BUF_SIZE];

void setup() {
  // put your setup code here, to run once:
  strip.setBrightness(30);
  strip.begin();
  strip.show();
  Serial1.begin(9600);
  Serial.begin(9600);

  delay(2000);
  Serial.println("Starting");
}

char readBlocking() {
  while (!Serial1.available());
  return Serial1.read();
}

boolean doRead() {
  Serial.println("Sending request..."); Serial.flush();

  while (Serial1.available()) Serial1.read();

  int i = 0;
  while (!Serial1.available() && i < 10) {
    Serial1.write('R');
    Serial1.write(':');
    Serial1.write('!');
    Serial1.flush();
    delay(50);
    i++;
  }

  Serial.println("Awaiting"); Serial.flush();

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
        Serial.print('"');
        Serial.print(buffer);
        Serial.print("\" => ");
        Serial.println(clockValues[i]);
        Serial.flush();
        break; //break while
      } else if (buffer[index] == '!') {
        buffer[index] = '\0';
        clockValues[i] = atoi(buffer);
        Serial.print('"');
        Serial.print(buffer);
        Serial.print("\" => ");
        Serial.println(clockValues[i]);
        Serial.flush();
        for (int j = i + 1; j < 24; j++) clockValues[j] = -1;
        return true;
      } else {
        index++;
      }
    }
  }
  return true;
}

void loop() {

 initialisationLeds();
  
//  while (!doRead()) {
//    initialisationLeds();
//  }

  if (doRead()) {
    Serial.println("Read success");
    acceptLeds();
  } else {
    Serial.println("Read failed.");
    rejectionLeds();
    return;
  }
  Serial.print(clockValues[0]);
  for (int i = 1; i < 24; i++) {
    Serial.print(", ");
    Serial.print(clockValues[i]);
    for (int i = 0; i < 24; i++) {
      setHourColour(clockValues[i], i);
      //break;
      delay(100);
    }
  }
  Serial.println();
  Serial.flush();
  delay(2000);
}

/*
   Method to set each individual LED to a colour dependent upon
   The corresponding Decibel reading for that timeslot.
*/
void setHourColour(int value, int pixel) {

  value = value / 10;

  switch (value) {
    case 0:
      strip.setPixelColor(pixel, 0, 0, 255); //Dark blue
      strip.show();
      break;
    case 1:
      strip.setPixelColor(pixel, 0, 50, 255); //lighter blue
      strip.show();
      break;
    case 2:
      strip.setPixelColor(pixel, 0, 150, 180); //cyan
      strip.show();
      break;
    case 3:
      strip.setPixelColor(pixel, 0,150,100); //pale cyan
      strip.show();
      break;
    case 4:
      strip.setPixelColor(pixel, 0,150,50); //blue-green
      strip.show();
      break;
    case 5:
      strip.setPixelColor(pixel, 50,150,50); //green-yellow 
      strip.show();
      break;
    case 6:
      strip.setPixelColor(pixel, 50,100,20); // tennis-yellow
      strip.show();
      break;
    case 7:
      strip.setPixelColor(pixel, 70,100,0); // yellow
      strip.show();
      break;
    case 8:
      strip.setPixelColor(pixel, 100,100,0); // orange 
      strip.show();
      break;
    case 9:
      strip.setPixelColor(pixel, 120,100,0); // vibrant orange
      strip.show();
      break;
    case 10:
      strip.setPixelColor(pixel, 120,80,0); //very vibrant red
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
