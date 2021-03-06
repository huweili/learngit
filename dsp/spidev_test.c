/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
//#include <linux/spi/spidev.h>
#include "spidev.h"
#include "yavp2mwG_v010/yavp2mwG.h"

#define SPI_DEBUG 1

int fd = -1;

static void pabort(const char *s)
{
	perror(s);
	abort();
}

static const char *device = "/dev/spidev1.0";
static uint8_t mode = SPI_CPHA;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay = 0;

int spi_write(uint8_t reg, uint8_t* pData, uint32_t len)
{
	uint32_t ret;
	uint32_t i ;
	uint8_t tx[len + 1];
	printf("spi_write   write reg = %.2X, size = %.2X\r\n", reg, len);	

	memset(tx, 0, sizeof(tx));
	tx[0] = reg;
   	for( i = 0; i < len; i++) { 
		tx[i+1] = pData[i];
	}
	
	for( i = 0; i < len + 1; i++) 
		printf("%.2X ", tx[i]);
	printf("\r\n");
			
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = 0,
		.len = len + 1,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1) {
		pabort("can't send spi message");
		return -1;
	}
	printf("\r\n++++++++++   spi_write  stop\r\n");

	return 0;
}

int spi_read(uint8_t reg, uint8_t* pData, uint32_t len)
{
	uint32_t ret;
	uint32_t i ;
	
	uint8_t tx[len + 1];
	uint8_t rx[len + 1];

	printf("spi_read reg = %x, size = %d\r\n",reg, len);

	memset(tx, 0, sizeof tx);
	memset(rx, 0, sizeof rx);
	
	tx[0] = reg;
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = len+1,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	printf("read ret = %d\r\n", ret);
	if (ret < 1) {
		pabort("can't send spi message");
		return -1;
	}
	/*printf("rx : ");
	for(ret = 0; ret < len + 1; ret++)
		printf("%.2X ", rx[len]);
	printf("\r\npD : ");*/
	for (ret = 0; ret < len; ret++) {
		pData[ret] = rx[ret+1];
		printf("%.2X ", pData[ret]);
	}
	printf("\r\n++++++++++++  spi_read  stop\r\n");

	return 0;
}

