/****************************************************************************
 *                                                                          *
 * Filename: crutil.c                                                       *
 *																    		*
 * Author: Matt Runyon	(AES implementation (incomplete) from Brad Conte)   *					
 *                                                                          *
 * Purpose : Crypto Library implementation file			                    *
 *                                                                          *
 * Last Upated : 02-14-17		 							 		    	*
 *																    		*
 * Notes: Letter frequency weights determined by stats found here:			*
 *	      https://en.wikipedia.org/wiki/Letter_frequency 	                *
 *                                                                          *
 *        Average English word length determined by study here:             *
 *        https://arxiv.org/ftp/arxiv/papers/1208/1208.6109.pdf             *
 *																			*
 *        Common Letter weights:						                    *
 *                                                                          *                               
 *		E = 12.702%/2.758% = 4.606											*
 *		T = 9.056%/2.758% = 3.284                                           *
 *		A = 8.167%/2.758% = 2.961                                           *
 *		O = 7.507%/2.758% = 2.722                                           *
 *		I = 6.966%/2.758% = 2.526                                           *
 *		N = 6.749%/2.758% = 2.447                                           *
 *		S = 6.327%/2.758% = 2.294                                           *
 *		H = 6.094%/2.758% = 2.209                                           *
 *		R = 5.987%/2.758% = 2.171                                           *
 *		D = 4.253%/2.758% = 1.542                                           *
 *		L = 4.025%/2.758% = 1.459                                           *
 *		U = 2.758%%/2.758% = 1                                              *
 *                                                                          *
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define uchar unsigned char // 8-bit byte
#define uint unsigned long // 32-bit word

/***************************************************************
*															   *
*			// GLOBAL VARIABLES //							   *
*															   *
****************************************************************/

const double meanWordLength = 5.1;

char allLetters[52] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F','f', 'G', 'g', 'H', 'h',
						'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p',
						'Q', 'q', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x',
						'Y', 'y', 'Z', 'z'};

double allLetterStats[52] = {0.08167, 0.08167, 0.01492, 0.01492, 0.02782, 0.02782, 0.04253, 0.04253,
							 0.12702, 0.12702, 0.0228, 0.0228, 0.02015, 0.02015, 0.06094, 0.06094,
							 0.06966, 0.06966, 0.00153, 0.00153, 0.00772, 0.00772, 0.04025, 0.04025,
							 0.02406, 0.02406, 0.06749, 0.06749, 0.07507, 0.07507, 0.01929, 0.01929,
							 0.0095, 0.0095, 0.05987, 0.05987, 0.06327, 0.06327, 0.09056, 0.09056,
							 0.02758, 0.02758, 0.00978, 0.00978, 0.02360, 0.02360, 0.0015, 0.0015,
							 0.01974,0.01974, 0.0074, 0.0074};

double allLetterStats_short[26] = {0.08167, 0.01492, 0.02782, 0.04253,0.12702, 0.0228, 0.02015, 0.06094,
							 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507,0.01929,
							 0.0095, 0.05987, 0.06327,0.09056, 0.02758, 0.00978,0.02360, 0.0015,
							 0.01974, 0.0074};

char commonLetters[25] = {'E', 'e', 'T', 't', 'A', 'a', 'O', 'o', 'I', 'i', 'N', 'n',
						  'S', 's', 'H', 'h', 'R', 'r', 'D', 'd', 'L', 'l','U', 'u'};

double commonLetterWeight[25] = {4.606, 4.606, 3.284, 3.284, 2.961, 2.961, 2.722, 2.722,
								 2.526, 2.526, 2.447, 2.447, 2.294, 2.294, 2.209, 2.209,
								 2.171, 2.171, 1.542, 1.542, 1.459, 1.459, 1.000, 1.000};

double commonLetterStats[25] = {0.12702, 0.12702, 0.09056, 0.09056, 0.08167, 0.08167, 0.07507, 0.07507,
								 0.06966, 0.06966, 0.06749, 0.06749, 0.06327, 0.06327, 0.06094, 0.06094,
								 0.05987, 0.05987, 0.04253, 0.04253, 0.04025, 0.04025, 0.02758, 0.02758};

char nonAlphaNumericChars[9] = {'#', '*', '@', '[', '\\', ']', '^', '_', '`'};
char nonAlphaNumericChars_v2[15] = {'#', '*', '@', '[', '\\', ']', '^', '_', '`', '%', '$','&','+','=','~'};

char bin8_table[97][9] =  {"00001011","00001101","00100000","00100001","00100010","00100011",
						   "00100100","00100101","00100110","00100111","00101000","00101001",
						   "00101010","00101011","00101100","00101101","00101110","00101111",
						   "00110000","00110001","00110010","00110011","00110100","00110101",
						   "00110110","00110111","00111000","00111001","00111010","00111011",
						   "00111100","00111101","00111110","00111111","01000000","01000001",
						   "01000010","01000011","01000100","01000101","01000110","01000111",
						   "01001000","01001001","01001010","01001011","01001100","01001101",
						   "01001110","01001111","01010000","01010001","01010010","01010011",
						   "01010100","01010101","01010110","01010111","01011000","01011001",
						   "01011010","01011011","01011100","01011101","01011110","01011111",
						   "01100000","01100001","01100010","01100011","01100100","01100101",
						   "01100110","01100111","01101000","01101001","01101010","01101011",
						   "01101100","01101101","01101110","01101111","01110000","01110001",
						   "01110010","01110011","01110100","01110101","01110110","01110111",
						   "01111000","01111001","01111010","01111011","01111100","01111101",
						   "01111110"};

char bin6_table[65][7] =   {"000000", "000001", "000010", "000011", "000100",
					   		"000101","000110", "000111", "001000", "001001",
					   		"001010", "001011", "001100", "001101", "001110",
					   		"001111", "010000", "010001", "010010", "010011",
							"010100", "010101", "010110", "010111", "011000",
							"011001", "011010", "011011", "011100", "011101",
							"011110", "011111", "100000", "100001", "100010",
							"100011", "100100", "100101", "100110", "100111",
							"101000", "101001", "101010", "101011", "101100",
							"101101", "101110", "101111", "110000", "110001",
							"110010", "110011", "110100", "110101", "110110",
							"110111", "111000", "111001", "111010", "111011",
							"111100", "111101", "111110", "111111", "000000"};

char bin4_table[16][5] = {"0000", "0001", "0010", "0011", "0100",
					   		"0101","0110", "0111", "1000", "1001",
					   		"1010", "1011", "1100", "1101", "1110",
					   		"1111"};

char base64_table[65] =      {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                            'w', 'x', 'y', 'z', '0', '1', '2', '3',
                            '4', '5', '6', '7', '8', '9', '+', '/','='};

char hex_table[17] = {'0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char hex2_table[97][3] = {"0A", "0D", "20", "21", "22", "23", "24", "25", "26", "27",
						  "28", "29", "2A", "2B", "2C", "2D", "2E", "2F", "30",
						  "31", "32", "33", "34", "35", "36", "37", "38",
						  "39", "3A","3B", "3C", "3D", "3E", "3F","40",
						  "41", "42", "43", "44", "45", "46", "47", "48",
						  "49", "4A","4B", "4C", "4D", "4E", "4F","50",
						  "51", "52", "53", "54", "55", "56", "57", "58",
						  "59", "5A","5B", "5C", "5D", "5E", "5F","60",
						  "61", "62", "63", "64", "65", "66", "67", "68",
						  "69", "6A","6B", "6C", "6D", "6E", "6F","70",
						  "71", "72", "73", "74", "75", "76", "77", "78",
						  "79", "7A","7B", "7C", "7D", "7E"};



char prascii_table[97] =   {'\n','\r',' ', '!', '"', '#', '$', '%%', '&', '\'', '(',')','*','+',',','-','.','/',
						 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
						 '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
						 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
						 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o' ,'p' ,'q', 'r', 's', 't', 'u',
						 'v', 'w', 'x', 'y', 'z', '{','|','}','~'};

