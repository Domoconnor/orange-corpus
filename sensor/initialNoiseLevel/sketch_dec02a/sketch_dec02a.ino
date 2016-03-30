#include <JeeLib.h> // Low power functions library

 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
  Serial.begin(9600);
}
 
 
void loop() 
{

  int avg = 0;
  int ref = 35;
  int refVal = 30;
  
  double peakToPeak;

  
  peakToPeak = getAmplitude();
  
  //Calculate decibels using power calculation
  double decibels = 20*log10(peakToPeak/refVal) + ref;
  Serial.println(peakToPeak);
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
      sample = analogRead(3);
      if (sample < 1024)  
      {
         if (sample > signalMax)
         {
            signalMax = sample;  
         }
         else if (sample < signalMin)
         {
            signalMin = sample; 
         }
      }
   }
   return signalMax - signalMin;  // max - min = peak-peak amplitude
}

