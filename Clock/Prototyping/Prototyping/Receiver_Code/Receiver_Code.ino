#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10000; // delay for half a second

int currentHour;

int clockValues[24] = { -1};

char data = ' '; //contains the message from arduino sender

void setup() {
  strip.setBrightness(60);
  strip.begin();
  strip.show();
  //send requests to the hub one after the other
  //request data for 24 hours

  //array of 24 values, non filled indexes have a value of "-1"
  //filled indexes have a value of the appropriate decibel reading

  Serial1.begin(9600);
  Serial.print("Starting...");


  //send serial request to hub for data
  //Data can be function of which lights are not lit up
  //

  for (int i = 0; i < 24; i++) {

    currentHour = i;

    Serial1.print("R:");
    Serial1.print(i);
    Serial.println("Sent request");
    while (!Serial1.available()) {
      delay(30000);
      Serial1.print("R: " + i);
    }

    int val = Serial1.available();

    int hour = Serial1.parseInt();
    Serial.print("Sucessfully received data for hour: " + hour);
    int decibel = Serial1.parseInt();
    Serial.print("Successfully received data for decibel: " + decibel);

    
    //if the hour read does not match the requested hour...
   /* if (hour != i) {
      Serial1.print("Incorrect hour!");
    }

    */
    if (decibel == -2) {
      //haven't been able to reach server
      i--;
      continue;
    }
    else if (decibel == -3) {
      //we don't have data on that
      break;
    }




  }

}


void loop() {


  int byte = Serial1.available();

  while (byte > 0) {

    int hour = Serial1.parseInt();
    int decibel = Serial1.parseInt();

    if ((currentHour + 1) == hour) {
      clockValues[currentHour] = decibel;
    }
  }


}

/*
  void clockCycle(uint16_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {

    //read a data value, decide on a colour
    //set colour to c

    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
  }
*/

void setHourColour(int value, int pixel) {

  value = value / 10;

  switch (value) {
    case 1:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 2:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 3:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 4:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 5:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 6:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 7:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 8:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 9:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
    case 10:
      strip.setPixelColor(pixel, (255, 255, 0));
      break;
  }

}
