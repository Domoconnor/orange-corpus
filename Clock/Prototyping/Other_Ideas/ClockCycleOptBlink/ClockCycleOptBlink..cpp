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
  strip.setBrightness(40);
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
  
  if (0 <= value <= 2) {
    //blue green
    strip.setPixelColor(pixel, 0, 200, 51); //blue green
    strip.show();
  }
  else if (2 <= value <= 4) {
    //green yellow
    strip.setPixelColor(pixel, 100, 255, 0); //green/yellow
    strip.show();
  }
  else if (4 <= value <= 6) {
    //yellow orange
    strip.setPixelColor(pixel, 100, 100, 0); //yellow - orange
    strip.show();
  }
  else if (6 <= value <= 8) {
    //orange red
    strip.setPixelColor(pixel, 240, 100, 0); // orange-red
    strip.show();
  }
  else if (8 <= value <= 10) {
    //very red
    strip.setPixelColor(pixel, 255, 0, 0); //very vibrant red
    strip.show();
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

void blinkPixel(int pixel, int c){

  while(i < 5){

    strip.
    
  }
  
}


}
