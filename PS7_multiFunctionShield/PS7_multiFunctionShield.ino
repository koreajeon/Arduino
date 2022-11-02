#include <OneWire.h>
#include <DallasTemperature.h>

#include <Time.h>  
#include <Wire.h>  
#include <DS1307RTC.h> 

#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);    
DallasTemperature sensors(&oneWire);

#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
#define BUTTON1 A1
#define BUTTON2 A2
#define BUTTON3 A3

int pin = 5;
int currentTime=0;
long previousTime=0;

const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

int Count1;
int Count2;
int TCount;
int V1, V2, V3, V4;
int i=0;
int k=0;

int X1, X2, X3, X4;
float VTCount;
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

void SendDataToSegment(byte Segment_no, byte hexValue);

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(LATCH_DIO,LOW); 
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO,HIGH);    
}

void WriteNumber1(int Number)
{
  WriteNumberToSegment(0 , Number);
}
void WriteNumber2(int Number)
{
  WriteNumberToSegment(1 , Number);
}
void WriteNumber3(int Number)
{
  WriteNumberToSegment(2 , Number);
}
void WriteNumber4(int Number)
{
  WriteNumberToSegment(3 , Number);
}


void WriteNumberT1(int Number)
{
  WriteNumberToSegment(0 , Number);
}
void WriteNumberT2(int Number)
{
  WriteNumberToSegment(1 , Number);
}
void WriteNumberT3(int Number)
{
  WriteNumberToSegment(2 , Number);
}
void WriteNumberT4(int Number)
{
  WriteNumberToSegment(3 , Number);
}



void setup(void)
{
  
  Serial.begin(9600);
  pinMode(pin,INPUT);
  sensors.begin();  
  setSyncProvider(RTC.get);  
  setTime(12,1,0,2,11,22);
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");

  pinMode(LATCH_DIO,OUTPUT);
  pinMode(CLK_DIO,OUTPUT);
  pinMode(DATA_DIO,OUTPUT);
  currentTime = millis();
  previousTime = 0;
}

void loop(void)
{ 
  
  digitalClockDisplay();  
  delay(1000);
  sensors.requestTemperatures(); 

  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW); // LOW를 줘야 풀업상태 유지
  delayMicroseconds(480);

  pinMode(pin,INPUT);

  previousTime=micros();

  
  
  
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" ");
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("");

  Count1 = minute();
  Count2 = second(); 
  
  V1 = ((Count1 / 10) % 10); 
  V2 = (Count1 % 10);  
  V3 = ((Count2 / 10) % 10);  
  V4 = (Count2 % 10);


  VTCount = sensors.getTempCByIndex(0)*100;
  TCount = VTCount;
  X1 = ((TCount/1000) % 10); 
  X2 = ((TCount/100) % 10);  
  X3 = ((TCount/10) % 10); 
  X4 = (TCount % 10); 

  if(!digitalRead(BUTTON1))
  {
    while(i<50)
    {
      WriteNumber1(V1);
      delay(10);
      WriteNumber2(V2);
      delay(10);
      WriteNumber3(V3);
      delay(10);
      WriteNumber4(V4);
      delay(10);
      i++;
    }
  }
   if(!digitalRead(BUTTON2))
    {
      while(k<50){
        WriteNumberT1(X1);
        delay(10);
        WriteNumberT2(X2);
        delay(10);
        WriteNumberT3(X3);
        delay(10);
        WriteNumberT4(X4);
        delay(10);
        k++;
       
      }
    }
    WriteNumberToSegment(0,0);
    WriteNumberToSegment(1,0);
    WriteNumberToSegment(2,0);
    WriteNumberToSegment(3,0);
}

