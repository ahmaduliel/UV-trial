#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 20
#define DHTTYPE DHT21

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(2, 9, 6, 8, 10, 12);

const int pinbtn1=3, pinbtn2=32, pinbtn3=34, pinbtn4=36, pinbtn5=5, pinbtn6=15;
int button1, button2, button3, button4, button5, button6; 
const int pinswitch1=33, pinswitch2=35, pinswitch3=37, pinswitch4=39, pinswitch5=41;
int switch1, switch2, switch3, switch4, switch5; 
const int led1=40, led2=42, led3=44, led4=46, led5=47, led6=48; 
const int buzzer1=11, buzzer2=13;
const int relay1=23, relay2=25, relay3=27, relay4=29;
const int pinlimit1=21, pinlimit2=22, pinlimit3=24, pinlimit4=26, pinlimit5=28, pinlimit6=30, pinlimit7=31;
int limit1, limit2, limit3, limit4, limit5, limit6, limit7;
const int en=1, dir=1, step1=1;

const int stepPin = 49; 
const int dirPin = 45; 
const int enPin = 43; 

unsigned long previousMillis = 0; 
const long interval = 1000;

int ms;
int inletTime=0, outletTime=0;
bool stateFull=0;

int countBottle=0; 
bool stateCount=0, laststateCount=0;

int delayMs(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    return ms++;
  }
}

void setButton(){
 pinMode(pinbtn1,INPUT);
 pinMode(pinbtn2,INPUT);
 pinMode(pinbtn3,INPUT);
 pinMode(pinbtn4,INPUT);
 pinMode(pinbtn5,INPUT);
 pinMode(pinbtn6,INPUT);
}

void setSwitch(){
 pinMode(pinswitch1,INPUT);
 pinMode(pinswitch2,INPUT);
 pinMode(pinswitch3,INPUT);
 pinMode(pinswitch4,INPUT);
 pinMode(pinswitch5,INPUT);
}

void setLed(){
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(led4,OUTPUT);
 pinMode(led5,OUTPUT);
 pinMode(led6,OUTPUT);
}

void setRelay(){
 pinMode(relay1,OUTPUT);
 pinMode(relay2,OUTPUT);
 pinMode(relay3,OUTPUT);
 pinMode(relay4,OUTPUT);
}

void setLimit(){
 pinMode(pinlimit1,INPUT_PULLUP);
 pinMode(pinlimit2,INPUT_PULLUP);
 pinMode(pinlimit3,INPUT);
 pinMode(pinlimit4,INPUT);
 pinMode(pinlimit5,INPUT);
 pinMode(pinlimit6,INPUT);
 pinMode(pinlimit7,INPUT);
}

void setup() {
  Serial2.begin(9600);
  lcd.begin(20, 4);
  dht.begin();
  setButton();
  setSwitch();
  setLed();
  setRelay();
  setLimit();
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);

  pinMode(buzzer1,OUTPUT);
  pinMode(buzzer2,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  pinMode(52,INPUT);
  pinMode(51,INPUT);
}

void readBtn(){
  button1=digitalRead(pinbtn1);
  button2=digitalRead(pinbtn2);
  button3=digitalRead(pinbtn3);
  button4=digitalRead(pinbtn4);
  button5=digitalRead(pinbtn5);
  button6=digitalRead(pinbtn6);
}

void readSwitch(){
  switch1=digitalRead(pinswitch1);
  switch2=digitalRead(pinswitch2);
  switch3=digitalRead(pinswitch3);
  switch4=digitalRead(pinswitch4);
  switch5=digitalRead(pinswitch5);
}

void readLimit(){
  limit1=digitalRead(pinlimit1);
  limit2=digitalRead(pinlimit2);
  limit3=digitalRead(pinlimit3);
  limit4=digitalRead(pinlimit4);
  limit5=digitalRead(pinlimit5);
  limit6=digitalRead(pinlimit6);
  limit7=digitalRead(pinlimit7);
}

void loop() {
  Serial2.println("Hello");
  readBtn();
  readSwitch();
  readLimit();
  digitalWrite(enPin,LOW);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  lcd.setCursor(0,0);
  lcd.print("H/T : ");
  
  lcd.setCursor(7,0);
  lcd.print(h,2);
  lcd.setCursor(14,0);
  lcd.print(t,2);
  
  lcd.setCursor(0,3);
  lcd.print("Button: ");

  lcd.print(button1);
  lcd.print(button2);
  lcd.print(button3);
  lcd.print(button4);
  lcd.print(button5);
  lcd.print(button6);
  
  lcd.setCursor(0,1);
  lcd.print("Switch: ");
  
  lcd.print(switch1);
  lcd.print(switch2);
  lcd.print(switch3);
  lcd.print(switch4);
  lcd.print(switch5);
  
  if(switch1 && stateFull==0){
    lcd.setCursor(15,1);
    lcd.print("    ");
    digitalWrite(led1, LOW);
    digitalWrite(dirPin,HIGH);
    for(int x = 0; x < 6000; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(30); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(30); 
    }
    //digitalWrite(buzzer1,HIGH);
  }
  else if(!switch1){
    digitalWrite(led1, HIGH);
    //digitalWrite(buzzer1,LOW);
    stateFull=0; 
  }  
  if(switch2){
    digitalWrite(led2, LOW);
    digitalWrite(relay1, HIGH);
  }
  else if(!switch2){
    digitalWrite(led2, HIGH);    
    digitalWrite(relay1, LOW);
  }
  if(switch3){
    digitalWrite(led3, LOW);
    digitalWrite(relay2, HIGH);
  }
  else if(!switch3){
    digitalWrite(led3, HIGH);    
    digitalWrite(relay2, LOW);
  }
  if(switch4){
    digitalWrite(led4, LOW);
    digitalWrite(relay4, HIGH);
    digitalWrite(buzzer2,HIGH);
  }
  else if(!switch4){
    digitalWrite(led4, HIGH);    
    digitalWrite(relay4, LOW);
    digitalWrite(buzzer2,LOW);
  }
  if(switch5){    
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(relay3, HIGH);
  }
  else if(!switch5){
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(relay3, LOW);
  }
  
  lcd.setCursor(0,2);
  lcd.print("Limit : ");

  lcd.print(limit1);
  lcd.print(limit2);
  lcd.print(limit3);
  lcd.print(limit4);
  lcd.print(limit5);
  lcd.print(limit6);
  lcd.print(limit7);
  
  if(limit1){
    lcd.setCursor(17,1);
    lcd.print(inletTime);
    inletTime=delayMs();
    if (inletTime >= 5){
      stateFull=1;
      lcd.setCursor(15,1);
      lcd.print("END");
    }
  }
//  else if(!limit1){
//    ms=0;
//  }
    
  if(limit2){
    ms=0;
  }
  else if(!limit2){
    lcd.setCursor(17,2);
    lcd.print(outletTime);
    outletTime=delayMs();
    if (outletTime >= 2){
      stateFull=1;
      lcd.setCursor(15,1);
      lcd.print("END");
    }
  }
  
  if(limit7){
    stateCount=1;
    if(stateCount!=laststateCount){
      countBottle++; 
    }     
    laststateCount=stateCount; 
  }
  else if(!limit7){
    stateCount=0;
    laststateCount=0;
  }

    lcd.setCursor(16,3);
    lcd.print(countBottle);  
}