// This is the specified AES SBox. To look up a substitution value, put the first
// nibble in the first index (row) and the second nibble in the second index (column).
const uchar aes_sbox[16][16] = {
   0x63,0x7C,0x77,0x7B,0xF2,0x6B,0x6F,0xC5,0x30,0x01,0x67,0x2B,0xFE,0xD7,0xAB,0x76,
   0xCA,0x82,0xC9,0x7D,0xFA,0x59,0x47,0xF0,0xAD,0xD4,0xA2,0xAF,0x9C,0xA4,0x72,0xC0,
   0xB7,0xFD,0x93,0x26,0x36,0x3F,0xF7,0xCC,0x34,0xA5,0xE5,0xF1,0x71,0xD8,0x31,0x15,
   0x04,0xC7,0x23,0xC3,0x18,0x96,0x05,0x9A,0x07,0x12,0x80,0xE2,0xEB,0x27,0xB2,0x75,
   0x09,0x83,0x2C,0x1A,0x1B,0x6E,0x5A,0xA0,0x52,0x3B,0xD6,0xB3,0x29,0xE3,0x2F,0x84,
   0x53,0xD1,0x00,0xED,0x20,0xFC,0xB1,0x5B,0x6A,0xCB,0xBE,0x39,0x4A,0x4C,0x58,0xCF,
   0xD0,0xEF,0xAA,0xFB,0x43,0x4D,0x33,0x85,0x45,0xF9,0x02,0x7F,0x50,0x3C,0x9F,0xA8,
   0x51,0xA3,0x40,0x8F,0x92,0x9D,0x38,0xF5,0xBC,0xB6,0xDA,0x21,0x10,0xFF,0xF3,0xD2,
   0xCD,0x0C,0x13,0xEC,0x5F,0x97,0x44,0x17,0xC4,0xA7,0x7E,0x3D,0x64,0x5D,0x19,0x73,
   0x60,0x81,0x4F,0xDC,0x22,0x2A,0x90,0x88,0x46,0xEE,0xB8,0x14,0xDE,0x5E,0x0B,0xDB,
   0xE0,0x32,0x3A,0x0A,0x49,0x06,0x24,0x5C,0xC2,0xD3,0xAC,0x62,0x91,0x95,0xE4,0x79,
   0xE7,0xC8,0x37,0x6D,0x8D,0xD5,0x4E,0xA9,0x6C,0x56,0xF4,0xEA,0x65,0x7A,0xAE,0x08,
   0xBA,0x78,0x25,0x2E,0x1C,0xA6,0xB4,0xC6,0xE8,0xDD,0x74,0x1F,0x4B,0xBD,0x8B,0x8A,
   0x70,0x3E,0xB5,0x66,0x48,0x03,0xF6,0x0E,0x61,0x35,0x57,0xB9,0x86,0xC1,0x1D,0x9E,
   0xE1,0xF8,0x98,0x11,0x69,0xD9,0x8E,0x94,0x9B,0x1E,0x87,0xE9,0xCE,0x55,0x28,0xDF,
   0x8C,0xA1,0x89,0x0D,0xBF,0xE6,0x42,0x68,0x41,0x99,0x2D,0x0F,0xB0,0x54,0xBB,0x16
};

const uchar aes_invsbox[16][16] = {
   0x52,0x09,0x6A,0xD5,0x30,0x36,0xA5,0x38,0xBF,0x40,0xA3,0x9E,0x81,0xF3,0xD7,0xFB,
   0x7C,0xE3,0x39,0x82,0x9B,0x2F,0xFF,0x87,0x34,0x8E,0x43,0x44,0xC4,0xDE,0xE9,0xCB,
   0x54,0x7B,0x94,0x32,0xA6,0xC2,0x23,0x3D,0xEE,0x4C,0x95,0x0B,0x42,0xFA,0xC3,0x4E,
   0x08,0x2E,0xA1,0x66,0x28,0xD9,0x24,0xB2,0x76,0x5B,0xA2,0x49,0x6D,0x8B,0xD1,0x25,
   0x72,0xF8,0xF6,0x64,0x86,0x68,0x98,0x16,0xD4,0xA4,0x5C,0xCC,0x5D,0x65,0xB6,0x92,
   0x6C,0x70,0x48,0x50,0xFD,0xED,0xB9,0xDA,0x5E,0x15,0x46,0x57,0xA7,0x8D,0x9D,0x84,
   0x90,0xD8,0xAB,0x00,0x8C,0xBC,0xD3,0x0A,0xF7,0xE4,0x58,0x05,0xB8,0xB3,0x45,0x06,
   0xD0,0x2C,0x1E,0x8F,0xCA,0x3F,0x0F,0x02,0xC1,0xAF,0xBD,0x03,0x01,0x13,0x8A,0x6B,
   0x3A,0x91,0x11,0x41,0x4F,0x67,0xDC,0xEA,0x97,0xF2,0xCF,0xCE,0xF0,0xB4,0xE6,0x73,
   0x96,0xAC,0x74,0x22,0xE7,0xAD,0x35,0x85,0xE2,0xF9,0x37,0xE8,0x1C,0x75,0xDF,0x6E,
   0x47,0xF1,0x1A,0x71,0x1D,0x29,0xC5,0x89,0x6F,0xB7,0x62,0x0E,0xAA,0x18,0xBE,0x1B,
   0xFC,0x56,0x3E,0x4B,0xC6,0xD2,0x79,0x20,0x9A,0xDB,0xC0,0xFE,0x78,0xCD,0x5A,0xF4,
   0x1F,0xDD,0xA8,0x33,0x88,0x07,0xC7,0x31,0xB1,0x12,0x10,0x59,0x27,0x80,0xEC,0x5F,
   0x60,0x51,0x7F,0xA9,0x19,0xB5,0x4A,0x0D,0x2D,0xE5,0x7A,0x9F,0x93,0xC9,0x9C,0xEF,
   0xA0,0xE0,0x3B,0x4D,0xAE,0x2A,0xF5,0xB0,0xC8,0xEB,0xBB,0x3C,0x83,0x53,0x99,0x61,
   0x17,0x2B,0x04,0x7E,0xBA,0x77,0xD6,0x26,0xE1,0x69,0x14,0x63,0x55,0x21,0x0C,0x7D
};