static const U08 au08test_00[]={
	0x19, 0x39, 0x40, 0x40, 0x0a, 0x09, 0x01, 0x01, 0x0a, 0x01, 0x01, 0x09, 0x01, 0x01, 0x09, 0x01, 
	0x00, 0x09, 0x0a, 0x15, 0x09, 0x02, 0x13, 0x19, 0x39, 0x08, 0x08, 0x0a, 0x09, 0x02, 0x03, 0x19, 
	0x39, 0x10, 0x10, 0x0a, 0x09, 0x37, 0x41, 0x19, 0x39, 0x80, 0x80, 0x32, 0x09, 0x02, 0x02, 0x0a, 
	0x01, 0x01, 0x0a, 0x01, 0x00, 0x01, 0x02, 0x01, 0x01, 0x02, 0x00, 0x02, 0x0d, 0x01, 0x02, 0x0e, 
	0x02, 0x02, 0x0f, 0x03, 0x02, 0x10, 0x03, 0x02, 0x09, 0xa2, 0x02, 0x0a, 0x02, 0x02, 0x0b, 0x02, 
	0x02, 0x04, 0x2b, 0x02, 0x05, 0x3f, 0x02, 0x08, 0x00, 0x02, 0x06, 0x3f, 0x02, 0x11, 0x00, 0x02, 
	0x18, 0x05, 0x02, 0x19, 0x0d, 0x02, 0x1a, 0x00, 0x02, 0x1b, 0x4e, 0x02, 0x1c, 0x00, 0x02, 0x1d, 
	0x00, 0x02, 0x1e, 0x02, 0x02, 0x13, 0x10, 0x02, 0x12, 0x04, 0x02, 0x01, 0x06, 0x0a, 0x04, 0x03, 
	0x1f, 0x02, 0x02, 0x02, 0x7f, 0x1f, 0x02, 0x02, 0x02, 0x7e, 0x02, 0x02, 0x3e, 0x01, 0x03, 0xbf, 
	0x11, 0x03, 0x40, 0x00, 0x0a, 0x01, 0x03, 0xbb, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x16, 0x0a, 0x02, 
	0x00, 0x89, 0x03, 0x0d, 0x00, 0x00, 0x09, 0x18, 0x00, 0x09, 0x29, 0xfc, 0x09, 0x2c, 0x80, 0x09, 
	0x06, 0xff, 0x09, 0x07, 0x87, 0x09, 0x3a, 0x10, 0x07, 0x00, 0x01, 0x07, 0x00, 0x00, 0x07, 0x02, 
	0x53, 0x07, 0x25, 0x02, 0x07, 0x26, 0x00, 0x07, 0x01, 0x42, 0x1a, 0x31, 0x08, 0x08, 0x64, 0x0a, 
	0x31, 0x08, 0x07, 0x02, 0x03, 0x09, 0x15, 0x03, 0x03, 0x44, 0x30, 0x03, 0x43, 0x81, 0x03, 0x47, 
	0x80, 0x04, 0x55, 0xa0, 0x1f, 0x4b, 
};
static const U08 au08test_16[]={
	0x03, 0x23, 0x00, 0x03, 0x25, 0x00, 0x03, 0x27, 0x00, 0x03, 0x29, 0x00, 0x83, 0x03, 0x2b, 0x00, 
	0x00, 0x83, 0x03, 0x2f, 0x00, 0x00, 0x83, 0x03, 0x33, 0x00, 0x00, 0x83, 0x03, 0x37, 0x00, 0x00, 
	0x83, 0x03, 0x3b, 0x00, 0x03, 0x83, 0x03, 0x3f, 0x00, 0x03, 0x03, 0x20, 0x00, 0x03, 0x21, 0x00, 
	0x03, 0x22, 0x00, 0x89, 0x04, 0x30, 0x00, 0x00, 0x00, 0x83, 0x06, 0x50, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x00, 0x41, 0x04, 0x10, 0x40, 0x04, 0x20, 0x00, 0x04, 0x30, 0x00, 0x04, 0x01, 0x01, 
	0x04, 0x11, 0x01, 0x04, 0x21, 0x00, 0x04, 0x31, 0x20, 0x04, 0x02, 0x24, 0x04, 0x03, 0x00, 0x04, 
	0x13, 0x00, 0x04, 0x23, 0x00, 0x04, 0x33, 0x00, 0x04, 0x04, 0x24, 0x04, 0x05, 0x00, 0x04, 0x15, 
	0x00, 0x04, 0x25, 0x00, 0x04, 0x35, 0x00, 0x04, 0x06, 0x44, 0x04, 0x16, 0x44, 0x04, 0x26, 0x44, 
	0x04, 0x36, 0x44, 0x04, 0x07, 0x00, 0x04, 0x17, 0x00, 0x04, 0x27, 0x00, 0x04, 0x08, 0x80, 0x04, 
	0x18, 0x80, 0x04, 0x28, 0x80, 0x04, 0x09, 0x80, 0x04, 0x19, 0x80, 0x04, 0x29, 0x80, 0x84, 0x03, 
	0x2b, 0x00, 0x00, 0x87, 0x07, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x08, 0x29, 0x00, 
	0x10, 0x00, 0x22, 0x00, 0x43, 0x00, 0x07, 0x30, 0x00, 0x07, 0x03, 0x00, 0x07, 0x12, 0x88, 0x87, 
	0x03, 0x15, 0x00, 0x00, 0x87, 0x04, 0x44, 0x00, 0x00, 0x00, 0x07, 0x08, 0x00, 0x87, 0x08, 0x1c, 
	0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x02, 0x42, 
};

