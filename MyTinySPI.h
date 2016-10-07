#ifndef MYTINYSPI_H
#define MYTINYSPI_H

#include <stdint.h>
#include <avr/io.h>
#include <util/atomic.h>

/*
 *  ATtiny85
 *  Master:
 *  DO (MISO)  -> SI
 *  DI (MOSI)  -> SO
 *
 *  Slave:
 *  DO = SO    -> DI
 *  DI = SI    -> DO
 */

//USI ports and pins
#ifdef __AVR_ATtiny85__
#define SPI_DDR_PORT DDRB
#define USCK_DD_PIN  DDB2
#define DO_DD_PIN    DDB1      //MISO
#define DI_DD_PIN    DDB0      //MOSI
#endif

//SPI data modes
#define SPI_MODE0 0x00
#define SPI_MODE1 0x04

class MyTinySPI
{
public:
  MyTinySPI();
  void begin(void);
  void setDataMode(uint8_t spiDataMode);
  uint8_t transfer(uint8_t spiData);
  void end(void);
};

extern MyTinySPI SPI;

#endif
