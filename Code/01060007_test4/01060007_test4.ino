#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x20,20,4);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

Servo PowderServo;              // ServoMotor for CoffeePowder
Servo SugarServo;               // ServoMotor for Sugar
#define UP 4
#define DOWN 5
#define SELECT 6
#define BACK 7
#define BlendPin 8              // ServoMotor for Blender
#define TempPin 10              // Temperature sensor connected pin
#define OutPin 11               // Outlet Pump connected pin
#define Inlet 12                // Water Inlet valve connected pin
#define HeatPin 13              // Controlling pin of the heater

int Temp;
int Row;
int Screen;
bool SugarAmountSelected = false;
bool PowderAmountSelected = false;
bool TemperatureSelected = false;
bool CoffeeMade = false;

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
    SugarMenu();
    if (SugarAmountSelected == true){
      PowderMenu();
      if (PowderAmountSelected == true){
        TemperatureMenu();
        if (TemperatureSelected == true){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Coffee in Making");
          if (CoffeeMade == true){
            Reset();
          }
        }
      }     
    }
  }
}


int MakeCoffee(int Temperature){
  TemperatureSelected = true;
  digitalWrite(Inlet,HIGH);
  delay(2000);
  digitalWrite(Inlet,LOW);
  Temp = analogRead(TempPin);
  
  while (Temp <= Temperature){
    digitalWrite(BlendPin,HIGH);
    digitalWrite(HeatPin,HIGH);
  }

  digitalWrite(HeatPin,LOW);
  digitalWrite(BlendPin,LOW);
  digitalWrite(OutPin,HIGH);
  delay(2000);
  digitalWrite(OutPin,LOW);
  CoffeeMade = true;
  return 0;
}

void PowderAmt(int PowderLvl){
  PowderServo.write(PowderLvl * 30);
  delay(100);
  PowderServo.write(0);
  delay(100);
  PowderAmountSelected = true;
  }
  
void SugarAmt(int SugarLvl){
  SugarServo.write(SugarLvl * 30);
  delay(100);
  SugarServo.write(0);
  delay(100);
  SugarAmountSelected = true;
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

void PowderMenu(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select Coffee Level");
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
      PowderAmt(1);
    }
    if (Row == 3 and SELECT == HIGH){
      PowderAmt(2);
    }
    if (Row == 4 and SELECT == HIGH){
      PowderAmt(3);
    }
}

void TemperatureMenu(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select Temperature");
    lcd.setCursor(0,1);
    lcd.blink();
    lcd.setCursor(1,1);
    lcd.print("50 deg Celcius");
    lcd.setCursor(1,2);
    lcd.print("60 deg Celcius");
    lcd.setCursor(1,3);
    lcd.print("70 deg Celcius");
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
      MakeCoffee(50);
    }
    if (Row == 3 and SELECT == HIGH){
      MakeCoffee(60);
    }
    if (Row == 4 and SELECT == HIGH){
      MakeCoffee(70);
    }
}

void Reset(){
  SugarAmountSelected = false;
  PowderAmountSelected = false;
  TemperatureSelected = false;
  CoffeeMade = false;
}
