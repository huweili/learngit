/****************************************************************************
 *
 *		Copyright(c) 2016 Yamaha Corporation. All rights reserved.
 *
 *		Module		: yavp2mwG_d.h
 *
 *		Description	: Yamaha AVP-2 middleware generic private definition.
 *
 *		Version		: 0.1.1		2016.08.23
 *
 ****************************************************************************/
#ifndef YAVP2MWG_D_H
#define YAVP2MWG_D_H

#include "yavp2mwG_Init.h"
#include "yavp2mwG_Audio.h"
#include "yavp2mwG_Mic.h"
#include "yavp2mwG_Audio1.h"
#include "yavp2mwG_Mic1.h"


/* DIF format */
#define	YAVP2MW_DIFFORMAT_BSSIZE		( 22)

static const U08	au08DIFFormatI2S[9][ YAVP2MW_DIFFORMAT_BSSIZE ]= {
{								/* I2S, Master, 48kHz, 24bit, BCLK=64	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* I2S, Master, 48kHz, 24bit, BCLK=48	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* I2S, Master, 48kHz, 24bit, BCLK=48	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* I2S, Master, 44.1kHz, 24bit, BCLK=64	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* I2S, Master, 44.1kHz, 24bit, BCLK=48	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* I2S, Master, 44.1kHz, 24bit, BCLK=48	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* I2S, Slave, Auto fs, 24bit, BCLK=64	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x01, 
	0x04, 0x1a, 0x0f, 
},
{								/* I2S, Slave, Auto fs, 24bit, BCLK=48	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x01, 
	0x04, 0x1a, 0x0f, 
},
{								/* I2S, Slave, Auto fs, 16bit, BCLK=32	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x80, 0x80,
	0x02, 0x06, 0x01, 
	0x04, 0x1a, 0x0f, 
}};

static const U08	au08DIFFormatPCM[4][ YAVP2MW_DIFFORMAT_BSSIZE ]= {
{								/* PCM, Master, 16kHz, 16bit, BCLK=32	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x01, 0x26, 0x00, 0x02, 0x00, 0x00, 0x44, 0x00, 0x01, 0x01,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* PCM, Master, 8kHz, 16bit, BCLK=32	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x01, 0x2A, 0x00, 0x02, 0x00, 0x00, 0x44, 0x00, 0x01, 0x01,
	0x02, 0x06, 0x15, 
	0x04, 0x1a, 0x8f, 
},
{								/* PCM, Slave, 16kHz, 16bit, BCLK=32	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x01, 0x26, 0x00, 0x02, 0x00, 0x00, 0x44, 0x00, 0x01, 0x01,
	0x02, 0x06, 0x01, 
	0x04, 0x1a, 0x0f, 
},
{								/* PCM, Slave,  8kHz, 16bit, BCLK=32	*/
	0x04, 0x1a, 0x00, 
	0x84, 0x0B, 0x10, 
	0x01, 0x2A, 0x00, 0x02, 0x00, 0x00, 0x44, 0x00, 0x01, 0x01,
	0x02, 0x06, 0x01, 
	0x04, 0x1a, 0x0f, 
}};

/* Initialize/Function select */
static const U08	au08InitE_Audio[]= {
	0x05, 0x40, 0x1B, 
};

static const U08	au08InitE_Mic[]= {
	0x05, 0x40, 0x24, 
};

static const U08	au08InitE_Test[]= {
	0x05, 0x40, 0x90, 
};

/* Beep volume */
#define	YAVP2MWG_BEEP_VOL_MAX			(  0)
#define	YAVP2MWG_BEEP_VOL_MIN			(-96)
#define	YAVP2MW_BEEPVOL_BS_ANALOG		(  2)
#define	YAVP2MW_BEEPVOL_BS_DIGITAL		(  5)

static const U08	au08BeppVolume[]= {
	0x03, 0x10, 0x00, 
	0x03, 0x06, 0x00, 
};

