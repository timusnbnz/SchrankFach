#include <SoftwareSerial.h>

unsigned long lastping = 0;
boolean connection = false;
PROGMEM const char HandshakeByte = 'T';
PROGMEM const int lockpin = 9;
PROGMEM const int rxpin = 11;
PROGMEM const int txpin = 10;

SoftwareSerial myserial(11, 10);

void setup() {
  Serial.begin(4800);
  myserial.begin(4800);
  pinMode(lockpin,OUTPUT);
}

void loop() {
  myserial.listen();
  while (myserial.available() > 0) {
    char inByte = myserial.read();
    if(inByte==Handshakebyte){
      lastping = millis();
      connection = true;
      if(not connection){
        connection = true;
        myserial.print(HandshakeByte);
      }
    }
  }
  if((millis()-lastping)>500){
    connection = false;
  }
  if(connection){
    digitalWrite(lockpin,HIGH);
  } else{
    digitalWrite(lockpin,LOW);
  }
}