static const U08 au08test_17[]={
	0x02, 0x04, 0x2b, 0x02, 0x05, 0x01, 0x02, 0x06, 0x01, 0x04, 0x0a, 0x0c, 0x04, 0x1a, 0x0c, 0x04, 
	0x2a, 0x30, 0x04, 0x3a, 0x0a, 0x04, 0x2c, 0x00, 0x07, 0x48, 0x00, 0x89, 0x05, 0x1b, 0x00, 0x00, 
	0x00, 0x00, 0x89, 0x03, 0x19, 0x80, 0x00, 0x03, 0x06, 0x60, 0x03, 0x08, 0x60, 0x03, 0x0a, 0x00, 
	0x03, 0x0c, 0x00, 0x83, 0x03, 0x0e, 0x00, 0x00, 0x83, 0x03, 0x10, 0x00, 0x00, 0x83, 0x03, 0x12, 
	0x00, 0x00, 0x08, 0x20, 0x00, 0x05, 0x00, 0x00, 0x03, 0x14, 0x00, 0x03, 0x16, 0x00, 0x03, 0x18, 
	0x00, 0x03, 0x1a, 0x00, 0x03, 0x1c, 0x60, 0x03, 0x1e, 0x60, 0x89, 0x03, 0x24, 0xef, 0x6f, 0x89, 
	0x03, 0x26, 0xef, 0x6f, 0x1f, 0x0a, 0x09, 0x3a, 0x00, 
};

static const U08 au08mictest_00[]={
	0x19, 0x39, 0x40, 0x40, 0x0a, 0x09, 0x01, 0x01, 0x0a, 0x01, 0x01, 0x09, 0x01, 0x01, 0x09, 0x01, 
	0x00, 0x09, 0x0a, 0x15, 0x09, 0x02, 0x13, 0x19, 0x39, 0x08, 0x08, 0x0a, 0x09, 0x02, 0x03, 0x19, 
	0x39, 0x10, 0x10, 0x0a, 0x09, 0x37, 0x41, 0x19, 0x39, 0x80, 0x80, 0x32, 0x09, 0x02, 0x02, 0x0a, 
	0x01, 0x01, 0x0a, 0x01, 0x00, 0x01, 0x02, 0x01, 0x01, 0x02, 0x00, 0x02, 0x0d, 0x03, 0x02, 0x0e, 
	0x03, 0x02, 0x0f, 0x03, 0x02, 0x10, 0x03, 0x02, 0x09, 0xa2, 0x02, 0x0a, 0x02, 0x02, 0x0b, 0x02, 
	0x02, 0x04, 0x2b, 0x02, 0x05, 0x3f, 0x02, 0x08, 0x00, 0x02, 0x06, 0x3f, 0x02, 0x11, 0x00, 0x02, 
	0x18, 0x05, 0x02, 0x19, 0x0d, 0x02, 0x1a, 0x00, 0x02, 0x1b, 0x4e, 0x02, 0x1c, 0x00, 0x02, 0x1d, 
	0x00, 0x02, 0x1e, 0x02, 0x02, 0x13, 0x10, 0x02, 0x12, 0x04, 0x02, 0x01, 0x06, 0x0a, 0x04, 0x03, 
	0x1f, 0x02, 0x02, 0x02, 0x7f, 0x1f, 0x02, 0x02, 0x02, 0x7e, 0x02, 0x02, 0x3e, 0x01, 0x03, 0xbf, 
	0x11, 0x03, 0x40, 0x00, 0x0a, 0x01, 0x03, 0xbb, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x16, 0x0a, 0x02, 
	0x00, 0x89, 0x03, 0x0d, 0x00, 0x00, 0x09, 0x18, 0x00, 0x09, 0x29, 0xfc, 0x09, 0x2c, 0x80, 0x09, 
	0x06, 0xbb, 0x09, 0x07, 0x86, 0x09, 0x3a, 0x10, 0x07, 0x00, 0x01, 0x07, 0x00, 0x00, 0x07, 0x02, 
	0x53, 0x07, 0x25, 0x02, 0x07, 0x26, 0x00, 0x07, 0x01, 0x42, 0x1a, 0x31, 0x08, 0x08, 0x64, 0x0a, 
	0x31, 0x08, 0x07, 0x02, 0x03, 0x09, 0x15, 0x03, 0x03, 0x44, 0x30, 0x03, 0x43, 0x81, 0x03, 0x47, 
	0x80, 0x04, 0x55, 0xa0, 0x1f, 0x4b, 
};