// - This table stores pre-calculated values for all possible GF(2^8) calculations.This
// table is only used by the (Inv)MixColumns steps.
// USAGE: The second index (column) is the coefficient of multiplication. Only 7 different
// coefficients are used: 0x01, 0x02, 0x03, 0x09, 0x0b, 0x0d, 0x0e, but multiplication by
// 1 is negligible leaving only 6 coefficients. Each column of the table is devoted to one
// of these coefficients, in the ascending order of value, from values 0x00 to 0xFF.
// (Columns are listed double-wide to conserve vertical space.)
uchar gf_mul[256][6] = {
   {0x00,0x00,0x00,0x00,0x00,0x00},{0x02,0x03,0x09,0x0b,0x0d,0x0e},
   {0x04,0x06,0x12,0x16,0x1a,0x1c},{0x06,0x05,0x1b,0x1d,0x17,0x12},
   {0x08,0x0c,0x24,0x2c,0x34,0x38},{0x0a,0x0f,0x2d,0x27,0x39,0x36},
   {0x0c,0x0a,0x36,0x3a,0x2e,0x24},{0x0e,0x09,0x3f,0x31,0x23,0x2a},
   {0x10,0x18,0x48,0x58,0x68,0x70},{0x12,0x1b,0x41,0x53,0x65,0x7e},
   {0x14,0x1e,0x5a,0x4e,0x72,0x6c},{0x16,0x1d,0x53,0x45,0x7f,0x62},
   {0x18,0x14,0x6c,0x74,0x5c,0x48},{0x1a,0x17,0x65,0x7f,0x51,0x46},
   {0x1c,0x12,0x7e,0x62,0x46,0x54},{0x1e,0x11,0x77,0x69,0x4b,0x5a},
   {0x20,0x30,0x90,0xb0,0xd0,0xe0},{0x22,0x33,0x99,0xbb,0xdd,0xee},
   {0x24,0x36,0x82,0xa6,0xca,0xfc},{0x26,0x35,0x8b,0xad,0xc7,0xf2},
   {0x28,0x3c,0xb4,0x9c,0xe4,0xd8},{0x2a,0x3f,0xbd,0x97,0xe9,0xd6},
   {0x2c,0x3a,0xa6,0x8a,0xfe,0xc4},{0x2e,0x39,0xaf,0x81,0xf3,0xca},
   {0x30,0x28,0xd8,0xe8,0xb8,0x90},{0x32,0x2b,0xd1,0xe3,0xb5,0x9e},
   {0x34,0x2e,0xca,0xfe,0xa2,0x8c},{0x36,0x2d,0xc3,0xf5,0xaf,0x82},
   {0x38,0x24,0xfc,0xc4,0x8c,0xa8},{0x3a,0x27,0xf5,0xcf,0x81,0xa6},
   {0x3c,0x22,0xee,0xd2,0x96,0xb4},{0x3e,0x21,0xe7,0xd9,0x9b,0xba},
   {0x40,0x60,0x3b,0x7b,0xbb,0xdb},{0x42,0x63,0x32,0x70,0xb6,0xd5},
   {0x44,0x66,0x29,0x6d,0xa1,0xc7},{0x46,0x65,0x20,0x66,0xac,0xc9},
   {0x48,0x6c,0x1f,0x57,0x8f,0xe3},{0x4a,0x6f,0x16,0x5c,0x82,0xed},
   {0x4c,0x6a,0x0d,0x41,0x95,0xff},{0x4e,0x69,0x04,0x4a,0x98,0xf1},
   {0x50,0x78,0x73,0x23,0xd3,0xab},{0x52,0x7b,0x7a,0x28,0xde,0xa5},
   {0x54,0x7e,0x61,0x35,0xc9,0xb7},{0x56,0x7d,0x68,0x3e,0xc4,0xb9},
   {0x58,0x74,0x57,0x0f,0xe7,0x93},{0x5a,0x77,0x5e,0x04,0xea,0x9d},
   {0x5c,0x72,0x45,0x19,0xfd,0x8f},{0x5e,0x71,0x4c,0x12,0xf0,0x81},
   {0x60,0x50,0xab,0xcb,0x6b,0x3b},{0x62,0x53,0xa2,0xc0,0x66,0x35},
   {0x64,0x56,0xb9,0xdd,0x71,0x27},{0x66,0x55,0xb0,0xd6,0x7c,0x29},
   {0x68,0x5c,0x8f,0xe7,0x5f,0x03},{0x6a,0x5f,0x86,0xec,0x52,0x0d},
   {0x6c,0x5a,0x9d,0xf1,0x45,0x1f},{0x6e,0x59,0x94,0xfa,0x48,0x11},
   {0x70,0x48,0xe3,0x93,0x03,0x4b},{0x72,0x4b,0xea,0x98,0x0e,0x45},
   {0x74,0x4e,0xf1,0x85,0x19,0x57},{0x76,0x4d,0xf8,0x8e,0x14,0x59},
   {0x78,0x44,0xc7,0xbf,0x37,0x73},{0x7a,0x47,0xce,0xb4,0x3a,0x7d},
   {0x7c,0x42,0xd5,0xa9,0x2d,0x6f},{0x7e,0x41,0xdc,0xa2,0x20,0x61},
   {0x80,0xc0,0x76,0xf6,0x6d,0xad},{0x82,0xc3,0x7f,0xfd,0x60,0xa3},
   {0x84,0xc6,0x64,0xe0,0x77,0xb1},{0x86,0xc5,0x6d,0xeb,0x7a,0xbf},
   {0x88,0xcc,0x52,0xda,0x59,0x95},{0x8a,0xcf,0x5b,0xd1,0x54,0x9b},
   {0x8c,0xca,0x40,0xcc,0x43,0x89},{0x8e,0xc9,0x49,0xc7,0x4e,0x87},
   {0x90,0xd8,0x3e,0xae,0x05,0xdd},{0x92,0xdb,0x37,0xa5,0x08,0xd3},
   {0x94,0xde,0x2c,0xb8,0x1f,0xc1},{0x96,0xdd,0x25,0xb3,0x12,0xcf},
   {0x98,0xd4,0x1a,0x82,0x31,0xe5},{0x9a,0xd7,0x13,0x89,0x3c,0xeb},
   {0x9c,0xd2,0x08,0x94,0x2b,0xf9},{0x9e,0xd1,0x01,0x9f,0x26,0xf7},
   {0xa0,0xf0,0xe6,0x46,0xbd,0x4d},{0xa2,0xf3,0xef,0x4d,0xb0,0x43},
   {0xa4,0xf6,0xf4,0x50,0xa7,0x51},{0xa6,0xf5,0xfd,0x5b,0xaa,0x5f},
   {0xa8,0xfc,0xc2,0x6a,0x89,0x75},{0xaa,0xff,0xcb,0x61,0x84,0x7b},
   {0xac,0xfa,0xd0,0x7c,0x93,0x69},{0xae,0xf9,0xd9,0x77,0x9e,0x67},
   {0xb0,0xe8,0xae,0x1e,0xd5,0x3d},{0xb2,0xeb,0xa7,0x15,0xd8,0x33},
   {0xb4,0xee,0xbc,0x08,0xcf,0x21},{0xb6,0xed,0xb5,0x03,0xc2,0x2f},
   {0xb8,0xe4,0x8a,0x32,0xe1,0x05},{0xba,0xe7,0x83,0x39,0xec,0x0b},
   {0xbc,0xe2,0x98,0x24,0xfb,0x19},{0xbe,0xe1,0x91,0x2f,0xf6,0x17},
   {0xc0,0xa0,0x4d,0x8d,0xd6,0x76},{0xc2,0xa3,0x44,0x86,0xdb,0x78},
   {0xc4,0xa6,0x5f,0x9b,0xcc,0x6a},{0xc6,0xa5,0x56,0x90,0xc1,0x64},
   {0xc8,0xac,0x69,0xa1,0xe2,0x4e},{0xca,0xaf,0x60,0xaa,0xef,0x40},
   {0xcc,0xaa,0x7b,0xb7,0xf8,0x52},{0xce,0xa9,0x72,0xbc,0xf5,0x5c},
   {0xd0,0xb8,0x05,0xd5,0xbe,0x06},{0xd2,0xbb,0x0c,0xde,0xb3,0x08},
   {0xd4,0xbe,0x17,0xc3,0xa4,0x1a},{0xd6,0xbd,0x1e,0xc8,0xa9,0x14},
   {0xd8,0xb4,0x21,0xf9,0x8a,0x3e},{0xda,0xb7,0x28,0xf2,0x87,0x30},
   {0xdc,0xb2,0x33,0xef,0x90,0x22},{0xde,0xb1,0x3a,0xe4,0x9d,0x2c},
   {0xe0,0x90,0xdd,0x3d,0x06,0x96},{0xe2,0x93,0xd4,0x36,0x0b,0x98},
   {0xe4,0x96,0xcf,0x2b,0x1c,0x8a},{0xe6,0x95,0xc6,0x20,0x11,0x84},
   {0xe8,0x9c,0xf9,0x11,0x32,0xae},{0xea,0x9f,0xf0,0x1a,0x3f,0xa0},
   {0xec,0x9a,0xeb,0x07,0x28,0xb2},{0xee,0x99,0xe2,0x0c,0x25,0xbc},
   {0xf0,0x88,0x95,0x65,0x6e,0xe6},{0xf2,0x8b,0x9c,0x6e,0x63,0xe8},
   {0xf4,0x8e,0x87,0x73,0x74,0xfa},{0xf6,0x8d,0x8e,0x78,0x79,0xf4},
   {0xf8,0x84,0xb1,0x49,0x5a,0xde},{0xfa,0x87,0xb8,0x42,0x57,0xd0},
   {0xfc,0x82,0xa3,0x5f,0x40,0xc2},{0xfe,0x81,0xaa,0x54,0x4d,0xcc},
   {0x1b,0x9b,0xec,0xf7,0xda,0x41},{0x19,0x98,0xe5,0xfc,0xd7,0x4f},
   {0x1f,0x9d,0xfe,0xe1,0xc0,0x5d},{0x1d,0x9e,0xf7,0xea,0xcd,0x53},
   {0x13,0x97,0xc8,0xdb,0xee,0x79},{0x11,0x94,0xc1,0xd0,0xe3,0x77},
   {0x17,0x91,0xda,0xcd,0xf4,0x65},{0x15,0x92,0xd3,0xc6,0xf9,0x6b},
   {0x0b,0x83,0xa4,0xaf,0xb2,0x31},{0x09,0x80,0xad,0xa4,0xbf,0x3f},
   {0x0f,0x85,0xb6,0xb9,0xa8,0x2d},{0x0d,0x86,0xbf,0xb2,0xa5,0x23},
   {0x03,0x8f,0x80,0x83,0x86,0x09},{0x01,0x8c,0x89,0x88,0x8b,0x07},
   {0x07,0x89,0x92,0x95,0x9c,0x15},{0x05,0x8a,0x9b,0x9e,0x91,0x1b},
   {0x3b,0xab,0x7c,0x47,0x0a,0xa1},{0x39,0xa8,0x75,0x4c,0x07,0xaf},
   {0x3f,0xad,0x6e,0x51,0x10,0xbd},{0x3d,0xae,0x67,0x5a,0x1d,0xb3},
   {0x33,0xa7,0x58,0x6b,0x3e,0x99},{0x31,0xa4,0x51,0x60,0x33,0x97},
   {0x37,0xa1,0x4a,0x7d,0x24,0x85},{0x35,0xa2,0x43,0x76,0x29,0x8b},
   {0x2b,0xb3,0x34,0x1f,0x62,0xd1},{0x29,0xb0,0x3d,0x14,0x6f,0xdf},
   {0x2f,0xb5,0x26,0x09,0x78,0xcd},{0x2d,0xb6,0x2f,0x02,0x75,0xc3},
   {0x23,0xbf,0x10,0x33,0x56,0xe9},{0x21,0xbc,0x19,0x38,0x5b,0xe7},
   {0x27,0xb9,0x02,0x25,0x4c,0xf5},{0x25,0xba,0x0b,0x2e,0x41,0xfb},
   {0x5b,0xfb,0xd7,0x8c,0x61,0x9a},{0x59,0xf8,0xde,0x87,0x6c,0x94},
   {0x5f,0xfd,0xc5,0x9a,0x7b,0x86},{0x5d,0xfe,0xcc,0x91,0x76,0x88},
   {0x53,0xf7,0xf3,0xa0,0x55,0xa2},{0x51,0xf4,0xfa,0xab,0x58,0xac},
   {0x57,0xf1,0xe1,0xb6,0x4f,0xbe},{0x55,0xf2,0xe8,0xbd,0x42,0xb0},
   {0x4b,0xe3,0x9f,0xd4,0x09,0xea},{0x49,0xe0,0x96,0xdf,0x04,0xe4},
   {0x4f,0xe5,0x8d,0xc2,0x13,0xf6},{0x4d,0xe6,0x84,0xc9,0x1e,0xf8},
   {0x43,0xef,0xbb,0xf8,0x3d,0xd2},{0x41,0xec,0xb2,0xf3,0x30,0xdc},
   {0x47,0xe9,0xa9,0xee,0x27,0xce},{0x45,0xea,0xa0,0xe5,0x2a,0xc0},
   {0x7b,0xcb,0x47,0x3c,0xb1,0x7a},{0x79,0xc8,0x4e,0x37,0xbc,0x74},
   {0x7f,0xcd,0x55,0x2a,0xab,0x66},{0x7d,0xce,0x5c,0x21,0xa6,0x68},
   {0x73,0xc7,0x63,0x10,0x85,0x42},{0x71,0xc4,0x6a,0x1b,0x88,0x4c},
   {0x77,0xc1,0x71,0x06,0x9f,0x5e},{0x75,0xc2,0x78,0x0d,0x92,0x50},
   {0x6b,0xd3,0x0f,0x64,0xd9,0x0a},{0x69,0xd0,0x06,0x6f,0xd4,0x04},
   {0x6f,0xd5,0x1d,0x72,0xc3,0x16},{0x6d,0xd6,0x14,0x79,0xce,0x18},
   {0x63,0xdf,0x2b,0x48,0xed,0x32},{0x61,0xdc,0x22,0x43,0xe0,0x3c},
   {0x67,0xd9,0x39,0x5e,0xf7,0x2e},{0x65,0xda,0x30,0x55,0xfa,0x20},
   {0x9b,0x5b,0x9a,0x01,0xb7,0xec},{0x99,0x58,0x93,0x0a,0xba,0xe2},
   {0x9f,0x5d,0x88,0x17,0xad,0xf0},{0x9d,0x5e,0x81,0x1c,0xa0,0xfe},
   {0x93,0x57,0xbe,0x2d,0x83,0xd4},{0x91,0x54,0xb7,0x26,0x8e,0xda},
   {0x97,0x51,0xac,0x3b,0x99,0xc8},{0x95,0x52,0xa5,0x30,0x94,0xc6},
   {0x8b,0x43,0xd2,0x59,0xdf,0x9c},{0x89,0x40,0xdb,0x52,0xd2,0x92},
   {0x8f,0x45,0xc0,0x4f,0xc5,0x80},{0x8d,0x46,0xc9,0x44,0xc8,0x8e},
   {0x83,0x4f,0xf6,0x75,0xeb,0xa4},{0x81,0x4c,0xff,0x7e,0xe6,0xaa},
   {0x87,0x49,0xe4,0x63,0xf1,0xb8},{0x85,0x4a,0xed,0x68,0xfc,0xb6},
   {0xbb,0x6b,0x0a,0xb1,0x67,0x0c},{0xb9,0x68,0x03,0xba,0x6a,0x02},
   {0xbf,0x6d,0x18,0xa7,0x7d,0x10},{0xbd,0x6e,0x11,0xac,0x70,0x1e},
   {0xb3,0x67,0x2e,0x9d,0x53,0x34},{0xb1,0x64,0x27,0x96,0x5e,0x3a},
   {0xb7,0x61,0x3c,0x8b,0x49,0x28},{0xb5,0x62,0x35,0x80,0x44,0x26},
   {0xab,0x73,0x42,0xe9,0x0f,0x7c},{0xa9,0x70,0x4b,0xe2,0x02,0x72},
   {0xaf,0x75,0x50,0xff,0x15,0x60},{0xad,0x76,0x59,0xf4,0x18,0x6e},
   {0xa3,0x7f,0x66,0xc5,0x3b,0x44},{0xa1,0x7c,0x6f,0xce,0x36,0x4a},
   {0xa7,0x79,0x74,0xd3,0x21,0x58},{0xa5,0x7a,0x7d,0xd8,0x2c,0x56},
   {0xdb,0x3b,0xa1,0x7a,0x0c,0x37},{0xd9,0x38,0xa8,0x71,0x01,0x39},
   {0xdf,0x3d,0xb3,0x6c,0x16,0x2b},{0xdd,0x3e,0xba,0x67,0x1b,0x25},
   {0xd3,0x37,0x85,0x56,0x38,0x0f},{0xd1,0x34,0x8c,0x5d,0x35,0x01},
   {0xd7,0x31,0x97,0x40,0x22,0x13},{0xd5,0x32,0x9e,0x4b,0x2f,0x1d},
   {0xcb,0x23,0xe9,0x22,0x64,0x47},{0xc9,0x20,0xe0,0x29,0x69,0x49},
   {0xcf,0x25,0xfb,0x34,0x7e,0x5b},{0xcd,0x26,0xf2,0x3f,0x73,0x55},
   {0xc3,0x2f,0xcd,0x0e,0x50,0x7f},{0xc1,0x2c,0xc4,0x05,0x5d,0x71},
   {0xc7,0x29,0xdf,0x18,0x4a,0x63},{0xc5,0x2a,0xd6,0x13,0x47,0x6d},
   {0xfb,0x0b,0x31,0xca,0xdc,0xd7},{0xf9,0x08,0x38,0xc1,0xd1,0xd9},
   {0xff,0x0d,0x23,0xdc,0xc6,0xcb},{0xfd,0x0e,0x2a,0xd7,0xcb,0xc5},
   {0xf3,0x07,0x15,0xe6,0xe8,0xef},{0xf1,0x04,0x1c,0xed,0xe5,0xe1},
   {0xf7,0x01,0x07,0xf0,0xf2,0xf3},{0xf5,0x02,0x0e,0xfb,0xff,0xfd},
   {0xeb,0x13,0x79,0x92,0xb4,0xa7},{0xe9,0x10,0x70,0x99,0xb9,0xa9},
   {0xef,0x15,0x6b,0x84,0xae,0xbb},{0xed,0x16,0x62,0x8f,0xa3,0xb5},
   {0xe3,0x1f,0x5d,0xbe,0x80,0x9f},{0xe1,0x1c,0x54,0xb5,0x8d,0x91},
   {0xe7,0x19,0x4f,0xa8,0x9a,0x83},{0xe5,0x1a,0x46,0xa3,0x97,0x8d}
};

