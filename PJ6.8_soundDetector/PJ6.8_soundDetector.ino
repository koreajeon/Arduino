/*  microphone 스케치
 *  일렉트릿 마이크로폰용으로 쓸 스파크펀이 만든 브레이크아웃 보드가
 *  0번 아날로그 핀에 연결된다.
 */


const int mcPin = A0;               // 0번 아날로그 핀에 연결된 마이크로폰
const int ledPin = LED_BUILTIN;     // 코드가 내장형 LED를 점멸할 것이다
const int middleValue = 512;        // 아날로그 값들의 범위 중 중간값
const int numberOfSamples = 128;    // 한 번에 판독할 분량


int sample;     // 매번 마이크로폰이 읽은 값
long signal;    // DC 오프셋을 제거한 이후의 판독값
long newReading;    //해당 루프에서 반복해 가며 읽은 판독값들의 평균

long runningAverage = 0;
const int averagedOver = 16;    // 새 값이 이동 평균에 영향을 미치는 속도 
const int threshold = 400;      // 불을 켜는 레벨 

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    long sumOfSquares = 0;
    for (int i=0; i< numberOfSamples; i++)
    {
        sample = analogRead(micPin);    // 판독값을 획득한다
        signal = (sample - middleValue);
        signal *= signal;
        sumOfSquares += signal;
    }

    newOfSquares += signal;


    newReading = sumOfSquars / numberOfSamples;

    //이동평균을 계산한다
    runningAverage = (((averagedOver-1) * runningAverage) + newReading) / averagedOver;

    Serial.print("new :");  Serial.print(newReading);
    Serial.print(",");
    Serial.print("running :"); Serial.println(runningAverage);

    if(runningAverage > threshold) // 평균값이 임계값보다 큰가?
    {
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }
}



