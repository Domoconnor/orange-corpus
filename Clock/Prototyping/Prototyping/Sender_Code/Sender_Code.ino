void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print('10,20,30,40,50,60,70,80,90,100,90,80,70,60,50,40,30,20,10,20,30,40,50');
  delay(1000);
}

