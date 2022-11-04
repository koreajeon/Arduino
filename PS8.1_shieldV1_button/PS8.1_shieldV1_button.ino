const int button1Pin = 2;     
const int button2Pin = 3;
const int led1Pin =  13;     
const int led2Pin =  12;
 
int button1State = 0;         
int button2State = 0;
 
void setup() 
{
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}
 
void loop() 
{
  button1State = digitalRead(button1Pin);
 
  if (button1State == LOW) 
  {
    digitalWrite(led1Pin, HIGH);
  } 
  else 
  {
    digitalWrite(led1Pin, LOW);
  }
 
   
  button2State = digitalRead(button2Pin);
 
  if (button2State == LOW) 
  {
    digitalWrite(led2Pin, HIGH);
  } 
  else 
  {
    digitalWrite(led2Pin, LOW);
  }
}