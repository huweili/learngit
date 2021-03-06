/*
 *  Batch Script for Yamaha AudioEngine Device version 1
 *
 *    Tool name     : YAD-1 Batch Script Maker
 *    Tool version  : 1.4.2
 *    Creation date : 2016/04/18/ 15:49:57
 */


/*
	[Init]
		Device Init
 */
static const U08 au08InitA[]={
	0x6f, 0x08, 0x00, 0x01, 0x6f, 0x09, 0x00, 0x04, 0x6f, 0x0a, 0x00, 0x02, 0x6f, 0x0b, 0x00, 0x02, 
	0x19, 0x39, 0x40, 0x40, 0x0a, 0x01, 0x02, 0x01, 0x0a, 0x01, 0x01, 0x09, 0x01, 0x01, 0x09, 0x01, 
	0x00, 0x09, 0x0a, 0x15, 0x09, 0x0f, 0xc0, 0x09, 0x2f, 0xf8, 0x09, 0x78, 0x80, 0x09, 0x69, 0x03, 
	0x09, 0x74, 0x0a, 0x09, 0x75, 0x0a, 0x09, 0x3e, 0x20, 0x09, 0x02, 0x13, 0x19, 0x39, 0x08, 0x08, 
	0x0a, 0x09, 0x02, 0x03, 0x19, 0x39, 0x10, 0x10, 0x0a, 0x09, 0x37, 0x41, 0x19, 0x39, 0x80, 0x80, 
	0x32, 0x09, 0x02, 0x02, 0x0a, 0x01, 0x01, 0x0a, 0x01, 0x00, 0x01, 0x02, 0x01, 0x01, 0x02, 0x00, 
	0x1f, 0x02, 0x09, 0x3e, 0x00, 0x02, 0x0d, 0x01, 0x02, 0x0e, 0x02, 0x02, 0x0f, 0x03, 0x02, 0x10, 
	0x03, 0x02, 0x09, 0xa2, 0x02, 0x0a, 0x00, 0x02, 0x0b, 0x02, 0x02, 0x04, 0x2b, 0x02, 0x05, 0x3f, 
	0x02, 0x08, 0x00, 0x02, 0x06, 0x3f, 0x02, 0x11, 0x00, 0x02, 0x18, 0x05, 0x02, 0x19, 0x0d, 0x02, 
	0x1a, 0x00, 0x02, 0x1b, 0x4e, 0x02, 0x1c, 0x00, 0x02, 0x1d, 0x00, 0x02, 0x1e, 0x02, 0x02, 0x13, 
	0x10, 0x02, 0x12, 0x04, 0x02, 0x01, 0x06, 0x0a, 0x04, 0x03, 0x1f, 0x02, 0x02, 0x02, 0x7f, 0x1f, 
	0x02, 0x02, 0x02, 0x7e, 0x02, 0x02, 0x3e, 0x01, 0x03, 0xbf, 0x11, 0x03, 0x40, 0x00, 0x0a, 0x01, 
	0x03, 0xbb, 0x01, 0x03, 0x9b, 0x11, 0x03, 0x20, 0x00, 0x0a, 0x01, 0x03, 0x99, 0x02, 0x02, 0x1e, 
	0x02, 0x02, 0x0e, 0x02, 0x02, 0x06, 0x02, 0x02, 0x02, 0x0a, 0x02, 0x00, 0x89, 0x03, 0x0d, 0x00, 
	0x00, 0x09, 0x18, 0x00, 0x09, 0x29, 0xfc, 0x09, 0x2c, 0xf0, 0x09, 0x06, 0x0f, 0x09, 0x07, 0x80, 
	0x09, 0x37, 0x40, 0x0a, 0x28, 0x00, 0x09, 0x3a, 0x10, 0x07, 0x00, 0x01, 0x07, 0x00, 0x00, 0x07, 
	0x02, 0x53, 0x07, 0x17, 0x50, 0x07, 0x18, 0x50, 0x09, 0x15, 0x05, 0x07, 0x25, 0x02, 0x07, 0x26, 
	0x00, 0x09, 0x13, 0x03, 0x07, 0x04, 0x30, 0x07, 0x63, 0x9f, 0x09, 0x73, 0x8a, 0x07, 0x01, 0x42, 
	0x1a, 0x31, 0x08, 0x08, 0x64, 0x0a, 0x31, 0x08, 0x07, 0x02, 0xf3, 0x09, 0x15, 0x85, 0x03, 0x44, 
	0x72, 0x03, 0x43, 0x81, 0x03, 0x47, 0x80, 0x04, 0x55, 0xa0, 0x1f, 0x4b, 
};


