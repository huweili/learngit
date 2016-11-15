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
#include "spidev.h"
#include "yavp2mwG_v010/yavp2mwG.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static int  volume;
static int8_t bass;
static int8_t middle;
static int8_t treble;
static int8_t balance;
static int8_t fader;
static uint8_t fix_eq;
static uint8_t eq_band;
static uint8_t mute;

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

#define VOLUME_MAX  40

static int      eqBandsGain[10];            // 保存每段EQ的值
static int      last_volume     = 0xFFFFFFFF;
static int8_t   last_bass       = 0xFF;
static int8_t   last_middle     = 0xFF;
static int8_t   last_treble     = 0xFF;
static int8_t   last_balance    = 0xFF;
static int8_t   last_fader      = 0xFF;
static uint8_t  last_eq_type    = 0xFF;

const int effectEQGain[10][10] = { 
    //band1 ---  band10
    { 5,  5,  3,  0,  0,  0,  0,  2,  2,  2},       // 古典
    { 0,  0,  3,  3,  3,  0,  2,  4,  4,  4},       // 爵士
    { 3,  1, -2, -3, -4, -3, -2,  0,  1,  2},       // 流行
    { 1,  2,  3, -1, -1,  0,  0,  4,  4,  4},       // 摇滚
    { 0,  2,  1,  0,  1,  0,  0, -2, -3, -5},       // 人声
    { 0,  2,  1,  0,  0,  0,  0, -2, -3, -5},       // 怀旧
    { 0,  0,  3,  4,  2,  5,  2,  0,  0,  0},       // 歌剧
    { 0,  0,  2,  2,  0,  0,  0,  3,  3,  3},       // 乡村
    { 3,  5,  1, -1, -1,  0,  0,  4,  4,  4},       // 舞曲
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},       // 关闭
};

//gain :  -12  --- 12
static int ymu836_set_eq_band(int band, int gain)
{
    if(band < 0 || band > 9)
        return -1;

    if(gain < -12 || gain > 12)
        return -1;

    if(gain == eqBandsGain[band])
        return -1;

    eqBandsGain[band] = gain;

    switch(band) {
        case 0:         // 31.25Hz
        case 1:         // 62.5Hz
        case 2:         // 125Hz
        case 3:         // 250Hz
        case 4:         // 500Hz
            YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ1,  1<<band, gain);
            break;
        case 5:         // 1kHz
        case 6:         // 2kHz
        case 7:         // 4kHz
        case 8:         // 8kHz
        case 9:         // 16kHz
            YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ2,  1<<(band-5), gain);
            break;
        default:
            break;
    }

    return 0;
}

static int ymu836_set_eq_type(int type)
{
    int i = 0;

    if(type < 0 || type > 9)
        return -1;

    if(type == last_eq_type)
        return -1;

    last_eq_type = type;

    for(i = 0; i < 10; i++) {
        ymu836_set_eq_band(i, effectEQGain[type][i]);
    }
    return 0;
}

static int ymu836_set_bass(int val)
{
    printf("bass = %d\r\n", val);
    if(val < -12 || val > 12)
        return -1;

    if(val == last_bass)
        return -1;

    last_bass = val;

    // 62.5Hz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ1,  1<<0, val);
    // 125Hz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ1,  1<<1, val);
    // 250Hz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ1,  1<<2, val);

    return 0;
}

static int ymu836_set_middle(int val)
{
    if(val < -12 || val > 12)
        return -1;

    if(val == last_middle)
        return -1;

    last_middle = val;

    // 250Hz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ1,  1<<3, val);
    // 500Hz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ1,  1<<4, val);
    // 1kHz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ2,  1<<0, val);
    // 2kHz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ2,  1<<1, val);

    return 0;
}

static int ymu836_set_treble(int val)
{
    if(val < -12 || val > 12)
        return -1;

    if(val == last_treble)
        return -1;

    last_treble = val;

    // 4kHz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ2,  1<<2, val);
    // 8kHz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ2,  1<<3, val);
    // 16kHz
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_GEQ2,  1<<4, val);

    return 0;
}

// balance: -128  --- 128,  -128及以下: MUTE，128及以上：128dB  
static int ymu836_set_balance(int val)
{
    printf("balance = %d\r\n", balance);
    /*if(val < -10 || val > 10)
        return -1;*/

    if(val == last_balance)
        return -1;

    last_balance = val;

    /*int temp = val * 128.0 / 10;*/
    int temp = val;
    printf("temp = %d\r\n", temp);
    if(temp != 0)
        YAVP2mwG_set_param(YAVP2MWG_AUDIO_BALANCE, -temp, temp);
    else
        YAVP2mwG_set_param(YAVP2MWG_AUDIO_BALANCE, 0, 0);

    YAVP2mwG_set_param(YAVP2MWG_AUDIO_VOLUME, last_volume, YAVP2MWG_UNMUTE);

    return 0;
}

