int sugar_low=10;
int sugar_medium=11;
int sugar_high=12;

int coffee_low=7;
int coffee_medium=8;
int coffee_high=9;

int milk_low=20;
int milk_medium=21;
int milk_high=22;

//Variables
int sugar_low_s=0;
int sugar_medium_s=0;
int sugar_high_s=0;

int coffee_low_s=0;
int coffee_medium_s=0;
int coffee_high_s=0;

int milk_low_s=0;
int milk_medium_s=0;
int milk_high_s=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sugar_low,OUTPUT);
  pinMode(sugar_medium,OUTPUT);
  pinMode(sugar_high,OUTPUT);
  pinMode(coffee_low,OUTPUT);
  pinMode(coffee_medium,OUTPUT);
  pinMode(coffee_high,OUTPUT);
  pinMode(milk_low,OUTPUT);
  pinMode(milk_medium,OUTPUT);
  pinMode(milk_high,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available>0)
  {
    Recieved=Serial.read();
  }

  if (sugar_low_s==0 && Received == '1')
  {
   digitalWrite(sugar_low,HIGH);
   Received = 0;
   sugar_low_s=1;
   }
   digitalWrite(sugar_low,LOW);
   Received = 0;
   sugar_low_s=0;

  if (sugar_medium_s==0 && Received == '2')
  {
   digitalWrite(sugar_medium,HIGH);
   Received = 0;
   sugar_medium_s=1;
   }
   digitalWrite(sugar_low,LOW);
   Received = 0;
   sugar_medium_s=0;

   if (sugar_high_s==0 && Received == '3')
  {
   digitalWrite(sugar_high,HIGH);
   Received = 0;
   sugar_high_s=1;
   }
   digitalWrite(sugar_low,LOW);
   Received = 0;
   sugar_high_s=0;

   if (coffee_low_s==0 && Received == '4')
  {
   digitalWrite(coffee_low,HIGH);
   Received = 0;
   coffee_low_s=1;
   }
   digitalWrite(coffee_low,LOW);
   Received = 0;
   coffee_low_s=0;

   if (coffee_medium_s==0 && Received == '5')
  {
   digitalWrite(coffee_medium,HIGH);
   Received = 0;
   coffee_medium_s=1;
   }
   digitalWrite(coffee_medium,LOW);
   Received = 0;
   coffee_medium_s=0;

   if (coffee_high_s==0 && Received == '6')
  {
   digitalWrite(coffee_high,HIGH);
   Received = 0;
   coffee_high_s=1;
   }
   digitalWrite(coffee_high,LOW);
   Received = 0;
   coffee_high_s=0;

   if (milk_low_s==0 && Received == '7')
  {
   digitalWrite(milk_low,HIGH);
   Received = 0;
   milk_low_s=1;
   }
   digitalWrite(milk_low,LOW);
   Received = 0;
   milk_low_s=0;

   if (milk_medium_s==0 && Received == '8')
  {
   digitalWrite(milk_medium,HIGH);
   Received = 0;
   milk_medium_s=1;
   }
   digitalWrite(milk_medium,LOW);
   Received = 0;
   milk_medium_s=0;

   if (milk_high_s==0 && Received == '9')
  {
   digitalWrite(milk_high,HIGH);
   Received = 0;
   milk_high_s=1;
   }
   digitalWrite(milk_high,LOW);
   Received = 0;
   milk_high_s=0;

}