/*
	[B-DSP setup]
		B-DSP coef download
 */
static const U08 au08InitB[]={
	0x6f, 0x08, 0x00, 0x01, 0x6f, 0x09, 0x00, 0x04, 0x6f, 0x0a, 0x00, 0x02, 0x6f, 0x0b, 0x00, 0x02, 
	0x05, 0x00, 0x00, 0x85, 0x04, 0x40, 0x9b, 0x10, 0x00, 0x01, 0x12, 0x00, 0x01, 0x13, 0x00, 0x01, 
	0x14, 0x00, 0x01, 0x15, 0x01, 0x81, 0x05, 0x16, 0xf8, 0x44, 0x41, 0x78, 0x81, 0x05, 0x16, 0xf8, 
	0x44, 0x41, 0x78, 0x01, 0x12, 0x00, 0x01, 0x13, 0x01, 0x01, 0x14, 0xd9, 0x01, 0x15, 0x01, 0x81, 
	0x75, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 
	0x55, 0x55, 0x00, 0x04, 0x1b, 0x4e, 0x00, 0x04, 0x8b, 0x43, 0x00, 0x05, 0x04, 0xc7, 0x00, 0x06, 
	0x72, 0xb0, 0x00, 0x07, 0x20, 0x15, 0x00, 0x07, 0xe0, 0x98, 0x00, 0x08, 0xb5, 0x96, 0xff, 0x40, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0xf9, 0x44, 
	0x1f, 0xe9, 0x01, 0x59, 0x36, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x64, 0x80, 0x21, 0x00, 0xad, 
	0xcf, 0x33, 0xfd, 0x49, 0x96, 0x16, 0x01, 0x12, 0x00, 0x01, 0x13, 0x00, 0x01, 0x14, 0x02, 0x01, 
	0x15, 0x01, 0x81, 0x11, 0x16, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 0x13, 0x00, 0x01, 0x14, 0x06, 0x01, 0x15, 
	0x01, 0x81, 0x21, 0x16, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0xf8, 0x42, 0x9e, 0x0a, 0xf7, 0x42, 0x95, 0xa7, 0xf8, 0x42, 0x9e, 0x0a, 0x01, 0x7b, 0xb1, 0x96, 
	0x00, 0x87, 0x92, 0x6c, 0x01, 0x12, 0x00, 0x01, 0x13, 0x00, 0x01, 0x14, 0x0e, 0x01, 0x15, 0x01, 
	0x81, 0x82, 0x01, 0x16, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 
	0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
	0x01, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 
	0x00, 0x80, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 0x13, 0x00, 0x01, 0x14, 0x4e, 0x01, 0x15, 0x01, 
	0x81, 0x3d, 0x16, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 
	0x12, 0x00, 0x01, 0x13, 0x00, 0x01, 0x14, 0x5d, 0x01, 0x15, 0x01, 0x81, 0x83, 0x7d, 0x16, 0x01, 
	0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xf5, 
	0x61, 0x3b, 0xff, 0xf6, 0x61, 0x3b, 0xff, 0xf5, 0x61, 0x3b, 0xff, 0x01, 0x7b, 0x11, 0xd3, 0x00, 
	0x89, 0xab, 0xbc, 0x00, 0x59, 0x0c, 0xdc, 0x01, 0xa6, 0xf3, 0x24, 0x00, 0x59, 0x0c, 0xdc, 0x01, 
	0x55, 0x86, 0xe1, 0xff, 0x8d, 0xb4, 0x9f, 0xfb, 0x70, 0xbf, 0x79, 0xfc, 0x70, 0xbf, 0x79, 0xfb, 
	0x70, 0xbf, 0x79, 0x01, 0x55, 0x86, 0xe1, 0xff, 0x8d, 0xb4, 0x9f, 0x00, 0x7b, 0x1d, 0xfa, 0x01, 
	0x84, 0xe2, 0x06, 0x00, 0x7b, 0x1d, 0xfa, 0x01, 0x7b, 0x11, 0xd3, 0x00, 0x89, 0xab, 0xbc, 0x01, 
	0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x04, 0x40, 0x3f, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xdd, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x04, 0x40, 0x3f, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x7f, 0xff, 0xdd, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x81, 0x81, 0x79, 0x16, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x04, 0x40, 0x3f, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x7f, 0xff, 0xdd, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 0x13, 0x01, 0x01, 0x14, 0x1a, 
	0x01, 0x15, 0x01, 0x81, 0x81, 0x5d, 0x16, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x04, 
	0x40, 0x3f, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0xc0, 0x00, 0x7f, 0xf9, 0x2d, 0xf3, 
	0x6d, 0x37, 0x1d, 0xf3, 0x6d, 0x37, 0x1d, 0x00, 0x7f, 0xf9, 0x2d, 0x01, 0x40, 0x00, 0x00, 0xff, 
	0x56, 0x6b, 0x4e, 0xff, 0x56, 0x6b, 0x4e, 0x00, 0x4f, 0x61, 0x8e, 0x00, 0x7a, 0x37, 0x14, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 0x13, 0x01, 0x01, 0x14, 0x51, 0x01, 0x15, 0x01, 0x81, 
	0x3d, 0x16, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x12, 
	0x00, 0x01, 0x13, 0x01, 0x01, 0x14, 0x60, 0x01, 0x15, 0x01, 0x81, 0x11, 0x16, 0x01, 0x40, 0x00, 
	0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 
	0x01, 0x13, 0x01, 0x01, 0x14, 0x64, 0x01, 0x15, 0x01, 0x81, 0x11, 0x16, 0x01, 0x40, 0x00, 0x00, 
	0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 
	0x13, 0x01, 0x01, 0x14, 0x68, 0x01, 0x15, 0x01, 0x81, 0x41, 0x16, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 0x13, 
	0x01, 0x01, 0x14, 0x78, 0x01, 0x15, 0x01, 0x81, 0x5d, 0x16, 0x02, 0x7f, 0x64, 0xf0, 0x00, 0x40, 
	0x26, 0xe7, 0x00, 0x40, 0x26, 0xe7, 0x00, 0x7f, 0xff, 0x8b, 0xfe, 0x40, 0x26, 0xe7, 0xff, 0x40, 
	0x00, 0x00, 0x01, 0x5a, 0x67, 0x04, 0x00, 0x5a, 0x9d, 0xf8, 0xff, 0x40, 0x4d, 0xe6, 0x00, 0x7f, 
	0xe5, 0xc1, 0x00, 0x7f, 0xf9, 0xcb, 0x01, 0x40, 0x00, 0xd4, 0x01, 0x40, 0x0b, 0x62, 0xf3, 0x52, 
	0xe5, 0xb0, 0xf5, 0x41, 0x89, 0x37, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x7f, 0xff, 0x4c, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x7f, 0xe9, 0x41, 0xf8, 0x71, 0x94, 0x9a, 0x00, 0x7f, 0xd5, 0x2a, 0x00, 0x80, 
	0x2a, 0xd6, 0x00, 0x7f, 0xaa, 0x53, 0x01, 0x12, 0x00, 0x01, 0x13, 0x01, 0x01, 0x14, 0x8f, 0x01, 
	0x15, 0x01, 0x81, 0x81, 0x5d, 0x16, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x04, 0x40, 
	0x3f, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0xc0, 0x00, 0x7f, 0xf9, 0x2d, 0xf3, 0x6d, 
	0x37, 0x1d, 0xf3, 0x6d, 0x37, 0x1d, 0x00, 0x7f, 0xf9, 0x2d, 0x01, 0x40, 0x00, 0x00, 0xff, 0x56, 
	0x6b, 0x4e, 0xff, 0x56, 0x6b, 0x4e, 0x00, 0x4f, 0x61, 0x8e, 0x00, 0x7a, 0x37, 0x14, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 
	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 0x13, 0x01, 0x01, 0x14, 0xc6, 0x01, 0x15, 0x01, 0x81, 0x3d, 
	0x16, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x12, 0x00, 
	0x01, 0x13, 0x01, 0x01, 0x14, 0xd5, 0x01, 0x15, 0x01, 0x81, 0x11, 0x16, 0x01, 0x40, 0x00, 0x00, 
	0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x01, 0x12, 0x00, 0x01, 
	0x13, 0x01, 0x01, 0x14, 0xe6, 0x01, 0x15, 0x05, 0x61, 0x16, 0x0c, 0x61, 0x16, 0x0d, 0x61, 0x16, 
	0x0e, 0x61, 0x16, 0x0f, 0x01, 0x12, 0x00, 0x01, 0x13, 0x01, 0x01, 0x14, 0xe6, 0x01, 0x15, 0x01, 
	0x81, 0x05, 0x16, 0x80, 0x00, 0x00, 0x00, 
};


