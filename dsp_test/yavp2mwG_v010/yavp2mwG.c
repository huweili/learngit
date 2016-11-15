/****************************************************************************
 *
 *		Copyright(c) 2016 Yamaha Corporation. All rights reserved.
 *
 *		Module		: yavp2mwG.h
 *
 *		Description	: Yamaha AVP-2 middleware generic module.
 *
 *		Version		: 0.1.1		2016.08.23
 *
 ****************************************************************************/
#include "yavp2mwG.h"
#include "yavp2mwG_d.h"

#define	YAVP2MWG_BSBUF_SIZE			(256)
#define	YAVP2MWG_MAX_SET			(8)


typedef struct YAVP2MWG_VOLUME {
	S08					s08Mute;
	S32					s32Volume;
} YAVP2MWG_VOLUME;

typedef struct YAVP2MWG_SCRIPT {
	const U08 *			pu08Script;
	U32					u32Size;
} YAVP2MWG_SCRIPT;

typedef struct YAVP2M4D_AUDIO_SETTING {
	YAVP2MWG_VOLUME		sVolume;
	YAVP2MWG_SCRIPT		sScript[ YAVP2MWG_MAX_SET ];
	S08					s08Analog;
	S08					s08Digital;
	S08					s08BalL;
	S08					s08BalR;
	S08					s08FadeF;
	S08					s08FadeR;
	S08					as08GEQ1[5];
	S08					as08GEQ2[5];
	S08					s08Param;

	U08					u08SICC1;
	U08					u08SICC2;
} YAVP2MWG_AUDIO;

typedef struct YAVP2MWG_MIC {
	YAVP2MWG_VOLUME		sReceive;
	YAVP2MWG_SCRIPT		sScript[ YAVP2MWG_MAX_SET ];
	S08					s08Param;
	S08					s08ADIF0;
	S08					s08ADIF2;
} YAVP2MWG_MIC;

typedef struct YAVP2MWG_TEST {
	S08					s08FLVolume;
	S08					s08FRVolume;
	S08					s08RLVolume;
	S08					s08RRVolume;
	S08					s08Source;
} YAVP2MWG_TEST;

typedef struct YAVP2M4D_INFO {
	S32					s32Temp1;
	S32					s32Temp2;
	S32					s32Func;

	U08					au08BS[ YAVP2MWG_BSBUF_SIZE ];

	YAVP2MWG_AUDIO		sAudio;
	YAVP2MWG_MIC		sMic;
	YAVP2MWG_TEST		sTest;
}YAVP2MWG_INFO;

static YAVP2MWG_INFO	gsInfo;

/* private functions */
/*******************************************************************************
 *	yavp2mwg_funcsel_registerA
 ******************************************************************************/
static	U08 *	yavp2mwg_funcsel_registerA
(
	U32 *		pu32Size
)
{
	U08 *		pu08BS;
	U32			u32Size, i;

	*pu32Size	= 0;
	pu08BS		= gsInfo.au08BS;

	u32Size		= sizeof( au08FuncSelC );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08FuncSelC[ i ];
	}

	switch ( gsInfo.s32Func )
	{
	case YAVP2MWG_FUNCTION_AUDIO1 :
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC0VOLUME + 0 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC0VOLUME + 1 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC1VOLUME + 0 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC1VOLUME + 1 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_ADIF0SEL ]		= 0x10;
		pu08BS[ YAVP2MW_FUNCSELC_BS_REFBACK ]		= 0x01;
		pu08BS[ YAVP2MW_FUNCSELC_BS_AE0MIX ]		= 0x12;
		break;

	case YAVP2MWG_FUNCTION_MIC1 :
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC0VOLUME + 0 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC0VOLUME + 1 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC1VOLUME + 0 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC1VOLUME + 1 ]= 0x60;
		pu08BS[ YAVP2MW_FUNCSELC_BS_ADIF0SEL ]		= 0x22;
		pu08BS[ YAVP2MW_FUNCSELC_BS_REFBACK ]		= 0x05;
		pu08BS[ YAVP2MW_FUNCSELC_BS_AE0MIX ]		= 0x02;
		break;

	case YAVP2MWG_FUNCTION_TEST1 :
	default :
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC0VOLUME + 0 ]= gsInfo.sTest.s08FLVolume + 96;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC0VOLUME + 1 ]= gsInfo.sTest.s08FRVolume + 96;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC1VOLUME + 0 ]= gsInfo.sTest.s08RLVolume + 96;
		pu08BS[ YAVP2MW_FUNCSELC_BS_DAC1VOLUME + 1 ]= gsInfo.sTest.s08RRVolume + 96;
		pu08BS[ YAVP2MW_FUNCSELC_BS_ADIF0SEL ]		= 0x10;
		pu08BS[ YAVP2MW_FUNCSELC_BS_REFBACK ]		= 0x01;
		pu08BS[ YAVP2MW_FUNCSELC_BS_AE0MIX ]		= 0x52;
		break;
	}
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;


	return gsInfo.au08BS;
}

/*******************************************************************************
 *	yavp2mwg_funcsel_registerB
 ******************************************************************************/
static	U08 *	yavp2mwg_funcsel_registerB
(
	U32 *		pu32Size
)
{
	U08 *		pu08BS;
	S08			s08Mute, s08Receive;
	U32			u32Size, i;

	*pu32Size	= 0;
	pu08BS		= gsInfo.au08BS;
	s08Mute		= 0;
	s08Receive	=(S08)( gsInfo.sMic.sReceive.s32Volume + 96 );
	if ( gsInfo.sAudio.sVolume.s08Mute	== YAVP2MWG_MUTE )
	{
		s08Mute		= YAVP2MWG_REGVAL_FDR4B_MUTE;
	}
	if ( gsInfo.sMic.sReceive.s08Mute	== YAVP2MWG_MUTE )
	{
		s08Receive	= 0;
	}

	u32Size		= sizeof( au08FuncSelD );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08FuncSelD[ i ];
	}

	switch ( gsInfo.s32Func )
	{
	case YAVP2MWG_FUNCTION_AUDIO1 :
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC0MIX + 0 ]	= 0x03;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC0MIX + 1 ]	= 0x01;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC1MIX + 0 ]	= 0x04;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC1MIX + 1 ]	= 0x00;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DIFO1VOL ]		= 0x00;
		pu08BS[ YAVP2MW_FUNCSELD_BS_FDR4BA ]		=(U08)( s08Mute | YAVP2MWG_REGVAL_FDR4B_START );
		pu08BS[ YAVP2MW_FUNCSELD_BS_FDR4BM ]		= 0x81;
		pu08BS[ YAVP2MW_FUNCSELD_BS_SINESTART ]		= 0x00;
		pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF0VOL ]		= gsInfo.sAudio.s08Analog + 96;
		pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF2VOL ]		= 0x00;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DIFI1VOL ]		= gsInfo.sAudio.s08Digital + 96;
		break;

	case YAVP2MWG_FUNCTION_MIC1 :
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC0MIX + 0 ]	= 0x01;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC0MIX + 1 ]	= 0x81;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC1MIX + 0 ]	= 0x00;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC1MIX + 1 ]	= 0x00;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DIFO1VOL ]		= 0x60;
		pu08BS[ YAVP2MW_FUNCSELD_BS_FDR4BA ]		= 0x81;
		pu08BS[ YAVP2MW_FUNCSELD_BS_FDR4BM ]		= 0x01;
		pu08BS[ YAVP2MW_FUNCSELD_BS_SINESTART ]		= 0x00;
		pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF0VOL ]		= gsInfo.sMic.s08ADIF0 + 96;
		pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF2VOL ]		= gsInfo.sMic.s08ADIF2 + 96;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DIFI1VOL ]		= s08Receive;
		break;

	case YAVP2MWG_FUNCTION_TEST1 :
	default :
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC0MIX + 0 ]	= 0x01;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC0MIX + 1 ]	= 0x81;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC1MIX + 0 ]	= 0x01;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DAC1MIX + 1 ]	= 0x81;
		pu08BS[ YAVP2MW_FUNCSELD_BS_DIFO1VOL ]		= 0x60;
		pu08BS[ YAVP2MW_FUNCSELD_BS_FDR4BA ]		= 0x81;
		pu08BS[ YAVP2MW_FUNCSELD_BS_FDR4BM ]		= 0x01;
		switch ( gsInfo.sTest.s08Source )
		{
		case YAVP2MWG_TESTSOURCE_NONE :
			pu08BS[ YAVP2MW_FUNCSELD_BS_SINESTART ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF0VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF2VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_DIFI1VOL ]	= 0x00;
			break;
		case YAVP2MWG_TESTSOURCE_SINE :
			pu08BS[ YAVP2MW_FUNCSELD_BS_SINESTART ]	= 0x01;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF0VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF2VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_DIFI1VOL ]	= 0x00;
			break;
		case YAVP2MWG_TESTSOURCE_MIC12 :
			pu08BS[ YAVP2MW_FUNCSELD_BS_SINESTART ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF0VOL ]	= 0x60;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF2VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_DIFI1VOL ]	= 0x00;
			break;
		case YAVP2MWG_TESTSOURCE_MIC3 :
			pu08BS[ YAVP2MW_FUNCSELD_BS_SINESTART ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF0VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF2VOL ]	= 0x60;
			pu08BS[ YAVP2MW_FUNCSELD_BS_DIFI1VOL ]	= 0x00;
			break;
		case YAVP2MWG_TESTSOURCE_DIFI2 :
		default :
			pu08BS[ YAVP2MW_FUNCSELD_BS_SINESTART ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF0VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_ADIF2VOL ]	= 0x00;
			pu08BS[ YAVP2MW_FUNCSELD_BS_DIFI1VOL ]	= 0x60;
			break;
		}
		break;
	}
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;


	return gsInfo.au08BS;
}

