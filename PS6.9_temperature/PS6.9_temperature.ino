#include <OneWire.h>
#include <DallasTemperature.h>
#include <Time.h>
#include <DS1307RTC.h> 

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
  setSyncProvider(RTC.get);  
  setTime(10,49,0,02,11,22);
  if(timeStatus()!= timeSet) 
     Serial.println("Unable RTC");
  else
     Serial.println("time start");  
}

void loop(void)
{ 
  
  sensors.requestTemperatures(); 

  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW); // LOW를 줘야 풀업상태 유지
  delayMicroseconds(480);

  pinMode(pin,INPUT);
  digitalClockDisplay();  
  delay(1000);
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


void digitalClockDisplay(){
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}