/*
	[Path]
		Set Signal Path
 */
static const U08 au08InitC[]={
	0x6f, 0x08, 0x00, 0x01, 0x6f, 0x09, 0x00, 0x04, 0x6f, 0x0a, 0x00, 0x02, 0x6f, 0x0b, 0x00, 0x02, 
	0x03, 0x23, 0x12, 0x03, 0x25, 0x20, 0x03, 0x27, 0x10, 0x03, 0x29, 0x40, 0x83, 0x03, 0x2b, 0x00, 
	0x00, 0x83, 0x03, 0x2f, 0x04, 0x00, 0x83, 0x03, 0x33, 0x00, 0x00, 0x83, 0x03, 0x37, 0x00, 0x00, 
	0x83, 0x03, 0x3b, 0x03, 0x01, 0x83, 0x03, 0x3f, 0x04, 0x00, 0x03, 0x20, 0x00, 0x03, 0x21, 0x00, 
	0x03, 0x22, 0x00, 0x89, 0x04, 0x30, 0x10, 0x20, 0x40, 0x09, 0x38, 0x80, 0x83, 0x06, 0x50, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x04, 0x00, 0x40, 0x04, 0x10, 0x40, 0x04, 0x20, 0x40, 0x04, 0x30, 0x00, 
	0x04, 0x01, 0x20, 0x04, 0x11, 0x20, 0x04, 0x21, 0x20, 0x04, 0x31, 0x20, 0x04, 0x02, 0x24, 0x04, 
	0x03, 0x02, 0x04, 0x13, 0x00, 0x04, 0x23, 0x00, 0x04, 0x33, 0x00, 0x04, 0x04, 0x24, 0x04, 0x05, 
	0x00, 0x04, 0x15, 0x00, 0x04, 0x25, 0x00, 0x04, 0x35, 0x00, 0x04, 0x06, 0x44, 0x04, 0x16, 0x44, 
	0x04, 0x26, 0x88, 0x04, 0x36, 0x88, 0x04, 0x07, 0x00, 0x04, 0x17, 0x00, 0x04, 0x27, 0x00, 0x04, 
	0x08, 0x80, 0x04, 0x18, 0x80, 0x04, 0x28, 0x80, 0x04, 0x09, 0x80, 0x04, 0x19, 0x80, 0x04, 0x29, 
	0x80, 0x84, 0x03, 0x2b, 0x00, 0x00, 0x87, 0x07, 0x47, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 
	0x08, 0x29, 0x01, 0x10, 0x01, 0x33, 0x01, 0x22, 0x00, 0x07, 0x30, 0x2a, 0x07, 0x03, 0x0f, 0x07, 
	0x12, 0x88, 0x87, 0x03, 0x15, 0x5b, 0x0c, 0x87, 0x04, 0x44, 0x0a, 0x0a, 0x0a, 0x07, 0x08, 0x05, 
	0x87, 0x08, 0x1c, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x02, 0x00, 0x87, 0x07, 0x32, 
	0x00, 0x00, 0x00, 0x68, 0x32, 0xd6, 0x87, 0x07, 0x38, 0x00, 0x00, 0x00, 0x68, 0x32, 0xd6, 0x87, 
	0x07, 0x3e, 0x00, 0x00, 0x00, 0x68, 0x32, 0xd6, 0x07, 0x31, 0x07, 0x07, 0x57, 0x00, 0x01, 0x22, 
	0x20, 0x01, 0x23, 0x00, 0x81, 0x04, 0x24, 0x29, 0x26, 0x10, 0x81, 0x04, 0x24, 0xb2, 0x43, 0xf0, 
	0x81, 0x04, 0x24, 0x0c, 0x5e, 0x07, 0x81, 0x04, 0x24, 0x4e, 0xbc, 0x0f, 0x81, 0x04, 0x24, 0xcb, 
	0x7b, 0xf8, 0x01, 0x22, 0x30, 0x01, 0x23, 0x00, 0x81, 0x04, 0x24, 0xd5, 0x17, 0x10, 0x81, 0x04, 
	0x24, 0x52, 0xbe, 0xf4, 0x81, 0x04, 0x24, 0x7b, 0xd3, 0xff, 0x81, 0x04, 0x24, 0xae, 0x41, 0x0b, 
	0x81, 0x04, 0x24, 0xaf, 0x14, 0x00, 0x01, 0x22, 0x00, 0x07, 0x09, 0x11, 

	0x08, 0x50, 0x01,	/* VOLUME Unmute */
	0x08, 0x52, 0x00,	/* SICC1 page0 */
	0x08, 0x54, 0x00,	/* SICC2 page0 */
	0x88, 0x08, 0x56,
				0x00,	/* offset */
				0x00,	/* volume */
				0x00,	/* balance-L */
				0x00,	/* balance-R */
				0x00,	/* fader-F */
				0x00,	/* fader-R */
				0x81,	/* Mute/Start */
	0x88, 0x08, 0x63,
				0x00,	/* offset */
				0x00,	/* volume */
				0x00,	/* balance-L */
				0x00,	/* balance-R */
				0x00,	/* fader-F */
				0x00,	/* fader-R */
				0x81,	/* Mute/Start */
};