/*******************************************************************************
 *	yavp2mwg_audio_register
 ******************************************************************************/
static	U08 *	yavp2mwg_audio_register
(
	U32 *		pu32Size
)
{
	U08 *		pu08BS;
	S08			s08Offset, s08Volume, s08Mute;
	U32			u32Size, i, j;

	gsInfo.sAudio.u08SICC1	= 1;
	gsInfo.sAudio.u08SICC2	= 1;

	*pu32Size	= 0;
	pu08BS		= gsInfo.au08BS;
	s08Volume	=(S08)( gsInfo.sAudio.sVolume.s32Volume >> 7 );
	s08Offset	=(S08)( gsInfo.sAudio.sVolume.s32Volume & 0x7F );
	s08Mute		= 0x00;
	if ( gsInfo.sAudio.sVolume.s32Volume	< 0 )
	{
		s08Offset	*= -1;
	}
	if ( gsInfo.sAudio.sVolume.s08Mute	== YAVP2MWG_MUTE )
	{
		s08Mute	= YAVP2MWG_REGVAL_FDR4B_MUTE;
	}

	u32Size	= sizeof( au08AudioFDR4B_ALL );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioFDR4B_ALL[ i ];
	}
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 0 ]	= YAVP2MWG_REGADR_FDR4BA_OFFSET;
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 1 ]	= s08Offset;
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 2 ]	= s08Volume;
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 3 ]	= gsInfo.sAudio.s08BalL;
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 4 ]	= gsInfo.sAudio.s08BalR;
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 5 ]	= gsInfo.sAudio.s08FadeF;
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 6 ]	= gsInfo.sAudio.s08FadeR;
	pu08BS[ YAVP2MW_AUDIOFDR4B_ALL_BS_OFFSET + 7 ]	=(U08)( s08Mute | YAVP2MWG_REGVAL_FDR4B_START );
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;

	u32Size		= 78;
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioGEQ1[ 0 ][ i ];
	}
	pu08BS	+= YAVP2MW_AUDIOSICC_BS_BAND1GAIN;
	for ( i = 0; i < 5; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			pu08BS[ j ]= au08GEQGain[ gsInfo.sAudio.as08GEQ1[ i ]+ 12 ][ j ];
		}
		pu08BS	+= YAVP2MW_AUDIOSICC_BS_GAINOFFSET;
	}
	*pu32Size	+= u32Size;
	pu08BS		+= 3;

	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioGEQ2[ 0 ][ i ];
	}
	pu08BS	+= YAVP2MW_AUDIOSICC_BS_BAND1GAIN;
	for ( i = 0; i < 5; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			pu08BS[ j ]= au08GEQGain[ gsInfo.sAudio.as08GEQ2[ i ]+ 12 ][ j ];
		}
		pu08BS	+= YAVP2MW_AUDIOSICC_BS_GAINOFFSET;
	}
	*pu32Size	+= u32Size;
	pu08BS		+= 3;

	u32Size		= sizeof( au08AudioTest );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioTest[ i ];
	}
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;

	switch ( gsInfo.s32Temp2 )
	{
	case YAVP2MWG_DIFFORMAT_I2S1 :
	case YAVP2MWG_DIFFORMAT_I2S2 :
	case YAVP2MWG_DIFFORMAT_I2S3 :
	case YAVP2MWG_DIFFORMAT_I2S4 :
	case YAVP2MWG_DIFFORMAT_I2S5 :
	case YAVP2MWG_DIFFORMAT_I2S6 :
	case YAVP2MWG_DIFFORMAT_I2S7 :
	case YAVP2MWG_DIFFORMAT_I2S8 :
	case YAVP2MWG_DIFFORMAT_I2S9 :
		u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
		for ( i = 0; i < u32Size; i++ )
		{
			pu08BS[ i ]= au08DIFFormatI2S[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_I2S1 ][ i ];
		}
		*pu32Size	+= u32Size;
		pu08BS		+= u32Size;
		break;

	case YAVP2MWG_DIFFORMAT_PCM1 :
	case YAVP2MWG_DIFFORMAT_PCM2 :
	case YAVP2MWG_DIFFORMAT_PCM3 :
	case YAVP2MWG_DIFFORMAT_PCM4 :
		u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
		for ( i = 0; i < u32Size; i++ )
		{
			pu08BS[ i ]= au08DIFFormatPCM[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_PCM1 ][ i ];
		}
		*pu32Size	+= u32Size;
		pu08BS		+= u32Size;
		break;
	default :
		break;
	}

	u32Size		= sizeof( au08FDSP_Start );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08FDSP_Start[ i ];
	}
	pu08BS[ YAVP2MW_FDSPSTART_BS_FSTART ]= 0x01;
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;

	return gsInfo.au08BS;
}

/*******************************************************************************
 *	yavp2mwg_mic_register
 ******************************************************************************/
static	U08 *	yavp2mwg_mic_register
(
	U32 *		pu32Size
)
{
	U08 *		pu08BS;
	U32			u32Size, i;

	*pu32Size	= 0;
	pu08BS		= gsInfo.au08BS;

	u32Size	= sizeof( au08MicTest );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08MicTest[ i ];
	}
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;

	switch ( gsInfo.s32Temp2 )
	{
	case YAVP2MWG_DIFFORMAT_I2S1 :
	case YAVP2MWG_DIFFORMAT_I2S2 :
	case YAVP2MWG_DIFFORMAT_I2S3 :
	case YAVP2MWG_DIFFORMAT_I2S4 :
	case YAVP2MWG_DIFFORMAT_I2S5 :
	case YAVP2MWG_DIFFORMAT_I2S6 :
	case YAVP2MWG_DIFFORMAT_I2S7 :
	case YAVP2MWG_DIFFORMAT_I2S8 :
	case YAVP2MWG_DIFFORMAT_I2S9 :
		u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
		for ( i = 0; i < u32Size; i++ )
		{
			pu08BS[ i ]= au08DIFFormatI2S[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_I2S1 ][ i ];
		}
		*pu32Size	+= u32Size;
		pu08BS		+= u32Size;
		break;

	case YAVP2MWG_DIFFORMAT_PCM1 :
	case YAVP2MWG_DIFFORMAT_PCM2 :
	case YAVP2MWG_DIFFORMAT_PCM3 :
	case YAVP2MWG_DIFFORMAT_PCM4 :
		u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
		for ( i = 0; i < u32Size; i++ )
		{
			pu08BS[ i ]= au08DIFFormatPCM[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_PCM1 ][ i ];
		}
		*pu32Size	+= u32Size;
		pu08BS		+= u32Size;
		break;
	default :
		break;
	}

	u32Size		= sizeof( au08FDSP_Start );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08FDSP_Start[ i ];
	}
	pu08BS[ YAVP2MW_FDSPSTART_BS_FSTART ]= 0x01;
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;

	return gsInfo.au08BS;
}

/*******************************************************************************
 *	yavp2mwg_test_register
 ******************************************************************************/
