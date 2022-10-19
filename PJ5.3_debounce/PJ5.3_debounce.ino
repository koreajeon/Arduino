/*
Debounce 스케치.
2번 핀에 연결된 스위치가 내장형 led를 켠다
디바운스 로직이 스위치 상태를 잘못 읽게 되는 상황을 방지한다.
*/

const int inputPin = 2; // 입력 핀 개수 
const int debounceDelay = 10; // 핀이 안정될 때까지 대기하기 위한 반복
bool last_button_state = LOW; // 버튼의 최종 상태
int ledState = LOW;
int count;

// 디바운스는 스위치가 안정적일 때 반환한다.
bool debounce(int pin)
{
    bool state;
    bool previousState;

    previousState = digitalRead(pin);
     // 스위치 상태를 저장
    for(int counter = 0; counter < debounceDelay; counter++)
    {
        delay(1); // 1ms 동안 대기
 //       Serial.println(counter);
        state = digitalRead(pin);
        if(state != previousState)
        {
            counter = 0; //상태가 변하면 카운터를 리셋
            previousState = state; // 그리고 나서 현재 상태를 저장
        }
        if(state == LOW)
            return true;
        else
            return false;
    }
    // 스위치가 안정된 상태를 디바운스 시간보다 더 오래 유지하면 이 자리로 도달하게 된다
}

void setup()
{
    pinMode(inputPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    bool button_state = debounce(inputPin);

    if(button_state)
    {
        if(count<100)
        {
            count++;
            Serial.println(count);
        }
        else
        {
            count--;
            Serial.println(count);
        }
    }

    // 버튼 상태가 변경되었고 버튼이 눌린 경루
    if(last_button_state != button_state && button_state == HIGH)
    {
        // LED를 토글
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
    }
    last_button_state = button_state;
}














