//Input pullup (입력 풀업) 스케치
// 2번 핀에 연결된 스위치가 내장형 LED를 켠다 

const int inputPin = 2 ; // 스위치를 위한 입력 핀

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(inputPin, INPUT_PULLUP);
}

void loop()
{
    
}