#include "MCP2515.h"





void setup() {
  Serial.begin(9600);
  MCP2515_init();
}

// the loop function runs over and over again forever
void loop() {
 // SPI_write();   // turn the LED on (HIGH is the voltage level)
  MCP2515_read(0xAA);
  delay(500);
}
