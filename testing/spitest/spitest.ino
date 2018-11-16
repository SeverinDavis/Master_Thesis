#include "MCP2515.h"





void setup() {
  MCP2515_init();
}

// the loop function runs over and over again forever
void loop() {
 // SPI_write();   // turn the LED on (HIGH is the voltage level)
  MCP2515_reset();
  delay(500);
}
