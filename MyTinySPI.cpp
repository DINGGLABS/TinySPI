#include "MyTinySPI.h"

void MyTinySPI::begin(void)
{
  USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK);    // enable Three-wire mode and select clock source
  SPI_DDR_PORT |= _BV(USCK_DD_PIN);                   // set the USCK pin as output
  SPI_DDR_PORT |= _BV(DO_DD_PIN);                     // set the DO pin as output
  SPI_DDR_PORT &= ~_BV(DI_DD_PIN);                    // set the DI pin as input
}

void MyTinySPI::setDataMode(uint8_t spiDataMode)
{
  if (spiDataMode == SPI_MODE1) USICR |= _BV(USICS0);
  else USICR &= ~_BV(USICS0);
}

uint8_t MyTinySPI::transfer(uint8_t spiData)
{
  USIDR = spiData;                     // set data register
  USISR = _BV(USIOIF);                 // clear counter and counter overflow interrupt flag
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)    // ensure a consistent clock period
  {
    while (!(USISR & _BV(USIOIF))) USICR |= _BV(USITC);  // SW SCK
  }
  return USIDR;
}

void MyTinySPI::end(void)
{
  USICR &= ~(_BV(USIWM1) | _BV(USIWM0));
}

MyTinySPI SPI = MyTinySPI();           // instantiate a tinySPI object