// fader: -128  --- 128,  -128及以下: MUTE，128及以上：128dB  
static int ymu836_set_fader(int val)
{
    printf("fader = %d\r\n", val);
    if(val < -10 || val > 10)
        return -1;

    if(val == last_fader)
        return -1;

    last_fader = val;

    int temp = val * 128.0 / 10;
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_FADER, -temp, temp);

    return 0;
}

int ymu836_audio_init(void) 
{
    D1("YMU836_audioinit\r\n");
    YAVP2mwG_set_param(YAVP2MWG_INITIALISE, YAVP2MWG_FUNCTION_AUDIO1, YAVP2MWG_DIFFORMAT_I2S7);
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_VOLUME,0,YAVP2MWG_UNMUTE);
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_INPUT_VOLUME,0,0);
    return 0;
}

int ymu836_set_audio_volume(int route, int volume) 
{
    printf("volume = %d\r\n", volume);
    if (volume > VOLUME_MAX)
        volume = VOLUME_MAX;
    /*else if(volume < 0)
      volume = 0;
      */
    if(last_volume == volume)
        return -1;

    last_volume = volume;
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_VOLUME, volume, YAVP2MWG_UNMUTE);
    return 0;
}
int ymu836_audio_mute(int mode) 
{
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_VOLUME, last_volume, YAVP2MWG_MUTE);
    return 0;
}

int ymu836_audio_unmute(int mode) 
{
    YAVP2mwG_set_param(YAVP2MWG_AUDIO_VOLUME, last_volume, YAVP2MWG_UNMUTE);
    return 0;
}

static void print_usage(const char *prog)
{
    printf("Usage: %s [-DsbdlHOLC3]\n", prog);
    puts("  -D --device   device to use (default /dev/spidev1.1)\n"
            "  -s --speed    max speed (Hz)\n"
            "  -d --delay    delay (usec)\n"
            "  -b --bpw      bits per word \n"
            "  -l --loop     loopback\n"
            "  -H --cpha     clock phase\n"
            "  -O --cpol     clock polarity\n"
            "  -L --lsb      least significant bit first\n"
            "  -C --cs-high  chip select active high\n"
            "  -3 --3wire    SI/SO signals shared\n");
    exit(1);
}

static void parse_opts(int argc, char *argv[])
{
    while (1) {
        static const struct option lopts[] = {
            { "volume",  1, 0, 'v' },
            { "bass",    1, 0, 'b' },
            { "middle",  1, 0, 'm' },
            { "treble",  1, 0, 't' },
            { "balance", 1, 0, 'l' },
            { "fader",   1, 0, 'f' },
            { "fix_eq",  1, 0, 'i' },
            { "eq_band", 1, 0, 'e' },
            { "mute",    1, 0, 'u' },
            { NULL, 0, 0, 0 },
        };
        int c;

        c = getopt_long(argc, argv, "v:b:m:t:l:f:i:e:u:", lopts, NULL);

        if (c == -1)
            break;

        switch (c) {
            case 'v':
                volume = atoi(optarg);
                ymu836_set_audio_volume(0, volume);
                break;
            case 'b':
                bass = atoi(optarg);
                ymu836_set_bass(bass);
                break;
            case 'm':
                middle = atoi(optarg);
                ymu836_set_middle(middle);
                break;
            case 't':
                treble = atoi(optarg);
                ymu836_set_treble(treble);
                break;
            case 'l':
                balance = atoi(optarg);
                ymu836_set_balance(balance);
                break;
            case 'f':
                fader = atoi(optarg);
                ymu836_set_fader(fader);
                break;
            case 'i':
                fix_eq = atoi(optarg);
                ymu836_set_eq_type(fix_eq);
                break;
            case 'e':
                eq_band = atoi(optarg);
                break;
            case 'u':
                mute = atoi(optarg);
                if(mute == 1)
                    ymu836_audio_mute(0);
                else
                    ymu836_audio_unmute(0);
                break;
            default:
                print_usage(argv[0]);
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    int ret = 0;

    fd = open(device, O_RDWR);
    if (fd < 0)
        pabort("can't open device");

    parse_opts(argc, argv);
    if(argc <= 1) {
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

        ymu836_audio_init(); 
    }

    close(fd);

    return ret;
}