/* Audio volume */
#define	YAVP2MWG_AUDIO_VOL_MAX				(  0)
#define	YAVP2MWG_AUDIO_VOL_MIN				(-16384)

#define	YAVP2MWG_REGADR_FDR4BA_OFFSET		(0x56)
#define	YAVP2MWG_REGADR_FDR4BA_VOLUME		(0x57)
#define	YAVP2MWG_REGADR_FDR4BA_BALANCE_L	(0x58)
#define	YAVP2MWG_REGADR_FDR4BA_BALANCE_R	(0x59)
#define	YAVP2MWG_REGADR_FDR4BA_FADER_F		(0x5A)
#define	YAVP2MWG_REGADR_FDR4BA_FADER_R		(0x5B)
#define	YAVP2MWG_REGADR_FDR4BA_MUTE			(0x5C)

#define	YAVP2MWG_REGVAL_FDR4B_MUTE			(0x80)
#define	YAVP2MWG_REGVAL_FDR4B_START			(0x01)

#define	YAVP2MW_AUDIOFDR4B_BS_MUTE1			(  2)
#define	YAVP2MW_AUDIOFDR4B_BS_REGSTER		(  5)
#define	YAVP2MW_AUDIOFDR4B_BS_VOLUME1		(  6)
#define	YAVP2MW_AUDIOFDR4B_BS_VOLUME2		(  7)
#define	YAVP2MW_AUDIOFDR4B_BS_MUTE2			( 10)

static const U08	au08AudioFDR4B[]= {
	0x08, YAVP2MWG_REGADR_FDR4BA_MUTE, 0x00,										/* MUTE, START */
	0x88, 0x03, 0x00, 
				0x00, 
				0x00, 
	0x08, YAVP2MWG_REGADR_FDR4BA_MUTE, 0x01,										/* MUTE, START */
};

/* Audio input volume */
#define	YAVP2MWG_AIN_VOL_MAX			(  0)
#define	YAVP2MWG_AIN_VOL_MIN			(-96)

#define	YAVP2MW_AINVOL_BS_ADIVOL		(  2)
#define	YAVP2MW_AINVOL_BS_DIFIVOL		(  5)
#define	YAVP2MW_AINVOL_BS_OPERATOR		( 11)
#define	YAVP2MW_AINVOL_BS_OPERAND		( 12)

static const U08	au08AudioInputVolume[]= {
	0x03, 0x0E, 0x00, 
	0x03, 0x08, 0x00, 
	0x65, 0x40, 0x00, 
	0x6f, 0x00, 0x04, 0x10, 
	0x75, 0x00, 0x40, 
};


/* GEQ */
#define	YAVP2MWG_AUDIOGEQ_GAIN_MAX		( 12)
#define	YAVP2MWG_AUDIOGEQ_GAIN_MIN		(-12)

#define	YAVP2MWG_COEFADRS_SICC1PAGE0_1	(0x00)
#define	YAVP2MWG_COEFADRS_SICC1PAGE0_2	(0x03)
#define	YAVP2MWG_COEFADRS_SICC1PAGE0_3	(0x44)	/* SICC1 AppBase0 +  4 */
#define	YAVP2MWG_COEFADRS_SICC1PAGE1_1	(0x00)
#define	YAVP2MWG_COEFADRS_SICC1PAGE1_2	(0x03)
#define	YAVP2MWG_COEFADRS_SICC1PAGE1_3	(0x53)	/* SICC1 AppBase0 + 19 */

#define	YAVP2MWG_COEFADRS_SICC2PAGE0_1	(0x00)
#define	YAVP2MWG_COEFADRS_SICC2PAGE0_2	(0x03)
#define	YAVP2MWG_COEFADRS_SICC2PAGE0_3	(0x80)	/* SICC2 AppBase0 +  4 */
#define	YAVP2MWG_COEFADRS_SICC2PAGE1_1	(0x00)
#define	YAVP2MWG_COEFADRS_SICC2PAGE1_2	(0x03)
#define	YAVP2MWG_COEFADRS_SICC2PAGE1_3	(0x8F)	/* SICC2 AppBase0 + 19 */

