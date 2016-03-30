#include <LowPower.h>
#include <RTClib.h>
#include <Wire.h>
#include <DS3231.h>
#include <ArduinoJson.h>


DS3231 clock;
RTCDateTime dt;
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

int battery_in = A6;
int raw_voltage;
float true_voltage;
float battery_capacity = 4.2;
float battery_voltage_shift = 0.25;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("\n ON \n");
  
  // Initialize DS3231
  Serial.println("Initialize DS3231");
  clock.begin();

  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);;
}

// the loop routine runs over and over again forever:
void loop() {
  StaticJsonBuffer<600> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& data = root.createNestedArray("data");

  for(int i=1; i<5; i++)
  {
    //Read the values in
    int avg = 0;
    int ref = 35;
    int refVal = 6;
    
    double peakToPeak;
    for (int x = 0; x < 8 ;x++)
    {
      avg += getAmplitude();
    }
    peakToPeak = avg/8;
    double decibels = 20*log10(peakToPeak/refVal) + ref;
    
    JsonObject& obj = data.createNestedObject();
    dt = clock.getDateTime();
    long curtime = dt.unixtime - 10000;
    delay(100);
    obj[String(curtime) ] = decibels;
    Serial.print(String(curtime));
    
    //Turn off for 2 minutes
    delay(1000);
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);  
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    
   }

    raw_voltage = analogRead(battery_in);
    float true_voltage = raw_voltage * (5.0 / 1023.0) - battery_voltage_shift;
    int int_voltage = int((true_voltage * 100) + 0.5);

    
   root["batt"] = int_voltage;
   
   char buffer[600];
   root.printTo(buffer, sizeof(buffer));
   for(int z = 0; z < strlen(buffer); z++)
   {
    Serial.print(buffer[z]);
    delay(2);
   }
   Serial.print("!");
   
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


