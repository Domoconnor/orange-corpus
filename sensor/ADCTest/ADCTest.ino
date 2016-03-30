#include <Adafruit_ADS1015.h>
#include <Wire.h>

Adafruit_ADS1115 ads; 
int16_t adc0;
 
void setup() 
{
  Serial.begin(9600);
  ads.setGain(GAIN_SIXTEEN);
  ads.begin();
  Serial.print(ads.getGain());
}
 
 
void loop() 
{
  
  adc0 = ads.readADC_Differential_0_1();  ;
  Serial.println(adc0);
}



