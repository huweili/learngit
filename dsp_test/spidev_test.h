#ifndef SPI_DEV_TEST_H
#define SPI_DEV_TEST_H

#include <stdint.h>

int spi_write(uint8_t reg, const uint8_t* pData, uint32_t size);
int spi_read(uint8_t reg, const uint8_t* pData, uint32_t size);

#endif
