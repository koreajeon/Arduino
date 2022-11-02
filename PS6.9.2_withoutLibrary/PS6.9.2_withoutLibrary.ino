
byte ROM[100][8];
byte num_devices=1, alarm_devices, CRC_Error;
float tempC_decimal=0.0000, tempF_decimal=0.0000;
byte LSB, MSB, TH, TL, Config;
byte TempSensor1[8]={0x28,0xBD,0xA2,0xA0,0x5,0x0,0x0,0x7F};

void setup()
{
  for(byte i=0; i<8; i++)
  ROM[0][i] = TempSensor1[i];
  
  Serial.begin(9600);
  DSB_search_all(5, 1);

  for(byte i=1; i<=num_devices; i++)
  DSB_scratch_write(5, i, 25, 0, 0xFF);
}

void loop(){
  DSB_search_all(5, 0);
  DSB_Convert_All(5);
  DSB_search_alarm(5, 1);
  
  
}


void DSB_byte_write(byte command, byte pin){
int i;

  for(i=0; i<8; i++){
    if(bitRead(command, i))
    {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      delayMicroseconds(1);
      pinMode(pin, INPUT);
      delayMicroseconds(60);
    }
    else
    {
      pinMode(pin, OUTPUT);
      digitalWrite(5, LOW);
      delayMicroseconds(59);
      pinMode(pin, INPUT);
      delayMicroseconds(1);
    }
  }
}

byte DSB_byte_read(byte pin){
  int i;
  byte byte_in;
  
   for(i=0; i<8; i++)
   {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    
    pinMode(pin, INPUT);
    delayMicroseconds(10);

    if(digitalRead(pin))//grab the line status
      bitSet(byte_in,i);//set it or...
    else
      bitClear(byte_in,i);
      delayMicroseconds(49);
    }

  return(byte_in); 
}


void DSB_Reset(byte pin){

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(500);
  pinMode(pin, INPUT);
  delayMicroseconds(500);
}



void DSB_search_all(byte pin, boolean printer){
  DSB_Search(0xF0, pin, printer);
}

void DSB_search_alarm(byte pin, boolean printer){
  DSB_Search(0xEC, pin, printer);
  alarm_devices=num_devices;
  DSB_Search(0xF0, pin, 0);
}

void DSB_get_temp_one_device(byte pin, byte printer){
  int i;
  LSB=0;
  MSB=0;
  tempC_decimal =0;
  DSB_Reset(pin);
  DSB_byte_write(0xCC, pin);
  DSB_byte_write(0x44, pin);
  DSB_Reset(pin);
  DSB_byte_write(0xCC, pin);
  DSB_scratch_read(pin);

  if(printer==1){
    Serial.print(tempC_decimal, 4);
    Serial.print("C ");
    Serial.print(tempF_decimal, 4);
    Serial.println("F ");
  }  
 
}


void DSB_get_one_address(byte pin, byte printer){
  int i;
  
  DSB_Reset(pin);//reset
  DSB_byte_write(0x33, pin);
  for(i=0; i<8; i++){
    ROM[0][i]=DSB_byte_read(pin);
    }
  
  if(printer==1){
    for(i=0; i<8; i++)
      {
      Serial.print(ROM[0][i],HEX); 
      Serial.print(":"); 
      }
    Serial.println("");
    
  }
  
}

void DSB_get_temp_address(byte pin, byte address, byte printer){
  int i;
  LSB=0;
  MSB=0;
  tempC_decimal =0;

  DSB_Reset(pin);
  DSB_byte_write(0x55, pin);
  for(i=0; i<8; i++)
  DSB_byte_write(ROM[address][i], pin);
  DSB_byte_write(0x44, pin);
  delay(750);
  DSB_Reset(pin);
  DSB_byte_write(0x55, pin);
  for(i=0; i<8; i++)
  DSB_byte_write(ROM[address][i], pin);
  DSB_scratch_read(pin);



if(printer==1){
Serial.print(tempC_decimal, 4);
Serial.print("C ");
Serial.print(tempF_decimal, 4);
Serial.println("F ");
}    
}

void DSB_Convert_All(byte pin){
int i, j;


  for(i=1; i<=num_devices; i++){
  DSB_Reset(pin);
  DSB_byte_write(0x55, pin);
  for(j=0; j<8; j++)
  DSB_byte_write(ROM[i][j], pin);
  DSB_byte_write(0x44, pin);
  delay(10);
  }
  
}

void DSB_scratch_write(byte pin, byte address, byte high, byte low, byte cnfig)
{
  int j;
  
  DSB_Reset(pin);
  DSB_byte_write(0x55, pin);
  for(j=0; j<8; j++)
  DSB_byte_write(ROM[address][j], pin);
  DSB_byte_write(0x4E, pin);
  DSB_byte_write(high, pin);
  DSB_byte_write(low, pin);
  DSB_byte_write(cnfig, pin);
  DSB_byte_write(0x55, pin);
  for(j=0; j<8; j++)
  DSB_byte_write(ROM[address][j], pin);
  DSB_byte_write(0x48, pin);
}

