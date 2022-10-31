const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int inPin1 = A1;
const int inPin2 = A2;
const int inPin3 = A3;


const int debounceTime = 20;
const int fastIncrement = 1000;
const int veryFastIncrement = 4000;
int count1 = 0;
int count2 = 0;
int count3 = 0;

void setup()
{
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    //pinMode(ledpin,)
    Serial.begin(9600);
}


void loop()
{
    int duration1 = switchTime1();
    int duration2 = switchTime2();
    int duration3 = switchTime3();
    
    if(duration1 > veryFastIncrement)
    {
        count1 = count1 + 10;
    }
    else if (duration1 > fastIncrement)
    {
        count1 = count1 + 4;
    }
    else if (duration1 > debounceTime)
    {
        count1 = count1 + 1;
    }
    else
    {
        if(count1 == 0)
        {
            digitalWrite(ledPin1, HIGH);
        }
        else
        {
            digitalWrite(ledPin1, LOW);
            count1 = count1 - 1;
        }
    }
//2
    if(duration2 > veryFastIncrement)
    {
        count2 = count2 + 10;
    }
    else if (duration2 > fastIncrement)
    {
        count2 = count2 + 4;
    }
    else if (duration2 > debounceTime)
    {
        count2 = count2 + 1;
    }
    else
    {
        if(count2 == 0)
        {
            digitalWrite(ledPin2, HIGH);
        }
        else
        {
            digitalWrite(ledPin2, LOW);
            count2 = count2 - 1;
        }
    }
//3
    if(duration3 > veryFastIncrement)
    {
        count3 = count3 + 10;
    }
    else if (duration3 > fastIncrement)
    {
        count3 = count3 + 4;
    }
    else if (duration3 > debounceTime)
    {
        count3 = count3 + 1;
    }
    else
    {
        if(count3 == 0)
        {
            digitalWrite(ledPin3, HIGH);
        }
        else
        {
            digitalWrite(ledPin3, LOW);
            count3 = count3 - 1;
        }
    }

    Serial.print(count1);
    Serial.print(" ");
    Serial.print(count2);
    Serial.print(" ");
    Serial.println(count3);
    delay(100);
}

//스위치가 눌린(LOW인) 시간을 밀리초(ms) 단위로 반환한다
long switchTime1()
{
    static unsigned long startTime = 1;
    static bool state1;

    if(digitalRead(inPin1) != state1)
    {
        state1 =! state1;
        startTime = millis();
    }

    if(state1==LOW)
    {
        return millis() - startTime;
    }
    else
    {
        return 0;
    }
}

long switchTime2()
{
    static unsigned long startTime = 1;
    static bool state2;

    if(digitalRead(inPin2) != state2)
    {
        state2 =! state2;
        startTime = millis();
    }

    if(state2==LOW)
    {
        return millis() - startTime;
    }
    else
    {
        return 0;
    }
}

long switchTime3()
{
    static unsigned long startTime = 1;
    static bool state3;

    if(digitalRead(inPin3) != state3)
    {
        state3 =! state3;
        startTime = millis();
    }

    if(state3==LOW)
    {
        return millis() - startTime;
    }
    else
    {
        return 0;
    }
}