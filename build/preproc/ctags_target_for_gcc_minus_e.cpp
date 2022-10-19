# 1 "c:\\Users\\KOSTA\\project\\arduino\\PJ1_sensor\\PJ1_sensor.ino"
const int sensorPin = A0;

void setup()
{
    pinMode(13, 0x1);
    Serial.begin(9600);
}

void loop()
{
    int delayval = analogRead(sensorPin);
    Serial.println(delayval);
    digitalWrite(13, 0x1);
    delay(delayval);
    digitalWrite(13, 0x0);
    delay(delayval);
}