#define	YAVP2MWG_COEFVAL_SICC1BAND1_FC	0x05, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC1BAND1_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC1BAND2_FC	0x06, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC1BAND2_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC1BAND3_FC	0x07, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC1BAND3_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC1BAND4_FC	0x08, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC1BAND4_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC1BAND5_FC	0x09, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC1BAND5_Q	0x01, 0x59, 0xAA, 0xAA

#define	YAVP2MWG_COEFVAL_SICC2BAND6_FC	0x0A, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC2BAND6_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC2BAND7_FC	0x0B, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC2BAND7_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC2BAND8_FC	0x0C, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC2BAND8_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC2BAND9_FC	0x0D, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC2BAND9_Q	0x01, 0x59, 0xAA, 0xAA
#define	YAVP2MWG_COEFVAL_SICC2BAND10_FC	0x0E, 0x7D, 0x00, 0x00
#define	YAVP2MWG_COEFVAL_SICC2BAND10_Q	0x01, 0x59, 0xAA, 0xAA

#define	YAVP2MWG_REGADR_SICC1_PAGE		(0x52)
#define	YAVP2MWG_REGADR_SICC2_PAGE		(0x54)

#define	YAVP2MW_AUDIOSICC_BS_BAND1GAIN	(15)
#define	YAVP2MW_AUDIOSICC_BS_GAINOFFSET	(12)

static const U08	au08AudioGEQ1[2][78]= {
{
	0x01, 0x32, YAVP2MWG_COEFADRS_SICC1PAGE0_1,						/* coef address */
	0x01, 0x33, YAVP2MWG_COEFADRS_SICC1PAGE0_2,
	0x01, 0x34, YAVP2MWG_COEFADRS_SICC1PAGE0_3,
	0x01, 0x35, 0x00,
	0x81, 0x3D, 0x36,
	0x80, 0x00, 0x00, 0x00,						/* band#1 gain */
	YAVP2MWG_COEFVAL_SICC1BAND1_FC,				/* band#1 fc */
	YAVP2MWG_COEFVAL_SICC1BAND1_Q,				/* band#1 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#2 gain */
	YAVP2MWG_COEFVAL_SICC1BAND2_FC,				/* band#2 fc */
	YAVP2MWG_COEFVAL_SICC1BAND2_Q,				/* band#2 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#3 gain */
	YAVP2MWG_COEFVAL_SICC1BAND3_FC,				/* band#3 fc */
	YAVP2MWG_COEFVAL_SICC1BAND3_Q,				/* band#3 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#4 gain */
	YAVP2MWG_COEFVAL_SICC1BAND4_FC,				/* band#4 fc */
	YAVP2MWG_COEFVAL_SICC1BAND4_Q,				/* band#4 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#5 gain */
	YAVP2MWG_COEFVAL_SICC1BAND5_FC,				/* band#5 fc */
	YAVP2MWG_COEFVAL_SICC1BAND5_Q,				/* band#5 Q */
	0x08, YAVP2MWG_REGADR_SICC1_PAGE, 0x00							/* page */
}, {
	0x01, 0x32, YAVP2MWG_COEFADRS_SICC1PAGE1_1,						/* coef address */
	0x01, 0x33, YAVP2MWG_COEFADRS_SICC1PAGE1_2,
	0x01, 0x34, YAVP2MWG_COEFADRS_SICC1PAGE1_3,
	0x01, 0x35, 0x00,
	0x81, 0x3D, 0x36,
	0x80, 0x00, 0x00, 0x00,						/* band#1 gain */
	YAVP2MWG_COEFVAL_SICC1BAND1_FC,				/* band#1 fc */
	YAVP2MWG_COEFVAL_SICC1BAND1_Q,				/* band#1 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#2 gain */
	YAVP2MWG_COEFVAL_SICC1BAND2_FC,				/* band#2 fc */
	YAVP2MWG_COEFVAL_SICC1BAND2_Q,				/* band#2 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#3 gain */
	YAVP2MWG_COEFVAL_SICC1BAND3_FC,				/* band#3 fc */
	YAVP2MWG_COEFVAL_SICC1BAND3_Q,				/* band#3 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#4 gain */
	YAVP2MWG_COEFVAL_SICC1BAND4_FC,				/* band#4 fc */
	YAVP2MWG_COEFVAL_SICC1BAND4_Q,				/* band#4 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#5 gain */
	YAVP2MWG_COEFVAL_SICC1BAND5_FC,				/* band#5 fc */
	YAVP2MWG_COEFVAL_SICC1BAND5_Q,				/* band#5 Q */
	0x08, YAVP2MWG_REGADR_SICC1_PAGE, 0x02							/* page */
} };

