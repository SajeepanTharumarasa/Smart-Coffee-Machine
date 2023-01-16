#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);

Servo SugarServo;
Servo PowderServo; 
Servo MilkServo;  
#define UP A0
#define DOWN A1
#define SELECT A2
#define BACK A3
#define BlendPin 3
#define TempPin 5
#define OutPin 6
#define Inlet 12              
#define HeatPin 13

int Temp;
int Row = 2;
int Screen;
int Sugar;
int Powder;
int Milk;
int Temperature;
bool CoffeeMade;
bool SugarAmountSelected = false;
bool PowderAmountSelected = false;
bool MilkAmountSelected = false;
bool TemperatureSelected = false;

void setup() {
  // put your setup code here, to run once:
  PowderServo.attach(1);
  SugarServo.attach(2);
  MilkServo.attach(3);
  PowderServo.write(0);
  SugarServo.write(0);
  MilkServo.write(0);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(SELECT, INPUT);
  pinMode(BACK, INPUT);
  pinMode(TempPin, INPUT);
  pinMode(BlendPin, OUTPUT);
  pinMode(OutPin, OUTPUT);
  pinMode(Inlet, OUTPUT);
  pinMode(HeatPin, OUTPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Default();  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SELECT) == HIGH){
    OnScreen("Select Sugar Level", "LOW", "MEDIUM", "HIGH");
    int Screen = 2;
    while (Screen == 2){
      SugarMenu();
      if (SugarAmountSelected){
        break;
      }
    }

    OnScreen("Select Powder Level", "LOW", "MEDIUM", "HIGH");
    Row = 2;
    while (SugarAmountSelected){
      PowderMenu();
      if (PowderAmountSelected){
        SugarAmountSelected = false;
        break;
      }
    }
    
    OnScreen("Select Milk Level", "LOW", "MEDIUM", "HIGH"); 
    Row = 2;
    while (PowderAmountSelected){
      MilkMenu();
      if (MilkAmountSelected){
        PowderAmountSelected = false;
        break;
      }
    }
    
    OnScreen("Select Temperature", "50 deg celcius", "60 deg celcius", "70 deg celcius"); 
    Row = 2;
    while (MilkAmountSelected){
      TemperatureMenu();
      if (TemperatureSelected){
        MilkAmountSelected = false;
        break;
      }
    }

    

    reset();
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(2,1);
    lcd.print("Making Coffee...");
    delay(1000);
    DataProcess(Sugar, Powder, Milk, Temperature);
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
        Sugar = 1;
        SugarAmountSelected = true;  
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
        Sugar = 2;
        SugarAmountSelected = true;
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
        Sugar = 3;
        SugarAmountSelected = true;
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
  delay(1000);
  SugarServo.write(0);
  delay(1000);
  Screen = 3;
}

void PowderMenu(){
    if (Row == 2){
      lcd.setCursor(0,1);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);
        Powder = 1;
        PowderAmountSelected = true;
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
        Powder = 2;
        PowderAmountSelected = true;
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
        Powder = 3;
        PowderAmountSelected = true;
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
  delay(1000);
  PowderServo.write(0);
  delay(1000);  
  Screen = 4;
}

void MilkMenu(){
    if (Row == 2){
      lcd.setCursor(0,1);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);
        Milk = 1;
        MilkAmountSelected = true;
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
        Milk = 2;
        MilkAmountSelected = true;
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
        Milk = 3;
        MilkAmountSelected = true;
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
  delay(1000);
  MilkServo.write(0);
  delay(1000);  
  Screen = 5;
}

void TemperatureMenu(){
    if (Row == 2){
      lcd.setCursor(0,1);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);
        Temperature = 50;
        TemperatureSelected = true;
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
        Temperature = 60;
        TemperatureSelected = true;
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
        Temperature = 70;
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

void MakeCoffee(int Temperature){
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
}

void DataProcess(int Sugar, int Powder, int Milk, int Temperature){
  SugarAmt(Sugar);
  PowderAmt(Powder);
  MilkAmt(Milk);
  MakeCoffee(Temperature);
}

void reset(){
  Row = 2;
  SugarAmountSelected = false;
  PowderAmountSelected = false;
  MilkAmountSelected = false;
  TemperatureSelected = false;
}

void OnScreen(String title, String lvl1, String lvl2, String lvl3){
  lcd.clear();    
  lcd.setCursor(1,0);
  lcd.print(title);
  lcd.setCursor(1,1);
  lcd.print(lvl1);
  lcd.setCursor(1,2);
  lcd.print(lvl2);
  lcd.setCursor(1,3);
  lcd.print(lvl3);   
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
