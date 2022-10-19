const int sensorPin = A0;

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