static const U08	au08AudioGEQ2[2][78]= {
{
	0x01, 0x32, YAVP2MWG_COEFADRS_SICC2PAGE0_1,						/* coef address */
	0x01, 0x33, YAVP2MWG_COEFADRS_SICC2PAGE0_2,
	0x01, 0x34, YAVP2MWG_COEFADRS_SICC2PAGE0_3,
	0x01, 0x35, 0x00,
	0x81, 0x3D, 0x36,
	0x80, 0x00, 0x00, 0x00,						/* band#6 gain */
	YAVP2MWG_COEFVAL_SICC2BAND6_FC,				/* band#6 fc */
	YAVP2MWG_COEFVAL_SICC2BAND6_Q,				/* band#6 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#7 gain */
	YAVP2MWG_COEFVAL_SICC2BAND7_FC,				/* band#7 fc */
	YAVP2MWG_COEFVAL_SICC2BAND7_Q,				/* band#7 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#8 gain */
	YAVP2MWG_COEFVAL_SICC2BAND8_FC,				/* band#8 fc */
	YAVP2MWG_COEFVAL_SICC2BAND8_Q,				/* band#8 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#9 gain */
	YAVP2MWG_COEFVAL_SICC2BAND9_FC,				/* band#9 fc */
	YAVP2MWG_COEFVAL_SICC2BAND9_Q,				/* band#9 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#10 gain */
	YAVP2MWG_COEFVAL_SICC2BAND10_FC,			/* band#10 fc */
	YAVP2MWG_COEFVAL_SICC2BAND10_Q,				/* band#10 Q */
	0x08, YAVP2MWG_REGADR_SICC2_PAGE, 0x00							/* page */
}, {
	0x01, 0x32, YAVP2MWG_COEFADRS_SICC2PAGE1_1,						/* coef address */
	0x01, 0x33, YAVP2MWG_COEFADRS_SICC2PAGE1_2,
	0x01, 0x34, YAVP2MWG_COEFADRS_SICC2PAGE1_3,
	0x01, 0x35, 0x00,
	0x81, 0x3D, 0x36,
	0x80, 0x00, 0x00, 0x00,						/* band#6 gain */
	YAVP2MWG_COEFVAL_SICC2BAND6_FC,				/* band#6 fc */
	YAVP2MWG_COEFVAL_SICC2BAND6_Q,				/* band#6 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#7 gain */
	YAVP2MWG_COEFVAL_SICC2BAND7_FC,				/* band#7 fc */
	YAVP2MWG_COEFVAL_SICC2BAND7_Q,				/* band#7 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#8 gain */
	YAVP2MWG_COEFVAL_SICC2BAND8_FC,				/* band#8 fc */
	YAVP2MWG_COEFVAL_SICC2BAND8_Q,				/* band#8 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#9 gain */
	YAVP2MWG_COEFVAL_SICC2BAND9_FC,				/* band#9 fc */
	YAVP2MWG_COEFVAL_SICC2BAND9_Q,				/* band#9 Q */
	0x80, 0x00, 0x00, 0x00,						/* band#10 gain */
	YAVP2MWG_COEFVAL_SICC2BAND10_FC,			/* band#10 fc */
	YAVP2MWG_COEFVAL_SICC2BAND10_Q,				/* band#10 Q */
	0x08, YAVP2MWG_REGADR_SICC2_PAGE, 0x02							/* page */
} };

