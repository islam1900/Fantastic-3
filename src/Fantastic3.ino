int start=2;int pwm=3;int ina=4;int inb=5;int steering =6;int ctrig=7;
int cecho=8;int recho=9;int rtrig=10; int ltrig=11;int lecho=12;int buz=13;
#include <Servo.h>
Servo steer;
int dc, dl, dr;
char Direction;
int servoCenter=95;
int counter=0;
long milli;
void setup (){
pinMode(ina,OUTPUT);
pinMode(pwm,OUTPUT);
pinMode(inb,OUTPUT);
pinMode(ctrig,OUTPUT);
pinMode(cecho, INPUT);
pinMode(rtrig,OUTPUT);
pinMode(recho, INPUT);
pinMode(ltrig,OUTPUT);
pinMode(lecho, INPUT);
pinMode(start, INPUT_PULLUP);
pinMode(buz,OUTPUT);
Serial.begin(9600);
steer.attach(steering);

Move(0,0);  
  for(int i=200;i<4000;i++){tone(buz,i,130);}
  while(digitalRead(start)==1){delay(2);}
  delay(250);
  milli= millis();
}

void loop(){
  qualify();
}
void qualify(){
Start();
for(int i=0; i<11; i++){
ultra();
if(Direction=='r'){
  while(dr<99 || ( (millis()-milli)<2000 )){
      ultra();
      center(70);
      }}
  else{
  while(dl<99 || ( (millis()-milli)<1500 )){
      ultra();
      center(70);
      }
      }
      turn();
      Move(100,0);
    delay(100);
      milli=millis();
}
if (Direction=='r'){
       Move(100,0);
       delay(400); 
} else{
  Move(100,0);  
  delay(800); }

Move(0,0);
delay(1000000000);
}


void Start(){
      ultra();
      while((dr<99 && dl<99) || ( (millis()-milli)<1200 ))
      {
      ultra();
      center(70);
      }
      if(dr>99){Direction='r';}
      else {Direction='l';}
      turn();
      milli=millis();
}


void turn(){
 if(Direction=='r'){
  Move(70,100);
  delay(250);
  ultra();
  while(dc<100){ultra();Move(50,100);}
  delay(0); // <-------ta3deel laffa henaa(20)
  Move(0,0);
  digitalWrite(buz,1);
  delay(100);
 }else{
  Move(70,-100);
  delay(300);
  ultra();
  while(dc<100){ultra();Move(50,-100);}
  delay(50); // <-------ta3deel laffa henaa(20)
  Move(0,0);
  digitalWrite(buz,1);
  delay(100);
  }
  digitalWrite(buz,0);
}


void center(int sp){
    ultra();
         if (dr<25){Move(sp,-20);digitalWrite(buz,0);}
    else if (dl<25){Move(sp,20);digitalWrite(buz,0);}
    else{Move(sp,0);}

}


void Move (int sp,int dir){
  int laffa;
  if(sp>0){
    int Speed=map(sp,1,100,1,255);

  analogWrite(pwm,Speed);
  digitalWrite(inb,1);
  digitalWrite(ina,0);
}
else if(sp<0){
   int Speed=map(sp,-1,-100,1,255);

  analogWrite(pwm,Speed);
  digitalWrite(inb,0);
  digitalWrite(ina,1);

}


else if(sp==0){
     digitalWrite(inb,1);
     digitalWrite(ina,1);
     analogWrite(pwm,0);
}
if(dir>=0){
 laffa=map(dir,0,100,servoCenter,0);
}
else {
  laffa=map(dir,-1,-100,servoCenter,180);
}
steer.write(laffa);
}


void ultra() {
  digitalWrite(ctrig,1);
  delayMicroseconds(10);
  digitalWrite(ctrig,0);
  int Tc = pulseIn(cecho,1,9100); 
   dc = Tc*0.034/2;
  if(dc==0){dc=100;}
 
  digitalWrite(rtrig,1);
  delayMicroseconds(10);
  digitalWrite(rtrig,0);
  int Tr = pulseIn(recho,1,9100); 
   dr = Tr*0.034/2;
  if(dr==0){dr=100;}
 
  
  digitalWrite(ltrig,1);
  delayMicroseconds(10);
  digitalWrite(ltrig,0);
  int TL = pulseIn(lecho,1,9100); 
   dl = TL*0.034/2;
  if(dl==0){dl=100;}
//    Serial.print(dl);
//    Serial.print("   ");
//    Serial.print(dc);
//    Serial.print("   ");
//    Serial.println(dr);
 
}