static	U08 *	yavp2mwg_test_register
(
	U32 *		pu32Size
)
{
	U08 *		pu08BS;
	U32			u32Size, i;

	*pu32Size	= 0;
	pu08BS		= gsInfo.au08BS;

	u32Size	= sizeof( au08TestTest );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08TestTest[ i ];
	}
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;

	switch ( gsInfo.s32Temp2 )
	{
	case YAVP2MWG_DIFFORMAT_I2S1 :
	case YAVP2MWG_DIFFORMAT_I2S2 :
	case YAVP2MWG_DIFFORMAT_I2S3 :
	case YAVP2MWG_DIFFORMAT_I2S4 :
	case YAVP2MWG_DIFFORMAT_I2S5 :
	case YAVP2MWG_DIFFORMAT_I2S6 :
	case YAVP2MWG_DIFFORMAT_I2S7 :
	case YAVP2MWG_DIFFORMAT_I2S8 :
	case YAVP2MWG_DIFFORMAT_I2S9 :
		u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
		for ( i = 0; i < u32Size; i++ )
		{
			pu08BS[ i ]= au08DIFFormatI2S[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_I2S1 ][ i ];
		}
		*pu32Size	+= u32Size;
		pu08BS		+= u32Size;
		break;

	case YAVP2MWG_DIFFORMAT_PCM1 :
	case YAVP2MWG_DIFFORMAT_PCM2 :
	case YAVP2MWG_DIFFORMAT_PCM3 :
	case YAVP2MWG_DIFFORMAT_PCM4 :
		u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
		for ( i = 0; i < u32Size; i++ )
		{
			pu08BS[ i ]= au08DIFFormatPCM[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_PCM1 ][ i ];
		}
		*pu32Size	+= u32Size;
		pu08BS		+= u32Size;
		break;
	default :
		break;
	}

	u32Size		= sizeof( au08FDSP_Start );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08FDSP_Start[ i ];
	}
	pu08BS[ YAVP2MW_FDSPSTART_BS_FSTART ]= 0x00;
	*pu32Size	+= u32Size;
	pu08BS		+= u32Size;

	return gsInfo.au08BS;
}

/*******************************************************************************
 *	yavp2mwg_initialize
 ******************************************************************************/
static	S32		yavp2mwg_initialize
(
	void
)
{
	S32				s32Ret, i;
	const U08 *		pu08Scirpt;
	U32				u32Size;

	s32Ret			= YAVP2mwG_CONTINUE;
	pu08Scirpt		= NULL;
	u32Size			= 0;

	switch ( gsInfo.s32Temp1 )
	{
	case 0 :
		pu08Scirpt	= au08InitA;
		u32Size		= sizeof( au08InitA );
		break;

	case 1 :
		pu08Scirpt	= au08InitB;
		u32Size		= sizeof( au08InitB );
		break;

	case 2 :
		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
		case YAVP2MWG_FUNCTION_TEST1 :
			pu08Scirpt	= au08AudioA;
			u32Size		= sizeof( au08AudioA );
			break;
		case YAVP2MWG_FUNCTION_MIC1 :
		default :
			pu08Scirpt	= au08MicA;
			u32Size		= sizeof( au08MicA );
			break;
		}
		break;

	case 3 :
		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
		case YAVP2MWG_FUNCTION_TEST1 :
			pu08Scirpt	= gsInfo.sAudio.sScript[ gsInfo.sAudio.s08Param ].pu08Script;
			u32Size		= gsInfo.sAudio.sScript[ gsInfo.sAudio.s08Param ].u32Size;
			break;
		case YAVP2MWG_FUNCTION_MIC1 :
		default :
			pu08Scirpt	= gsInfo.sMic.sScript[ gsInfo.sMic.s08Param ].pu08Script;
			u32Size		= gsInfo.sMic.sScript[ gsInfo.sMic.s08Param ].u32Size;
			break;
		}
		break;

	case 4 :
		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
		case YAVP2MWG_FUNCTION_TEST1 :
			pu08Scirpt	= au08AudioB;
			u32Size		= sizeof( au08AudioB );
			break;
		case YAVP2MWG_FUNCTION_MIC1 :
		default :
			pu08Scirpt	= au08MicB;
			u32Size		= sizeof( au08MicB );
			break;
		}
		break;

	case 5 :
		pu08Scirpt	= au08InitC;
		u32Size		= sizeof( au08InitC );
		break;

	case 6 :
		pu08Scirpt	= au08InitD;
		u32Size		= sizeof( au08InitD );
		break;

	case 7 :
		pu08Scirpt	= yavp2mwg_funcsel_registerA(&u32Size );
		break;

	case 8 :
		switch ( gsInfo.s32Temp2 )
		{
		case YAVP2MWG_DIFFORMAT_I2S1 :
		case YAVP2MWG_DIFFORMAT_I2S2 :
		case YAVP2MWG_DIFFORMAT_I2S3 :
		case YAVP2MWG_DIFFORMAT_I2S4 :
		case YAVP2MWG_DIFFORMAT_I2S5 :
		case YAVP2MWG_DIFFORMAT_I2S6 :
		case YAVP2MWG_DIFFORMAT_I2S7 :
		case YAVP2MWG_DIFFORMAT_I2S8 :
		case YAVP2MWG_DIFFORMAT_I2S9 :
			pu08Scirpt	= au08DIFFormatI2S[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_I2S1 ];
			u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
			break;

		case YAVP2MWG_DIFFORMAT_PCM1 :
		case YAVP2MWG_DIFFORMAT_PCM2 :
		case YAVP2MWG_DIFFORMAT_PCM3 :
		case YAVP2MWG_DIFFORMAT_PCM4 :
			pu08Scirpt	= au08DIFFormatPCM[ gsInfo.s32Temp2 - YAVP2MWG_DIFFORMAT_PCM1 ];
			u32Size		= YAVP2MW_DIFFORMAT_BSSIZE;
			break;

		default :
			s32Ret		= YAVP2mwG_ERROR;
			break;
		}
		break;

	case 9 :
		gsInfo.sAudio.sVolume.s08Mute	= YAVP2MWG_MUTE;
		gsInfo.sAudio.sVolume.s32Volume	= 0;
		gsInfo.sAudio.s08Analog			= YAVP2MWG_AIN_VOL_MIN;
		gsInfo.sAudio.s08Digital		= YAVP2MWG_AIN_VOL_MIN;
		gsInfo.sAudio.s08BalL			= 0;
		gsInfo.sAudio.s08BalR			= 0;
		gsInfo.sAudio.s08FadeF			= 0;
		gsInfo.sAudio.s08FadeR			= 0;
		gsInfo.sAudio.u08SICC1			= 1;
		gsInfo.sAudio.u08SICC2			= 1;
		for ( i = 0; i < 5; i++ )
		{
			gsInfo.sAudio.as08GEQ1[ i ]	= 0;
			gsInfo.sAudio.as08GEQ2[ i ]	= 0;
		}

		gsInfo.sMic.sReceive.s08Mute	= YAVP2MWG_MUTE;
		gsInfo.sMic.sReceive.s32Volume	= 0;
		gsInfo.sMic.s08ADIF0			= 0;
		gsInfo.sMic.s08ADIF2			= 0;

		gsInfo.sTest.s08FLVolume		= -96;
		gsInfo.sTest.s08FRVolume		= -96;
		gsInfo.sTest.s08RLVolume		= -96;
		gsInfo.sTest.s08RRVolume		= -96;

		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
			pu08Scirpt	= au08InitE_Audio;
			u32Size		= sizeof( au08InitE_Audio );
			break;
		case YAVP2MWG_FUNCTION_MIC1 :
			pu08Scirpt	= au08InitE_Mic;
			u32Size		= sizeof( au08InitE_Mic );
			break;
		case YAVP2MWG_FUNCTION_TEST1 :
		default :
			pu08Scirpt	= au08InitE_Test;
			u32Size		= sizeof( au08InitE_Test );
			break;
		}
		break;

	case 10 :
		pu08Scirpt	= yavp2mwg_funcsel_registerB(&u32Size );
		s32Ret		= YAVP2mwG_SUCCESS;
		break;

	default :
		s32Ret		= YAVP2mwG_ERROR;
		break;
	}

	if (( s32Ret		!= YAVP2mwG_ERROR )
	 && ( pu08Scirpt	!= NULL )
	 && ( u32Size		!= 0 ))
	{
		if ( YAVP2mwG_batch_process( pu08Scirpt, u32Size )< YAD1DD_SUCCESS )
		{
			s32Ret	= YAVP2mwG_ERROR;
		}
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_function_select
 ******************************************************************************/
static	S32		yavp2mwg_function_select
(
	void
)
{
	S32				s32Ret;
	const U08 *		pu08Scirpt;
	U32				u32Size;

	s32Ret			= YAVP2mwG_CONTINUE;
	pu08Scirpt		= NULL;
	u32Size			= 0;

	switch ( gsInfo.s32Temp1 )
	{
	case 0 :
		pu08Scirpt	= au08FuncSelA;
		u32Size		= sizeof( au08FuncSelA );
		break;

	case 1 :
		pu08Scirpt	= au08FuncSelB;
		u32Size		= sizeof( au08FuncSelB );
		break;

	case 2 :
		pu08Scirpt	= yavp2mwg_funcsel_registerA(&u32Size );
		break;

	case 3 :
		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
			pu08Scirpt	= au08AudioA;
			u32Size		= sizeof( au08AudioA );
			break;

		case YAVP2MWG_FUNCTION_MIC1 :
			pu08Scirpt	= au08MicA;
			u32Size		= sizeof( au08MicA );
			break;

		case YAVP2MWG_FUNCTION_TEST1 :
		default :
			pu08Scirpt	= au08Nop;
			u32Size		= sizeof( au08Nop );
			break;
		}
		break;

	case 4 :
		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
			pu08Scirpt	= gsInfo.sAudio.sScript[ gsInfo.sAudio.s08Param ].pu08Script;
			u32Size		= gsInfo.sAudio.sScript[ gsInfo.sAudio.s08Param ].u32Size;
			break;

		case YAVP2MWG_FUNCTION_MIC1 :
			pu08Scirpt	= gsInfo.sMic.sScript[ gsInfo.sMic.s08Param ].pu08Script;
			u32Size		= gsInfo.sMic.sScript[ gsInfo.sMic.s08Param ].u32Size;
			break;

		case YAVP2MWG_FUNCTION_TEST1 :
		default :
			pu08Scirpt	= au08Nop;
			u32Size		= sizeof( au08Nop );
			break;
		}
		break;

	case 5 :
		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
			pu08Scirpt	= au08AudioB;
			u32Size		= sizeof( au08AudioB );
			break;

		case YAVP2MWG_FUNCTION_MIC1 :
			pu08Scirpt	= au08MicB;
			u32Size		= sizeof( au08MicB );
			break;

		case YAVP2MWG_FUNCTION_TEST1 :
		default :
			pu08Scirpt	= au08Nop;
			u32Size		= sizeof( au08Nop );
			break;
		}
		break;

	case 6 :
		switch ( gsInfo.s32Func )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
			pu08Scirpt	= yavp2mwg_audio_register(&u32Size );
			break;

		case YAVP2MWG_FUNCTION_MIC1 :
			pu08Scirpt	= yavp2mwg_mic_register(&u32Size );
			break;

		case YAVP2MWG_FUNCTION_TEST1 :
		default :
			pu08Scirpt	= yavp2mwg_test_register(&u32Size );
			break;
		}
		break;

	case 7 :
		pu08Scirpt	= yavp2mwg_funcsel_registerB(&u32Size );
		s32Ret		= YAVP2mwG_SUCCESS;
		break;

	default :
		s32Ret		= YAVP2mwG_ERROR;
		break;
	}

	if (( s32Ret		!= YAVP2mwG_ERROR )
	 && ( pu08Scirpt	!= NULL )
	 && ( u32Size		!= 0 ))
	{
		if ( YAVP2mwG_batch_process( pu08Scirpt, u32Size )< YAD1DD_SUCCESS )
		{
			s32Ret	= YAVP2mwG_ERROR;
		}
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_audio_input_vol
 ******************************************************************************/
static	S32		yavp2mwg_audio_input_vol
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	U08			u08RegA, u08RegD, u08Ope1, u08Ope2;
	U08 *		pu08BS;
	U32			u32Size, i;

	u08Ope1	= 0x04;
	u08Ope2	= 0x10;

	if		( s32Prm1	>= YAVP2MWG_AIN_VOL_MAX )
	{
		s32Prm1	= YAVP2MWG_AIN_VOL_MAX;
		u08RegA	= 96;
	}
	else if	( s32Prm1	<= YAVP2MWG_AIN_VOL_MIN )
	{
		s32Prm1	= YAVP2MWG_AIN_VOL_MIN;
		u08RegA	= 0;
		u08Ope1	= 0x05;
		u08Ope2	= 0xEF;
	}
	else
	{
		u08RegA	=(U08)( s32Prm1 + 96 );
	}
	if		( s32Prm2	>= YAVP2MWG_AIN_VOL_MAX )
	{
		s32Prm2	= YAVP2MWG_AIN_VOL_MAX;
		u08RegD	= 96;
	}
	else if	( s32Prm2	<= YAVP2MWG_AIN_VOL_MIN )
	{
		s32Prm2	= YAVP2MWG_AIN_VOL_MIN;
		u08RegD	= 0;
	}
	else
	{
		u08RegD	=(U08)( s32Prm2 + 96 );
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08AudioInputVolume );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioInputVolume[ i ];
	}
	pu08BS[ YAVP2MW_AINVOL_BS_ADIVOL ]		= u08RegA;
	pu08BS[ YAVP2MW_AINVOL_BS_DIFIVOL ]		= u08RegD;
	pu08BS[ YAVP2MW_AINVOL_BS_OPERATOR ]	= u08Ope1;
	pu08BS[ YAVP2MW_AINVOL_BS_OPERAND ]		= u08Ope2;

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sAudio.s08Analog		=(S08)s32Prm1;
		gsInfo.sAudio.s08Digital	=(S08)s32Prm2;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_audio_coef
 ******************************************************************************/
