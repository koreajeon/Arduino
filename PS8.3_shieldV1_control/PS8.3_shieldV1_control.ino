#include <IRremote.h>
#define sw1 2
#define sw2 3
#define led_pass 12
#define led_fail 13
#define led_R 9
#define led_G 11
#define led_B 10
int RECV_PIN = 6; //define input pin on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;
#define buzzer 5

long past_time = 0;
long test_start = 0;
int led_switch = 0;
int flag = 0;

const int LED = 12;
const int SENSOR = A1;

int brightness = 0;
double val = 0;
int result = 0;

int infrared  = 7;
int led = 12;

int final = 0; 
double LL = 0;

void setup()
{
    
    pinMode(sw1, INPUT);
    pinMode(sw2, INPUT);
    pinMode(led_pass, OUTPUT);
    pinMode(led_fail, OUTPUT);
    pinMode(led_R, OUTPUT);
    pinMode(led_G, OUTPUT);
    pinMode(led_B, OUTPUT);
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, HIGH);
    
    pinMode(LED, OUTPUT);
    pinMode(SENSOR,INPUT);

    pinMode(infrared, INPUT);
    pinMode(led, OUTPUT);

    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver

    Serial.begin(9600);
}



void test()
{

    if(led_switch == 3) led_switch = 0;
    led_rgb(led_switch);
    test_sensor();
    led_switch++;    
}

void test_result()
{
    switch(final)
    {      

        case 0: start_buzzer();
                digitalWrite(led_R, LOW);
                digitalWrite(led_B, LOW);
                digitalWrite(led_G, HIGH);
                Serial.println("dark&nobody");
                delay(5000);
                start_buzzer();
                break;     
        case 1: start_buzzer();
                digitalWrite(led_R, LOW);
                digitalWrite(led_B, HIGH);
                digitalWrite(led_G, LOW);
                Serial.println("bright&detector");
                Serial.println("dark&nobody");
                delay(5000);
                start_buzzer();
                break;
        case 2: start_buzzer();
                digitalWrite(led_R, HIGH);
                digitalWrite(led_G, LOW);
                digitalWrite(led_B, LOW);
                Serial.println("bight&&detector!!");
                delay(5000);
                start_buzzer();
                break;
    }
    digitalWrite(buzzer,HIGH);
    digitalWrite(buzzer,LOW);
    return final;
}

void test_end()
{
    digitalWrite(led_R, LOW);
    digitalWrite(led_B, LOW);
    digitalWrite(led_G, LOW);
    digitalWrite(led_pass, LOW);
    digitalWrite(led_fail, LOW);

    start_buzzer();
    delay(500);
    start_buzzer();
    delay(500);
}



long sw1_time()
{
    static unsigned long start_time = 0;
    static bool state;
    if(digitalRead(sw1) != state)
    {
        state = !state;
        start_time = millis();
    } 
    if(state == LOW)
    {
        return millis() - start_time;
    }
    else
    {
        return 0;
    }
}

long sw2_time()
{
    static unsigned long start_time = 0;
    static bool state;
    if(digitalRead(sw2) != state)
    {
        state = !state;
        start_time = millis();
    } 
    if(state == LOW)
    {
        return millis() - start_time;
    }
    else
    {
        return 0;
    }
}

void start_buzzer()
{
   int i;
   for(i = 0; i < 80; i++){
    digitalWrite(buzzer,LOW);// sound
    delay(1);//delay1ms
    digitalWrite(buzzer,HIGH);//not sound
    delay(1);
   }
}

void led_rgb(int led_switch)
{   
    switch(led_switch)
    {           
        case 0: digitalWrite(led_R, HIGH);
                digitalWrite(led_G, LOW);
                break;
        case 1: digitalWrite(led_R, LOW);
                digitalWrite(led_B, HIGH);
                break;
        case 2: digitalWrite(led_B, LOW);
                digitalWrite(led_G, HIGH);
                break;
        default: digitalWrite(led_G, LOW);
                digitalWrite(led_R, LOW);
                digitalWrite(led_B, LOW);
                break;
    }
    
}

void test_sensor()
{
  val = analogRead(SENSOR);
  int state = !digitalRead(infrared);

  Serial.println(val);

  brightness = val/4;

  analogWrite(LED,brightness);
  result = round(val/1000);
  Serial.println(result);
  
  Serial.print("Infrared = ");
  Serial.println(state);

  if(state == 1){
    digitalWrite(led, HIGH);
    Serial.println("Warning");
    test_end();
  }

  else{
    digitalWrite(led, LOW);
    Serial.println("Safe");
  }

  final = result + state;
  Serial.println(final);
  delay(1000);
}


void loop()
{   
    long currunt_time = millis();
    //0.5초마다 스위치 상태 확인
    if (irrecv.decode(&results)) {
              Serial.println(results.value, HEX);
              Serial.println(results.value);
                if (results.value==16724175&&result==1)
                {
                  Serial.println("pass");
                  digitalWrite(led_pass, HIGH);
                  delay(1000);
                  digitalWrite(led_pass, LOW);
                }
                else if (results.value==16718055&&result==1)
                {
                  Serial.println("fail");
                  digitalWrite(led_fail, HIGH);
                  delay(1000);
                  digitalWrite(led_fail, LOW);
                }
                else 
                  Serial.println("NO");
              irrecv.resume(); // Receive the next value
            }

    if(currunt_time - past_time >= 500)
    {   
        past_time = currunt_time;

        int sw1_duration = sw1_time();
        int sw2_duration = sw2_time();
        if(flag == 0){
        //지속 시간 확인
            if((sw1_duration && sw2_duration >= 800) && (sw1_duration && sw2_duration <= 1000))
            {   

                 start_buzzer();

            }      

        // 1초 이상이면 테스트 스타트
            if(sw1_duration && sw2_duration >= 1000 )
            { 
                flag = 1;
                led_switch = 0;
                test_start = millis();
            }
        }
        //test 진행

        if(flag == 1)
        {

            test();
            
            if((millis() - test_start >= 20000) && flag == 1) flag = 2;
        }
        

        //test 종료      
         if(flag == 2)
        {
            test_result();
            delay(3000);
            Serial.println(LL);
            test_end();
            flag = 0;
           
        }

           
    }
        
    
}