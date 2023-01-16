#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,20,4);

Servo SugarServo;
Servo PowderServo; 
Servo MilkServo;  
#define UP A0
#define DOWN A1
#define SELECT A2
#define BACK A3

int Row = 2;
int Screen;
bool SugarAmountSelected = false;
bool PowderAmountSelected = false;
bool MilkAmountSelected = false;

void setup() {
  // put your setup code here, to run once:
  PowderServo.attach(1);
  SugarServo.attach(2);
  MilkServo.attach(3);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Default();
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(SELECT, INPUT);
  pinMode(BACK, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SELECT) == HIGH){
    OnScreen("Select Sugar Level");
    int Screen = 2;
    while (Screen == 2){
      SugarMenu();
      if (SugarAmountSelected){
        break;
      }
    }

    OnScreen("Select Powder Level");
    Row = 2;
    while (SugarAmountSelected){
      PowderMenu();
      if (PowderAmountSelected){
        SugarAmountSelected = false;
        break;
      }
    }
    
    OnScreen("Select Milk Level"); 
    Row = 2;
    while (PowderAmountSelected){
      MilkMenu();
      if (MilkAmountSelected){
        PowderAmountSelected = false;
        break;
      }
    }

    reset();
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(2,1);
    lcd.print("Making Coffee...");
    delay(3000);
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Coffee is READY!");
    delay(1000);
    Default();
  }
}

void SugarMenu(){
    if (Row == 2){
      lcd.setCursor(0,1);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        SugarAmt(1);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 3;
        delay(500);
      }
      if (digitalRead(UP) == HIGH){
        Row = 4;
        delay(500);
      }
    }

    if (Row == 3){
      lcd.setCursor(0,2);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        SugarAmt(2);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 4;
        delay(500);
      }
      else if (digitalRead(UP) == HIGH){
        Row = 2;
        delay(500);
      }
    }

    if (Row == 4){
      lcd.setCursor(0,3);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        SugarAmt(3);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 2;
        delay(500);
      }
      else if (digitalRead(UP) == HIGH){
        Row = 3;
        delay(500);
      }
    }
}

void SugarAmt(int SugarLvl){
  SugarServo.write(SugarLvl * 30);
  delay(100);
  SugarServo.write(0);
  delay(100);
  Screen = 3;
  SugarAmountSelected = true;
}

void PowderMenu(){
    if (Row == 2){
      lcd.setCursor(0,1);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        PowderAmt(1);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 3;
        delay(500);
      }
      if (digitalRead(UP) == HIGH){
        Row = 4;
        delay(500);
      }
    }

    if (Row == 3){
      lcd.setCursor(0,2);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        PowderAmt(2);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 4;
        delay(500);
      }
      if (digitalRead(UP) == HIGH){
        Row = 2;
        delay(500);
      }
    }

    if (Row == 4){
      lcd.setCursor(0,3);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        PowderAmt(3);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 2;
        delay(500);
      }
      else if (digitalRead(UP) == HIGH){
        Row = 3;
        delay(500);
      }
    }
}

void PowderAmt(int PowderLvl){
  PowderServo.write(PowderLvl * 30);
  delay(100);
  PowderServo.write(0);
  delay(100);  
  Screen = 4;
  PowderAmountSelected = true;
}

void MilkMenu(){
    if (Row == 2){
      lcd.setCursor(0,1);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        MilkAmt(1);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 3;
        delay(500);
      }
      if (digitalRead(UP) == HIGH){
        Row = 4;
        delay(500);
      }
    }

    if (Row == 3){
      lcd.setCursor(0,2);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        MilkAmt(2);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 4;
        delay(500);
      }
      if (digitalRead(UP) == HIGH){
        Row = 2;
        delay(500);
      }
    }

    if (Row == 4){
      lcd.setCursor(0,3);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        MilkAmt(3);
      }
      if (digitalRead(DOWN) == HIGH){
        Row = 2;
        delay(500);
      }
      else if (digitalRead(UP) == HIGH){
        Row = 3;
        delay(500);
      }
    }
}

void MilkAmt(int MilkLvl){
  MilkServo.write(MilkLvl * 30);
  delay(100);
  MilkServo.write(0);
  delay(100);  
  Screen = 5;
  MilkAmountSelected = true;
}

void reset(){
  Row = 2;
  SugarAmountSelected = false;
  PowderAmountSelected = false;
  MilkAmountSelected = false;
  
}

void OnScreen(String title){
  lcd.clear();    
  lcd.setCursor(1,0);
  lcd.print(title);
  lcd.setCursor(1,1);
  lcd.print("LOW");
  lcd.setCursor(1,2);
  lcd.print("MEDIUM");
  lcd.setCursor(1,3);
  lcd.print("HIGH");   
  delay(500);
}

void Default(){
  lcd.clear();
  lcd.print("SMART COFFEE MACHINE");
  lcd.setCursor(4,2);
  lcd.print("Press Select");
  lcd.setCursor(3,3);
  lcd.print("to make coffee");  
}
