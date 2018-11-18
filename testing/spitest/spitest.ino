#include "MCP2515.h"
#include "CAN.h"





void setup() {
  Serial.begin(9600);
  MCP2515_init();
}

// the loop function runs over and over again forever
void loop() {

  if(Serial.available() > 0){
    uint8_t readByte = Serial.read();

    if(readByte =='r') {
       Serial.println("reading");
       Serial.println(MCP2515_read(0x36),HEX);
    }
    if(readByte =='w') {
       Serial.println("writing");
       MCP2515_write(0x36, 0x02);
       }
    if(readByte =='5') {
       Serial.println("writing");
       MCP2515_write(0x36, 0x05);
    }
    if(readByte =='6') {
       Serial.println("writing");
       MCP2515_write(0x36, 0x06);
    
    }
  }
 // SPI_write();   // turn the LED on (HIGH is the voltage level)
}
