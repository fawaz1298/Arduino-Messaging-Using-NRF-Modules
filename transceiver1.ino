#include <SPI.h>
#include <RF24.h>
RF24 radio(10,9);
void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(0xF0F0F0F0D2LL);
    radio.openReadingPipe(1, 0xF0F0F0F0E1LL);  
    radio.startListening();
    Serial.println("TEXT 2 on:");
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
        char receivedMessage[32] = "";
        radio.read(receivedMessage, sizeof(receivedMessage));        
        if(test=='y'||test=='Y'){
          Serial.println("Enter key:");
          while(!Serial.available());
          long int key=Serial.parseInt();
          String rstr=String(receivedMessage);
          for(int i=0;i<rstr.length();i++)
            {
            rstr[i]-=key;
            }
          Serial.println("ard 2: " + rstr);
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
        long int key1=123456789;
        Serial.println("ard 1: "+str);
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
