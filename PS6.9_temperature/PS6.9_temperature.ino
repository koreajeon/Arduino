#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

int pin = 5;
int currentTime=0;
long previousTime=0;

OneWire oneWire(ONE_WIRE_BUS);    


DallasTemperature sensors(&oneWire);

void setup(void)
{
  
  Serial.begin(9600);
  pinMode(pin,INPUT);
  sensors.begin();  
}

void loop(void)
{ 
  
  sensors.requestTemperatures(); 

  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW); // LOW를 줘야 풀업상태 유지
  delayMicroseconds(480);

  pinMode(pin,INPUT);

  previousTime=micros();

  while(!digitalRead(pin)){};

  while(digitalRead(pin)){};


  while(!digitalRead(pin)){};

  Serial.print("2 : ");
  Serial.print(micros()-previousTime);

  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" ");
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("");
 
  
  delay(500);
}