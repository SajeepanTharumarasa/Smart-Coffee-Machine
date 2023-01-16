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
#define BlendPin 3            
#define TempPin 5              
#define OutPin 6               
#define Inlet 12                
#define HeatPin 13 

int Temp;
int Row = 2;
int Screen;
bool CoffeeMade;
bool SugarAmountSelected = false;
bool PowderAmountSelected = false;
bool MilkAmountSelected = false;
bool TemperatureSelected = false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  Default();
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
      if (CoffeeMade){
        MilkAmountSelected = false;
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

void TemperatureMenu(){
    if (Row == 2){
      lcd.setCursor(0,1);
      lcd.blink();
      if (digitalRead(SELECT) == HIGH){
        delay(500);        
        MakeCoffee(50);
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
        MakeCoffee(60);
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
        MakeCoffee(70);
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