static	S32		yavp2mwg_audio_coef
(
	void
)
{
	S32				s32Ret;
	const U08 *		pu08Scirpt;
	U32				u32Size;

	s32Ret			= YAVP2mwG_CONTINUE;
	pu08Scirpt		= NULL;
	u32Size			= 0;

	switch ( gsInfo.s32Temp1 )
	{
	case 0 :
		pu08Scirpt	= au08AudioCoefA;
		u32Size		= sizeof( au08AudioCoefA );
		break;

	case 1 :
		pu08Scirpt	= au08AudioCoefB;
		u32Size		= sizeof( au08AudioCoefB );
		break;

	case 2 :
		pu08Scirpt	= gsInfo.sAudio.sScript[ gsInfo.sAudio.s08Param ].pu08Script;
		u32Size		= gsInfo.sAudio.sScript[ gsInfo.sAudio.s08Param ].u32Size;
		break;

	case 3 :
		pu08Scirpt	= yavp2mwg_audio_register( &u32Size );
		break;

	case 4 :
		s32Ret		= yavp2mwg_audio_input_vol( gsInfo.sAudio.s08Analog, gsInfo.sAudio.s08Digital );
		break;

	default :
		s32Ret		= YAVP2mwG_ERROR;
		break;
	}

	if (( s32Ret		!= YAVP2mwG_ERROR )
	 && ( pu08Scirpt	!= NULL )
	 && ( u32Size		!= 0 ))
	{
		if ( YAVP2mwG_batch_process( pu08Scirpt, u32Size )< YAD1DD_SUCCESS )
		{
			s32Ret	= YAVP2mwG_ERROR;
		}
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_init
 ******************************************************************************/
static	S32		yavp2mwg_init
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret, i;
	S08			s08Prm;

	s32Ret	= YAVP2mwG_CONTINUE;
	s08Prm	= 0;

	switch ( s32Prm1 )
	{
	case YAVP2MWG_FUNCTION_AUDIO1 :
	case YAVP2MWG_FUNCTION_AUDIO2 :
	case YAVP2MWG_FUNCTION_AUDIO3 :
	case YAVP2MWG_FUNCTION_AUDIO4 :
	case YAVP2MWG_FUNCTION_AUDIO5 :
	case YAVP2MWG_FUNCTION_AUDIO6 :
	case YAVP2MWG_FUNCTION_AUDIO7 :
	case YAVP2MWG_FUNCTION_AUDIO8 :
		s08Prm	=(S08)( s32Prm1 - YAVP2MWG_FUNCTION_AUDIO1 );
		s32Prm1	= YAVP2MWG_FUNCTION_AUDIO1;
		break;

	case YAVP2MWG_FUNCTION_MIC1 :
	case YAVP2MWG_FUNCTION_MIC2 :
	case YAVP2MWG_FUNCTION_MIC3 :
	case YAVP2MWG_FUNCTION_MIC4 :
	case YAVP2MWG_FUNCTION_MIC5 :
	case YAVP2MWG_FUNCTION_MIC6 :
	case YAVP2MWG_FUNCTION_MIC7 :
	case YAVP2MWG_FUNCTION_MIC8 :
		s08Prm	=(S08)( s32Prm1 - YAVP2MWG_FUNCTION_MIC1 );
		s32Prm1	= YAVP2MWG_FUNCTION_MIC1;
		break;

	case YAVP2MWG_FUNCTION_TEST1 :
	case YAVP2MWG_FUNCTION_TEST2 :
	case YAVP2MWG_FUNCTION_TEST3 :
	case YAVP2MWG_FUNCTION_TEST4 :
	case YAVP2MWG_FUNCTION_TEST5 :
		s08Prm	=(S08)( s32Prm1 - YAVP2MWG_FUNCTION_TEST1 );
		s32Prm1	= YAVP2MWG_FUNCTION_TEST1;
		break;

	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	switch ( s32Prm2 )
	{
	case YAVP2MWG_DIFFORMAT_I2S1 :
	case YAVP2MWG_DIFFORMAT_I2S2 :
	case YAVP2MWG_DIFFORMAT_I2S3 :
	case YAVP2MWG_DIFFORMAT_I2S4 :
	case YAVP2MWG_DIFFORMAT_I2S5 :
	case YAVP2MWG_DIFFORMAT_I2S6 :
	case YAVP2MWG_DIFFORMAT_I2S7 :
	case YAVP2MWG_DIFFORMAT_I2S8 :
	case YAVP2MWG_DIFFORMAT_I2S9 :
	case YAVP2MWG_DIFFORMAT_PCM1 :
	case YAVP2MWG_DIFFORMAT_PCM2 :
	case YAVP2MWG_DIFFORMAT_PCM3 :
	case YAVP2MWG_DIFFORMAT_PCM4 :
		break;
	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	if ( s32Ret	!= YAVP2mwG_ERROR )
	{
		gsInfo.s32Temp1		= 0;
		gsInfo.s32Temp2		= s32Prm2;
		gsInfo.s32Func		= s32Prm1;
		switch ( s32Prm1 )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
			gsInfo.sAudio.s08Param	= s08Prm;
			gsInfo.sMic.s08Param	= 0;
			gsInfo.sTest.s08Source	= 0;
			break;
		case YAVP2MWG_FUNCTION_MIC1 :
			gsInfo.sAudio.s08Param	= 0;
			gsInfo.sMic.s08Param	= s08Prm;
			gsInfo.sTest.s08Source	= 0;
			break;
		case YAVP2MWG_FUNCTION_TEST1 :
		default :
			gsInfo.sAudio.s08Param	= 0;
			gsInfo.sMic.s08Param	= 0;
			gsInfo.sTest.s08Source	= s08Prm;
			break;
		}

		for ( i = 0; i < YAVP2MWG_MAX_SET; i++ )
		{
			gsInfo.sAudio.sScript[ i ].pu08Script	= au08Nop;
			gsInfo.sAudio.sScript[ i ].u32Size		= sizeof( au08Nop );
			gsInfo.sMic.sScript[ i ].pu08Script		= au08Nop;
			gsInfo.sMic.sScript[ i ].u32Size		= sizeof( au08Nop );
		}
		/* audio parameter */
		gsInfo.sAudio.sScript[ 0 ].pu08Script	= au08Audio1;
		gsInfo.sAudio.sScript[ 0 ].u32Size		= sizeof( au08Audio1 );

		/* mic parameter */
		gsInfo.sMic.sScript[ 0 ].pu08Script		= au08Mic1;
		gsInfo.sMic.sScript[ 0 ].u32Size		= sizeof( au08Mic1 );
	}

	while ( s32Ret	== YAVP2mwG_CONTINUE )
	{
		s32Ret	= yavp2mwg_initialize();
		if ( s32Ret	== YAVP2mwG_CONTINUE )
		{
			gsInfo.s32Temp1	++;
		}
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_beep_vol
 ******************************************************************************/
static	S32		yavp2mwg_beep_vol
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	U08			u08Reg;
	U08 *		pu08BS;
	U32			u32Size, i;

	if		( s32Prm1	> YAVP2MWG_BEEP_VOL_MAX )
	{
		u08Reg	= 96;
	}
	else if	( s32Prm1	< YAVP2MWG_BEEP_VOL_MIN )
	{
		u08Reg	= 0;
	}
	else
	{
		u08Reg	=(U08)( s32Prm1 + 96 );
	}

	if ( s32Prm2	== YAVP2MWG_MUTE )
	{
		u08Reg	= 0;
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08BeppVolume );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08BeppVolume[ i ];
	}
	pu08BS[ YAVP2MW_BEEPVOL_BS_ANALOG ]		= u08Reg;
	pu08BS[ YAVP2MW_BEEPVOL_BS_DIGITAL ]	= u08Reg;

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_funcsel
 ******************************************************************************/
static	S32		yavp2mwg_funcsel
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	S08			s08Prm;

	s32Ret	= YAVP2mwG_CONTINUE;
	s08Prm	= 0;

	switch ( s32Prm1 )
	{
	case YAVP2MWG_FUNCTION_AUDIO1 :
	case YAVP2MWG_FUNCTION_AUDIO2 :
	case YAVP2MWG_FUNCTION_AUDIO3 :
	case YAVP2MWG_FUNCTION_AUDIO4 :
	case YAVP2MWG_FUNCTION_AUDIO5 :
	case YAVP2MWG_FUNCTION_AUDIO6 :
	case YAVP2MWG_FUNCTION_AUDIO7 :
	case YAVP2MWG_FUNCTION_AUDIO8 :
		s08Prm	=(S08)( s32Prm1 - YAVP2MWG_FUNCTION_AUDIO1 );
		s32Prm1	= YAVP2MWG_FUNCTION_AUDIO1;
		break;

	case YAVP2MWG_FUNCTION_MIC1 :
	case YAVP2MWG_FUNCTION_MIC2 :
	case YAVP2MWG_FUNCTION_MIC3 :
	case YAVP2MWG_FUNCTION_MIC4 :
	case YAVP2MWG_FUNCTION_MIC5 :
	case YAVP2MWG_FUNCTION_MIC6 :
	case YAVP2MWG_FUNCTION_MIC7 :
	case YAVP2MWG_FUNCTION_MIC8 :
		s08Prm	=(S08)( s32Prm1 - YAVP2MWG_FUNCTION_MIC1 );
		s32Prm1	= YAVP2MWG_FUNCTION_MIC1;
		break;

	case YAVP2MWG_FUNCTION_TEST1 :
	case YAVP2MWG_FUNCTION_TEST2 :
	case YAVP2MWG_FUNCTION_TEST3 :
	case YAVP2MWG_FUNCTION_TEST4 :
	case YAVP2MWG_FUNCTION_TEST5 :
		s08Prm	=(S08)( s32Prm1 - YAVP2MWG_FUNCTION_TEST1 );
		s32Prm1	= YAVP2MWG_FUNCTION_TEST1;
		break;

	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	switch ( s32Prm2 )
	{
	case YAVP2MWG_DIFFORMAT_I2S1 :
	case YAVP2MWG_DIFFORMAT_I2S2 :
	case YAVP2MWG_DIFFORMAT_I2S3 :
	case YAVP2MWG_DIFFORMAT_I2S4 :
	case YAVP2MWG_DIFFORMAT_I2S5 :
	case YAVP2MWG_DIFFORMAT_I2S6 :
	case YAVP2MWG_DIFFORMAT_I2S7 :
	case YAVP2MWG_DIFFORMAT_I2S8 :
	case YAVP2MWG_DIFFORMAT_I2S9 :
	case YAVP2MWG_DIFFORMAT_PCM1 :
	case YAVP2MWG_DIFFORMAT_PCM2 :
	case YAVP2MWG_DIFFORMAT_PCM3 :
	case YAVP2MWG_DIFFORMAT_PCM4 :
		break;
	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	if ( s32Ret	!= YAVP2mwG_ERROR )
	{
		gsInfo.s32Temp1		= 0;
		gsInfo.s32Temp2		= s32Prm2;
		gsInfo.s32Func		= s32Prm1;
		switch ( s32Prm1 )
		{
		case YAVP2MWG_FUNCTION_AUDIO1 :
			gsInfo.sAudio.s08Param	= s08Prm;
			break;
		case YAVP2MWG_FUNCTION_MIC1 :
			gsInfo.sMic.s08Param	= s08Prm;
			break;
		case YAVP2MWG_FUNCTION_TEST1 :
		default :
			gsInfo.sTest.s08Source	= s08Prm;
			break;
		}
	}

	while ( s32Ret	== YAVP2mwG_CONTINUE )
	{
		s32Ret	= yavp2mwg_function_select();
		if ( s32Ret	== YAVP2mwG_CONTINUE )
		{
			gsInfo.s32Temp1	++;
		}
	}

	return s32Ret;
}


/*******************************************************************************
 *	yavp2mwg_audio_vol
 ******************************************************************************/
static	S32		yavp2mwg_audio_vol
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	S08			s08Volume, s08Offset, s08Mute;
	U08 *		pu08BS;
	U32			u32Size, i;

	if		( s32Prm1	>= YAVP2MWG_AUDIO_VOL_MAX )
	{
		s32Prm1		= YAVP2MWG_AUDIO_VOL_MAX;
		s08Volume	= 0x00;
		s08Offset	= 0x00;
	}
	else if	( s32Prm1	<= YAVP2MWG_AUDIO_VOL_MIN )
	{
		s32Prm1		= YAVP2MWG_AUDIO_VOL_MIN;
		s08Volume	= 0x80;
		s08Offset	= 0x80;
	}
	else
	{
		s08Volume	=(S08)(( s32Prm1 >> 7 )+ 1 );
		s08Offset	=(S08)(( s32Prm1 & 0x7F )| 0x80 );
	}

	s08Mute		= 0x00;
	if ( s32Prm2	== YAVP2MWG_MUTE )
	{
		s08Mute	= YAVP2MWG_REGVAL_FDR4B_MUTE;
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08AudioFDR4B );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioFDR4B[ i ];
	}
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_MUTE1 ]	= s08Mute;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_REGSTER ]	= YAVP2MWG_REGADR_FDR4BA_OFFSET;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_VOLUME1 ]	= s08Offset;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_VOLUME2 ]	= s08Volume;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_MUTE2 ]	=(U08)( s08Mute | YAVP2MWG_REGVAL_FDR4B_START );

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sAudio.sVolume.s08Mute	=(S08)s32Prm2;
		gsInfo.sAudio.sVolume.s32Volume	= s32Prm1;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_audio_balance
 ******************************************************************************/
