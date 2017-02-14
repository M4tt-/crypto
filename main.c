/****************************************************************************
 *                                                                          *
 * Filename: main.c                                                         *
 *																			*
 * Author: Matt Runyon														*					
 *                                                                          *
 * Purpose : Test Suite for crypto library				                    *
 *                                                                          *
 * Last Upated : 02-14-17		 							 				*
 *																			*
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "crutil.h"
//#include "GnuWin32\include\openssl\opensslconf.h"
//#include "GnuWin32\include\openssl\e_os2.h"
//#include "GnuWin32\include\openssl\bio.h"
//#include "GnuWin32\include\openssl\conf.h"
//#include "GnuWin32\include\openssl\evp.h"
//#include "GnuWin32\include\openssl\err.h"
//#include "GnuWin32\include\openssl\aes.h"

#define ECB 1

int main(void) {
 	
	char bit0 = '0';
	char bit1 = '1';
	double arr1[] = {0,1,2,3,4,5,6,7,8,9};
	double arr2[] = {9,8,7,6,5,4,3,2,1,0};
	double arr3[] = {1,1,1,1,1,1,1};
	double arr4[] = {1.123,6.43,-8.32,-19375.23,1.0000001,-234.54,6.42};
	double arr5[] = {1.123,6.43,-8.32,-19375.23,1.0000001,-234.54,6.431};
	double arr6[] = {1.123,6.43,-8.32,-19375.23,1.0000001,-19375.24,6.431};
	char** fileLines;

	char* case1 = hex2bin('A');
	char* case2 = hex2bin('B');
	char* case3 = hex2bin('7');
	char* case4 = hex2bin('E');
	
	printf("Testing hex2bin ...\n\n");
	printf("Case 1: 'A':\n");
	printf("Expected Result: 1010.\n");
	printf("Actual Result:   %s.\n\n", case1);
	printf("Case 2: 'B':\n");
	printf("Expected Result: 1011.\n");
	printf("Actual Result:   %s.\n\n", case2);
	printf("Case 3: '7':\n");
	printf("Expected Result: 0111.\n");
	printf("Actual Result:   %s.\n\n", case3);
	printf("Case 4: 'F':\n");
	printf("Expected Result: 1111.\n");
	printf("Actual Result:   %s.\n\n", case4);

	case1 = hexStr2bin("AF");
	case2 = hexStr2bin("9D2");
	case3 = hexStr2bin("5c2B");
	case4 = hexStr2bin("EE09F");
	char* case5 = hexStr2bin("095A26");
	char* case6 = hexStr2bin("F5DC380AF");
	char* case7 = hexStr2bin("F5DC380ABE");
	char* case8 = hexStr2bin("F5DC380ABEC452F");
	char* case9 = hexStr2bin("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	printf("Testing hexStr2bin ...\n\n");
	printf("Case 1: 'Length of hex string equal to 2':\n");
	printf("Expected Result: 10101111.\n");
	printf("Actual Result:   %s.\n\n", case1);
	printf("Case 2: 'Length of hex string equal to 3':\n");
	printf("Expected Result: 100111010010.\n");
	printf("Actual Result:   %s.\n\n", case2);
	printf("Case 3: 'Length of hex string equal to 4 (mixed lower case/upper case)':\n");
	printf("Expected Result: 0101110000101011.\n");
	printf("Actual Result:   %s.\n\n", case3);
	printf("Case 4: 'Length of hex string equal to 5':\n");
	printf("Expected Result: 11101110000010011111.\n");
	printf("Actual Result:   %s.\n\n", case4);
	printf("Case 5: 'Length of hex string equal to 6':\n");
	printf("Expected Result: 000010010101101000100110.\n");
	printf("Actual Result:   %s.\n\n", case5);
	printf("Case 6: 'Length of hex string equal to 9':\n");
	printf("Expected Result: 111101011101110000111000000010101111.\n");
	printf("Actual Result:   %s.\n\n", case6);
	printf("Case 7: 'Length of hex string equal to 10':\n");
	printf("Expected Result: 1111010111011100001110000000101010111110.\n");
	printf("Actual Result:   %s.\n\n", case7);
	printf("Case 8: 'Length of hex string equal to 15':\n");
	printf("Expected Result: 111101011101110000111000000010101011111011000100010100101111.\n");
	printf("Actual Result:   %s.\n\n", case8);
	printf("Case 9: 'Length of hex string equal to 60':\n");
	printf("Expected Result: ?.\n");
	printf("Actual Result:   %s.\n\n", case9);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);
	free(case8);
	free(case9);

    printf("Testing bin2hexChar ...\n\n");
	printf("Case 1: 0000:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0000"));
	printf("Case 2: 0001:\n");
	printf("Expected Result: 1\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0001"));
	printf("Case 3: 0010:\n");
	printf("Expected Result: 2\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0010"));
	printf("Case 4: 0011:\n");
	printf("Expected Result: 3\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0011"));
	printf("Case 5: 0100:\n");
	printf("Expected Result: 4\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0100"));
	printf("Case 6: 0101:\n");
	printf("Expected Result: 5\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0101"));
	printf("Case 7: 0110:\n");
	printf("Expected Result: 6\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0110"));
	printf("Case 8: 0111:\n");
	printf("Expected Result: 7\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("0111"));
	printf("Case 9: 1000:\n");
	printf("Expected Result: 8\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1000"));
	printf("Case 10: 1001:\n");
	printf("Expected Result: 9\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1001"));
	printf("Case 11: 1010:\n");
	printf("Expected Result: A\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1010"));
	printf("Case 12: 1011:\n");
	printf("Expected Result: B\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1011"));
	printf("Case 13: 1100:\n");
	printf("Expected Result: C\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1100"));
	printf("Case 14: 1101:\n");
	printf("Expected Result: D\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1101"));
	printf("Case 15: 1110:\n");
	printf("Expected Result: E\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1110"));
	printf("Case 16: 1111:\n");
	printf("Expected Result: F\n");
	printf("Actual Result:   %c\n\n", bin2hexChar("1111"));

	case1 = bin2b64Str("11100101");
	case2 = bin2b64Str("000000111110");
	case3 = bin2b64Str("1000001100110");
	case4 = bin2b64Str("1000001100110010101");
	case5 = bin2b64Str("111100111101111110111111");
	case6 = bin2b64Str("100001110010011011110110111101101101");
	case7 = bin2b64Str("101110101111110000110001110010110011110100110101110110");
    printf("Testing bin2b64Str ...\n\n");
	printf("Case 1: 'Length of binary string greater than 6 (8 bits)':\n");
	printf("Expected Result: Dl\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: 'Length of binary string greater than 6 (12 bits)':\n");
	printf("Expected Result: A+\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: 'Length of binary string greater than 6 (13 bits)':\n");
	printf("Expected Result: BBm\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: 'Length of binary string greater than 6 (19 bits)':\n");
	printf("Expected Result: BBmV\n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: 'Length of binary string greater than 6 (24 bits)':\n");
	printf("Expected Result: 89+/\n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: 'Length of binary string greater than 6 (36 bits)':\n");
	printf("Expected Result: hyb29t\n");
	printf("Actual Result:   %s\n\n", case6);
	printf("Case 7: 'Length of binary string greater than 6 (54 bits)':\n");
	printf("Expected Result: uvwxyz012\n");
	printf("Actual Result:   %s\n\n", case7);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);
	
    printf("Testing b64Char2bin ...\n\n");
	printf("Case 1: Converting 'A' to binary:\n");
	printf("Expected Result: 000000\n");
	printf("Actual Result:   %s\n\n", b64Char2bin('A'));
	printf("Case 2: Converting 'J' to binary:\n");
	printf("Expected Result: 001001\n");
	printf("Actual Result:   %s\n\n", b64Char2bin('J'));
	printf("Case 3: Converting 'd' to binary:\n");
	printf("Expected Result: 011101\n");
	printf("Actual Result:   %s\n\n", b64Char2bin('d'));
	printf("Case 4: Converting '0' to binary:\n");
	printf("Expected Result: 110100\n");
	printf("Actual Result:   %s\n\n", b64Char2bin('0'));
	printf("Case 5: Converting '/' to binary:\n");
	printf("Expected Result: 111111\n");
	printf("Actual Result:   %s\n\n", b64Char2bin('/'));
	
	case1 = b642bin("AA==");
	case2 = b642bin("d8Q=");
	case3 = b642bin("+aHg");
	case4 = b642bin("p8sNho3/");
	case5 = b642bin("kNSHd94m7uyT4dg=");
	case6 = b642bin("su8d+wd/8ajbVnRq7w==");
	case7 = b642bin("HUIfTQsPAh9PE048");
	case8 = b642bin("HUIfTQsPAh9PE048Gmll");
	printf("Testing b642bin ...\n\n");
	printf("Case 1: Converting 'AA==' to bin:\n");
	printf("Expected Result: 00000000\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: Converting 'd8Q=' to bin:\n");
	printf("Expected Result: 0111011111000100\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: Converting '+aHg' to bin:\n");
	printf("Expected Result: 111110011010000111100000\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: Converting 'p8sNho3/' to bin:\n");
	printf("Expected Result: 101001111100101100001101100001101000110111111111\n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: Converting 'kNSHd94m7uyT4dg=' to bin:\n");
	printf("Expected Result: 1001000011010100100001110111011111011110001001101110111011101100100100111110000111011000\n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: Converting 'su8d+wd/8ajbVnRq7w==' to bin:\n");
	printf("Expected Result: 10110010111011110001110111111011000001110111111111110001101010001101101101010110011101000110101011101111\n");
	printf("Actual Result:   %s\n\n", case6);
	printf("Case 7: Converting 'HUIfTQsPAh9PE048' to bin:\n");
	printf("Expected Result: 000111010100001000011111010011010000101100001111000000100001111101001111000100110100111000111100\n");
	printf("Actual Result:   %s\n\n", case7);
	printf("Case 8: Converting 'HUIfTQsPAh9PE048Gmll' to bin:\n");
	printf("Expected Result: 000111010100001000011111010011010000101100001111000000100001111101001111000100110100111000111100000110100110100101100101\n");
	printf("Actual Result:   %s\n\n", case8);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);
	free(case8);
	
	case1 = bin2hexStr("11100101");
	case2 = bin2hexStr("000000111110");
	case3 = bin2hexStr("1000001100110");
	case4 = bin2hexStr("1000001100110010101");
	case5 = bin2hexStr("111100111101111110111111");
	case6 = bin2hexStr("100001110010011011110110111101101101");
	case7 = bin2hexStr("111101010011101000111100111100011010111001");
	case8 = bin2hexStr("101110101111110000110001110010110011110100110101110110");
	case9 = bin2hexStr("100111010011101101011100111100011010111001000110100001101010");
	printf("Testing bin2hexStr ...\n\n");
	printf("Case 1: 11100101 (8 bits):\n");
	printf("Expected Result: E5\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: 000000111110 (12 bits):\n");
	printf("Expected Result: 03E\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: 1000001100110 (13 bits):\n");
	printf("Expected Result: 1066\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: 1000001100110010101 (19 bits):\n");
	printf("Expected Result: 41995\n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: 111100111101111110111111 (24 bits):\n");
	printf("Expected Result: F3DFBF\n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: 100001110010011011110110111101101101 (36 bits):\n");
	printf("Expected Result: 8726F6F6D\n");
	printf("Actual Result:   %s\n\n", case6);
	printf("Case 7: 111101010011101000111100111100011010111001 (42 bits):\n");
	printf("Expected Result: 3D4E8F3C6B9\n");
	printf("Actual Result:   %s\n\n", case7);
	printf("Case 8: 101110101111110000110001110010110011110100110101110110 (54 bits):\n");
	printf("Expected Result: 2EBF0C72CF4D76\n");
	printf("Actual Result:   %s\n\n", case8);
	printf("Case 9: 100111010011101101011100111100011010111001000110100001101010 (60 bits):\n");
	printf("Expected Result: 9D3B5CF1AE4686A\n");
	printf("Actual Result:   %s\n\n", case9);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);
	free(case8);
	free(case9);
	
	printf("Testing charand ...\n\n");
	printf("Case 1: 0&1:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", charand(bit0,bit1));
	printf("Case 2: 1&0:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", charand(bit1,bit0));
	printf("Case 3: 0&0:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", charand(bit0,bit0));
	printf("Case 4: 1&1:\n");
	printf("Expected Result: 1\n");
	printf("Actual Result:   %c\n\n", charand(bit1,bit1));

	case1 = strand("00","01");
	case2 = strand("01","01");
	case3 = strand("111","101");
	case4 = strand("10101110","10010011");
	printf("Testing strand ...\n\n");
	printf("Case 1: 00&01: (2-bit AND)\n");
	printf("Expected Result: 00\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: 01&01: (2-bit AND)\n");
	printf("Expected Result: 01\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: 111&101: (3-bit AND)\n");
	printf("Expected Result: 101\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: 10101110&10010011: (8-bit AND)\n");
	printf("Expected Result: 10000010\n");
	printf("Actual Result:   %s\n\n", case4);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	
	printf("Testing charxor ...\n\n");
	printf("Case 1: 0^1:\n");
	printf("Expected Result: 1\n");
	printf("Actual Result:   %c\n\n", charxor(bit0,bit1));
	printf("Case 2: 1^0:\n");
	printf("Expected Result: 1\n");
	printf("Actual Result:   %c\n\n", charxor(bit1,bit0));
	printf("Case 3: 0^0:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", charxor(bit0,bit0));
	printf("Case 4: 1^1:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", charxor(bit1,bit1));
	
	case1 = strxor("0000","0001");
	case2 = strxor("1010","1011");
	case3 = strxor("10000","11101");
	case4 = strxor("110011","010101");
	case5 = strxor("1010101","0101010");
	case6 = strxor("11100101","11001100");
	case7 = strxor("100110100101010101011100110101001101010101101110","000001001001001001110101111101101101101101001100");
	printf("Testing strxor ...\n\n");
	printf("Case 1: %s^%s (4 bit string):\n", "0000","0001");
	printf("Expected Result: 0001\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: %s^%s (4 bit string):\n","1010","1011");
	printf("Expected Result: 0001\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: %s^%s (5 bit string):\n","10000","11101");
	printf("Expected Result: 01101\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: %s^%s (6 bit string):\n","110011","010101");
	printf("Expected Result: 100110\n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: %s^%s (7 bit string):\n","1010101","0101010");
	printf("Expected Result: 1111111\n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: %s^%s (8 bit string):\n","11100101","11001100");
	printf("Expected Result: 00101001 \n");
	printf("Actual Result:   %s\n\n", case6);
	printf("Case 7: 100110100101010101011100110101001101010101101110^000001001001001001110101111101101101101101001100 (48 bit string):\n","11100101","11001100");
	printf("Expected Result: 100111101100011100101001001000100000111000100010 \n");
	printf("Actual Result:   %s\n\n", case7);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);

	case1 = hexxor("AF","72");
	case2 = hexxor("9D2","E48");
	case3 = hexxor("5c2B","80F2");
	case4 = hexxor("EE09F","25CB3");
	case5 = hexxor("095A26","8D40F1");
	case6 = hexxor("1c0111001f010100061a024b53535009181c","686974207468652062756c6c277320657965");
	printf("Testing hexxor (i.e. CryptoPals Challenge 2, Set 1)...\n\n");
	printf("Case 1: %s^%s (2 hex chars):\n","AF","72");
	printf("Expected Result: DD\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: %s^%s (3 hex chars):\n","9D2","E48");
	printf("Expected Result: 79A\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: %s^%s (4 hex chars):\n","5c2B","80F2");
	printf("Expected Result: DCD9\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: %s^%s (5 hex chars):\n","EE09F","25CB3");
	printf("Expected Result: CBC2C\n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: %s^%s (6 hex chars):\n","095A26","8D40F1");
	printf("Expected Result: 841AD7\n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: %s^%s (36 hex chars):\n","1c0111001f010100061a024b53535009181c","686974207468652062756c6c277320657965");
	printf("Expected Result: 746865206b696420646f6e277420706c6179\n");
	printf("Actual Result:   %s\n\n", case6);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	
	case1 = dec2bin(0,8);
	case2 = dec2bin(1,8);
	case3 = dec2bin(2,8);
	case4 = dec2bin(3,8);
	case5 = dec2bin(23,8);
	case6 = dec2bin(64,8);
	case7 = dec2bin(132,8);
	case8 = dec2bin(200,8);
	case9 = dec2bin(120,7);
	printf("Testing dec2bin ...\n\n");
	printf("Case 1: Converting 0 (dec) to 8-bit binary:\n");
	printf("Expected Result: 00000000\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: Converting 1 (dec) to 8-bit binary:\n");
	printf("Expected Result: 00000001\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: Converting 2 (dec) to 8-bit binary:\n");
	printf("Expected Result: 00000010\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: Converting 3 (dec) to 8-bit binary:\n");
	printf("Expected Result: 00000011\n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: Converting 23 (dec) to 8-bit binary:\n");
	printf("Expected Result: 00010111\n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: Converting 64 (dec) to 8-bit binary:\n");
	printf("Expected Result: 01000000\n");
	printf("Actual Result:   %s\n\n", case6);
	printf("Case 7: Converting 132 (dec) to 8-bit binary:\n");
	printf("Expected Result: 10000100\n");
	printf("Actual Result:   %s\n\n", case7);
	printf("Case 8: Converting 200 (dec) to 8-bit binary:\n");
	printf("Expected Result: 11001000\n");
	printf("Actual Result:   %s\n\n", case8);
	printf("Case 9: Converting 120 (dec) to 7-bit binary:\n");
	printf("Expected Result: 1111000\n");
	printf("Actual Result:   %s\n\n", case9);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);
	free(case8);
	free(case9);

	printf("Testing printNbitBin ...\n\n");
	printf("Case 1: Printing 1-bit binary numbers:\n");
	printf("Actual Result:\n");
	printNbitBin(1);
	printf("Case 2: Printing 2-bit binary numbers:\n");
	printf("Actual Result:\n");
	printNbitBin(2);
	printf("Case 3: Printing 3-bit binary numbers:\n");
	printf("Actual Result:\n");
	printNbitBin(3);

	printf("Testing bin2prasciiChar ...\n\n");
	printf("Case 1: Converting 00100000 to ASCII:\n");
	printf("Expected Result:   \n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("00100000"));
	printf("Case 2: Converting 00100001 to ASCII:\n");
	printf("Expected Result: !\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("00100001"));
	printf("Case 3: Converting 00110000 to ASCII:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("00110000"));
	printf("Case 4: Converting 00111000 to ASCII:\n");
	printf("Expected Result: 8\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("00111000"));
	printf("Case 5: Converting 01000001 to ASCII:\n");
	printf("Expected Result: A\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01000001"));
	printf("Case 6: Converting 01000101 to ASCII:\n");
	printf("Expected Result: E\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01000101"));
	printf("Case 7: Converting 01001101 to ASCII:\n");
	printf("Expected Result: M\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01001101"));
	printf("Case 8: Converting 01010111 to ASCII:\n");
	printf("Expected Result: W\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01010111"));
	printf("Case 9: Converting 01011011 to ASCII:\n");
	printf("Expected Result: [\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01011011"));
	printf("Case 10: Converting 01100001 to ASCII:\n");
	printf("Expected Result: a\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01100001"));
	printf("Case 11: Converting 01100111 to ASCII:\n");
	printf("Expected Result: g\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01100111"));
	printf("Case 12: Converting 01110000 to ASCII:\n");
	printf("Expected Result: p\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01110000"));
	printf("Case 13: Converting 01111010 to ASCII:\n");
	printf("Expected Result: z\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01111010"));
	printf("Case 14: Converting 01100101 to ASCII:\n");
	printf("Expected Result: e\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01100101"));
	printf("Case 15: Converting 01110100 to ASCII:\n");
	printf("Expected Result: t\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01110100"));
	printf("Case 16: Converting 01110011 to ASCII:\n");
	printf("Expected Result: s\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01110011"));
	printf("Case 17: Converting 01111110 to ASCII:\n");
	printf("Expected Result: ~\n");
	printf("Actual Result:   %c\n\n", bin2prasciiChar("01111110"));

	case1 = bin2prasciiStr("0110100001100101011011000110110001101111");
	case2 = bin2prasciiStr("01100101010101000100000101001111010010010100111000100000011100110100100001010010010001000100110001010101");
	case3 = bin2prasciiStr("0100110100110100011101000111010000101101");
	case4 = bin2prasciiStr("0100100101101100011011110111011001100101011110010110111101110101");
	printf("Testing bin2prasciiStr ...\n\n");
	printf("Case 1: Converting 0110100001100101011011000110110001101111 to ASCII:\n");
	printf("Expected Result: hello\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: Converting 01100101010101000100000101001111010010010100111000100000011100110100100001010010010001000100110001010101 to ASCII:\n");
	printf("Expected Result: eTAOIN sHRDLU\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: Converting 0100110100110100011101000111010000101101 to ASCII:\n");
	printf("Expected Result: M4tt-\n");
	printf("Actual Result:   %s\n\n", case3);
	
	printf("Case 4: Converting Kristin's Valentine's Day card to ASCII...:\n");
	printf("Expected Result: i love you\n");
	printf("Actual Result:   %s\n\n", case4);
	free(case1);
	free(case2);
	free(case3);
	free(case4);

	case1 = prasciiChar2bin('E');
	case2 = prasciiChar2bin('T');
	case3 = prasciiChar2bin('A');
	case4 = prasciiChar2bin('O');
	case5 = prasciiChar2bin('I');
	case6 = prasciiChar2bin('N');
	case7 = prasciiChar2bin('s');
	case8 = prasciiChar2bin('h');
	case9 = prasciiChar2bin('\"');
	printf("Testing prasciiChar2bin ...\n\n");
	printf("Case 1: Converting E to binary:\n");
	printf("Expected Result: 01000101 \n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: Converting T to binary:\n");
	printf("Expected Result: 01010100 \n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: Converting A to binary:\n");
	printf("Expected Result: 01000001 \n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: Converting O to binary:\n");
	printf("Expected Result: 01001111 \n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: Converting I to binary:\n");
	printf("Expected Result: 01001001 \n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: Converting N to binary:\n");
	printf("Expected Result: 01001110 \n");
	printf("Actual Result:   %s\n\n", case6);
	printf("Case 7: Converting s to binary:\n");
	printf("Expected Result: 01110011 \n");
	printf("Actual Result:   %s\n\n", case7);
	printf("Case 8: Converting h to binary:\n");
	printf("Expected Result: 01101000 \n");
	printf("Actual Result:   %s\n\n", case8);
	printf("Case 9: Converting \" to binary:\n");
	printf("Expected Result: 00100010 \n");
	printf("Actual Result:   %s\n\n", case9);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);
	free(case8);
	free(case9);

	case1 = prasciiStr2bin("Curvilinear");
	case2 = prasciiStr2bin("Rectilinear");
	case3 = prasciiStr2bin("-Goldeneye007");
	printf("Testing prasciiStr2bin ...\n\n");
	printf("Case 1: Converting 'Curvilinear' to binary:\n");
	printf("Expected Result: 0100001101110101011100100111011001101001011011000110100101101110011001010110000101110010\n");
	printf("Actual Result:   %s\n\n", prasciiStr2bin("Curvilinear"));
	printf("Case 2: Converting 'Rectilinear' to binary:\n");
	printf("Expected Result: 0101001001100101011000110111010001101001011011000110100101101110011001010110000101110010\n");
	printf("Actual Result:   %s\n\n", prasciiStr2bin("Rectilinear"));
	printf("Case 3: Converting '-Goldeneye007' to binary:\n");
	printf("Expected Result: 00101101010001110110111101101100011001000110010101101110011001010111100101100101001100000011000000110111 \n");
	printf("Actual Result:   %s\n\n", prasciiStr2bin("-Goldeneye007"));
	free(case1);
	free(case2);
	free(case3);
	
	printf("Testing hex2prasciiChar ...\n\n");
	printf("Case 1: Converting 0x20 to ASCII:\n");
	printf("Expected Result:   \n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("20"));
	printf("Case 2: Converting 0x21 to ASCII:\n");
	printf("Expected Result: !\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("21"));
	printf("Case 3: Converting 0x30 to ASCII:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("30"));
	printf("Case 4: Converting 0x38 to ASCII:\n");
	printf("Expected Result: 8\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("38"));
	printf("Case 5: Converting 0x41 to ASCII:\n");
	printf("Expected Result: A\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("41"));
	printf("Case 6: Converting 0x45 to ASCII:\n");
	printf("Expected Result: E\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("45"));
	printf("Case 7: Converting 0x5B to ASCII:\n");
	printf("Expected Result: [\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("5b"));
	printf("Case 8: Converting 0x70 to ASCII:\n");
	printf("Expected Result: p\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("70"));
	printf("Case 9: Converting 0x65 to ASCII:\n");
	printf("Expected Result: e\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("65"));
	printf("Case 10: Converting 0x7E to ASCII:\n");
	printf("Expected Result: ~\n");
	printf("Actual Result:   %c\n\n", hex2prasciiChar("7e"));

	case1 = hex2prasciiStr("68656C6C6F");
	case2 = hex2prasciiStr("6554414f494e20734852444c55");
	case3 = hex2prasciiStr("4D3474742D");
	case4 = hex2prasciiStr("49BE65E3537826E725687ABCD59C467CA1B10146956FF19CA77564DD66BB7294E8361AE99772867AFF248F317B783215AB79FAADBD1E914E618558D7AC784350293CB0DA98D365D8");
	printf("Testing hex2prasciiStr ...\n\n");
	printf("Case 1: Converting 0x68656C6C6F to ASCII:\n");
	printf("Expected Result: hello\n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: Converting 0x6554414f494e20734852444c55 to ASCII:\n");
	printf("Expected Result: eTAOIN sHRDLU\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: Converting 0x4D3474742D to ASCII:\n");
	printf("Expected Result: M4tt-\n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: Converting 0x49BE65E3537826E725687ABCD59C467CA1B10146956FF19CA77564DD66BB7294E8361AE99772867AFF248F317B783215AB79FAADBD1E914E618558D7AC784350293CB0DA98D365D8 to ASCII:\n");
	printf("Expected Result: I0e0Sx&0%hz000F|000F0o000ud0f0r006000r0z0$01{x200y00000Na0X00xCP)<0000e0\n");
	printf("Actual Result:   %s\n\n", case4);
	free(case1);
	free(case2);
	free(case3);
	free(case4);

	case1 = prasciiChar2hex('E');
	case2 = prasciiChar2hex('T');
	case3 = prasciiChar2hex('A');
	case4 = prasciiChar2hex('O');
	case5 = prasciiChar2hex('I');
	case6 = prasciiChar2hex('N');
	case7 = prasciiChar2hex('s');
	case8 = prasciiChar2hex('h');
	case9 = prasciiChar2hex('\\');
	printf("Testing prasciiChar2hex ...\n\n");
	printf("Case 1: Converting E to hex:\n");
	printf("Expected Result: 45 \n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: Converting T to hex:\n");
	printf("Expected Result: 54 \n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: Converting A to hex:\n");
	printf("Expected Result: 41 \n");
	printf("Actual Result:   %s\n\n", case3);
	printf("Case 4: Converting O to hex:\n");
	printf("Expected Result: 4F \n");
	printf("Actual Result:   %s\n\n", case4);
	printf("Case 5: Converting I to hex:\n");
	printf("Expected Result: 49 \n");
	printf("Actual Result:   %s\n\n", case5);
	printf("Case 6: Converting N to hex:\n");
	printf("Expected Result: 4E \n");
	printf("Actual Result:   %s\n\n", case6);
	printf("Case 7: Converting s to hex:\n");
	printf("Expected Result: 73 \n");
	printf("Actual Result:   %s\n\n", case7);
	printf("Case 8: Converting h to hex:\n");
	printf("Expected Result: 68 \n");
	printf("Actual Result:   %s\n\n", case8);
	printf("Case 9: Converting \\ to hex:\n");
	printf("Expected Result: 5C \n");
	printf("Actual Result:   %s\n\n", case9);
	free(case1);
	free(case2);
	free(case3);
	free(case4);
	free(case5);
	free(case6);
	free(case7);
	free(case8);
	free(case9);

	case1 = prasciiStr2hex("Matt");
	case2 = prasciiStr2hex("\"Stokes Polarimetry\"");
	case3 = prasciiStr2hex("~itTakes12Know1.");
	printf("Testing prasciiStr2hex ...\n\n");
	printf("Case 1: Converting Matt to hex:\n");
	printf("Expected Result: 4D617474 \n");
	printf("Actual Result:   %s\n\n", case1);
	printf("Case 2: Converting '\"Stokes Polarimetry\"' to hex:\n");
	printf("Expected Result: 2253746F6B657320506F6C6172696D6574727922\n");
	printf("Actual Result:   %s\n\n", case2);
	printf("Case 3: Converting '~itTakes12Know1.' to hex:\n");
	printf("Expected Result: 7E697454616B657331324B6E6F77312E\n");
	printf("Actual Result:   %s\n\n", case3);
	free(case1);
	free(case2);
	free(case3);

	printf("Testing scorePlainText ...\n\n");
	printf("Case 1: plaintext -- 'Non-abelian geometric phase'\n");
	printf("Expected Result: 47.349 \n");
	printf("Actual Result:   %f\n\n", scorePlaintext("Non-abelian geometric phase"));
	printf("Case 2: plaintext -- 'Silicon Photonics':\n");
	printf("Expected Result: 22.966 \n");
	printf("Actual Result:   %f\n\n", scorePlaintext("Silicon Photonics"));
	printf("Case 3: plaintext -- 'y?zxw-238[]':\n");
	printf("Expected Result: -27.636 \n");
	printf("Actual Result:   %f\n\n", scorePlaintext("y?zxw-238[]"));

	printf("Testing findMaxElement ...\n\n");
	printf("Case 1: [0,1,2,3,4,5,6,7,8,9]\n");
	printf("Expected Result: 9 \n");
	printf("Actual Result:   %d\n\n", findMaxElement(arr1,10));
	printf("Case 2: [9,8,7,6,5,4,3,2,1,0]\n");
	printf("Expected Result: 0 \n");
	printf("Actual Result:   %d\n\n", findMaxElement(arr2,10));
	printf("Case 3: [1,1,1,1,1,1,1]\n");
	printf("Expected Result: 6 \n");
	printf("Actual Result:   %d\n\n", findMaxElement(arr3,7));
	printf("Case 4: [1.123,6.43,-8.32,-19375.23,1.0000001,-234.54,6.42]\n");
	printf("Expected Result: 1 \n");
	printf("Actual Result:   %d\n\n", findMaxElement(arr4,7));
	printf("Case 5: [1.123,6.43,-8.32,-19375.23,1.0000001,-234.54,6.431]\n");
	printf("Expected Result: 6 \n");
	printf("Actual Result:   %d\n\n", findMaxElement(arr5,7));

	printf("Testing findMinElement ...\n\n");
	printf("Case 1: [0,1,2,3,4,5,6,7,8,9]\n");
	printf("Expected Result: 0 \n");
	printf("Actual Result:   %d\n\n", findMinElement(arr1,10));
	printf("Case 2: [9,8,7,6,5,4,3,2,1,0]\n");
	printf("Expected Result: 9 \n");
	printf("Actual Result:   %d\n\n", findMinElement(arr2,10));
	printf("Case 3: [1,1,1,1,1,1,1]\n");
	printf("Expected Result: 6 \n");
	printf("Actual Result:   %d\n\n", findMinElement(arr3,7));
	printf("Case 4: [1.123,6.43,-8.32,-19375.23,1.0000001,-234.54,6.42]\n");
	printf("Expected Result: 3 \n");
	printf("Actual Result:   %d\n\n", findMinElement(arr4,7));
	printf("Case 5: [1.123,6.43,-8.32,-19375.23,1.0000001,-19375.24,6.431]\n");
	printf("Expected Result: 5 \n");
	printf("Actual Result:   %d\n\n", findMinElement(arr6,7));
	
	case1 = xorcyph_encryptHexKey("Matt","AA");
	case2 = xorcyph_encryptHexKey("\"Stokes Polarimetry\"","61");
	case3 = xorcyph_encryptHexKey("~itTakes12Know1.","7d");
	case4 = xorcyph_encryptHexKey("Isaac","4e");
	printf("Testing xorcyph_encryptSingleByteHex ...\n\n");
	printf("Case 1: Encrypting 'Matt' with 0xAA\n");
	printf("Expected Result: E7CBDEDE \n");
	printf("Actual Result:   %s\n\n", xorcyph_encryptHexKey("Matt","AA"));
	printf("Case 2: Encrypting '\"Stokes Polarimetry\"' with 0x61\n");
	printf("Expected Result: 4332150E0A041241310E0D0013080C0415131843\n");
	printf("Actual Result:   %s\n\n", xorcyph_encryptHexKey("\"Stokes Polarimetry\"","61"));
	printf("Case 3: Encrypting '~itTakes12Know1.' with 0x7d\n");
	printf("Expected Result: 031409291C16180E4C4F3613120A4C53\n");
	printf("Actual Result:   %s\n\n", xorcyph_encryptHexKey("~itTakes12Know1.","7d"));
	printf("Case 4: Encrypting 'Isaac' with 0x4e\n");
	printf("Expected Result: 073D2F2F2D\n");
	printf("Actual Result:   %s\n\n", xorcyph_encryptHexKey("Isaac","4e"));
	free(case1);
	free(case2);
	free(case3);
	free(case4);

	char* hexKey =  xorcyph_getSingleByteHexKey("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	char* decryptedHex = xorcyph_decryptHex("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", hexKey);
	char* decryptedMessage = hex2prasciiStr(decryptedHex);
	printf("Testing xorcyph_getSingleByteHexKey (i.e. CryptoPals Challenge 3, Set 1)...\n\n");
	printf("Case 1: Decrypting XOR-encrypted hex string '1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'\n");
	printf("Key found: %s\n", hexKey);
	printf("Decrypted hex:   %s\n", decryptedHex);
	printf("Decrypted ASCII:   %s\n\n", decryptedMessage);
	free(decryptedHex);
	free(decryptedMessage);

	char* binCiphertext = hexStr2bin("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	char* binKey =  xorcyph_getSingleByteBinKey(binCiphertext);
	char* decryptedBin = xorcyph_decryptBin(binCiphertext, binKey);
	decryptedMessage = bin2prasciiStr(decryptedBin);
	printf("Testing xorcyph_getSingleByteBinKey (i.e. CryptoPals Challenge 3, Set 1)...\n\n");
	printf("Case 1: Decrypting XOR-encrypted bin string %s\n", binCiphertext);
	printf("Key found: %s\n", binKey);
	printf("Decrypted binary:   %s\n", decryptedBin);
	printf("Decrypted ASCII:   %s\n\n", decryptedMessage);
	free(decryptedBin);
	free(decryptedMessage);
	
	printf("Testing textFile2Array ...\n\n");
	printf("Compare each of the following lines with c:\\Users\\mtrun\\singleByteXORhexCandidates.txt...\n");
	fileLines = textFile2Array("c:\\Users\\mtrun\\singleByteXORhexCandidates.txt");
	printf("Function call textFile2Array() successful.\nPrinting newly generated array:\n");
	for(int k = 0; k<327;++k)
		printf("File line %d: %s\n", k+1,fileLines[k]);
	
	int line;
	printf("\nTesting xorcyph_findEncryptedLine (i.e. CryptoPals Challenge 4, Set 1) ...\n\n");
	line = xorcyph_findEncryptedHexLine(fileLines,327);
	printf("The XOR encoded string is on line %d.\n",line);
	hexKey = xorcyph_getSingleByteHexKey(fileLines[line]);
	decryptedHex = xorcyph_decryptHex(fileLines[line], hexKey);
	decryptedMessage = hex2prasciiStr(decryptedHex);
	printf("The encryption key used is: %s\nThe decrypted ASCII text is:\n\"%s\"\n",hexKey,decryptedMessage);
	free(decryptedHex);
	free(decryptedMessage);	
	
	char* encryptedMessage = xorcyph_encryptPlainKey("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal","ICE");
	printf("Testing xorcyph_encryptPlainKey (i.e. CryptoPals Challenge 5, Set 1) ...\n\n");
	printf("Case 1: Encrypting 'Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal' wth key 'ICE'...\n");
	printf("Expected Result: 0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f\n");
	printf("Actual Result:   %s\n\n", encryptedMessage);
	free(encryptedMessage);

	printf("Testing getHammingDistance...\n\n");
	printf("Case 1: 'Rectilinear' and 'Curvilinear'\n");
	printf("Expected Result: 6\n");
	printf("Actual Result:   %d\n\n", getHammingDistance("Rectilinear","Curvilinear"));
	printf("Case 2: 'this is a test' and 'wokka wokka!!!'\n");
	printf("Expected Result: 37\n");
	printf("Actual Result:   %d\n\n", getHammingDistance("this is a test","wokka wokka!!!"));
 	
	int n = 4;
	/* If you want to test the followng function, decrease MAX_KEYSIZE to below 4 
	int* byteSizes = xorcyph_findLeastNormalizedHammingBytes("001101010010101001001110100101101000100100100100110100100101111101010010011000011010011101010101",n);
	printf("Testing xorcyph_findNumByteLeastHamming...\n\n");
	printf("Case 1: 001101010010101001001110100101101000100100100100110100100101111101010010011000011010011101010101\n");
	printf("Expected Result: \n5, 4, 3, 2\n");
	printf("Actual Result:\n");
	for(int i = 0; i<n; ++i){
		if(i==n-1){
			printf("%d\n", byteSizes[i]);
		}else{
			printf("%d, ", byteSizes[i]);
		}
	}
	free(byteSizes);
	n = 4;
	byteSizes = xorcyph_findLeastNormalizedHammingBytes("0011010111011010010111110010100101100110111001110100111101011011010101010111011101000010011011101111000000001111",n);
	printf("Case 2: 0011010111011010010111110010100101100110111001110100111101011011010101010111011101000010011011101111000000001111\n");
	printf("Expected Result: \n5, 4, 3, 2\n");
	printf("Actual Result:\n");
	for(int i = 0; i<n; ++i){
		if(i==n-1){
			printf("%d\n", byteSizes[i]);
		}else{
			printf("%d, ", byteSizes[i]);
		}
	}
	free(byteSizes);
	
	char** array1 = (char**)malloc((2)*sizeof(char*));
	for(int i = 0; i < 2; ++i){
		array1[i] = (char*)malloc(3*sizeof(char));
		for(int j = 0; j < 2;++j){
			if(j==0 && i==0){
				array1[i][j] = '1';
			}
			else if(j==1 && i==0){
				array1[i][j] = '2';
			}else if(j==0 && i==1){
				array1[i][j] = '3';
			}else if(j==1 && i==1){
				array1[i][j] = '4';
			}
		}
	}
	array1[0][2] = '\0';
	array1[1][2] = '\0';

	char** array2 = (char**)malloc((3)*sizeof(char*));
	for(int i = 0; i < 3; ++i){
		array2[i] = (char*)malloc(4*sizeof(char));
		for(int j = 0; j < 3;++j){
			if(j==0 && i==0)
				array2[i][j] = '0';
			else if(j==1 && i==0)
				array2[i][j] = '8';
			else if(j==2 && i==0)
				array2[i][j] = '7';
			else if(j==0 && i==1)
				array2[i][j] = '4';
			else if(j==1 && i==1)
				array2[i][j] = '9';
			else if(j==2 && i==1)
				array2[i][j] = '5';
		}
	}
	array2[0][3] = '\0';
	array2[1][3] = '\0';

	char** array3 = (char**)malloc((7)*sizeof(char*));
	for(int i = 0; i < 7; ++i){
		array3[i] = (char*)malloc(8*sizeof(char));
		for(int j = 0; j < 7;++j){
			if(j==0 && i==0)
				array3[i][j] = '4';
			else if(j==1 && i==0)
				array3[i][j] = 'f';
			else if(j==2 && i==0)
				array3[i][j] = 's';
			else if(j==3 && i==0)
				array3[i][j] = 'B';
			else if(j==4 && i==0)
				array3[i][j] = 'c';
			else if(j==5 && i==0)
				array3[i][j] = '3';
			else if(j==6 && i==0)
				array3[i][j] = '+';
			else if(j==0 && i==1)
				array3[i][j] = '8';
			else if(j==1 && i==1)
				array3[i][j] = 'c';
			else if(j==2 && i==1)
				array3[i][j] = 'v';
			else if(j==3 && i==1)
				array3[i][j] = '2';
			else if(j==4 && i==1)
				array3[i][j] = '3';
			else if(j==5 && i==1)
				array3[i][j] = 'm';
			else if(j==6 && i==1)
				array3[i][j] = '0';
			else if(j==0 && i==2)
				array3[i][j] = '9';
			else if(j==1 && i==2)
				array3[i][j] = 'F';
			else if(j==2 && i==2)
				array3[i][j] = 'm';
			else if(j==3 && i==2)
				array3[i][j] = 'z';
			else if(j==4 && i==2)
				array3[i][j] = 'A';
			else if(j==5 && i==2)
				array3[i][j] = 'd';
			else if(j==6 && i==2)
				array3[i][j] = '3';
			else if(j==0 && i==3)
				array3[i][j] = '9';
			else if(j==1 && i==3)
				array3[i][j] = '2';
			else if(j==2 && i==3)
				array3[i][j] = '3';
			else if(j==3 && i==3)
				array3[i][j] = 'h';
			else if(j==4 && i==3)
				array3[i][j] = 's';
			else if(j==5 && i==3)
				array3[i][j] = 'm';
			else if(j==6 && i==3)
				array3[i][j] = '5';
			else if(j==0 && i==4)
				array3[i][j] = '3';
			else if(j==1 && i==4)
				array3[i][j] = '9';
			else if(j==2 && i==4)
				array3[i][j] = '5';
			else if(j==3 && i==4)
				array3[i][j] = 'm';
			else if(j==4 && i==4)
				array3[i][j] = 'd';
			else if(j==5 && i==4)
				array3[i][j] = 'W';
			else if(j==6 && i==4)
				array3[i][j] = '1';
			else if(j==0 && i==5)
				array3[i][j] = '9';
			else if(j==1 && i==5)
				array3[i][j] = '2';
			else if(j==2 && i==5)
				array3[i][j] = 'h';
			else if(j==3 && i==5)
				array3[i][j] = 's';
			else if(j==4 && i==5)
				array3[i][j] = 'd';
			else if(j==5 && i==5)
				array3[i][j] = 'm';
			else if(j==6 && i==5)
				array3[i][j] = '5';
			else if(j==0 && i==6)
				array3[i][j] = 'M';
			else if(j==1 && i==6)
				array3[i][j] = 'W';
			else if(j==2 && i==6)
				array3[i][j] = 'G';
			else if(j==3 && i==6)
				array3[i][j] = '6';
			else if(j==4 && i==6)
				array3[i][j] = 's';
			else if(j==5 && i==6)
				array3[i][j] = 'k';
			else if(j==6 && i==6)
				array3[i][j] = '0';
		}
	}
	array3[0][7] = '\0';
	array3[1][7] = '\0';
	array3[2][7] = '\0';
	array3[3][7] = '\0';
	array3[4][7] = '\0';
	array3[5][7] = '\0';
	array3[6][7] = '\0';

	char** tarray1;
	char** tarray2;
	char** tarray3;
	printf("Testing transposeCharArray...\n\n");
	printf("Case 1: {\"12\",\"34\"}\n");
	printf("Expected Result:\n13\n24\n\n");
	tarray1 = transposeCharArray(array1,2,2);
	printf("Actual Result:\n%s\n%s\n\n", tarray1[0],tarray1[1]);
	printf("Case 2: {\"087\",\"495\"}\n");
	printf("Expected Result:\n04\n89\n75\n");
	tarray2 = transposeCharArray(array2,2,3);
	printf("Actual Result:\n%s\n%s\n%s\n\n", tarray2[0],tarray2[1],tarray2[2]);
	printf("Case 3: {\"4fsBc3+\",\"8cv23m0\",\"9FmzAd3\",\"923hsm5\",\"395mdW1\", \"92hsdm5\", \"MWG6sk0\"}\n");
	printf("Expected Result: \n489939M\nfcF292W\nsvm35hG\nB2zhms6\nc3Asdds\n3mdmWmk\n+035150\n\n");
	tarray3 = transposeCharArray(array3,7,7);
	printf("Actual Result:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", tarray3[0],tarray3[1],tarray3[2],
			tarray3[3],tarray3[4],tarray3[5],tarray3[6]);
	free(tarray1);
	free(tarray2);
	free(tarray3);
	free(array3);

	char* array1cat = cat2dCharMat(array1,2,2);
	char* array2cat = cat2dCharMat(array2,2,3);
	printf("Testing cat2dCharMat()...\n\n");
	printf("Case 1: {\"12\",\"34\"}\n");
	printf("Expected Result: 1234\n");
	printf("Actual Result:   %s\n", array1cat);
	printf("Case 2: {\"087\",\"495\"}\n");
	printf("Expected Result: 087495\n");
	printf("Actual Result:   %s\n", array2cat);
	free(array2cat);
	free(array2);
	free(array1cat);
	free(array1);
	
	char* c6s1bin;
	char* c6s1;
	int* keySizes;
	n = 15;
	printf("Testing Repeated-Key XOR Decryption (i.e. CryptoPals Challenge 6, Set 1) ...\n\n");
	printf("Converting text file into string......");
	
	c6s1 = textFile2String("c:\\Users\\mtrun\\c6s1.txt");
	printf("Success.\n\nDecoding Base64 into binary ...");
	c6s1bin = b642bin(c6s1);
	printf("Success (length of string = %d chars).\n\nPrinting binary string: %s\n\nObtaining top %d most probable key sizes (in bytes) ...", (int)strlen(c6s1bin),c6s1bin,n);
	keySizes = xorcyph_findLeastNormalizedHammingBytes(c6s1bin, n);
	printf("Success:\nThe most probable key sizes (in bytes) are: ");
	for(int j = 0; j<n; ++j){
		if(j==n-1){
			printf("and %d.\n\n", keySizes[j]);
		}else{
			printf("%d, ", keySizes[j]);
		}
	}
	int keySize = 29;
	printf("Attempting to break repeating key XOR with key size of %d bytes ...\n\n",keySize);
	char* VigCipherKey = xorcyph_decryptNbyteRepKey(c6s1bin,keySize);
    printf("The %d-byte key is: %s\n\nThe %d-byte key in ASCII is: %s\n\nRepeating key to match length of cipher text ...", keySize,VigCipherKey, keySize, bin2prasciiStr(VigCipherKey));
	char VigCipherKey_full[strlen(c6s1bin)];
	int loops = (strlen(c6s1bin)/(8*keySize));
	printf("Calculated number of loops: %d\n", loops);
	for(int i = 0; i <= loops; ++i){
		if(i==0){
			strcpy(VigCipherKey_full,VigCipherKey);
		}else if(i==loops){
			int cipherLen = strlen(c6s1bin);
			int keyLen = strlen(VigCipherKey_full);
			strncat(VigCipherKey_full,VigCipherKey,cipherLen - keyLen);
			VigCipherKey_full[cipherLen] = '\0';
		}else{
			strcat(VigCipherKey_full,VigCipherKey);
		}
	}
	printf("Done.\nLength of cipher text: %d\nLength of viginere key: %d\n\n", strlen(c6s1bin), strlen(VigCipherKey_full));
	printf("Printing Final Vigenere key: %s\n\n",VigCipherKey_full);
	printf("XOR'ing ciphertext with key....");
	char* xorH;
	xorH = strxor(c6s1bin,VigCipherKey_full);
	printf("Success.\n\nConverting binary to ASCII plaintext...");
	char* plaintext = bin2prasciiStr(xorH);
	printf("Success.\nPrinting plaintext: %s\n",plaintext);
	free(xorH);
	free(c6s1);
	free(c6s1bin);
	free(plaintext);
*/
	//printf("CryptoPals Challenge 7, Set 1\n");
	/* Convert to ciphertext to hex string for convenience */
	char* c7s1hex = bin2hexStr(b642bin(textFile2String("c:\\Users\\mtrun\\c7s1.txt")));
	char* key = prasciiStr2hex("YELLOW SUBMARINE");
	//printf("Printing hex ciphertext (%d chars): %s\n\nPrinting hex key: %s\n\nPrinting number of blocks: %d\n\n",strlen(c7s1hex), c7s1hex,key, strlen(c7s1hex)/32);
	
	char* output[16];
	//aes_decrypt(c7s1hex, output, "59454C4C4F57205355424D4152494E45", 32);
	//printf("Prnting output: %s\n", output);
	//for(int i = 0; i < strlen(c7s1hex)/32; ++i){ // For every 16 bytes of the hex cipher text ...
		//char** fourByFour_T = malloc(pow(2,4)*sizeof(char*)); // Declare a 4byte x 4byte matrix

		/* Cast every 16 bytes into a 4x4 matrix / XOR the relevant bytes with the relevant key bytes */
		//for(int j = 0; j < 4; ++j){
			//fourByFour_T[j] = malloc(9);
			//memcpy(fourByFour_T[j],&c7s1hex[32*i + 8*j],8);
			//fourByFour_T[8] = '\0';
		//}
		//printf("Printing the 4-byte x 4-byte matrix:\n");
		//for(int k = 0; k < 4;++k){
		//	printf("Row %d: %s\n",k, fourByFour_T[k]);
		//}
		
		/* Transpose the matrix -- AES wants consecutive bytes in columns, this puts bytes into rows 
		char** fourByFour = transpose2DCharArray(fourByFour_T,4,8);
		printf("Printing the 4-byte x 4-byte matrix:\n");
		for(int k = 0; k < 4;++k){
			printf("Row %d: %s\n",k, fourByFour_T[k]);
		}

		/* Perform the row swapping 
	}

	char** c7s1bin_t = transposeCharArray(fourByN,strlen(c7s1bin)/32,32);
	for(int i = 0; i < 32; ++i)
		printf("Printing transpose column %d (%d chars): %s\n", i+1,strlen(c7s1bin_t[i]),c7s1bin_t[i]);

	for(int k = 0; k < strlen(c7s1bin_t/32); ++k){
		char** block = malloc(4*sizeof(char*));
		for(int i = 0; i < 32; ++i){
			block[i] = malloc(5);
			for(int j = 0; j < 4; ++j){
				block[i][j] = c7s1bin_t[4*i+j];
			}
		}
	}
	/*
	plaintext = malloc(strlen(c7s1bin));
	for(int i = 0; i < strlen(c7s1bin)/128; ++i){
		char* block = malloc(129);
		char* xor = malloc(129);
		memcpy(block, &c7s1bin[128*i],128);
		block[128] = '\0';
		xor = strxor(block,key);
		printf("Decrypting block %d: %s\n", i+1,block);
		if(i == 0){
			strcpy(plaintext,xor);
		}else{
			printf("Attempting concatenation ...");
			strcat(plaintext,xor);
			printf("Successfully concatenated block %d to plaintext\n",i+1);
		}
		printf("Attempting to free variables...");
		free(block);
		free(xor);
		printf("Successfully freed variables.\n");
	}

	printf("Printing final plaintext: %s\n", bin2prasciiStr(plaintext));
	free(plaintext);
	*/

	return 0;
}
