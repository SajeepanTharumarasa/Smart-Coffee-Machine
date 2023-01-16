#include <Servo.h>

Servo SugarServo;
Servo PowderServo; 
Servo MilkServo;
#define BlendPin 4
#define TempPin 5
#define OutPin 6
#define Inlet 12              
#define HeatPin 13

int Temp;
int Sugar;
int Powder;
int Milk;
int Temperature;

void setup() {
  // put your setup code here, to run once:
  PowderServo.attach(1);
  SugarServo.attach(2);
  MilkServo.attach(3);
  PowderServo.write(0);
  SugarServo.write(0);
  MilkServo.write(0);
  pinMode(TempPin, INPUT);
  pinMode(BlendPin, OUTPUT);
  pinMode(OutPin, OUTPUT);
  pinMode(Inlet, OUTPUT);
  pinMode(HeatPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  DataProcess(2,2,2,60);
  delay(10000);
}

void SugarAmt(int SugarLvl){
  SugarServo.write(SugarLvl * 30);
  delay(100);
  SugarServo.write(0);
  delay(100);
}

void PowderAmt(int PowderLvl){
  PowderServo.write(PowderLvl * 30);
  delay(100);
  PowderServo.write(0);
  delay(100);
}

void MilkAmt(int MilkLvl){
  MilkServo.write(MilkLvl * 30);
  delay(100);
  MilkServo.write(0);
  delay(100);
}

void MakeCoffee(int Temperature){
//  digitalWrite(Inlet,HIGH);
//  delay(2000);
//  digitalWrite(Inlet,LOW);
  Temp = analogRead(TempPin);
  
  while (Temp <= Temperature){
    //digitalWrite(BlendPin,HIGH);
    digitalWrite(HeatPin,HIGH);
  }

  digitalWrite(HeatPin,LOW);
//  digitalWrite(BlendPin,LOW);
//  digitalWrite(OutPin,HIGH);
  delay(2000);
//  digitalWrite(OutPin,LOW);
}

void DataProcess(int Sugar, int Powder, int Milk, int Temperature){
  SugarAmt(Sugar);
  PowderAmt(Powder);
  MilkAmt(Milk);
  MakeCoffee(Temperature);
}