/***************************************************************
*															   *
*			// hex2bin() //									   *
*															   *
****************************************************************/
char* hex2bin(char hex){

	int n = 16;
	int k;
	char* bin;

	for(k=0;k<n;k++){
		if (toupper(hex) == hex_table[k]) {
			bin = bin4_table[k];
			break;	
		}
	}
	return bin;
}

/***************************************************************
*															   *
*			// hexStr2bin() //								   *
*															   *
****************************************************************/
char* hexStr2bin(char *hex_str) {
 
    int i;
    char *str;
    size_t len = strlen(hex_str);

    char* bin_str = (char*)malloc(((len * 4) + 1) * sizeof(char));
    for (i = 0; i < (int)len; i++) {
      const char* binQuartet = hex2bin(hex_str[i]);
      memcpy(&bin_str[4*i], binQuartet,5);
    }
    return bin_str;
}

/***************************************************************
*															   *
*			// bin2hexChar() //								   *
*															   *
****************************************************************/
char bin2hexChar(char *bin){

    int k = 0;
    for(int i = 0; i < 4; i++){
        k = k * 2 + *bin++ - '0';
    }
    return hex_table[k];
}

/***************************************************************
*															   *
*			// bin2hexStr() //								   *
*															   *
****************************************************************/
char* bin2hexStr(char* binStr) {

    size_t loops, len = strlen(binStr);
    int r = len % 4;
    if(r)
        r = 4 - r;

    char *paddedBin = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
    memset(paddedBin, '0', r);//add padding to top
    memcpy(paddedBin + r, binStr, len + 1);
    loops = (len + r) / 4;
    char *hexStr = malloc((loops + 1)*sizeof(char));//+1 for NUL
    for(size_t i = 0; i < loops; i++){
        hexStr[i] = bin2hexChar(paddedBin + i * 4);
    }
    hexStr[loops] = '\0';
    free(paddedBin);
    return hexStr;
}

/***************************************************************
*															   *
*			// string_compare() //							   *
*															   *
****************************************************************/
int string_compare(char *str1, char *str2)
{
    int ctr=0;

    while(str1[ctr]==str2[ctr])
    {
        if(str1[ctr]=='\0'||str2[ctr]=='\0')
            break;
        ctr++;
    }
    if(str1[ctr]=='\0' && str2[ctr]=='\0')
        return 1;
    else
        return 0;
}

/***************************************************************
*															   *
*			// bin2b64Char() //								   *
*															   *
****************************************************************/
char bin2b64Char(char* bin)
{
	
	char buffer[] = {'0','0','0','0','0','0','\0'};
	char b64;
	int i,r;
	size_t len = strlen(bin);
	
	if(len<6){
		r = 6-len%6;
		memmove(&buffer[r],bin,len);
		for(i=0;i<64;i++){
			if(string_compare(buffer,bin6_table[i])==1){
				b64 = base64_table[i];
				break;
			}
		}
	}else{
		for(i=0;i<64;i++){
			if(string_compare(bin,bin6_table[i])==1){
				b64 = base64_table[i];
				break;
			}
		}
	}
	return b64;
}

