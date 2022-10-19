#include <Arduino.h>
#line 1 "c:\\Users\\KOSTA\\project\\arduino\\PJ1_sensor\\PJ1_sensor.ino"
const int sensorPin = A0;

#line 3 "c:\\Users\\KOSTA\\project\\arduino\\PJ1_sensor\\PJ1_sensor.ino"
void setup();
#line 9 "c:\\Users\\KOSTA\\project\\arduino\\PJ1_sensor\\PJ1_sensor.ino"
void loop();
#line 3 "c:\\Users\\KOSTA\\project\\arduino\\PJ1_sensor\\PJ1_sensor.ino"
void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int delayval = analogRead(sensorPin);
    Serial.println(delayval);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delayval);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayval);                     
}

