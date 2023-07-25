
#include <LiquidCrystal.h>  
LiquidCrystal lcd(9, 12, 6, 4, 3, 11);  
void (* resetFunc) (void)=0;

const int trigpin= 8;  
const int echopin= 7;  
const int motorpin=10;
int inputValue;
long duration;  
int distance;

int PercentageFunction(){
 
  int n=14;
  int m;
  float percentage;
  digitalWrite(trigpin,HIGH);  
  delayMicroseconds(100);  
  digitalWrite(trigpin,LOW);  
  duration=pulseIn(echopin,HIGH);    
  distance = duration*0.034/2;
  m=n-distance;  
  percentage=m*100/n;
  return percentage;

}

void setup(){
   int flag = 0;
  lcd.begin(16, 2); 
  lcd.print("MOTOR IS : "); 
  pinMode(motorpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(trigpin,OUTPUT);
  Serial.begin(9600);
  if (flag==0){
    lcd.print("ON");
  }
  
  while(true){
 if(inputValue=='b'){
      lcd.setCursor(0, 0);
      lcd.print("SYSTEM  OFF   ");
      lcd.setCursor(0, 1);
      lcd.print("                  ");
      Serial.println("off");
      digitalWrite(motorpin,HIGH);
      delay(100);
      break;
    }
    delay(1000);
    int p=PercentageFunction();

    if(p>0){
      Serial.println(p);
      
     
    }
    
    if(p<77 && p>0){
      digitalWrite(motorpin,LOW);
      lcd.setCursor(0, 1);
      lcd.print("Water Level: ");
      lcd.print(p);
      lcd.print("%");
    }

     if(p>=77){
      digitalWrite(motorpin,HIGH);
       lcd.setCursor(9, 0);
      lcd.print(": OFF");
      delay(5000);
      flag = 1;
      
    }

    inputValue=Serial.read();
    
   

  }
  if(flag==1){
    lcd.setCursor(8, 0);
    lcd.print(" : OFF");
    
  }
  


}

void loop(){
 
  inputValue=Serial.read();
 
  if(inputValue=='a'){
    
    Serial.println("on");
    resetFunc();
  }

}