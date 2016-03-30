#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

#define NUMPIXELS 24

#define hour 3600000

#define five 300000

#define one 60000

int startpos = 18;

int endpos = startpos % 24 + 24;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



int clockValues[24] = {10,20,30,40,50,60,10,20,30,40,50,60,10,20,30,40,50,60,10,20,30,40,50,60};

void setup() {
  // put your setup code here, to run once:
  strip.setBrightness(40);
  strip.begin();
  strip.show();
}


void loop() {
  // put your main code here, to run repeatedly:

  initialisationLeds();

    for(int i = 0; i < 24; i++){
      if(setHourColour(clockValues[i], startpos) == false){
        return;
        }
   // initialisationLeds();
            if (startpos >= 24) {
                startpos = 0;
            }
            setHourColour(clockValues[i], startpos);
            delay(500);
            startpos++;
    }
  startpos = 18;
  delay(10000);
}

boolean setHourColour(int value, int pixel) {

  if (value > -1) {
    value = value / 10;
  }

  switch (value) {
    //Case for values in the future which have not been recorded yet.
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
    case 1:
      strip.setPixelColor(pixel, 255, 255, 255); // white
      strip.show();
      break;
    case 2:
      strip.setPixelColor(pixel, 255, 204, 204); //white-pink
      strip.show();
      break;
    case 3:
      strip.setPixelColor(pixel, 255, 153, 153); //very pale pink
      strip.show();
      break;
    case 4:
      strip.setPixelColor(pixel, 255, 102, 102); //pale pink
      strip.show();
      break;
    case 5:
      strip.setPixelColor(pixel, 255, 51, 51); // bright pink
      strip.show();
      break;
    case 6:
      strip.setPixelColor(pixel, 255, 0, 0); //very vibrant red
      strip.show();
      break;
  }

}

void initialisationLeds() {
  int i = 0;
  while (i < 3) {
    for (int j = 0; j <= 24; j++) {
      if (startpos >= 24) {
        startpos = 0;
      }
      strip.setPixelColor(startpos, 255, 204, 153);
      strip.show();
      startpos++;
      delay(50);
    }
    startpos = 18;
    strip.clear();

    i++;
  }

}

void rejectionLeds() {
    int i = 0;
  while (i < 3) {
    for (int j = 0; j <= 24; j++) {
      if (startpos >= 24) {
        startpos = 0;
      }
      strip.setPixelColor(startpos, 255, 0, 0);
      strip.show();
      startpos++;
      delay(50);
    }
    startpos = 18;
    strip.clear();

    i++;
  }
}

void nullServerLeds() {
     int i = 0;
  while (i < 3) {
    for (int j = 0; j <= 24; j++) {
      if (startpos >= 24) {
        startpos = 0;
      }
      strip.setPixelColor(startpos, 0, 0, 255);
      strip.show();
      startpos++;
      delay(50);
    }
    startpos = 18;
    strip.clear();

    i++;
  }
}
