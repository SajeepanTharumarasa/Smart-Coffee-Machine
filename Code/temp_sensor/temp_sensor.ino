#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

float temp;
int RelayPin = 9;

void setup(void)
{
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  // Set RelayPin as an output pin
  pinMode(RelayPin, OUTPUT);
}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures();  
  temp =sensors.getTempCByIndex(0);
  delay(50);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print((char)176);//shows degrees character
  Serial.println("C  |  ");
  
  if(temp<80){
      // Let's turn on the relay...
      digitalWrite(RelayPin, HIGH);
      }
  else{
      // Let's turn off the relay...
      digitalWrite(RelayPin, LOW);
      }
}
