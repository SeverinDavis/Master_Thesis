#ifndef MCP2515_H
#define MCP2515_H

#include <SPI.h>

const int SPI_SS = 10;
const int SPI_CLK = 13;
const int SPI_MISO = 12;

typedef enum {
  RESET       = 0b11000000, 
  READ        = 0b00000011,
  WRITE       = 0b00000010,
  READ_STATUS = 0b10100000,
  RS_STATUS   = 0b10110000,
  BIT_MODIFY  = 0b00000101
} MCP_SPI_CMD;

//sends a single byte to MCP2515 via SPI
bool SPI_write(uint8_t cmd)
{
  //slave select low
  digitalWrite(SPI_SS, LOW);
  delay(1);
  //transfer command
  SPI.transfer(cmd);
  delay(1);
  //slave select high
  digitalWrite(SPI_SS, HIGH);
}

//initializes SPI to communicate with MCP2515
void MCP2515_init() {
  pinMode(SPI_SS, OUTPUT);
  SPI.begin ();
  SPI.setClockDivider(SPI_CLOCK_DIV32);
}

//sens reset signal to mcp2515
void MCP2515_reset(){
  SPI_write(RESET);
}

#endif
