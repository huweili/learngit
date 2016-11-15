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

static int  volume;
static int8_t bass;
static int8_t middle;
static int8_t treble;
static int8_t balance;
static int8_t fader;
static uint8_t fix_eq;
static uint8_t eq_band;
static uint8_t mute;

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
            { "volume",  2, 0, 'v' },
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
                printf("1st = %x\r\n", atoi(optarg));
                /*printf("2nd = %x\r\n", atoi(argv[optind]));
                printf("3nd = %x\r\n", atoi(argv[optind + 1]));*/
                break;
            case 'b':
                bass = atoi(optarg);
                break;
            case 'm':
                middle = atoi(optarg);
                break;
            case 't':
                treble = atoi(optarg);
                break;
            case 'l':
                balance = atoi(optarg);
                break;
            case 'f':
                fader = atoi(optarg);
                break;
            case 'i':
                fix_eq = atoi(optarg);
                break;
            case 'e':
                eq_band = atoi(optarg);
                break;
            case 'u':
                mute = atoi(optarg);
                break;
            default:
                print_usage(argv[0]);
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    parse_opts(argc, argv);

    return 0;
}
