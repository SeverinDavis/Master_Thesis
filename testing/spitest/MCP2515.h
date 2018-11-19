#ifndef MCP2515_H
#define MCP2515_H

#define DEBUG

#include <SPI.h>
#include "CAN.h"

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
bool SPI_send(uint8_t cmd)
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

//writes a byte to a specified register
bool MCP2515_write(uint8_t reg, uint8_t data)
{
  //slave select low
  digitalWrite(SPI_SS, LOW);
  delay(1);
  //transfer command
  SPI.transfer(WRITE);
  //transfer register
  SPI.transfer(reg);
  //transfer data
  SPI.transfer(data);
  delay(1);
  //slave select high
  digitalWrite(SPI_SS, HIGH);
}

//writes a byte to a specified starting register and keeps writing into following registers
bool MCP2515_write_batch(uint8_t reg, uint8_t* data, uint8_t data_length)
{
  //slave select low
  digitalWrite(SPI_SS, LOW);
  delay(1);
  //transfer command
  SPI.transfer(WRITE);
  //transfer register
  SPI.transfer(reg);
  //transfer data
  for(int i = 0; i < data_length; i++)
    SPI.transfer(data[i]);
  delay(1);
  //slave select high
  digitalWrite(SPI_SS, HIGH);
}

//reads a byte from a specified register
uint8_t MCP2515_read(uint8_t reg)
{
  //slave select low
  digitalWrite(SPI_SS, LOW);
  delay(1);
  //transfer command
  SPI.transfer(READ);
  //transfer register
  SPI.transfer(reg);
  //transfer data
  uint8_t data = SPI.transfer(0x00);
  delay(1);
  //slave select high
  digitalWrite(SPI_SS, HIGH);

  return data;
}

void MCP2515_load(can_message p_message) {
  //load identifier hi (31h, 41h, 51h)
  //identifier is stored in lower 11 bits of 16 bit of can_message
  //shift identifier down 3 bits to get upper 8 bits.
  uint8_t identifier_hi = p_message.identifier >> 3;
  MCP2515_write(0x31, identifier_hi);

  //load identifier low (32h, 42h, 52h)
  //remaining 3 lower bits need to be in upper three bits of identifier_lo
  uint8_t identifier_lo = p_message.identifier << 5;
  MCP2515_write(0x32, identifier_lo);

  //length field is lower 4 bits. Apply mask to ensure now other bits are set (35h, 45h, 55h)
  uint8_t data_length = p_message.data_length & 0x0F;
  MCP2515_write(0x35, data_length);

  MCP2515_write_batch(0x36, p_message.data, p_message.data_length);


}

//initializes SPI to communicate with MCP2515
void MCP2515_init() {
  pinMode(SPI_SS, OUTPUT);
  digitalWrite(SPI_SS, HIGH);
  SPI.begin ();
  SPI.setClockDivider(SPI_CLOCK_DIV32);
}

//sens reset signal to mcp2515
void MCP2515_reset(){
  SPI_send(RESET);
}

#endif
