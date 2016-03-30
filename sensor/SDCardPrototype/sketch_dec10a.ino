
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
const int ref = 36; //Decibel Reading from external device
const int refVal = 5; //Amplitude when reference value from external device is 42 Db
unsigned int sample;
 
RTC_DS1307 RTC;
 
void setup() 
{
   Serial.begin(9600);
}
 
 
void loop() 
{
  double peakToPeak;
  int avg = 0;

  
  for (int x = 0; x < 3 ;x++)
  {
    avg += getAmplitude();
  }
  
  Serial.println(getAmplitude());

  peakToPeak = avg/3;
  double decibels = 20*log10(peakToPeak/refVal) + ref;

  Serial.println(decibels);
  delay(1000);
}

int getAmplitude() 
{
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  unsigned long startMillis= millis();  // Start of sample window
  
  // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   return signalMax - signalMin;  // max - min = peak-peak amplitude
}

void write(double decibels)
{
 
  DateTime now = RTC.now();
  File dataFile = SD.open("log.txt", FILE_WRITE);
   // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(now.unixtime());
    dataFile.print(",");
    dataFile.println(decibels);
    dataFile.close();
    // print to the serial port too:
    Serial.print(now.unixtime());
    Serial.print(",");
    Serial.println(decibels);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening log.txt");
  }
}

