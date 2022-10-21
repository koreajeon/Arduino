void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    int count = 1;
    char onoff = (char) Serial.read();
    int num = (onoff - '0');

    if(num == 1){
        on();
    }
    else if(num == 0){
        off();
    }

    for(count; count < 100; count++){
        Serial.println(count);
        delay(100);
    }
    for(count; count > 1; count--){
        if(num == 1){
            on();
        }
        else if(num == 0){
            off();
        }
        Serial.println(count);
        delay(100);
    }
}

void on(){
    digitalWrite(LED_BUILTIN, HIGH);
}

void off(){
    digitalWrite(LED_BUILTIN, LOW);
}