#include <SoftSerial.h>
#include <TinyPinChange.h>
#include <avr/eeprom.h>

boolean connection = false;
PROGMEM const char HandshakeByte = 'T';
PROGMEM const char idCheckByte = 't';
PROGMEM const int ledpin = 1;
PROGMEM const int analogseed = 0;

SoftSerial mySerial(3, 4); // RX, TX

void setup()  
{
  mySerial.begin(4800);
  pinMode(ledpin,OUTPUT);
  pinMode(analogseed,INPUT);
  randomSeed(analogRead(analogseed));
}

void loop()
{
  while(not connection){
    digitalWrite(ledpin,HIGH);
    mySerial.print(HandshakeByte);
    delay(400);
    digitalWrite(ledpin,LOW);
    mySerial.listen();
    if(mySerial.available()>0){
      char inByte = mySerial.read();
      if(inByte==HandshakeByte){
        connection = true;
        digitalWrite(ledpin,HIGH);
        mySerial.listen();
        while(true){
          while(mySerial.available()>0){
            char inByte = mySerial.read();            
          }
        }
      }
    }
    delay(100);
  }
  mySerial.println(HandshakeByte);
  delay(200);  
}
