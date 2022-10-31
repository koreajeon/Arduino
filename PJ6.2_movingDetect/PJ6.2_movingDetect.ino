int T = 9;

void setup(){
    Serial.begin(9600);
    pinMode(T, INPUT);
}

void loop(){
    if (LOW == digitalRead(T)){
        Serial.println("P");
    }
    else 
    {
    Serial.println("NP");
    }
    delay(410);
}