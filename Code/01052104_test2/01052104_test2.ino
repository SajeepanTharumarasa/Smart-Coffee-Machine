#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x20,20,4);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo PowderServo;
Servo SugarServo;
#define Coffee 1
#define Sugar 2
#define Servo3 3
#define UP 4
#define DOWN 5
#define SELECT 6
#define BACK 7
#define BlendPin 8
#define TempPin 10
#define OutPin 11

int Temp;
int Row;
int Screen;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  lcd.print("Smart Coffee Machine");
  PowderServo.write(0);
  SugarServo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SELECT == HIGH){

        
  }
  

}

int MakeCoffee(int Temperature){
  Temp = analogRead(TempPin);
  
  while (Temp <= Temperature){
    analogWrite(BlendPin,255);
  }
  analogWrite(BlendPin,0);

  digitalWrite(OutPin,HIGH);
  return 0;
}

void PowderAmt(int PowderLvl){
  if (PowderLvl == 1){
    PowderServo.write(30);
    delay(100);
    PowderServo.write(0);
    delay(100);
  }
  if (PowderLvl == 2){
    PowderServo.write(60);
    delay(100);
    PowderServo.write(0);
    delay(100);
  }
  if (PowderLvl == 3){
    PowderServo.write(90);
    delay(100);
    PowderServo.write(0);
    delay(100);
  }
}

void SugarAmt(int SugarLvl){
  SugarServo.write(SugarLvl * 30);
  delay(100);
  SugarServo.write(0);
  delay(100);
}

void Navigate(){
  if (UP == 1){
    lcd.setCursor(0,0);
    lcd.blink();
    Row = 1;
  }
  
  if (DOWN == 1){
    lcd.setCursor(0,1);
    lcd.blink();
    Row = 2;
  }
}

void Menu(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Sugar Level");
    lcd.setCursor(1,1);
    lcd.print("Delete Audio");
    Screen = 1;
    Row = 0;
}

void SugarMenu(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select Sugar Level");
    lcd.setCursor(0,1);
    lcd.blink();
    lcd.setCursor(1,1);
    lcd.print("LOW");
    lcd.setCursor(1,2);
    lcd.print("MEDIUM");
    lcd.setCursor(1,3);
    lcd.print("HIGH");
    Row = 2;

    if ((Row == 2 and DOWN == HIGH) or (Row == 4 and UP == HIGH)){
      lcd.setCursor(0,2);
      lcd.blink();
      Row = 3;
    }

    if ((Row == 3 and DOWN == HIGH) or (Row == 1 and UP == HIGH)){
      lcd.setCursor(0,3);
      lcd.blink();
      Row = 4;
    }

    if ((Row == 4 and DOWN == HIGH) or (Row == 2 and UP == HIGH)){
      lcd.setCursor(0,2);
      lcd.blink();
      Row = 2;
    }

    if (Row == 2 and SELECT == HIGH){
      SugarAmt(1);
    }

    if (Row == 3 and SELECT == HIGH){
      SugarAmt(2);
    }

    if (Row == 4 and SELECT == HIGH){
      SugarAmt(3);
    }
}
