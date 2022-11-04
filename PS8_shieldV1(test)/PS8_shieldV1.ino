#define redLed 12
#define blueLed 13

void setup()
{
    pinMode(redLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
}

void loop()
{
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, LOW);
    delay(1000);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, HIGH);
    delay(1000);
}