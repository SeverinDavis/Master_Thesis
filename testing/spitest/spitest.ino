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
       uint8_t data[8];
       data[0] = 1;
       data[1] = 2;
       data[2] = 3;
       data[3] = 7;
       data[4] = 1;
       data[5] = 2;
       data[6] = 3;
       data[7] = 7;
       
       can_message message = can_message_create(7, data, 8);
       Serial.println("loading");
       MCP2515_load(message);
       }
    if(readByte =='5') {
       Serial.println("reading");
       Serial.println(MCP2515_read(0x31),HEX);
       Serial.println(MCP2515_read(0x32),HEX);
       Serial.println(MCP2515_read(0x35),HEX);
       Serial.println(MCP2515_read(0x36),HEX);
       Serial.println(MCP2515_read(0x37),HEX);
       Serial.println(MCP2515_read(0x38),HEX);
       Serial.println(MCP2515_read(0x39),HEX);
       Serial.println(MCP2515_read(0x3A),HEX);
       Serial.println(MCP2515_read(0x3B),HEX);
       Serial.println(MCP2515_read(0x3C),HEX);
       Serial.println(MCP2515_read(0x3D),HEX);
    }
    if(readByte =='6') {
       Serial.println("reading");
       Serial.println(MCP2515_read(0x32),HEX);
    
    }
  }
}
