
#ifndef ARM_MT9D111_H
#define ARM_MT9D111_H


#include "stdint.h"
#include "ARM_SSDV.h"


#define GO_TO_STANDBY									// comment out to disable


#define SSDV_CALLSIGN "TT7S"							// max. 6 characters
#define MT9D111_BUFFER_SIZE 45000
extern uint8_t JPEGbuffer[MT9D111_BUFFER_SIZE];


/*
	How many SSDV packets in between two telemetry strings?
*/
#define TELEMETRY_EVERY_X_PACKETS 3


/*
	The SSDV algorithm requires the JPEG image dimensions to be a multiple of 16.
	Potential resolutions with aspect ratio 1.33333.
		X		Y				X		Y				X		Y
		64		48				704		528				1344	1008
		128		96				768		576				1408	1056
		192		144				832		624				1472	1104
		256		192				896		672				1536	1152
		320		240				960		720				1600	1200
		384		288				1024	768
		448		336				1088	816
		512		384				1152	864
		576		432				1216	912
		640		480				1280	960
	
	The quality factor should be chosen with the size of the SRAM buffer in mind.
	The SSDV algorithm uses fixed quantization tables corresponding to quality factor of 50 (Qscale 32).
	
	Qscale = 16 * (100 - quality) / 25			for quality >= 50
	Qscale = 1600 / quality						for quality < 50
	
	Quality		Qscale			Quality		Qscale	
	100			0				55			29
	95			3				50			32
	90			6				45			36
	85			10				40			40
	80			13				35			46
	75			16				30			53
	70			19				25			64
	65			22				20			80
	60			26				15			107
*/
#define RES_X 320
#define RES_Y 240

#define QSCALE_1 32
#define QSCALE_2 64
#define QSCALE_3 123

#define NUM_IMAGES 1


/*
	CONFIGURATION and HANDSHAKING
		Bit 0		If 1, video; if 0, still snapshot.
		Bit 1		Enable handshaking with host at every error frame.
		Bit 2		Enable retry after an unsuccessful encode or transfer.
		Bit 3		Host indicates it is ready for next frame.
		Bit 4		Enable scaled quantization table generation.
		Bit 5		Enable auto-select quantization table.
		Bit 6:7		Quantization table ID.
*/
#define JPEG_CONFIGURATION 0b00111010


/*
	COLOR FORMAT
		0	YCBCR422
		1	YCBCR420
		2	MONOCHROME
		
	GAMMA
		0	1.0
		1	0.56
		2	0.45 (default)
		3	user-defined gamma table
	
	CONTRAST
		0	slope 100%
		1	slope 125%
		2	slope 150%
		3	slope 175%
		4	noise-reduction contrast (default)
*/
#define JPEG_COLOR_FORMAT 0
#define JPEG_GAMMA 2
#define JPEG_CONTRAST 4

#define FORMAT_YCBCR422 0
#define FORMAT_YCBCR420 1
#define FORMAT_MONOCHROME 2


/*
	JPEG DRIVERS
		Bit 0		Auto exposure
		Bit 1		Flicker detection
		Bit 2		Auto white balance
		Bit 3		Histogram
		Bit 4		Auto focus
		Bit 5		force outdoor white balance
		Bit 6:7		improved Auto focus
*/
#define JPEG_DRIVERS 0b00000001
#define JPEG_RESTART_INTERVAL 0


/*
	READ MODE B (0x20 page 0)
		Bit 15		enable binning
		Bit 13		enable zoom
		Bits 12:11	00 - zoom 2x	01 - zoom 4x	10 - zoom 8x	11 - zoom 16x
		Bit 10		use 1 ADC instead of 2
		Bit 9		enable and show border
		Bit 8		add 4-pixel border
		Bit 7		enable column skip
		Bits 6:5	00 - column skip 2x		01 - column skip 4x		10 - column skip 8x		11 - column skip 16x
		Bit 4		enable row skip
		Bits 3:2	00 - row skip 2x		01 - row skip 4x		10 - row skip 8x		11 - row skip 16x
		Bit 1		mirror columns
		Bit 0		mirror rows
*/
#define READ_MODE_B 0b0000000000000000