/***************************************************************
*															   *
*			// bin2b64Str() //								   *
*															   *
****************************************************************/
char* bin2b64Str(char* binStr){

	char *paddedBin;
    int i,r, loops;
	char buffer[] = {'0','0','0','0','0','0','\0'};

	int count = 0;
	r = 6-strlen(binStr)%6;
	if(r!=6){
		loops = (int)strlen(binStr)/6+1;
		paddedBin = (char*)malloc(((strlen(binStr)+r) + 1) * sizeof(char));
		memmove(paddedBin,&buffer[6-r],r);
		memmove(&paddedBin[r],binStr,strlen(binStr)+1);
	}else{
		loops = (int)strlen(binStr)/6;
		paddedBin = (char*)malloc(((strlen(binStr)) + 1) * sizeof(char));
		memmove(paddedBin,binStr,strlen(binStr)+1);
	}
	char* b64str = (char *)malloc((strlen(binStr)+r + 1)*sizeof(char));
	for(i=0;i<loops;i++){
		char sextet[7];
		++count;
		memcpy(sextet,&paddedBin[6*i],6);
		sextet[6]='\0';
		b64str[i] = bin2b64Char(sextet);
	}
	b64str[loops]='\0';
	free(paddedBin);
    return b64str;
}

/***************************************************************
*															   *
*			// b64Char2bin() //								   *
*															   *
****************************************************************/
char* b64Char2bin(char b64){

	int n = 66;
	int k;
	char *bin;

	for(k=0;k<n;k++){
		if (b64 == base64_table[k]) {
			if(b64 == '='){
				break;
			}else{
				bin = bin6_table[k];
				break;
			}	
		}
	}
	return bin;
}

/***************************************************************
*																*
*			// b642bin() //		  					     		*
*																*
****************************************************************/
char* b642bin(char *b64) {

	size_t loops, len = strlen(b64);
    int r = len % 4;
	char* paddedB64;
    if(r){
        r = 4 - r;
	    paddedB64 = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
	    memset(paddedB64, '=', len+r);//add padding to top
	    memcpy(paddedB64, b64, len);
		paddedB64[len+r] = '\0';
	}else{
    	paddedB64 = b64;
	}
	
	char* bin = malloc((6*strlen(paddedB64))*sizeof(char));
	for(int i = 0; i < strlen(paddedB64)/4; ++i){
		char* quartet = malloc(5*sizeof(char));
		memcpy(quartet, &paddedB64[4*i],4);
		quartet[4] = '\0';
		if(quartet[2] == '=' && quartet[3] == '='){
			if(quartet[1]!= 'A' && quartet[1]!= 'Q' && quartet[1]!= 'g' && quartet[1]!= 'w'){
				quartet[1] = 'A';
			}
			
			for(int k = 0; k < 66; ++k){
				if(quartet[0] == base64_table[k]){
					memcpy(&bin[24*i],bin6_table[k],6);
					break;
				}
			}
			for(int k = 0; k < 66; ++k){
				if(quartet[1] == base64_table[k]){
					memcpy(&bin[24*i+6],bin6_table[k],2);
					break;
				}
			}
			bin[24*i+8] = '\0';
		}else if(quartet[2] != '=' && quartet[3] == '='){
			if(quartet[2]!='A' && quartet[2]!= 'E' && quartet[2]!= 'I' && quartet[2]!= 'M' && quartet[2]!= 'Q'
				 && quartet[2]!= 'U' && quartet[2]!= 'Y' && quartet[2]!= 'c' && quartet[2]!= 'g'
				 && quartet[2]!= 'k' && quartet[2]!= 'o' && quartet[2]!= 's' && quartet[2]!= 'w'
				 && quartet[2]!= '0' && quartet[2]!= '4' && quartet[2]!= '8'){
				quartet[2] = 'A';
			}
			for(int j = 0; j < 3; ++j){
				for(int k = 0; k < 66; ++k){
					if(quartet[j] == base64_table[k]){
						memcpy(&bin[24*i+6*j],bin6_table[k],6);
						break;
					}
				}
			}
			for(int k = 0; k < 66; ++k){
				if(quartet[2] == base64_table[k]){
					break;
				}
			}
			bin[24*i+16] = '\0';
		}else{
			for(int j = 0; j < 4; ++j){
				for(int k = 0; k < 66; ++k){
					if(quartet[j] == base64_table[k]){
						if(i==0 && j==0)
							strcpy(bin,bin6_table[k]);
						else
							strcat(bin,bin6_table[k]);
						break;
					}
				}
			}
			if(i==strlen(paddedB64)/4){
				bin[24*(i+1)] = '\0';
			}
		}
		free(quartet);
	}
	return bin;
}

/***************************************************************
*																*
*			// dec2bin() //										*
*																*
****************************************************************/
char* dec2bin(int n, int pad){
	
	if(pow(2,pad)<n){
		printf("Insufficient number of bits for decimal to binary conversion.\nTerminating.\n");
		exit(1);
	}else{
		int delta=n, p=0,count=0;
		int ncopy = n;
		char ones[] = {'1','1'};
		char* bin = (char*)malloc((pad+1)*sizeof(char));
		memset(bin,'0',pad);
		while(delta!=0){
			int j=0;
			while(pow(2,j)<=delta){
				p=j;
				++j;
			}
			delta = abs(ncopy-pow(2,p));
			ncopy =delta;
			memcpy(&bin[pad-1-p],ones,1);
		count++;
		}
		bin[pad]='\0';
		return bin;
	}
}

/***************************************************************
*																*
*			// bin2prasciiChar() //								*
*																*
****************************************************************/
char bin2prasciiChar(char* bin){

	char prascii = '$';
	for(int i =0;i<97;++i){
		if(string_compare(bin,bin8_table[i])==1){
			prascii = prascii_table[i];
			break;
		}
	}
	return prascii;
}

/***************************************************************
*																*
*			// bin2prasciiStr() //								*
*																*
****************************************************************/
char* bin2prasciiStr(char* binStr){

	size_t loops, len = strlen(binStr);
    int r = len % 8;
    if(r)
        r = 8 - r;

    char *paddedBin = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
    memset(paddedBin, '0', r);//add padding to top
    memcpy(paddedBin + r, binStr, len + 1);
    loops = (len + r) / 8;
    char *prasciiStr = malloc((loops + 1)*sizeof(char));//+1 for NUL
	char octet[9];
	memset(octet, '0', 8);
	octet[8]='\0';
    for(size_t i = 0; i < loops; i++){
		memcpy(octet, &paddedBin[8*i],8);
        prasciiStr[i] = bin2prasciiChar(octet);
    }
    prasciiStr[loops] = '\0';
    free(paddedBin);
    return prasciiStr;
}

/***************************************************************
*															   *
*			// prasciChar2bin() //							   *
*															   *
****************************************************************/
char* prasciiChar2bin(char prascii){

	char *bin = malloc(9*sizeof(char));
	for(int i =0;i<97;++i){
		if(prascii==prascii_table[i]){
			memcpy(bin,bin8_table[i],8);
			break;
		}
	}
	bin[8] = '\0';
	return bin;
}

/***************************************************************
*															   *
*			// prasciiStr2bin() //							   *
*															   *
****************************************************************/
char* prasciiStr2bin(char *prascii) {
 
    int i;
    size_t len = strlen(prascii);

    char* bin_str = (char*)malloc(((len * 8) + 1) * sizeof(char));
    for (i = 0; i < (int)len; i++) {
      char* binOctet = (char*)malloc(9*sizeof(char));
	  memcpy(binOctet,prasciiChar2bin(prascii[i]),8);
      memcpy(&bin_str[8*i], binOctet,8);
    }
    bin_str[8*len] = '\0';
    return bin_str;
}

/***************************************************************
*															   *
*			// hex2prasciiChar() //							   *
*															   *
****************************************************************/
char hex2prasciiChar(char* hex){

	char prascii = '0';
	char hexUpper[3];
	hexUpper[0] = hex[0];
	hexUpper[1] = toupper(hex[1]);
	hexUpper[2] = '\0';
	
	for(int i =0;i<97;++i){
		if(string_compare(hexUpper,hex2_table[i])==1){
			prascii = prascii_table[i];
			break;
		}
	}
	return prascii;
}

/***************************************************************
*															   *
*			// hex2prasciiStr() //							   *
*															   *
****************************************************************/
char* hex2prasciiStr(char* hexStr){

	size_t loops, len = strlen(hexStr);
    int r = len % 2;
    if(r)
        r = 2 - r;

    char *paddedHex = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
    memset(paddedHex, '0', r);//add padding to top
    memcpy(paddedHex + r, hexStr, len + 1);
    loops = (len + r) / 2;
    char *prasciiStr = malloc((loops + 1)*sizeof(char));//+1 for NUL
    for(size_t i = 0; i < loops; i++){
		char* duet = (char*)malloc(3*sizeof(char));
		memset(duet, '0', 2);
		duet[2]='\0';
		memcpy(duet, &paddedHex[2*i],2);
        prasciiStr[i] = hex2prasciiChar(duet);
		free(duet);
    }
    prasciiStr[loops] = '\0';
    free(paddedHex);
    return prasciiStr;
}

