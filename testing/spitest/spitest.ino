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


void setup() {
  // set the slaveSelectPin as an output:
  pinMode(SPI_SS, OUTPUT);
  SPI.begin ();
  SPI.setClockDivider(SPI_CLOCK_DIV32);
}

// the loop function runs over and over again forever
void loop() {
  SPI_write();   // turn the LED on (HIGH is the voltage level)

  delay(500);
}

bool SPI_write()
{
    // take the SS pin low to select the chip:
  digitalWrite(SPI_SS, LOW);
  delay(1);
  SPI.transfer(0xAA);
  SPI.transfer(0x55);
  delay(1);
  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_SS, HIGH);
  
}