/*
	OUTPUT CONFIGURATION (0x0D page 2)
		Bit 11		freeze update
		Bit 10		enable spoof ITU-R BT.601 codes
		Bit	9		enable JPEG status insertion
		Bit 8		duplicate FRAME_VALID on LINE_VALID
		Bit 7		swaps the even and odd bytes in JPEG data stream
		Bit 6		enable variable pixel clock rate
		Bit 5		ignore spoof frame height
		Bit 4		insert SOI and EOI when FRAME_VALID is HIGH
		Bit 3		enable SOI/EOI insertion
		Bit 2		enable pixel clock during invalid data
		Bit 1		enable output pixel clock between frames
		Bit 0		enable spoof frame
*/
#define OUTPUT_CONFIGURATION 0b0000000000000000


/*
	REGISTER WRITE
		MT9D111_register_write(WRITE_PAGE, page);
		MT9D111_register_write(address, data);

	REGISTER READ
		MT9D111_register_write(WRITE_PAGE, page);
		MT9D111_register_read(address);

	VARIABLE WRITE
		MT9D111_register_write(WRITE_PAGE, 1);
		MT9D111_variable_write(driverID, offset, size, val);

	VARIABLE READ
		MT9D111_register_write(WRITE_PAGE, 1);
		MT9D111_variable_read(driverID, offset, size);
	
	PAGE
		0/1/2
	
	STATE_TIMEOUT
		timeout = x * 0.025
		10s = 400 * 25ms
*/
#define DEVICE_ADDRESS 0x48
#define WRITE_PAGE 0xF0
#define WRITE_VAR 0xC6
#define READ_VAR 0xC8
#define WAIT_FOR_STATE_TIMEOUT 200


/*
	A set of buffers for individual image processing steps.
*/
extern uint8_t img_id;
extern uint8_t img[64];
extern uint8_t pkt[SSDV_PKT_SIZE];


/*
	JPEG settings variables.
*/
extern uint32_t res_x;
extern uint32_t res_y;
extern uint8_t qscale_1;
extern uint8_t qscale_2;
extern uint8_t qscale_3;
extern uint8_t jpeg_gamma;
extern uint8_t jpeg_contrast;
extern uint8_t jpeg_drivers;

extern uint32_t packetsPerTelem;


/*
	A collection of basic Quantization, ZigZag and Huffman tables.
*/
static uint8_t JPEG_StdQuantTblY[64] = {
	16,  11,  10,  16,  24,  40,  51,  61,	12,  12,  14,  19,  26,  58,  60,  55,
	14,  13,  16,  24,  40,  57,  69,  56,	14,  17,  22,  29,  51,  87,  80,  62,
	18,  22,  37,  56,  68,  109, 103, 77,	24,  35,  55,  64,  81,  104, 113, 92,
	49,  64,  78,  87, 103,  121, 120, 101,	72,  92,  95,  98, 112,  100, 103,  99
};

static uint8_t JPEG_StdQuantTblC[64] = {
	17,  18,  24,  47,  99,  99,  99,  99,	18,  21,  26,  66,  99,  99,  99,  99,
	24,  26,  56,  99,  99,  99,  99,  99,	47,  66,  99,  99,  99,  99,  99,  99,
	99,  99,  99,  99,  99,  99,  99,  99,	99,  99,  99,  99,  99,  99,  99,  99,
	99,  99,  99,  99,  99,  99,  99,  99,	99,  99,  99,  99,  99,  99,  99,  99
};

static uint8_t zigzag[64] = {
	0,	1,	5,	6,	14,	15,	27,	28,	2,	4,	7,	13,	16,	26,	29,	42,	3,	8,	12,	17,	25,	30,	41,	43,	9,	11,	18,	24,	31,	40,	44,	53,
	10,	19,	23,	32,	39,	45,	52,	54,	20,	22,	33,	38,	46,	51,	55,	60,	21,	34,	37,	47,	50,	56,	59,	61,	35,	36,	48,	49,	57,	58,	62,	63
};

