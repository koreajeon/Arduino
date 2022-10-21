int num = 0;
char send;
int state = true;
unsigned long past_Time, current_Time;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  past_Time = millis();
}
  
void loop() {
  unsigned long current_Time = millis();
   // put your main code here, to run repeatedly:
  if(current_Time - past_Time >= 500){
    past_Time = current_Time;

    if(state == true){
      Serial.println(num);
      num++;
    }
    else if(state == false) {
      Serial.println(num);
      num--;
    }
    
    if(Serial.available() > 0){
      send = Serial.read();
      if(send == '1'){
        digitalWrite(LED_BUILTIN, HIGH)}
      else if(send == '0')
      {digitalWrite(LED_BUILTIN, LOW)}
      Serial.print("Led_State_Change :");
      Serial.println(send);
    }


    if(num == 100) state = !state;
    else if(num == 0) state = !state;


  }
  
       
 }