static	S32		yavp2mwg_audio_balance
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	S08			s08RegL, s08RegR, s08Mute;
	U08 *		pu08BS;
	U32			u32Size, i;

	s08Mute	= 0;
	if ( gsInfo.sAudio.sVolume.s08Mute	== YAVP2MWG_MUTE )
	{
		s08Mute	= YAVP2MWG_REGVAL_FDR4B_MUTE;
	}
	s08RegL	=(S08)s32Prm1;
	s08RegR	=(S08)s32Prm2;

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08AudioFDR4B );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioFDR4B[ i ];
	}
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_MUTE1 ]	= s08Mute;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_REGSTER ]	= YAVP2MWG_REGADR_FDR4BA_BALANCE_L;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_VOLUME1 ]	= s08RegL;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_VOLUME2 ]	= s08RegR;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_MUTE2 ]	=(U08)( s08Mute | YAVP2MWG_REGVAL_FDR4B_START );

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sAudio.s08BalL	=(S08)s32Prm1;
		gsInfo.sAudio.s08BalR	=(S08)s32Prm2;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_audio_fader
 ******************************************************************************/
static	S32		yavp2mwg_audio_fader
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	S08			s08RegF, s08RegR, s08Mute;
	U08 *		pu08BS;
	U32			u32Size, i;

	s08Mute	= 0;
	if ( gsInfo.sAudio.sVolume.s08Mute	== YAVP2MWG_MUTE )
	{
		s08Mute	= YAVP2MWG_REGVAL_FDR4B_MUTE;
	}
	s08RegF	=(S08)s32Prm1;
	s08RegR	=(S08)s32Prm2;

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08AudioFDR4B );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioFDR4B[ i ];
	}
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_MUTE1 ]	= s08Mute;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_REGSTER ]	= YAVP2MWG_REGADR_FDR4BA_FADER_F;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_VOLUME1 ]	= s08RegF;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_VOLUME2 ]	= s08RegR;
	pu08BS[ YAVP2MW_AUDIOFDR4B_BS_MUTE2 ]	=(U08)( s08Mute | YAVP2MWG_REGVAL_FDR4B_START );

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sAudio.s08FadeF	=(S08)s32Prm1;
		gsInfo.sAudio.s08FadeR	=(S08)s32Prm2;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_audio_geq
 ******************************************************************************/