static const U08	au08GEQGain[25][4]={
	{	0x04, 0xA0, 0x00, 0x00	},			/* -12[dB] */
	{	0x04, 0xA8, 0x00, 0x00	},			/* -11[dB] */
	{	0x04, 0xB0, 0x00, 0x00	},			/* -10[dB] */
	{	0x04, 0xB8, 0x00, 0x00	},			/*  -9[dB] */
	{	0x03, 0x80, 0x00, 0x00	},			/*  -8[dB] */
	{	0x03, 0x90, 0x00, 0x00	},			/*  -7[dB] */
	{	0x03, 0xA0, 0x00, 0x00	},			/*  -6[dB] */
	{	0x03, 0xB0, 0x00, 0x00	},			/*  -5[dB] */
	{	0x02, 0x80, 0x00, 0x00	},			/*  -4[dB] */
	{	0x02, 0xA0, 0x00, 0x00	},			/*  -3[dB] */
	{	0x01, 0x80, 0x00, 0x00	},			/*  -2[dB] */
	{	0x00, 0x80, 0x00, 0x00	},			/*  -1[dB] */
	{	0x80, 0x00, 0x00, 0x00	},			/*   0[dB] */
	{	0x01, 0x40, 0x00, 0x00	},			/*   1[dB] */
	{	0x02, 0x40, 0x00, 0x00	},			/*   2[dB] */
	{	0x02, 0x60, 0x00, 0x00	},			/*   3[dB] */
	{	0x03, 0x40, 0x00, 0x00	},			/*   4[dB] */
	{	0x03, 0x50, 0x00, 0x00	},			/*   5[dB] */
	{	0x03, 0x60, 0x00, 0x00	},			/*   6[dB] */
	{	0x03, 0x70, 0x00, 0x00	},			/*   7[dB] */
	{	0x04, 0x40, 0x00, 0x00	},			/*   8[dB] */
	{	0x04, 0x48, 0x00, 0x00	},			/*   9[dB] */
	{	0x04, 0x50, 0x00, 0x00	},			/*  10[dB] */
	{	0x04, 0x58, 0x00, 0x00	},			/*  11[dB] */
	{	0x04, 0x60, 0x00, 0x00	}			/*  12[dB] */
};

/* Audio parameter */
#define	YAVP2MWG_REGADR_FDSPSTART		(0x20)


static const U08	au08AudioCoefA[]={
	0x08, YAVP2MWG_REGADR_FDR4BA_MUTE, 0x81, 
	0x1f, 0x3c,								/* wait 60msec */
};

static const U08	au08AudioCoefB[]={
	0x04, 0x1A, 0x00, 
	0x02, 0x06, 0x2b, 
	0x03, 0x0e, 0x00, 
	0x03, 0x08, 0x00, 
	0x08, YAVP2MWG_REGADR_FDSPSTART, 0x00, 
	0x1f, 0x14,								/* wait 20msec */
};

#define	YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET	( 5)

static const U08	au08AudioFDR4B_ALL[]= {
	0x08, YAVP2MWG_REGADR_FDR4BA_MUTE, 0x81,
	0x88, 0x08, YAVP2MWG_REGADR_FDR4BA_OFFSET, 
		0x00, 								/* offset */
		0x00, 								/* volume */
		0x00, 								/* balance l */
		0x00, 								/* balance r */
		0x00, 								/* fader f */
		0x00, 								/* fader r */
		0x01, 								/* mute/start */
};


#define	YAVP2MW_FDSPSTART_BS_FSTART			( 2)