/***************************************************************
*															   *
*			// prasciiChar2hex() //							   *
*															   *
****************************************************************/
char* prasciiChar2hex(char prascii){

	char *hex = malloc(3*sizeof(char));
	for(int i =0;i<97;++i){
		if(prascii==prascii_table[i]){
			memcpy(hex,hex2_table[i],3);
			break;
		}
	}
	hex[3] = '\0';
	return hex;
}

/***************************************************************
*															   *
*			// prasciiStr2hex() //							   *
*															   *
****************************************************************/
char* prasciiStr2hex(char *prascii) {
 
    int i;
    size_t len = strlen(prascii);

    char* hex_str = (char*)malloc(((len * 2) + 1) * sizeof(char));
    for (i = 0; i < (int)len; i++) {
      char* hexDuet = (char*)malloc(3*sizeof(char));
	  memcpy(hexDuet,prasciiChar2hex(prascii[i]),2);
      memcpy(&hex_str[2*i], hexDuet,2);
    }
    hex_str[2*len] = '\0';
    return hex_str;
}

/***************************************************************
*															   *
*			// charand() //									   *
*															   *
****************************************************************/
char charand(char bit1,char bit2){
	
	if(bit1 == '1' && bit2 == '1')
		return '1';
	else 
		return '0';

}

/***************************************************************
*															   *
*			// strand() //									   *
*															   *
****************************************************************/
char* strand(char* str1,char* str2){
	
	char* and = (char*)malloc((strlen(str1)+1)*sizeof(char));
	for(int i=0;i<(int)strlen(str1);++i){
		const char temp = charand(str1[i],str2[i]);
		and[i] = temp;
	}
	and[strlen(str1)]='\0';
	return and;

}

/***************************************************************
*															   *
*			// charxor() //									   *
*															   *
****************************************************************/
char charxor(char bit1,char bit2){
	
	if((bit1 == '1' && bit2 == '0') || (bit1 == '0' && bit2 == '1'))
		return '1';
	else 
		return '0';

}

/***************************************************************
*															   *
*			// strxor() //									   *
*															   *
****************************************************************/
char* strxor(char* str1, char* str2){
	
	char* xor = malloc((strlen(str1)+1));
	for(int i=0;i<(int)strlen(str1);++i){
		const char temp = charxor(str1[i],str2[i]);
		xor[i] = temp;
	}
	xor[strlen(str1)]='\0';
	return xor;
}

/***************************************************************
*															   *
*			// hexxor() //									   *
*															   *
****************************************************************/
char* hexxor(char* str1, char* str2){

	int binlen;
	int len1 = strlen(str1);
	char* bxor;
	char* hxor;
	if(strlen(str1)!=strlen(str2)){
		printf("This is a fixed width XOR function -- each hex string must be the same length!\n");
		exit(1);
	}else{
		binlen = 4*len1;
		char* bin1 = (char*)malloc((binlen+1)*sizeof(char));
		char* bin2 = (char*)malloc((binlen+1)*sizeof(char));
		memcpy(bin1,hexStr2bin(str1),binlen+1);
		memcpy(bin2,hexStr2bin(str2),binlen+1);
		bin2 = hexStr2bin(str2);
		bxor = strxor(bin1,bin2);
		hxor = bin2hexStr(bxor);
		return hxor;
	}
}

/***************************************************************
*															   *
*			// transposeCharArray() //						   *
*															   *
****************************************************************/
char** transposeCharArray(char** A, int m, int n){

	char** tarray = (char**)malloc((n)*sizeof(char*));
	for(int i = 0; i < n; ++i){
		printf("Transposing row %d ...\n\n",i+1);
		tarray[i] = (char*)malloc((m+1)*sizeof(char));
		for(int j = 0; j < m;++j){
			printf("Swapping column %d ...\n",j+1);
			tarray[i][j] = A[j][i];
		}
		tarray[i][m] = '\0';
	}
	return tarray;
}

/***************************************************************
*															   *
*			// cat2DCharMat() //							   *
*															   *
****************************************************************/
char* cat2dCharMat(char** A, int m, int n){
	
	char* temp = malloc((m*n+1)*sizeof(char));
	int length = 0;
	for(int i = 0; i < m;++i){
		memcpy(&temp[n*i], A[i],strlen(A[i]));
		length += (int)strlen(A[i]);
	}
	temp[length] = '\0';
	printf("Length of concatenated string is %d chars.\n",strlen(temp));
	return temp;
}

/***************************************************************
*															   *
*			// printNbitBin() //							   *
*															   *
****************************************************************/
void printNbitBin(int n){
	
	if(n==0){
		printf("Can't print a zero bit number! Terminating.\n");
		exit(1);
	}else{
		for(int i = 0;i<pow(2,n);++i){
			if(i==0){
				printf("\n{ \"%s\",", dec2bin(i,n));
			}else if(i==pow(2,n)-1){
				printf("\"%s\"};\n\n",dec2bin(i,n));
			}else{
				printf("\"%s\",",dec2bin(i,n));
			}
		}
	}
}

/***************************************************************
*														*
*			// textFile2Array() //							*
*														*
****************************************************************/
char** textFile2Array(char* file){

    int i = 0;
    int lines_allocated = pow(2,9);
    int max_line_len = pow(2,6);

    char **lines = (char **)malloc(sizeof(char*)*lines_allocated);
    FILE *fp = fopen(file, "r");
    if (fp == 0)
    {
        fprintf(stderr, "failed to open %s\n",file);
        exit(1);
    }
    while (i < lines_allocated)
    {
		lines[i] = malloc(max_line_len*sizeof(char));
		if(fgets(lines[i],max_line_len-1,fp)==NULL)
			break;
		else{
			for(int j=0;j<strlen(lines[i]);++j){
				if(lines[i][j]=='\n')
					lines[i][j] = '\0';
			}
		}
        i += 1;
    }
    fclose(fp);
    return lines;
}