static	S32		yavp2mwg_audio_geq
(
	S32			s32Prm1,
	S32			s32Prm2,
	S32			s32Sel
)
{
	S08			as08Gain[5];
	S08 *		ps08Gain;
	S32			s32Ret;
	U08 *		pu08BS;
	const U08 *	pu08SICC;
	U32			u32Size, i, j;


	if ( s32Sel	== 0 )
	{
		ps08Gain	= gsInfo.sAudio.as08GEQ1;
		if ( gsInfo.sAudio.u08SICC1	== 0 )
		{			/* page 0 */
			pu08SICC	= au08AudioGEQ1[ 0 ];
		}
		else
		{			/* page 1 */
			pu08SICC	= au08AudioGEQ1[ 1 ];
		}
		gsInfo.sAudio.u08SICC1	=( gsInfo.sAudio.u08SICC1 + 1 )& 0x01;
	}
	else
	{
		ps08Gain	= gsInfo.sAudio.as08GEQ2;
		if ( gsInfo.sAudio.u08SICC2	== 0 )
		{			/* page 0 */
			pu08SICC	= au08AudioGEQ2[ 0 ];
		}
		else
		{			/* page 1 */
			pu08SICC	= au08AudioGEQ2[ 1 ];
		}
		gsInfo.sAudio.u08SICC2	=( gsInfo.sAudio.u08SICC2 + 1 )& 0x01;
	}

	for ( i = 0; i < 5; i++ )
	{
		if (( s32Prm1 &( 0x01 << i ))!= 0 )
		{
			if		( s32Prm2	> YAVP2MWG_AUDIOGEQ_GAIN_MAX )
			{
				as08Gain[ i ]= YAVP2MWG_AUDIOGEQ_GAIN_MAX;
			}
			else if	( s32Prm2	< YAVP2MWG_AUDIOGEQ_GAIN_MIN )
			{
				as08Gain[ i ]= YAVP2MWG_AUDIOGEQ_GAIN_MIN;
			}
			else
			{
				as08Gain[ i ]=(S08)s32Prm2;
			}
		}
		else
		{
			as08Gain[ i ]= ps08Gain[ i ];
		}
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= 78;
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= pu08SICC[ i ];
	}

	pu08BS	+= YAVP2MW_AUDIOSICC_BS_BAND1GAIN;
	for ( i = 0; i < 5; i++ )
	{
		for ( j = 0; j < 4; j++ )
		{
			pu08BS[ j ]= au08GEQGain[ as08Gain[ i ]+ 12 ][ j ];
		}
		pu08BS	+= YAVP2MW_AUDIOSICC_BS_GAINOFFSET;
	}

	s32Ret	= YAVP2mwG_batch_process( gsInfo.au08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		for ( i = 0; i < 5; i++ )
		{
			ps08Gain[ i ]= as08Gain[ i ];
		}
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_audio_param
 ******************************************************************************/
static	S32		yavp2mwg_audio_param
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;

	if ( gsInfo.s32Func	== YAVP2MWG_FUNCTION_AUDIO1 )
	{
		s32Ret	= YAVP2mwG_CONTINUE;
	}
	else
	{
		s32Ret	= YAVP2mwG_SUCCESS;
	}

	switch ( s32Prm1 )
	{
	case YAVP2MWG_FUNCTION_AUDIO1 :
	case YAVP2MWG_FUNCTION_AUDIO2 :
	case YAVP2MWG_FUNCTION_AUDIO3 :
	case YAVP2MWG_FUNCTION_AUDIO4 :
	case YAVP2MWG_FUNCTION_AUDIO5 :
	case YAVP2MWG_FUNCTION_AUDIO6 :
	case YAVP2MWG_FUNCTION_AUDIO7 :
	case YAVP2MWG_FUNCTION_AUDIO8 :
		s32Prm1	-= YAVP2MWG_FUNCTION_AUDIO1;
		break;

	case YAVP2MWG_FUNCTION_MIC1 :
	case YAVP2MWG_FUNCTION_MIC2 :
	case YAVP2MWG_FUNCTION_MIC3 :
	case YAVP2MWG_FUNCTION_MIC4 :
	case YAVP2MWG_FUNCTION_MIC5 :
	case YAVP2MWG_FUNCTION_MIC6 :
	case YAVP2MWG_FUNCTION_MIC7 :
	case YAVP2MWG_FUNCTION_MIC8 :
	case YAVP2MWG_FUNCTION_TEST1 :
	case YAVP2MWG_FUNCTION_TEST2 :
	case YAVP2MWG_FUNCTION_TEST3 :
	case YAVP2MWG_FUNCTION_TEST4 :
	case YAVP2MWG_FUNCTION_TEST5 :
	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	switch ( s32Prm2 )
	{
	case YAVP2MWG_DIFFORMAT_I2S1 :
	case YAVP2MWG_DIFFORMAT_I2S2 :
	case YAVP2MWG_DIFFORMAT_I2S3 :
	case YAVP2MWG_DIFFORMAT_I2S4 :
	case YAVP2MWG_DIFFORMAT_I2S5 :
	case YAVP2MWG_DIFFORMAT_I2S6 :
	case YAVP2MWG_DIFFORMAT_I2S7 :
	case YAVP2MWG_DIFFORMAT_I2S8 :
	case YAVP2MWG_DIFFORMAT_I2S9 :
	case YAVP2MWG_DIFFORMAT_PCM1 :
	case YAVP2MWG_DIFFORMAT_PCM2 :
	case YAVP2MWG_DIFFORMAT_PCM3 :
	case YAVP2MWG_DIFFORMAT_PCM4 :
		break;
	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	if ( s32Ret	!= YAVP2mwG_ERROR )
	{
		gsInfo.s32Temp1			= 0;
		gsInfo.s32Temp2			= s32Prm2;
		gsInfo.sAudio.s08Param	=(S08)s32Prm1;
	}

	while ( s32Ret	== YAVP2mwG_CONTINUE )
	{
		s32Ret	= yavp2mwg_audio_coef();
		if ( s32Ret	== YAVP2mwG_CONTINUE )
		{
			gsInfo.s32Temp1	++;
		}
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_audio_test
 ******************************************************************************/
static	S32		yavp2mwg_audio_test
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	U08			u08F1, u08F2, u08F3, u08B;
	U08 *		pu08BS;
	U32			u32Size, i;

	u08F1	=(U08)(( s32Prm1 >> 16 )& 0x00FF );
	u08F2	=(U08)(( s32Prm1 >>  8 )& 0x00FF );
	u08F3	=(U08)(( s32Prm1 >>  0 )& 0x00FF );
	u08B	=(U08)(( s32Prm2 >>  0 )& 0x00FF );

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08AudioTest );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08AudioTest[ i ];
	}
	pu08BS[ YAVP2MW_AUDIOSICC_BS_FAPPEXEC + 0 ]	= u08F1;
	pu08BS[ YAVP2MW_AUDIOSICC_BS_FAPPEXEC + 1 ]	= u08F2;
	pu08BS[ YAVP2MW_AUDIOSICC_BS_FAPPEXEC + 2 ]	= u08F3;
	pu08BS[ YAVP2MW_AUDIOSICC_BS_BAPPEXEC ]		= u08B;

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_mic_receive_vol
 ******************************************************************************/
static	S32		yavp2mwg_mic_receive_vol
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	U08			u08Reg;
	S32			s32Ret;
	U08 *		pu08BS;
	U32			u32Size, i;

	if		( s32Prm1	> YAVP2MWG_MIC_VOL_MAX )
	{
		s32Prm1	= YAVP2MWG_MIC_VOL_MAX;
		u08Reg	= 0x60;
	}
	else if	( s32Prm1	< YAVP2MWG_MIC_VOL_MIN )
	{
		s32Prm1	= YAVP2MWG_MIC_VOL_MIN;
		u08Reg	= 0;
	}
	else
	{
		u08Reg	=(U08)( s32Prm1 + 96 );
	}
	if ( s32Prm2	== YAVP2MWG_MUTE )
	{
		u08Reg	= 0;
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08MicReceiveVol );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08MicReceiveVol[ i ];
	}
	pu08BS[ YAVP2MW_MICINPUTVOL_BS_DIF1VOL ]	= u08Reg;

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sMic.sReceive.s32Volume	= s32Prm1;
		gsInfo.sMic.sReceive.s08Mute	=(S08)s32Prm2;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_mic_input_vol
 ******************************************************************************/
static	S32		yavp2mwg_mic_input_vol
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	U08 *		pu08BS;
	U32			u32Size, i;

	if		( s32Prm1	> YAVP2MWG_MIC_VOL_MAX )
	{
		s32Prm1	= YAVP2MWG_MIC_VOL_MAX;
	}
	else if	( s32Prm1	< YAVP2MWG_MIC_VOL_MIN )
	{
		s32Prm1	= YAVP2MWG_MIC_VOL_MIN;
	}
	else
	{
		;		/* nop */
	}
	if		( s32Prm2	> YAVP2MWG_MIC_VOL_MAX )
	{
		s32Prm2	= YAVP2MWG_MIC_VOL_MAX;
	}
	else if	( s32Prm2	< YAVP2MWG_MIC_VOL_MIN )
	{
		s32Prm2	= YAVP2MWG_MIC_VOL_MIN;
	}
	else
	{
		;		/* nop */
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08MicInputVol );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08MicInputVol[ i ];
	}
	pu08BS[ YAVP2MW_MICINPUTVOL_BS_ADI0VOL ]	=(S08)( s32Prm1 + 96 );
	pu08BS[ YAVP2MW_MICINPUTVOL_BS_ADI2VOL ]	=(S08)( s32Prm2 + 96 );

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sMic.s08ADIF0	=(S08)s32Prm1;
		gsInfo.sMic.s08ADIF2	=(S08)s32Prm2;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_test_volume_F
 ******************************************************************************/
static	S32		yavp2mwg_test_volume_F
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	U08 *		pu08BS;
	U32			u32Size, i;

	if		( s32Prm1	> YAVP2MWG_TEST_VOL_MAX )
	{
		s32Prm1	= YAVP2MWG_TEST_VOL_MAX;
	}
	else if	( s32Prm1	< YAVP2MWG_TEST_VOL_MIN )
	{
		s32Prm1	= YAVP2MWG_TEST_VOL_MIN;
	}
	else
	{
		;		/* nop */
	}
	if		( s32Prm2	> YAVP2MWG_TEST_VOL_MAX )
	{
		s32Prm2	= YAVP2MWG_TEST_VOL_MAX;
	}
	else if	( s32Prm2	< YAVP2MWG_TEST_VOL_MIN )
	{
		s32Prm2	= YAVP2MWG_TEST_VOL_MIN;
	}
	else
	{
		;		/* nop */
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08TestVolume );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08TestVolume[ i ];
	}
	pu08BS[ YAVP2MW_TESTVOL_BS_REGADRS ]	= YAVP2MWG_REGADR_DAC0VOLUME;
	pu08BS[ YAVP2MW_TESTVOL_BS_VOLUME_L ]	=(S08)( s32Prm1 + 96 );
	pu08BS[ YAVP2MW_TESTVOL_BS_VOLUME_R ]	=(S08)( s32Prm2 + 96 );

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sTest.s08FLVolume	=(S08)s32Prm1;
		gsInfo.sTest.s08FRVolume	=(S08)s32Prm2;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_test_volume_R
 ******************************************************************************/