/*
	[Path]
		Set Signal Path
 */
static const U08 au08mictest_16[]={
	0x03, 0x23, 0x00, 0x03, 0x25, 0x00, 0x03, 0x27, 0x00, 0x03, 0x29, 0x00, 0x83, 0x03, 0x2b, 0x00, 
	0x00, 0x83, 0x03, 0x2f, 0x00, 0x00, 0x83, 0x03, 0x33, 0x00, 0x00, 0x83, 0x03, 0x37, 0x00, 0x00, 
	0x83, 0x03, 0x3b, 0x00, 0x10, 0x83, 0x03, 0x3f, 0x00, 0x10, 0x03, 0x20, 0x00, 0x03, 0x21, 0x00, 
	0x03, 0x22, 0x00, 0x89, 0x04, 0x30, 0x40, 0x00, 0x00, 0x83, 0x06, 0x50, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x00, 0x41, 0x04, 0x10, 0x40, 0x04, 0x20, 0x00, 0x04, 0x30, 0x00, 0x04, 0x01, 0x01, 
	0x04, 0x11, 0x01, 0x04, 0x21, 0x00, 0x04, 0x31, 0x20, 0x04, 0x02, 0x24, 0x04, 0x03, 0x00, 0x04, 
	0x13, 0x00, 0x04, 0x23, 0x00, 0x04, 0x33, 0x00, 0x04, 0x04, 0x24, 0x04, 0x05, 0x00, 0x04, 0x15, 
	0x00, 0x04, 0x25, 0x00, 0x04, 0x35, 0x00, 0x04, 0x06, 0x44, 0x04, 0x16, 0x44, 0x04, 0x26, 0x44, 
	0x04, 0x36, 0x44, 0x04, 0x07, 0x00, 0x04, 0x17, 0x00, 0x04, 0x27, 0x00, 0x04, 0x08, 0x80, 0x04, 
	0x18, 0x80, 0x04, 0x28, 0x80, 0x04, 0x09, 0x80, 0x04, 0x19, 0x80, 0x04, 0x29, 0x80, 0x84, 0x03, 
	0x2b, 0x00, 0x00, 0x87, 0x07, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x08, 0x29, 0x01, 
	0x00, 0x00, 0x22, 0x00, 0x43, 0x00, 0x07, 0x30, 0x00, 0x07, 0x03, 0x00, 0x07, 0x12, 0x88, 0x87, 
	0x03, 0x15, 0x00, 0x00, 0x87, 0x04, 0x44, 0x00, 0x00, 0x00, 0x07, 0x08, 0x00, 0x87, 0x08, 0x1c, 
	0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x02, 0x00, 
};


/*
	[Start]
		Set Volume
 */
static const U08 au08mictest_17[]={
	0x02, 0x04, 0x2b, 0x02, 0x05, 0x3f, 0x02, 0x06, 0x3f, 0x04, 0x0a, 0x30, 0x04, 0x1a, 0x30, 0x04, 
	0x2a, 0x30, 0x04, 0x3a, 0x0a, 0x04, 0x2c, 0x00, 0x07, 0x48, 0x00, 0x89, 0x05, 0x1b, 0x00, 0x00, 
	0x23, 0x00, 0x89, 0x03, 0x19, 0x80, 0x00, 0x03, 0x06, 0x00, 0x03, 0x08, 0x00, 0x03, 0x0a, 0x00, 
	0x03, 0x0c, 0x00, 0x83, 0x03, 0x0e, 0x60, 0x60, 0x83, 0x03, 0x10, 0x00, 0x00, 0x83, 0x03, 0x12, 
	0x00, 0x00, 0x08, 0x20, 0x00, 0x05, 0x00, 0x00, 0x03, 0x14, 0x00, 0x03, 0x16, 0x00, 0x03, 0x18, 
	0x00, 0x03, 0x1a, 0x00, 0x03, 0x1c, 0x60, 0x03, 0x1e, 0x60, 0x89, 0x03, 0x24, 0xef, 0x6f, 0x89, 
	0x03, 0x26, 0xef, 0x6f, 0x1f, 0x0a, 0x09, 0x3a, 0x00, 
};

