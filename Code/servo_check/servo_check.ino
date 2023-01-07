#include <Servo.h>

int potPin = 0;
int servoPin = 9;
Servo servo;

void setup() {
    servo.attach(servoPin);
}

void loop() {
    
    int angle =0;
    servo.write(angle);
    delay(1000);

    for(int i=0;i<180;i++){
      angle = angle+1;
      servo.write(angle);
      }
    delay(1000);
    
}