static	S32		yavp2mwg_test_volume_R
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	U08 *		pu08BS;
	U32			u32Size, i;

	if		( s32Prm1	> YAVP2MWG_TEST_VOL_MAX )
	{
		s32Prm1	= YAVP2MWG_TEST_VOL_MAX;
	}
	else if	( s32Prm1	< YAVP2MWG_TEST_VOL_MIN )
	{
		s32Prm1	= YAVP2MWG_TEST_VOL_MIN;
	}
	else
	{
		;		/* nop */
	}
	if		( s32Prm2	> YAVP2MWG_TEST_VOL_MAX )
	{
		s32Prm2	= YAVP2MWG_TEST_VOL_MAX;
	}
	else if	( s32Prm2	< YAVP2MWG_TEST_VOL_MIN )
	{
		s32Prm2	= YAVP2MWG_TEST_VOL_MIN;
	}
	else
	{
		;		/* nop */
	}

	pu08BS	= gsInfo.au08BS;
	u32Size	= sizeof( au08TestVolume );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08TestVolume[ i ];
	}
	pu08BS[ YAVP2MW_TESTVOL_BS_REGADRS ]	= YAVP2MWG_REGADR_DAC1VOLUME;
	pu08BS[ YAVP2MW_TESTVOL_BS_VOLUME_L ]	=(S08)( s32Prm1 + 96 );
	pu08BS[ YAVP2MW_TESTVOL_BS_VOLUME_R ]	=(S08)( s32Prm2 + 96 );

	s32Ret	= YAVP2mwG_batch_process( pu08BS, u32Size );
	if ( s32Ret	< YAD1DD_SUCCESS )
	{
		s32Ret	= YAVP2mwG_ERROR;
	}
	else
	{
		gsInfo.sTest.s08RLVolume	=(S08)s32Prm1;
		gsInfo.sTest.s08RRVolume	=(S08)s32Prm2;
	}

	return s32Ret;
}

/*******************************************************************************
 *	yavp2mwg_test_source
 ******************************************************************************/
