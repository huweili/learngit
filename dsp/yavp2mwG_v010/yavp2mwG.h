/****************************************************************************
 *
 *		Copyright(c) 2016 Yamaha Corporation. All rights reserved.
 *
 *		Module		: yavp2mwG.h
 *
 *		Description	: Yamaha AVP-2 middleware generic public definition.
 *
 *		Version		: 0.1.0		2016.04.28
 *
 ****************************************************************************/
#ifndef YAVP2MWG_H
#define YAVP2MWG_H

#include "../src/yad1driver.h"

#define	YAVP2mwG_CONTINUE			( 1)
#define	YAVP2mwG_SUCCESS			( 0)
#define	YAVP2mwG_ERROR				(-129)

/* for YAVP2mwG_set_param */
/* u32Func */
#define	YAVP2MWG_INITIALISE			(0x00)
#define	YAVP2MWG_FUNCTION_SELECT	(0x01)
#define	YAVP2MWG_BEEP_VOLUME		(0x02)
#define	YAVP2MWG_AUDIO_VOLUME		(0x10)
#define	YAVP2MWG_AUDIO_INPUT_VOLUME	(0x11)
#define	YAVP2MWG_AUDIO_BALANCE		(0x12)
#define	YAVP2MWG_AUDIO_FADER		(0x13)
#define	YAVP2MWG_AUDIO_GEQ1			(0x14)
#define	YAVP2MWG_AUDIO_GEQ2			(0x15)
#define	YAVP2MWG_AUDIO_TEST			(0x16)
#define	YAVP2MWG_MIC_RECEIVE_VOLUME	(0x20)
#define	YAVP2MWG_MIC_INPUT_VOLUME	(0x21)
#define	YAVP2MWG_TEST_VOLUME_F		(0x30)
#define	YAVP2MWG_TEST_VOLUME_R		(0x31)
#define	YAVP2MWG_TEST_SOURCE		(0x32)

/* Function select */
#define	YAVP2MWG_FUNCTION_AUDIO1	(0x00)
#define	YAVP2MWG_FUNCTION_AUDIO2	(0x01)
#define	YAVP2MWG_FUNCTION_AUDIO3	(0x02)
#define	YAVP2MWG_FUNCTION_AUDIO4	(0x03)
#define	YAVP2MWG_FUNCTION_AUDIO5	(0x04)
#define	YAVP2MWG_FUNCTION_AUDIO6	(0x05)
#define	YAVP2MWG_FUNCTION_AUDIO7	(0x06)
#define	YAVP2MWG_FUNCTION_AUDIO8	(0x07)
#define	YAVP2MWG_FUNCTION_MIC1		(0x10)
#define	YAVP2MWG_FUNCTION_MIC2		(0x11)
#define	YAVP2MWG_FUNCTION_MIC3		(0x12)
#define	YAVP2MWG_FUNCTION_MIC4		(0x13)
#define	YAVP2MWG_FUNCTION_MIC5		(0x14)
#define	YAVP2MWG_FUNCTION_MIC6		(0x15)
#define	YAVP2MWG_FUNCTION_MIC7		(0x16)
#define	YAVP2MWG_FUNCTION_MIC8		(0x17)
#define	YAVP2MWG_FUNCTION_TEST1		(0x20)
#define	YAVP2MWG_FUNCTION_TEST2		(0x21)
#define	YAVP2MWG_FUNCTION_TEST3		(0x22)
#define	YAVP2MWG_FUNCTION_TEST4		(0x23)
#define	YAVP2MWG_FUNCTION_TEST5		(0x24)

/* Test source */
#define	YAVP2MWG_TESTSOURCE_NONE	(0)
#define	YAVP2MWG_TESTSOURCE_SINE	(1)
#define	YAVP2MWG_TESTSOURCE_MIC12	(2)
#define	YAVP2MWG_TESTSOURCE_MIC3	(3)
#define	YAVP2MWG_TESTSOURCE_DIFI2	(4)

/* Mute/Unmute */
#define	YAVP2MWG_MUTE				(0)
#define	YAVP2MWG_UNMUTE				(1)

/* DIF format */
#define	YAVP2MWG_DIFFORMAT_I2S1		(0x00)		/* I2S, Master, 48kfs,   BCLK=64, 24bit */
#define	YAVP2MWG_DIFFORMAT_I2S2		(0x01)		/* I2S, Master, 48kfs,   BCLK=48, 24bit */
#define	YAVP2MWG_DIFFORMAT_I2S3		(0x02)		/* I2S, Master, 48kfs,   BCLK=32, 16bit */
#define	YAVP2MWG_DIFFORMAT_I2S4		(0x03)		/* I2S, Master, 44.1kfs, BCLK=64, 24bit */
#define	YAVP2MWG_DIFFORMAT_I2S5		(0x04)		/* I2S, Master, 44.1kfs, BCLK=48, 24bit */
#define	YAVP2MWG_DIFFORMAT_I2S6		(0x05)		/* I2S, Master, 44.1kfs, BCLK=32, 16bit */
#define	YAVP2MWG_DIFFORMAT_I2S7		(0x06)		/* I2S, Slave,  Auto fs, BCLK=64, 24bit */
#define	YAVP2MWG_DIFFORMAT_I2S8		(0x07)		/* I2S, Slave,  Auto fs, BCLK=48, 24bit */
#define	YAVP2MWG_DIFFORMAT_I2S9		(0x08)		/* I2S, Slave,  Auto fs, BCLK=32, 16bit */
#define	YAVP2MWG_DIFFORMAT_PCM1		(0x80)		/* PCM, Master, 16kfs,   BCLK=32, 16bit */
#define	YAVP2MWG_DIFFORMAT_PCM2		(0x81)		/* PCM, Master,  8kfs,   BCLK=32, 16bit */
#define	YAVP2MWG_DIFFORMAT_PCM3		(0x82)		/* PCM, Slave,  16kfs,   BCLK=32, 16bit */
#define	YAVP2MWG_DIFFORMAT_PCM4		(0x83)		/* PCM, Slave,   8kfs,   BCLK=32, 16bit */

#ifdef __cplusplus
extern "C" {
#endif

S32		YAVP2mwG_write_register	( U08 u08Page, U08 u08Adr, const U08 * pu08Data, U32 u32Size );
S32		YAVP2mwG_read_register	( U08 u08Page, U08 u08Adr, U08 * pu08Data, U32 u32Size );
S32		YAVP2mwG_batch_process	( const U08 * pu08BS, U32 u32Size );
S32		YAVP2mwG_set_param		( S32 s32Func, S32 s32Prm1, S32 s32Prm2 );

#ifdef __cplusplus
};
#endif

#endif /* YAVP2MWG_H */