void DSB_scratch_read(byte pin){
  int i, j;
  byte data_in[9], CRC=0;
  boolean CRCxor;
  tempC_decimal=0;

  DSB_byte_write(0xBE, pin);
  for(i=0; i<9; i++)
  {
    data_in[i]=DSB_byte_read(pin);
  }
  
  for(i=0; i<8; i++){
    for(j=0; j<8; j++){
      CRCxor = bitRead(data_in[i], j) ^ bitRead(CRC, 0);
      bitWrite(CRC, 3, (CRCxor^bitRead(CRC, 3)));
      bitWrite(CRC, 4, (CRCxor^bitRead(CRC, 4)));
      CRC = CRC>>1;
      bitWrite(CRC, 7, CRCxor);
    }
  }

  if(CRC==data_in[8])
  {
    LSB=data_in[0];
    MSB=data_in[1];
    TH=data_in[2];
    TL=data_in[3];
    Config=data_in[4];
    CRC_Error=0;   
  }
  else
  {
    CRC_Error=1;
    LSB=0;
    MSB=0;
    TH=0;
    TL=0;
    Config=0;  
  }

  
  if(bitRead(MSB, 7)==0){
    for(i=0; i<4; i++){
      if(bitRead(LSB,i)==0){
        tempC_decimal = tempC_decimal+pow(2.0000, -4.0000+i);
      }

    }
    tempC_decimal = tempC_decimal + (LSB>>4) + ((B00000111 & MSB)<<4); 
    tempF_decimal = (tempC_decimal)*9.0000/5.0000+32.00000;
  }
  else
  {
    word full16 = ((((B00000111 & MSB)<<8) + LSB) ^ 0xFFFF)+1;
    MSB = full16>>8;
    LSB=  full16 & 0x00FF;
 
    for(i=0; i<4; i++){
      if(bitRead(LSB,i))
        tempC_decimal = tempC_decimal+pow(2.0000, -4.0000+i);
      } 
  
    tempC_decimal = (tempC_decimal + (LSB>>4) + ((B00000111 & MSB)<<4))*-1; 
    tempF_decimal = (tempC_decimal)*9.0000/5.0000+32.00000;
  }
}


void DSB_Search(byte search_command, byte pin, boolean printer){
  int i, j, k, n;
  
  byte true_check[8]={0,0,0,0,0,0,0,0};
  byte comp_check[8]={0,0,0,0,0,0,0,0};
  byte last_disc[8]={0,0,0,0,0,0,0,0};
  byte disc_check[8]={0,0,0,0,0,0,0,0};
  num_devices=1;
  

  for(i=0; i<num_devices; i++){
      DSB_Reset(pin);
      DSB_byte_write(search_command, pin);
    for(k=0; k<8; k++){
      for(j=0; j<8; j++){
        bitWrite(true_check[k], j, search_read(pin));
        bitWrite(comp_check[k], j, search_read(pin));
        if(bitRead(true_check[k], j)==0 && bitRead(comp_check[k], j)==0){
          if(bitRead(disc_check[k], j)==0){
            for(n=0; n<8; n++){
              last_disc[n]=0;
            }
            bitSet(last_disc[k], j);
            bitWrite(ROM[num_devices][k], j, 0);
            search_write(0, pin);
            }
    else{
    bitWrite(ROM[num_devices][k], j, 1);
    search_write(1, pin);
      }
    }
    
    if(bitRead(true_check[k], j)==1 && bitRead(comp_check[k], j)==1)
    {
    num_devices=0;
    }
    else
    {
    bitWrite(ROM[num_devices][k], j, bitRead(true_check[k], j));
    search_write(bitRead(true_check[k], j), pin);
    }
    }
    
    
    for(k=7; k>=0; k--){
      for(j=7; j>=0; j--){

        if(bitRead(last_disc[k],j)  && bitRead(disc_check[k],j)==0){
        bitSet(disc_check[k],j);
        num_devices++;
        k=0;
        j=0;
      }
      else
      bitClear(disc_check[k],j);
      }}
      
     
  }
  
  if(printer==1){
  Serial.print("Found ");
  Serial.println(num_devices);
  for(j=1; j<=num_devices; j++){
    for(i=0; i<8; i++){
      Serial.print(ROM[j][i], HEX);
      Serial.print(":");
    }
  Serial.print("  ");
  DSB_get_temp_address(pin, j, 1);

  }
  }
}

boolean search_read(byte pin){


   pinMode(pin, OUTPUT);
   digitalWrite(pin, LOW);
   delayMicroseconds(1);
   pinMode(pin, INPUT);
   delayMicroseconds(10);
   
 
   if(digitalRead(pin)==HIGH){
     delayMicroseconds(49);
   return 1;
   }
   else{
     delayMicroseconds(49);
   return 0;

   }
}
void search_write(boolean val, byte pin){


    if(val==0){ 
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);  
      delayMicroseconds(59);
      pinMode(pin, INPUT);
      delayMicroseconds(1);  
    }
    else{
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      delayMicroseconds(1); 
      pinMode(pin, INPUT);
      delayMicroseconds(60);
    }
}