static	S32		yavp2mwg_test_source
(
	S32			s32Prm1,
	S32			s32Prm2
)
{
	S32			s32Ret;
	U08 *		pu08BS;
	const U08 *	pu08DIFBS;
	U32			u32Size, i;

	s32Ret	= YAVP2mwG_SUCCESS;
	pu08BS	= gsInfo.au08BS;

	switch ( s32Prm2 )
	{
	case YAVP2MWG_DIFFORMAT_I2S1 :
	case YAVP2MWG_DIFFORMAT_I2S2 :
	case YAVP2MWG_DIFFORMAT_I2S3 :
	case YAVP2MWG_DIFFORMAT_I2S4 :
	case YAVP2MWG_DIFFORMAT_I2S5 :
	case YAVP2MWG_DIFFORMAT_I2S6 :
	case YAVP2MWG_DIFFORMAT_I2S7 :
	case YAVP2MWG_DIFFORMAT_I2S8 :
	case YAVP2MWG_DIFFORMAT_I2S9 :
		pu08DIFBS	= au08DIFFormatI2S[ s32Prm2 - YAVP2MWG_DIFFORMAT_I2S1 ];
		for ( i = 0; i < YAVP2MW_DIFFORMAT_BSSIZE; i++ )
		{
			pu08BS[ i ]= pu08DIFBS[ i ];
		}
		break;
	case YAVP2MWG_DIFFORMAT_PCM1 :
	case YAVP2MWG_DIFFORMAT_PCM2 :
	case YAVP2MWG_DIFFORMAT_PCM3 :
	case YAVP2MWG_DIFFORMAT_PCM4 :
		pu08DIFBS	= au08DIFFormatPCM[ s32Prm2 - YAVP2MWG_DIFFORMAT_PCM1 ];
		for ( i = 0; i < YAVP2MW_DIFFORMAT_BSSIZE; i++ )
		{
			pu08BS[ i ]= pu08DIFBS[ i ];
		}
		break;
	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	pu08BS	+= YAVP2MW_DIFFORMAT_BSSIZE;
	u32Size	=  sizeof( au08TestSource );
	for ( i = 0; i < u32Size; i++ )
	{
		pu08BS[ i ]= au08TestSource[ i ];
	}
	switch ( s32Prm1 )
	{
	case YAVP2MWG_TESTSOURCE_NONE :
		pu08BS[ YAVP2MW_TESTSOURCE_BS_SINESTART ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF0VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF2VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_DIFI1VOL ]	= 0x00;
		break;
	case YAVP2MWG_TESTSOURCE_SINE :
		pu08BS[ YAVP2MW_TESTSOURCE_BS_SINESTART ]	= 0x01;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF0VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF2VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_DIFI1VOL ]	= 0x00;
		break;
	case YAVP2MWG_TESTSOURCE_MIC12 :
		pu08BS[ YAVP2MW_TESTSOURCE_BS_SINESTART ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF0VOL ]	= 0x60;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF2VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_DIFI1VOL ]	= 0x00;
		break;
	case YAVP2MWG_TESTSOURCE_MIC3 :
		pu08BS[ YAVP2MW_TESTSOURCE_BS_SINESTART ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF0VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF2VOL ]	= 0x60;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_DIFI1VOL ]	= 0x00;
		break;
	case YAVP2MWG_TESTSOURCE_DIFI2 :
		pu08BS[ YAVP2MW_TESTSOURCE_BS_SINESTART ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF0VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_ADIF2VOL ]	= 0x00;
		pu08BS[ YAVP2MW_TESTSOURCE_BS_DIFI1VOL ]	= 0x60;
		break;
	default :
		s32Ret	= YAVP2mwG_ERROR;
		break;
	}

	if ( YAVP2mwG_SUCCESS	== s32Ret )
	{
		s32Ret	= YAVP2mwG_batch_process( gsInfo.au08BS, u32Size + YAVP2MW_DIFFORMAT_BSSIZE );
		if ( s32Ret	< YAD1DD_SUCCESS )
		{
			s32Ret	= YAVP2mwG_ERROR;
		}
		else
		{
			gsInfo.sTest.s08Source	=(S08)s32Prm1;
		}
	}

	return s32Ret;
}

/* public functions */
/*******************************************************************************
 *	YAVP2mwG_write_register
 *
 *	Function:
 *			write parameter.
 *	Argument:
 *			u08Page				page select
 *			u08Adr				address
 *			pu08Data			pointer to write data buffer
 *			u32Size				size of write data[byte]
 *	Return:
 *			YAD1DD_SUCCESS		success
 *			YAD1DD_ERROR_SPI	error(SPI)
 *			YAD1DD_ERROR_ARG	error(argument)
 *
 ******************************************************************************/
S32			YAVP2mwG_write_register
(
	U08			u08Page,
	U08			u08Adr,
	const U08 *	pu08Data,
	U32			u32Size
)
{
	return YAD1DD_Write( u08Page, u08Adr, pu08Data, u32Size );
}

/*******************************************************************************
 *	YAVP2mwG_read_register
 *
 *	Function:
 *			read parameter.
 *	Argument:
 *			u08Page				page select
 *			u08Adr				address
 *			pu08Data			pointer to write data buffer
 *			u32Size				size of write data[byte]
 *	Return:
 *			YAD1DD_SUCCESS		success
 *			YAD1DD_ERROR_SPI	error(SPI)
 *			YAD1DD_ERROR_ARG	error(argument)
 *
 ******************************************************************************/
S32			YAVP2mwG_read_register
(
	U08			u08Page,
	U08			u08Adr,
	U08 *		pu08Data,
	U32			u32Size
)
{
	return YAD1DD_Read( u08Page, u08Adr, pu08Data, u32Size );
}

/*******************************************************************************
 *	YAVP2mwG_batch_process
 *
 *	Function:
 *			execute batch script.
 *	Argument:
 *			pu08BS				pointer to batch script buffer
 *			u32Size				size of batch script data[byte]
 *	Return:
 *			YAD1DD_SUCCESS		success
 *			YAD1DD_ERROR_SPI	error(SPI)
 *			YAD1DD_ERROR_ARG	error(argument)
 *			YAD1DD_ERROR_SYN	error(batch script format)
 *			YAD1DD_ERROR_TO		error(time out)
 *
 ******************************************************************************/
S32			YAVP2mwG_batch_process
(
	const U08 *	pu08BS,
	U32			u32Size
)
{
	return YAD1DD_BatchProcess( pu08BS, u32Size );
}

/*******************************************************************************
 *	YAVP2mwG_set_param
 *
 *	Function:
 *			set parameter.
 *	Argument:
 *			s32Func				Function ID
 *			s32Prm1				Parameter 1
 *			s32Prm2				Parameter 2
 *	Return:
 *			YAVP2mwG_SUCCESS	success
 *			YAVP2mwG_ERROR		error
 *
 ******************************************************************************/
S32			YAVP2mwG_set_param
(
	S32		s32Func,
	S32		s32Prm1,
	S32		s32Prm2
)
{
	S32			s32Ret;

	s32Ret	= YAVP2mwG_ERROR;

	switch ( s32Func )
	{
	case YAVP2MWG_INITIALISE :
		s32Ret	= yavp2mwg_init( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_BEEP_VOLUME :
		s32Ret	= yavp2mwg_beep_vol( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_FUNCTION_SELECT :
		s32Ret	= yavp2mwg_funcsel( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_AUDIO_VOLUME :
		s32Ret	= yavp2mwg_audio_vol( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_AUDIO_INPUT_VOLUME :
		s32Ret	= yavp2mwg_audio_input_vol( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_AUDIO_BALANCE :
		s32Ret	= yavp2mwg_audio_balance( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_AUDIO_FADER :
		s32Ret	= yavp2mwg_audio_fader( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_AUDIO_GEQ1 :
		s32Ret	= yavp2mwg_audio_geq( s32Prm1, s32Prm2, 0 );
		break;

	case YAVP2MWG_AUDIO_GEQ2 :
		s32Ret	= yavp2mwg_audio_geq( s32Prm1, s32Prm2, 1 );
		break;

	case YAVP2MWG_AUDIO_TEST :
		s32Ret	= yavp2mwg_audio_test( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_MIC_RECEIVE_VOLUME :
		s32Ret	= yavp2mwg_mic_receive_vol( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_MIC_INPUT_VOLUME :
		s32Ret	= yavp2mwg_mic_input_vol( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_TEST_VOLUME_F :
		s32Ret	= yavp2mwg_test_volume_F( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_TEST_VOLUME_R :
		s32Ret	= yavp2mwg_test_volume_R( s32Prm1, s32Prm2 );
		break;

	case YAVP2MWG_TEST_SOURCE :
		s32Ret	= yavp2mwg_test_source( s32Prm1, s32Prm2 );
		break;

	default :
		break;
	}

	return s32Ret;
}