U08 au08_yadsel_IF[59];
U08 au08_yadsel_IM_A[239];
U08 au08_yadsel_IM_MA[85];
U08 au08_yadsel_IM_MB[86];
U08 au08_yadsel_IM_B[72];
U08 au08_yadsel_IM_C[87];
U08 au08_yadsel_IM_E[95];
U08 au08_yadsel_IM_F[128];
U08 au08_yadsel_IM_ANA[59];
U08 au08_yadsel_IM_CD[50];

int main(int argc, char *argv[])
{
    int ret = 0;
    unsigned int i=0;

    fd = open(device, O_RDWR);
    if (fd < 0)
        pabort("can't open device");

    /*
     * spi mode
     */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
        pabort("can't set spi mode");

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
        pabort("can't get spi mode");

    uint8_t msb_first = 0;
    ret = ioctl(fd, SPI_IOC_WR_LSB_FIRST, &msb_first);
    if(ret == -1)
        pabort("can't set msb first");
    /*
     * bits per word
     */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't set bits per word");

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't get bits per word");

    /*
     * max speed hz
     */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("can't set max speed hz");

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("can't get max speed hz");

    printf("spi mode: %d\n", mode);
    printf("bits per word: %d\n", bits);
    printf("max speed22: %d Hz (%d KHz)\n", speed, speed/1000);
    /*while(1)
      {
      yavp2mwg_set_param(yavp2mwg_initialise, yavp2mwg_function_test2, yavp2mwg_difformat_i2s7);
      yavp2mwg_set_param(yavp2mwg_test_volume_f, -50, 0);
      yavp2mwg_set_param(yavp2mwg_test_volume_r, -50, 0);
      usleep(1000*1000);
      }*/
    //	while(1)
    {
      YAVP2mwG_set_param(YAVP2MWG_INITIALISE, YAVP2MWG_FUNCTION_AUDIO1, YAVP2MWG_DIFFORMAT_I2S7);
     // YAVP2mwG_set_param(YAVP2MWG_FUNCTION_SELECT,YAVP2MWG_FUNCTION_MIC1,YAVP2MWG_DIFFORMAT_I2S7);
      YAVP2mwG_set_param(YAVP2MWG_AUDIO_VOLUME,0,YAVP2MWG_UNMUTE);
      YAVP2mwG_set_param(YAVP2MWG_AUDIO_INPUT_VOLUME,0,0);
      /*YAVP2mwG_set_param(YAVP2MWG_MIC_RECEIVE_VOLUME,0,YAVP2MWG_UNMUTE);
      YAVP2mwG_set_param(YAVP2MWG_MIC_INPUT_VOLUME,0,0);
    //	usleep(1000*1000);*/
    }//*/
    /*YAVP2mwG_batch_process(au08test_00, sizeof(au08test_00));
      YAVP2mwG_batch_process(au08test_16, sizeof(au08test_16));
      YAVP2mwG_batch_process(au08test_17, sizeof(au08test_17));
      */
    /*uint8_t myStr = 0;
      uint32_t result = 0;
      while(1)
      result = YAVP2mwG_read_register(YAD1DD_REGSEL_IM_ANA, 0x00, &myStr, 1 );*/

    //YAVP2mwG_set_param(YAVP2MWG_INITIALISE, YAVP2MWG_FUNCTION_AUDIO1, YAVP2MWG_DIFFORMAT_I2S7);
    /*YAVP2mwG_batch_process(au08test_00, sizeof(au08test_00));
      YAVP2mwG_batch_process(au08test_16, sizeof(au08test_16));
      YAVP2mwG_batch_process(au08test_17, sizeof(au08test_17));
      */
    /*YAVP2mwG_batch_process(au08mictest_00, sizeof(au08test_00));
    YAVP2mwG_batch_process(au08mictest_16, sizeof(au08mictest_16));
    YAVP2mwG_batch_process(au08mictest_17, sizeof(au08mictest_17));*/
/*
    U08 str = 0;
    for( i = 0; i < sizeof(au08_yadsel_IF); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IF, i, &str, 1);
        au08_yadsel_IF[i] = str;
    }	

    for( i = 0; i < sizeof(au08_yadsel_IM_A); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_A, i,  &str, 1);
        au08_yadsel_IM_A[i] = str;
    }	

    for( i = 0; i < sizeof(au08_yadsel_IM_MA); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_MA, i,  &str, 1);
        au08_yadsel_IM_MA[i] = str;
    }	

    for( i = 0; i < sizeof(au08_yadsel_IM_MB); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_MB, i,  &str, 1);
        au08_yadsel_IM_MB[i] = str;
    }	

    for( i = 0; i < sizeof(au08_yadsel_IM_B); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_B, i,  &str, 1);
        au08_yadsel_IM_B[i] = str;
    }	

    for( i = 0; i < sizeof(au08_yadsel_IM_C); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_C, i,  &str, 1);
        au08_yadsel_IM_C[i] = str;
    }

    for( i = 0; i < sizeof(au08_yadsel_IM_E); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_E, i,  &str, 1);
        au08_yadsel_IM_E[i] = str;
    }

    for( i = 0; i < sizeof(au08_yadsel_IM_F); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_F, i,  &str, 1);
        au08_yadsel_IM_F[i] = str;
    }

    for( i = 0; i < sizeof(au08_yadsel_IM_ANA); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_ANA, i,  &str, 1);
        au08_yadsel_IM_ANA[i] = str;
    }

    for( i = 0; i < sizeof(au08_yadsel_IM_CD); i++) {
        YAVP2mwG_read_register(YAD1DD_REGSEL_IM_CD, i,  &str, 1);
        au08_yadsel_IM_CD[i] = str;
    }


    printf("++++++++++++++++++++++++++++au08_yadsel_IF\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IF); i++) {
        printf("%.2X ", au08_yadsel_IF[i]);
    }
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_A\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_A); i++) {
        printf("%.2X ", au08_yadsel_IM_A[i]);
    }	
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_MA\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_MA); i++) {
        printf("%.2X ", au08_yadsel_IM_MA[i]);
    }	
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_MB\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_MB); i++) {
        printf("%.2X ", au08_yadsel_IM_MB[i]);
    }	
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_B\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_B); i++) {
        printf("%.2X ", au08_yadsel_IM_B[i]);
    }
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_C\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_C); i++) {
        printf("%.2X ", au08_yadsel_IM_C[i]);
    }
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_E\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_E); i++) {
        printf("%.2X ", au08_yadsel_IM_E[i]);
    }	
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_F\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_F); i++) {
        printf("%.2X ", au08_yadsel_IM_F[i]);
    }	
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_ANA\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_ANA); i++) {
        printf("%.2X ", au08_yadsel_IM_ANA[i]);
    }	
    printf("\r\n");

    printf("++++++++++++++++++++++++++++au08_yadsel_IM_CD\r\n");
    for( i = 0; i < sizeof(au08_yadsel_IM_CD); i++) {
        printf("%.2X ", au08_yadsel_IM_CD[i]);
    }	
    printf("\r\n");
*/

    close(fd);

    return ret;
}