static uint32_t JPEG_StdHuffmanTbl[384] = {
	0x100, 0x101, 0x204, 0x30b, 0x41a, 0x678, 0x7f8, 0x9f6,	0xf82, 0xf83, 0x30c, 0x41b, 0x679, 0x8f6, 0xaf6, 0xf84,
	0xf85, 0xf86, 0xf87, 0xf88, 0x41c, 0x7f9, 0x9f7, 0xbf4,	0xf89, 0xf8a, 0xf8b, 0xf8c, 0xf8d, 0xf8e, 0x53a, 0x8f7,
	0xbf5, 0xf8f, 0xf90, 0xf91, 0xf92, 0xf93, 0xf94, 0xf95,	0x53b, 0x9f8, 0xf96, 0xf97, 0xf98, 0xf99, 0xf9a, 0xf9b,
	0xf9c, 0xf9d, 0x67a, 0xaf7, 0xf9e, 0xf9f, 0xfa0, 0xfa1,	0xfa2, 0xfa3, 0xfa4, 0xfa5, 0x67b, 0xbf6, 0xfa6, 0xfa7,
	0xfa8, 0xfa9, 0xfaa, 0xfab, 0xfac, 0xfad, 0x7fa, 0xbf7,	0xfae, 0xfaf, 0xfb0, 0xfb1, 0xfb2, 0xfb3, 0xfb4, 0xfb5,
	0x8f8, 0xec0, 0xfb6, 0xfb7, 0xfb8, 0xfb9, 0xfba, 0xfbb,	0xfbc, 0xfbd, 0x8f9, 0xfbe, 0xfbf, 0xfc0, 0xfc1, 0xfc2,
	0xfc3, 0xfc4, 0xfc5, 0xfc6, 0x8fa, 0xfc7, 0xfc8, 0xfc9,	0xfca, 0xfcb, 0xfcc, 0xfcd, 0xfce, 0xfcf, 0x9f9, 0xfd0,
	0xfd1, 0xfd2, 0xfd3, 0xfd4, 0xfd5, 0xfd6, 0xfd7, 0xfd8,	0x9fa, 0xfd9, 0xfda, 0xfdb, 0xfdc, 0xfdd, 0xfde, 0xfdf,
	0xfe0, 0xfe1, 0xaf8, 0xfe2, 0xfe3, 0xfe4, 0xfe5, 0xfe6,	0xfe7, 0xfe8, 0xfe9, 0xfea, 0xfeb, 0xfec, 0xfed, 0xfee,
	0xfef, 0xff0, 0xff1, 0xff2, 0xff3, 0xff4, 0xff5, 0xff6,	0xff7, 0xff8, 0xff9, 0xffa, 0xffb, 0xffc, 0xffd, 0xffe,
	0x30a, 0xaf9, 0xfff, 0xfff, 0xfff, 0xfff, 0xfff, 0xfff,	0xfd0, 0xfd1, 0xfd2, 0xfd3, 0xfd4, 0xfd5, 0xfd6, 0xfd7,
	0x101, 0x204, 0x30a, 0x418, 0x419, 0x538, 0x678, 0x8f4,	0x9f6, 0xbf4, 0x30b, 0x539, 0x7f6, 0x8f5, 0xaf6, 0xbf5,
	0xf88, 0xf89, 0xf8a, 0xf8b, 0x41a, 0x7f7, 0x9f7, 0xbf6,	0xec2, 0xf8c, 0xf8d, 0xf8e, 0xf8f, 0xf90, 0x41b, 0x7f8,
	0x9f8, 0xbf7, 0xf91, 0xf92, 0xf93, 0xf94, 0xf95, 0xf96,	0x53a, 0x8f6, 0xf97, 0xf98, 0xf99, 0xf9a, 0xf9b, 0xf9c,
	0xf9d, 0xf9e, 0x53b, 0x9f9, 0xf9f, 0xfa0, 0xfa1, 0xfa2,	0xfa3, 0xfa4, 0xfa5, 0xfa6, 0x679, 0xaf7, 0xfa7, 0xfa8,
	0xfa9, 0xfaa, 0xfab, 0xfac, 0xfad, 0xfae, 0x67a, 0xaf8,	0xfaf, 0xfb0, 0xfb1, 0xfb2, 0xfb3, 0xfb4, 0xfb5, 0xfb6,
	0x7f9, 0xfb7, 0xfb8, 0xfb9, 0xfba, 0xfbb, 0xfbc, 0xfbd,	0xfbe, 0xfbf, 0x8f7, 0xfc0, 0xfc1, 0xfc2, 0xfc3, 0xfc4,
	0xfc5, 0xfc6, 0xfc7, 0xfc8, 0x8f8, 0xfc9, 0xfca, 0xfcb,	0xfcc, 0xfcd, 0xfce, 0xfcf, 0xfd0, 0xfd1, 0x8f9, 0xfd2,
	0xfd3, 0xfd4, 0xfd5, 0xfd6, 0xfd7, 0xfd8, 0xfd9, 0xfda,	0x8fa, 0xfdb, 0xfdc, 0xfdd, 0xfde, 0xfdf, 0xfe0, 0xfe1,
	0xfe2, 0xfe3, 0xaf9, 0xfe4, 0xfe5, 0xfe6, 0xfe7, 0xfe8,	0xfe9, 0xfea, 0xfeb, 0xfec, 0xde0, 0xfed, 0xfee, 0xfef,
	0xff0, 0xff1, 0xff2, 0xff3, 0xff4, 0xff5, 0xec3, 0xff6,	0xff7, 0xff8, 0xff9, 0xffa, 0xffb, 0xffc, 0xffd, 0xffe,
	0x100, 0x9fa, 0xfff, 0xfff, 0xfff, 0xfff, 0xfff, 0xfff,	0xfd0, 0xfd1, 0xfd2, 0xfd3, 0xfd4, 0xfd5, 0xfd6, 0xfd7,
	0x100, 0x202, 0x203, 0x204, 0x205, 0x206, 0x30e, 0x41e,	0x53e, 0x67e, 0x7fe, 0x8fe, 0xfff, 0xfff, 0xfff, 0xfff,
	0x100, 0x101, 0x102, 0x206, 0x30e, 0x41e, 0x53e, 0x67e,	0x7fe, 0x8fe, 0x9fe, 0xafe, 0xfff, 0xfff, 0xfff, 0xfff
};