static const U08	au08FDSP_Start[]={
	0x08, YAVP2MWG_REGADR_FDSPSTART, 0x01, 
	0x1f, 0x14, 								/* wait 20msec */
};

/* Audio test */
#define	YAVP2MWG_REGADR_FAPPEXEC		(0x41)
#define	YAVP2MWG_REGADR_BAPPEXEC		(0x40)

#define	YAVP2MW_AUDIOSICC_BS_FAPPEXEC	( 3)
#define	YAVP2MW_AUDIOSICC_BS_BAPPEXEC	( 8)

static const U08	au08AudioTest[]= {
	0x88, 0x04, YAVP2MWG_REGADR_FAPPEXEC,
	0xff, 0xff, 0xff,
	0x05, YAVP2MWG_REGADR_BAPPEXEC, 0x1b,
};

static const U08	au08MicTest[]= {
	0x88, 0x04, YAVP2MWG_REGADR_FAPPEXEC,
	0xff, 0xff, 0xff,
	0x05, YAVP2MWG_REGADR_BAPPEXEC, 0x34,
};

static const U08	au08TestTest[]= {
	0x88, 0x04, YAVP2MWG_REGADR_FAPPEXEC,
	0xff, 0xff, 0xff,
	0x05, YAVP2MWG_REGADR_BAPPEXEC, 0x90,
};


/* function select */
#define	YAVP2MWG_REGADR_FDR4BM_OFFSET		(0x63)
#define	YAVP2MWG_REGADR_FDR4BM_VOLUME		(0x64)
#define	YAVP2MWG_REGADR_FDR4BM_BALANCE_L	(0x65)
#define	YAVP2MWG_REGADR_FDR4BM_BALANCE_R	(0x66)
#define	YAVP2MWG_REGADR_FDR4BM_FADER_F		(0x67)
#define	YAVP2MWG_REGADR_FDR4BM_FADER_R		(0x68)
#define	YAVP2MWG_REGADR_FDR4BM_MUTE			(0x69)

static const U08	au08FuncSelA[]={
	0x08, YAVP2MWG_REGADR_FDR4BA_MUTE, 0x81, 
	0x08, YAVP2MWG_REGADR_FDR4BM_MUTE, 0x81, 
	0x05, 0x45, 0x00, 
	0x1f, 0x3c,									/* wait 60msec */
};

static const U08	au08FuncSelB[]={
	0x03, 0x0e, 0x00, 
	0x03, 0x12, 0x00, 
	0x03, 0x08, 0x00, 
	0x03, 0x16, 0x00, 
	0x08, YAVP2MWG_REGADR_FDSPSTART, 0x00, 
	0x1f, 0x14,									/* wait 20msec */
};

#define	YAVP2MW_FUNCSELC_BS_DAC0VOLUME	(19)
#define	YAVP2MW_FUNCSELC_BS_DAC1VOLUME	(24)
#define	YAVP2MW_FUNCSELC_BS_ADIF0SEL	(28)
#define	YAVP2MW_FUNCSELC_BS_REFBACK		(39)
#define	YAVP2MW_FUNCSELC_BS_AE0MIX		(45)

static const U08	au08FuncSelC[]={
	0x03, 0x1A, 0x00, 
	0x02, 0x06, 0x2B, 
	0x83, 0x03, 0x3B, 0x01, 0x01, 
	0x83, 0x03, 0x3F, 0x00, 0x00, 
	0x83, 0x03, 0x1C, 0x60, 0x60, 				/* DAC#0 volume */
	0x83, 0x03, 0x1E, 0x60, 0x60, 				/* DAC#1 volume */
	0x07, 0x2A, 0x10, 							/* ADIF#0 selector */
	0x67, 0x2D, 0x00, 
	0x6f, 0x00, 0x05, 0xFB, 
	0x6f, 0x00, 0x04, 0x00, 					/* REFBACK */
	0x77, 0x00, 0x2D, 
	0x03, 0x23, 0x12, 							/* AE0 Mixer */
};

