const int potPin = A0;
const int ledPin = LED_BUILTIN;
int val = 0;

void setup()
{
    
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    val = analogRead(potPin);
    digitalWrite(ledPin, HIGH);
    delay(val);
    digitalWrite(ledPin, LOW);
    delay(val);
    Serial.print(val);
}