// Functions
uint8_t MT9D111_test_write(uint8_t address, uint16_t data);
void MT9D111_register_write(uint8_t address, uint16_t data);
uint16_t MT9D111_register_read(uint8_t address);
void MT9D111_variable_write(uint8_t driverID, uint8_t offset, uint8_t size, uint16_t val);
uint16_t MT9D111_variable_read(uint8_t driverID, uint8_t offset, uint8_t size);
void MT9D111_init(void);
void MT9D111_deinit(void);
uint32_t MT9D111_wait_for_state(uint8_t state);
uint32_t MT9D111_get_state(void);
void MT9D111_reset(void);
void MT9D111_execute_command(uint8_t cmd);
void MT9D111_standby(void);
void MT9D111_exit_standby(void);
uint32_t MT9D111_get_mode(void);
void MT9D111_preview_mode(void);
void MT9D111_capture_mode(void);
void MT9D111_refresh(void);
void MT9D111_refresh_mode(void);
uint32_t MT9D111_get_version(void);
void MT9D111_mode_1(void);
void MT9D111_mode_2(void);
uint32_t MT9D111_get_image(void);


// JPEG HEADER Functions
uint32_t JfifApp0Marker(uint8_t *pbuf);
uint32_t FrameHeaderMarker(uint8_t *pbuf, uint32_t width, uint32_t height, uint8_t format);
uint32_t ScanHeaderMarker(uint8_t *pbuf, uint8_t format);
uint32_t DefineQuantizationTableMarker(uint8_t *pbuf, uint32_t qscale, uint8_t format);
uint32_t DefineHuffmanTableMarkerDC(uint8_t *pbuf, uint32_t *htable, uint8_t class_id);
uint32_t DefineHuffmanTableMarkerAC(uint8_t *pbuf, uint32_t *htable, uint8_t class_id);
uint32_t DefineRestartIntervalMarker(uint8_t *pbuf, uint8_t ri);
uint32_t CreateJpegHeader(uint8_t *header, uint32_t width, uint32_t height, uint8_t format, uint8_t restart_int, uint32_t qscale);


#endif // ARM_MT9D111_H