#define	YAVP2MW_FUNCSELD_BS_DAC0MIX		( 3)
#define	YAVP2MW_FUNCSELD_BS_DAC1MIX		( 8)
#define	YAVP2MW_FUNCSELD_BS_DIFO1VOL	(12)
#define	YAVP2MW_FUNCSELD_BS_FDR4BA		(15)
#define	YAVP2MW_FUNCSELD_BS_FDR4BM		(18)
#define	YAVP2MW_FUNCSELD_BS_SINESTART	(21)
#define	YAVP2MW_FUNCSELD_BS_ADIF0VOL	(24)
#define	YAVP2MW_FUNCSELD_BS_ADIF2VOL	(27)
#define	YAVP2MW_FUNCSELD_BS_DIFI1VOL	(30)

static const U08	au08FuncSelD[]={
	0x83, 0x03, 0x3B, 0x03, 0x01, 				/* DAC#0 Mixer */
	0x83, 0x03, 0x3F, 0x04, 0x00, 				/* DAC#1 Mixer */
	0x03, 0x16, 0x00, 							/* DIFO#1 volume */
	0x08, YAVP2MWG_REGADR_FDR4BA_MUTE, 0x01, 	/* FDR4B Audio */
	0x08, YAVP2MWG_REGADR_FDR4BM_MUTE, 0x81, 	/* FDR4B Mic */
	0x05, 0x45, 0x00, 							/* sine start */
	0x03, 0x0e, 0x00, 							/* ADIF#0 volume */
	0x03, 0x12, 0x00, 							/* ADIF#2 volume */
	0x03, 0x08, 0x00, 							/* DIFI#1 volume */
};

/* mic volume */
#define	YAVP2MWG_MIC_VOL_MAX			(  0)
#define	YAVP2MWG_MIC_VOL_MIN			(-96)

#define	YAVP2MW_MICINPUTVOL_BS_DIF1VOL	( 2)

static const U08	au08MicReceiveVol[]={
	0x03, 0x08, 0x00, 
};

#define	YAVP2MW_MICINPUTVOL_BS_ADI0VOL	( 2)
#define	YAVP2MW_MICINPUTVOL_BS_ADI2VOL	( 5)

static const U08	au08MicInputVol[]={
	0x03, 0x0e, 0x00, 
	0x03, 0x12, 0x00, 
};


/* test volume */
#define	YAVP2MW_TESTVOL_BS_REGADRS		( 2)
#define	YAVP2MW_TESTVOL_BS_VOLUME_L		( 3)
#define	YAVP2MW_TESTVOL_BS_VOLUME_R		( 4)

#define	YAVP2MWG_REGADR_DAC0VOLUME		(0x1C)
#define	YAVP2MWG_REGADR_DAC1VOLUME		(0x1E)

#define	YAVP2MWG_TEST_VOL_MAX			(  0)
#define	YAVP2MWG_TEST_VOL_MIN			(-96)

static const U08	au08TestVolume[]={
	0x83, 0x03, YAVP2MWG_REGADR_DAC0VOLUME, 
	0x00, 0x00, 
};

/* test source */
#define	YAVP2MW_TESTSOURCE_BS_SINESTART	( 2)
#define	YAVP2MW_TESTSOURCE_BS_ADIF0VOL	( 5)
#define	YAVP2MW_TESTSOURCE_BS_ADIF2VOL	( 8)
#define	YAVP2MW_TESTSOURCE_BS_DIFI1VOL	(11)

static const U08	au08TestSource[]={
	0x05, 0x45, 0x00, 							/* sine start */
	0x03, 0x0e, 0x00, 							/* ADIF#0 volume */
	0x03, 0x12, 0x00, 							/* ADIF#2 volume */
	0x03, 0x08, 0x00, 							/* DIFI#1 volume */
};


/* nop script */
static const U08	au08Nop[]= {
	0x6f, 0x00, 0x00, 0x00,
};

#endif /* YAVP2MWG_D_H */
