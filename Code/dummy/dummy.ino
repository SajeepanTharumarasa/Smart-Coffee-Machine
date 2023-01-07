int button = A1;
int led=4;

void setup() {
  // put your setup code here, to run once:
  pinMode(A1,INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(A1)==HIGH){
    digitalWrite(led,HIGH);}

  
}
