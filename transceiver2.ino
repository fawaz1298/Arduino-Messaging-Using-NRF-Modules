#include <SPI.h>
#include <RF24.h>
#include <string.h>
RF24 radio(10,9);
void setup(){
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(0xF0F0F0F0E1LL);
    radio.openReadingPipe(1, 0xF0F0F0F0D2LL);
    radio.startListening();
    Serial.println("TEXT 1 on:");
    pinMode(8,OUTPUT);
}
void loop() {
    if(radio.available()){
        Serial.println("message available\npress y to open");
        digitalWrite(8,HIGH);
        while(!Serial.available());
        char test=Serial.read();
        while (Serial.available() > 0) {
          char garbageChar = Serial.read();
        }
        string receivedMessage = "";
        radio.read(receivedMessage, sizeof(receivedMessage));        
        if(test=='y'||test=='Y'){
          long int key=123456789;
          String rstr=String(receivedMessage);
          for(int i=0;i<rstr.length();i++)
            {
            rstr[i]-=key;
            }
          Serial.println("ard 1: " + rstr);
        }
        else Serial.println("!!!!message killed!!!!");
        delay(1000);
        digitalWrite(8,LOW);
        while (Serial.available() > 0) {
          char garbageChar = Serial.read();
        }
    }
      if (Serial.available() > 0) {
        digitalWrite(8,HIGH);
        radio.stopListening();
        String str = Serial.readStringUntil('\n');
        while (Serial.available() > 0) {
        char garbageChar = Serial.read();
        }
        Serial.println("Enter key:");
        while(!Serial.available());
        int key1=Serial.parseInt();
        Serial.println("ard 2: "+str);
        for(int i=0;i<str.length();i++)
          {
           str[i]+=key1;
          }
        radio.write(str.c_str(), str.length()+1);
        delay(1000);
        digitalWrite(8,LOW);
        radio.startListening();
     }
}
