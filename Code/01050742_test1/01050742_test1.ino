#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define int Coffee 1
#define int Sugar 2
#define int Servo3 3
#define int UP 4
#define int DOWN 5
#define int SELECT 6
#define int BACK 7

void setup() {
  // put your setup code here, to run once:
  //lcd.begin();
  lcd.print("Smart Coffee Machine");

}

void loop() {
  // put your main code here, to run repeatedly:

}