/***************************************************************
*															   *
*			// textFile2String() //							   *
*															   *
****************************************************************/
char* textFile2String(char* file){

    int i = 0;
    int lines_allocated = pow(2,8);
    int max_line_len = pow(2,6);
	int len;

    FILE *fp = fopen(file, "r");
	if (fp == 0)
    {
        fprintf(stderr, "failed to open %s\n",file);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fseek(fp, SEEK_SET, 0);
    char* lines = malloc(len);
    while (i < lines_allocated)
    {
		char* buffer = malloc(max_line_len);
		if(fgets(buffer,max_line_len,fp)==NULL)
			break;
		buffer[strcspn(buffer, "\n")] = '\0';
		if(i==0)
			strcpy(lines,buffer);
		else
			strcat(lines,buffer);
        i += 1;
		free(buffer);
    }
    fclose(fp);

    return lines;
}

/***************************************************************
*															   *
*			// findMaxElement() //							   *
*															   *
****************************************************************/
int findMaxElement(double* array, int len){
	
	int index=0;
	double max = -pow(2,32);
	for(int i = 0;i<len;++i){
		if((double)array[i]>=max){
			max = (double)array[i];
			index = i;
		}
	}
	return index;
}

/***************************************************************
*															   *
*			// findMinElement() //							   *
*															   *
****************************************************************/
int findMinElement(double* array, int len){
	
	int index=0;
	double max = pow(2,32);
	for(int i = 0;i<len;++i){
		if((double)array[i]<=max){
			max = (double)array[i];
			index = i;
		}
	}
	return index;
}

/***************************************************************
*															   *
*			// scorePlaintext() //							   *
*															   *
****************************************************************/
double scorePlaintext(char* plaintext){

	double score = 0;
	double typicalSpaceCount = strlen(plaintext)/meanWordLength;
	int spaceCount = 0;
	for(int i=0;i<(int)strlen(plaintext);++i){
		for(int j=0; j<24;++j){
			if(plaintext[i]==commonLetters[j]){
				score += commonLetterWeight[j]; // Reward common letters
			}
		}
		for(int k=0; k<9;++k){
			if(plaintext[i]==nonAlphaNumericChars[k]){
				score += -2*commonLetterWeight[findMaxElement(commonLetterWeight,24)]; // Penalize uncommon chars
			}
		}
		if(plaintext[i]== ' ')
			spaceCount += 1;
	}
	if((double)spaceCount < 0.5*typicalSpaceCount)
		score += -2*commonLetterWeight[findMaxElement(commonLetterWeight,24)]; // Penalize lack of spaces

	if((double)spaceCount < 1.2*typicalSpaceCount && (double)spaceCount > 0.8*typicalSpaceCount)
		score += 2*commonLetterWeight[findMaxElement(commonLetterWeight,24)]; // Reward acceptable amount of spaces

	return score;
}

/***************************************************************
*															   *
*			// scorePlaintext_chiSquare() //				   *
*															   *
****************************************************************/
double scorePlaintext_chiSquare(char* plaintext){

	double score = 0;
	double count[26];
	double chiSquares[27];
	for(int i = 0; i < 26; ++i)
		count[i] = 0;
	int spaceCountReal = 0;
	double spaceCountExpected = strlen(plaintext)/meanWordLength;
	for(int j = 0; j < strlen(plaintext); ++j){
		if(plaintext[j]=='A' || plaintext[j]=='a')
			count[0] += 1;
		else if(plaintext[j]=='B' || plaintext[j]=='b')
			count[1] += 1;
		else if(plaintext[j]=='C' || plaintext[j]=='c')
			count[2] += 1;
		else if(plaintext[j]=='D' || plaintext[j]=='d')
			count[3] += 1;
		else if(plaintext[j]=='E' || plaintext[j]=='e')
			count[4] += 1;
		else if(plaintext[j]=='F' || plaintext[j]=='f')
			count[5] += 1;
		else if(plaintext[j]=='G' || plaintext[j]=='g')
			count[6] += 1;
		else if(plaintext[j]=='H' || plaintext[j]=='h')
			count[7] += 1;
		else if(plaintext[j]=='I' || plaintext[j]=='i')
			count[8] += 1;
		else if(plaintext[j]=='J' || plaintext[j]=='j')
			count[9] += 1;
		else if(plaintext[j]=='K' || plaintext[j]=='k')
			count[10] += 1;
		else if(plaintext[j]=='L' || plaintext[j]=='l')
			count[11] += 1;
		else if(plaintext[j]=='M' || plaintext[j]=='m')
			count[12] += 1;
		else if(plaintext[j]=='N' || plaintext[j]=='n')
			count[13] += 1;
		else if(plaintext[j]=='O' || plaintext[j]=='o')
			count[14] += 1;
		else if(plaintext[j]=='P' || plaintext[j]=='p')
			count[15] += 1;
		else if(plaintext[j]=='Q' || plaintext[j]=='q')
			count[16] += 1;
		else if(plaintext[j]=='R' || plaintext[j]=='r')
			count[17] += 1;
		else if(plaintext[j]=='S' || plaintext[j]=='s')
			count[18] += 1;
		else if(plaintext[j]=='T' || plaintext[j]=='t')
			count[19] += 1;
		else if(plaintext[j]=='U' || plaintext[j]=='u')
			count[20] += 1;
		else if(plaintext[j]=='V' || plaintext[j]=='v')
			count[21] += 1;
		else if(plaintext[j]=='W' || plaintext[j]=='w')
			count[22] += 1;
		else if(plaintext[j]=='X' || plaintext[j]=='x')
			count[23] += 1;
		else if(plaintext[j]=='Y' || plaintext[j]=='y')
			count[24] += 1;
		else if(plaintext[j]=='Z' || plaintext[j]=='z')
			count[25] += 1;
		else if(plaintext[j]==' ')
			spaceCountReal += 1;
	}
	for(int k = 0; k < 26; ++k){
		chiSquares[k] = pow((count[k]/strlen(plaintext)-allLetterStats_short[k]),2)/allLetterStats_short[k];
	}
	chiSquares[26] = pow(spaceCountReal-spaceCountExpected,2)/spaceCountExpected;
	for(int i = 0; i < 27; ++i)
		score += chiSquares[i];

	return score;
}

/***************************************************************
*															   *
*			// getHammingDistance() //						   *
*															   *
****************************************************************/
int getHammingDistance(char* str1, char* str2){

	if(strlen(str1)!=strlen(str2)){
		printf("The Hamming distance is reserved for strings of equal length. Terminating (1).\n");
		exit(1);
	}else{
		int count = 0;
		char* binStr1 = (char*)malloc((8*strlen(str1)+1)*sizeof(char));
		char* binStr2 = (char*)malloc((8*strlen(str2)+1)*sizeof(char));
		binStr1 = prasciiStr2bin(str1);
		binStr2 = prasciiStr2bin(str2);
		for(int i = 0; i < strlen(binStr1);++i){
			if(binStr1[i]!=binStr2[i])
				++count;
		}
		free(binStr1);
		free(binStr2);
		return count;
	}
}
/***************************************************************
*															   *
*			// gcd() //										   *
*															   *
****************************************************************/
int gcd(int x,int y){
	
	int g;
	if(x<0)
		x=-x;
	
	if(y<0)
		y=-y;
	
	if(x+y==0)
		return x;
	
	g = y;
	while(x > 0){
	   g = x;
	   x = y%x;
	   y = g;
	}
	return g;
}
/***************************************************************
*															   *
*			// multiple_gcd() //							   *
*															   *
****************************************************************/
int multiple_gcd(int m,int* x){
	
	size_t i;
	int g;
	if(m<1)
		return 0;

	g = x[0];
	for(i = 1; i < m; ++i)
		g = gcd(g,x[i]);
	
	return g;
}

/***************************************************************
*															   *
*			// totient() //									   *
*															   *
****************************************************************/
int totient(int x){
	int n = 0;
	for(int i = 1; i < x; ++i){
		if(gcd(i,x)==1)
			n++;
	}
	return n;
}

/***************************************************************
*															   *
*			// modexp() //									   *
*															   *
****************************************************************/
int modexp(int, int, int){

	int s,t,u;
	s = 1;
	t = x;
	u = y;

	while(u){
		if(u&1)
			s = (s*t)%n;
		u>>=1;
		t = (t*t)%n;
	}
	return(s);
}

/***************************************************************
*															   *
*			// chinese_remainder() //						   *
*															   *
****************************************************************/
int chinese_remainder(size_t r, int* m, int* u){

	size_t i;
	int modulus;
	int n = 0;

	modulus = 1;
	for(i = 0; i < r; ++i)
		modulus *=m[i];
	
	for(i = 0; i < r; ++i){
		n += u[i] * modexp(modulus / m[i],totient(m[i]),m[i]);
		n %= modulus;
	}

	return n;
}

/***************************************************************
*															   *
*			// xorcyph_getSingleByteHexKey() //				   *
*															   *
****************************************************************/
char* xorcyph_getSingleByteBinKey(char* bin){   

	double scores[97];
	memset(scores, 0,97);
	int len = strlen(bin); // get length of input
	int keyIndex = 0;
    for(int i = 0;i<97;++i){ // for every plaintext letter
		char* key = (char*)malloc((len+1)*sizeof(char));
		char* xord = (char *)malloc((len+1)*sizeof(char));
		char* plaintext = (char*)malloc((len/8+1)*sizeof(char));
		for(int j = 0; j<len/8;++j){
			memcpy(&key[8*j],bin8_table[i],8);
		}
		key[len]='\0';
		memcpy(xord,strxor(bin,key),len);//try decryption with key
		xord[len] = '\0';
		memcpy(plaintext, bin2prasciiStr(xord),len/8); // Convert binary to ASCII
		plaintext[len/8] = '\0';
		scores[i] = scorePlaintext_chiSquare(plaintext);
		free(key);
		free(xord);
		free(plaintext);
	}
	keyIndex = findMinElement(scores,97);
	return bin8_table[keyIndex];
}
/***************************************************************
*															   *
*			// xorcyph_encryptHexKey() //					   *
*															   *
****************************************************************/
char* xorcyph_encryptHexKey(char* plaintext, char* hexKey){

	int len = strlen(plaintext);
	int keyLen = strlen(hexKey);
	char* keyBuff = (char*)malloc((2*len+1)*sizeof(char));
	for(int i = 0; i<len;++i){
		int charsLeft = 2*len-keyLen*i;
		if(charsLeft>=keyLen){
			memcpy(&keyBuff[keyLen*i],hexKey,keyLen);
		}else{
			memcpy(&keyBuff[keyLen*i],hexKey,charsLeft);
			break;
		}
	}
	keyBuff[2*len]='\0';
	return hexxor(prasciiStr2hex(plaintext),keyBuff);
}

/***************************************************************
*															   *
*			// xorcyph_decryptHex() //						   *
*															   *
****************************************************************/
char* xorcyph_decryptHex(char* hex, char* key){   

	char* keyBuff = (char*)malloc((strlen(hex)+1)*sizeof(char));
	char* plainHex;
	if(strlen(hex)!=strlen(key)){
		for(int k = 0; k<strlen(hex)/2;++k){
			memcpy(&keyBuff[2*k],key,2);
		}
		keyBuff[strlen(hex)]='\0';
	}else
		keyBuff = key;
	
	plainHex = hexxor(hex,keyBuff);
	free(keyBuff);
	return plainHex;
}

/***************************************************************
*															   *
*			// xorcyph_encryptPlainKey() //					   *
*															   *
****************************************************************/
char* xorcyph_encryptPlainKey(char* plaintext, char* plainKey){

	char* hexKey = prasciiStr2hex(plainKey);
	return xorcyph_encryptHexKey(plaintext,hexKey);
}

/***************************************************************
*															   *
*			// xorcyph_getSingleByteHexKey() //				   *
*															   *
****************************************************************/
char* xorcyph_getSingleByteHexKey(char* hex){   

	double scores[97];
	memset(scores, 0,97);
	int len = strlen(hex); // get length of input
	int keyIndex = 0;
    for(int i = 0;i<97;++i){ // for each of 16 hex chars
		char* key = (char*)malloc((len+1)*sizeof(char));
		char* xord = (char *)malloc((len+1)*sizeof(char));
		char* plaintext = (char*)malloc((len/2+1)*sizeof(char));
		for(int j = 0; j<len/2;++j){
			memcpy(&key[2*j],hex2_table[i],2);
		}
		key[len]='\0';
		memcpy(xord,hexxor(hex,key),len+1);//try decryption with key
		memcpy(plaintext, hex2prasciiStr(xord),len/2); // Convert binary to ASCII
		plaintext[len/2] = '\0';
		scores[i] = scorePlaintext_chiSquare(plaintext);
		free(key);
		free(xord);
		free(plaintext);
	}
	keyIndex = findMinElement(scores,97);
	return hex2_table[keyIndex];
}

/***************************************************************
*															   *
*			// xorcyph_encryptBinKey() //					   *
*															   *
****************************************************************/
char* xorcyph_encryptBinKey(char* plaintext, char* binKey){

	int len = strlen(plaintext);
	int keyLen = strlen(binKey);
	char* keyBuff = (char*)malloc((8*len+1)*sizeof(char));
	for(int i = 0; i<len;++i){
		int charsLeft = 8*len-keyLen*i;
		if(charsLeft>=keyLen){
			memcpy(&keyBuff[keyLen*i],binKey,keyLen);
		}else{
			memcpy(&keyBuff[keyLen*i],binKey,charsLeft);
			break;
		}
	}
	keyBuff[8*len]='\0';
	return strxor(prasciiStr2bin(plaintext),keyBuff);
}

/***************************************************************
*															   *
*			// xorcyph_decryptBin() //				   		   *
*															   *
****************************************************************/
char* xorcyph_decryptBin(char* bin, char* key){   

	int len = strlen(bin);
	char* keyBuff = (char*)malloc((len+1)*sizeof(char));
	for(int k = 0; k<len/8;++k){
		memcpy(&keyBuff[8*k],key,8);
	}
	keyBuff[len]='\0';

	return strxor(bin,keyBuff);
}

/***************************************************************
*															   *
*			// xorcyph_findEncryptedHexLine() //			   *
*															   *
****************************************************************/
int xorcyph_findEncryptedHexLine(char** lines, int numLines){

	double scores[numLines];
	int index,line_length = 60;
	char** decryptedLines = (char**)malloc((numLines)*sizeof(char));
	memset(scores,0,numLines);
	for(int i = 0; i < numLines; ++i){
		decryptedLines[i] = (char*)malloc((line_length+1)*sizeof(char));
		char* lineKey = xorcyph_getSingleByteHexKey(lines[i]);
		decryptedLines[i] = hex2prasciiStr(xorcyph_decryptHex(lines[i],lineKey));
		scores[i] = scorePlaintext_chiSquare(decryptedLines[i]);
		free(decryptedLines[i]);
	}
	index = findMinElement(scores,numLines);
	return index;
}

/***************************************************************
*																*
*			// xorcyph_findLeastNormalizedHammingBytes() //		*
*																*
****************************************************************/
int* xorcyph_findLeastNormalizedHammingBytes(char* bin, int n){

	int MAX_KEYSIZE = 40;
	if(MAX_KEYSIZE > strlen(bin)/16){
		printf("Error: Key size cannot be larger than %d for this string. Terminating.\n",strlen(bin)/16);
		exit(1);
	}
	if(n > MAX_KEYSIZE){
		printf("Error: Either decrease number of bytes or increase MAX_KEYSIZE. Terminating.\n");
		exit(1);
	}
	double* hammingDistances = (double*)malloc((MAX_KEYSIZE)*sizeof(double));
	for(int keySize = 2;keySize <= MAX_KEYSIZE; ++keySize){
		char* block1 = (char*)malloc((8*keySize+1)*sizeof(char));
		char* block2 = (char*)malloc((8*keySize+1)*sizeof(char));
		memcpy(block1,bin,8*keySize);
		memcpy(block2,&bin[8*keySize],8*keySize);
		block1[8*keySize] = '\0';
		block2[8*keySize] = '\0';
		hammingDistances[keySize-2] = (double)getHammingDistance(block1,block2)/keySize;
		free(block1);
		free(block2);
	}
	int* byteSizes = malloc(n*sizeof(int));
	for(int i = 0; i < n; ++i){
		int indexMin = findMinElement(hammingDistances,MAX_KEYSIZE-1);
		byteSizes[i] = indexMin+2;
		hammingDistances[indexMin] = pow(2,16);
	}
	free(hammingDistances);
	return byteSizes;
}

/***************************************************************
*																*
*			// xorcyph_decryptNbyteRepKey() //          	    *
*																*
****************************************************************/
char* xorcyph_decryptNbyteRepKey(char* bin, int keySize){

	/* Break cipher text into keySize blocks -- VERIFIED*/
	int numBlocks = strlen(bin)/(8*keySize); // number of block to analyze
	char partitionsArray[numBlocks][8*keySize+1];
	char partitionsArrayT[keySize][8*numBlocks+1];

	printf("Creating %d partitions (%d bytes each) from ciphertext ...",numBlocks,keySize);
	for(int i = 0; i<numBlocks;++i){
		memcpy(partitionsArray[i],&bin[8*i*keySize],8*keySize);
		partitionsArray[i][8*keySize] = '\0';
																						//printf("partitions[%d]: %s\n\n", i, partitionsArray[i]);
	}

	/* Transpose blocks so that each new block i contains the i'th ordered byte of each old block -- VERIFIED*/
	printf("Success.\nJoining the first byte of each partition to create %d new partitions (%d bytes each) ...", keySize,numBlocks);
	for(int i = 0; i < keySize; ++i){
		for(int j = 0; j < numBlocks; ++j){
			//printf("Printing partitions[%d]: %s", j,8*i,partitions[j]);
			memcpy(&partitionsArrayT[i][8*j],&partitionsArray[j][8*i],8);
			//if(j==numBlocks-1)
			//	partitionsT[i][8*(j+1)] = '\0';
		}
	}
	
	printf("Success.\nPerforming single byte XOR decryption on each partition ...");
	char* cipherKey = malloc((8*keySize+1));
	if(!cipherKey){
		printf("Cannot allocate memory for cipherKey. Terminating.\n");
		exit(1);
	}
	for(int i = 0; i < keySize; ++i){ 
		//printf("Decrypting Partition #%d\n",i+1);
		double scores[97];
		memset(scores, 0,97);
		int len = strlen(partitionsArrayT[i]); // get length of input
		char* partitionsT = partitionsArrayT[i];
		int keyIndex = 0;

		/* For every potential 1 byte key, attempt decryption of partition. Record scores. */
	    for(int j = 0;j<97;++j){
			//printf("Extending key: %s...",bin8_table[j]); 
			char* key = (char*)malloc((len+1)*sizeof(char));
			char* xord = (char *)malloc((len+1)*sizeof(char));
			char* plaintext = (char*)malloc((len/8+1)*sizeof(char));

			/* Duplicate key into string until size matches partition */
			for(int k = 0; k<len/8;++k){
				memcpy(&key[8*k],bin8_table[j],8);
			}
			key[len]='\0';
			//printf("Complete.\nXOR'ing with ciphertext ...");
			/* XOR the cipher text with key and convert to ASCII */
			//printf("Printing key: %s (%d chars)\n", key, strlen(key));
			//printf("Printing partition: %s (%d chars)\n", partitionsT, strlen(partitionsT));
			memcpy(xord,strxor(partitionsT,key),len+1);//try decryption with key
			xord[len] = '\0';
			//printf("Complete.\nConverting to ASCII ...", xord);
			strcpy(plaintext, bin2prasciiStr(xord)); // Convert binary to ASCII
			//printf("Key: %s\n Plaintext: %s\n", key, plaintext);
			//printf("Plaintext[%d]: %s\n",i, plaintext);
			//printf("xorcyph_decrypt(): Successfully converted XOR'd input to plaintext ... \n");
			//printf("Complete.\nScoring plaintext ...");
			plaintext[len/8] = '\0';
			/* Score the resulting plaintext */
			scores[j] = scorePlaintext_chiSquare(plaintext);
			//printf("Complete.\nFreeing key ...");
			//printf("xorcyph_decrypt(): Successfully scored plaintext ... \n");
			free(key);
			//printf("Complete.\nFreeing xord ...");
			free(xord);
			//printf("Complete.\nFreeing plaintext...");
			//free(plaintext);
			//printf("Complete.\n");
			//printf("xorcyph_decrypt(): Successfully freed plaintext ... \n");
		}
		//printf("Exited for loop.\n");
		/* Print all scores */
		//printf("The scores for partition #%d are:\n",i);
		for(int q = 0; q < 97; ++q){
			//printf("scores[%d] = %s: %f\n", q,bin8_table[q],scores[q]);
		}
		/* Find the highest scoring 1-byte key and save it*/
		keyIndex = findMinElement(scores,97);
		char* byteKey = bin8_table[keyIndex];
		if(i==0)
			strcpy(cipherKey,byteKey);
		else
			strcat(cipherKey,byteKey);
		//printf("Printing key for byte %d: %s\n", i+1,byteKey);
		//printf("Highest score: %f (scores[%d])\n", scores[keyIndex],keyIndex);
	}
	cipherKey[8*keySize] = '\0';
	//printf("Success.\nPrinting Vigenere Cipher key: %s\n", cipherKey);
	
	return cipherKey;
}
