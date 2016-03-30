#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

#define NUMPIXELS 24

#define hour 3600000

#define five 300000

#define one 60000

int pos18 = 18;

int endpos = pos18 % 24 + 24;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



int clockValues[24] = {7, 20, 40, 50, 80, 100, 100, 50, 40, 45, 47, 38, 70, 68, 68, 60, 50, 30, 35, 30, 28, 30, 20, 10};

void setup() {
  // put your setup code here, to run once:
  strip.setBrightness(40);
  strip.begin();
  strip.show();
}


void loop() {
  // put your main code here, to run repeatedly:

  initialisationLeds();

  for (pos18; pos18 < endpos; pos18++) {
    int i = 0;
    if (setHourColour(clockValues[i], pos18) == false) {
      return;
    }
    //Delay for x minutes before reading in next value
    //  delay(one);
    //run initialisation step
    initialisationLeds();
    for (int j = 0; j <= 24; j++) {
      if (pos18 >= 24) {
        pos18 = 0;
      }
      setHourColour(clockValues[i], pos18);
      delay(50);
      pos18++;

    }
    i++;
  }

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
    for (int j = 0; j <= 24; j++) {
      if (pos18 >= 24) {
        pos18 = 0;
      }
      strip.setPixelColor(pos18, 255, 204, 153);
      strip.show();
      pos18++;
      delay(50);
    }
    pos18 = 18;
    strip.clear();

    i++;
  }

}

void rejectionLeds() {
  int i = 0;
  while (i < 3) {
    for (pos18; pos18 < endpos; pos18++) {
      strip.setPixelColor(pos18, 255, 0, 0);
      strip.show();
      delay(50);
    }
    strip.clear();
    i++;
  }
}

void nullServerLeds() {
  int i = 0;
  while (i < 3) {
    for (pos18; pos18 < endpos; pos18++) {
      if (pos18 >= 24) {
        pos18 = 0;
      }
      strip.setPixelColor(pos18, 0, 0, 255);
      strip.show();
      delay(50);
    }
    strip.clear();
    i++;
  }
}