/*
	[Start]
		Set Volume
 */
static const U08 au08InitD[]={
	0x6f, 0x08, 0x00, 0x01, 0x6f, 0x09, 0x00, 0x04, 0x6f, 0x0a, 0x00, 0x02, 0x6f, 0x0b, 0x00, 0x02, 
	0x02, 0x04, 0x2b, 
	0x02, 0x05, 0x01, 
	0x02, 0x06, 0x01, 
	0x04, 0x0a, 0x0c, 
	0x04, 0x1a, 0x00, 
	0x04, 0x2a, 0x30, 
	0x04, 0x3a, 0x0a, 
	0x04, 0x2c, 0x00, 
	0x07, 0x48, 0x08, 
	0x89, 0x05, 0x1b, 0x21, 0x21, 0x21, 0x21, 
	0x89, 0x03, 0x19, 0x80, 0x00, 
	0x03, 0x06, 0x00, 
	0x03, 0x08, 0x00, 
	0x03, 0x0a, 0x00, 
	0x03, 0x0c, 0x00, 
	0x83, 0x03, 0x0e, 0x00, 0x00, 
	0x83, 0x03, 0x10, 0x00, 0x00, 
	0x83, 0x03, 0x12, 0x00, 0x00, 
	0x08, 0x20, 0x01, 
	0x05, 0x00, 0x01, 
	0x03, 0x14, 0x00, 
	0x03, 0x16, 0x00, 
	0x03, 0x18, 0x00, 
	0x03, 0x1a, 0x00, 
	0x03, 0x1c, 0x60, 
	0x03, 0x1e, 0x00, 
	0x89, 0x03, 0x24, 0xef, 0x6f, 
	0x89, 0x03, 0x26, 0xef, 0x6f, 
	0x1f, 0x0a, 
	0x09, 0x3a, 0x00, 
};
