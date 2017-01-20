#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char bin2b64Char(char*);
extern char* bin2b64Str(char*);
extern char* bin2b64Str_test(char*);
extern char* hex2bin(char);
extern char* hexstr2bin(char*);
extern char bin2hexChar(char*);
extern char* bin2hexStr(char*);

void testSuite(void) {
 
	char* bin1 = "11100101";
	char* bin2 = "000000111110";
	char* bin3 = "1000001100110";
	char* bin4 = "1000001100110010101";
	char* bin5 = "111100111101111110111111";
	char* bin6 = "100001110010011011110110111101101101";
	char* bin7 = "101110101111110000110001110010110011110100110101110110";
	char* bin8 = "0000";
	char* bin9 = "0001";
	char* bin10 = "0010";
	char* bin11 = "0011";
	char* bin12 = "0100";
	char* bin13 = "0101";
	char* bin14 = "0110";
	char* bin15 = "0111";
	char* bin16 = "1000";
	char* bin17 = "1001";
	char* bin18 = "1010";
	char* bin19 = "1011";
	char* bin20 = "1100";
	char* bin21 = "1101";
	char* bin22 = "1110";
	char* bin23 = "1111";
	char* bin24 = "111101010011101000111100111100011010111001";
	char* bin25 = "100111010011101101011100111100011010111001000110100001101010";
	char* hex1 = "AF";
	char* hex2 = "9D2"; 
	char* hex3 = "5c2B"; 
	char* hex4 = "EE09F"; 
	char* hex5 = "095A26";
	char* hex6 = "F5DC380AF";
	char* hex7 = "F5DC380ABE";
	char* hex8 = "F5DC380ABEC452F";
	
	printf("Testing hex2bin ...\n\n");
	printf("Case 1: 'A':\n");
	printf("Expected Result: 1010.\n");
	printf("Actual Result:   %s.\n\n", hex2bin('A'));
	printf("Case 2: 'B':\n");
	printf("Expected Result: 1011.\n");
	printf("Actual Result:   %s.\n\n", hex2bin('B'));
	printf("Case 3: '7':\n");
	printf("Expected Result: 0111.\n");
	printf("Actual Result:   %s.\n\n", hex2bin('7'));
	printf("Case 4: 'F':\n");
	printf("Expected Result: 1111.\n");
	printf("Actual Result:   %s.\n\n", hex2bin('F'));
	
	printf("Testing hexstr2bin ...\n\n");
	printf("Case 1: 'Length of hex string equal to 2':\n");
	printf("Expected Result: 10101111.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex1));
	printf("Case 2: 'Length of hex string equal to 3':\n");
	printf("Expected Result: 100111010010.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex2));
	printf("Case 3: 'Length of hex string equal to 4 (mixed lower case/upper case)':\n");
	printf("Expected Result: 0101110000101011.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex3));
	printf("Case 4: 'Length of hex string equal to 5':\n");
	printf("Expected Result: 11101110000010011111.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex4));
	printf("Case 5: 'Length of hex string equal to 6':\n");
	printf("Expected Result: 000010010101101000100110.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex5));
	printf("Case 6: 'Length of hex string equal to 9':\n");
	printf("Expected Result: 111101011101110000111000000010101111.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex6));
	printf("Case 7: 'Length of hex string equal to 10':\n");
	printf("Expected Result: 1111010111011100001110000000101010111110.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex7));
	printf("Case 8: 'Length of hex string equal to 15':\n");
	printf("Expected Result: 111101011101110000111000000010101011111011000100010100101111.\n");
	printf("Actual Result:   %s.\n\n", hexstr2bin(hex8));


    printf("Testing bin2hexChar ...\n\n");
	printf("Case 1: 0000:\n");
	printf("Expected Result: 0\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin8));
	printf("Case 2: 0001:\n");
	printf("Expected Result: 1\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin9));
	printf("Case 3: 0010:\n");
	printf("Expected Result: 2\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin10));
	printf("Case 4: 0011:\n");
	printf("Expected Result: 3\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin11));
	printf("Case 5: 0100:\n");
	printf("Expected Result: 4\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin12));
	printf("Case 6: 0101:\n");
	printf("Expected Result: 5\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin13));
	printf("Case 7: 0110:\n");
	printf("Expected Result: 6\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin14));
	printf("Case 8: 0111:\n");
	printf("Expected Result: 7\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin15));
	printf("Case 9: 1000:\n");
	printf("Expected Result: 8\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin16));
	printf("Case 10: 1001:\n");
	printf("Expected Result: 9\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin17));
	printf("Case 11: 1010:\n");
	printf("Expected Result: A\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin18));
	printf("Case 12: 1011:\n");
	printf("Expected Result: B\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin19));
	printf("Case 13: 1100:\n");
	printf("Expected Result: C\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin20));
	printf("Case 14: 1101:\n");
	printf("Expected Result: D\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin21));
	printf("Case 15: 1110:\n");
	printf("Expected Result: E\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin22));
	printf("Case 16: 1111:\n");
	printf("Expected Result: F\n");
	printf("Actual Result:   %c\n\n", bin2hexChar(bin23));

	
    printf("Testing bin2b64Str ...\n\n");
	printf("Case 1: 'Length of binary string greater than 6 (8 bits)':\n");
	printf("Expected Result: Dl\n");
	printf("Actual Result:   %s\n\n", bin2b64Str(bin1));
	printf("Case 2: 'Length of binary string greater than 6 (12 bits)':\n");
	printf("Expected Result: A+\n");
	printf("Actual Result:   %s\n\n", bin2b64Str(bin2));
	printf("Case 3: 'Length of binary string greater than 6 (13 bits)':\n");
	printf("Expected Result: BBm\n");
	printf("Actual Result:   %s\n\n", bin2b64Str(bin3));
	printf("Case 4: 'Length of binary string greater than 6 (19 bits)':\n");
	printf("Expected Result: BBmV\n");
	printf("Actual Result:   %s\n\n", bin2b64Str(bin4));
	printf("Case 5: 'Length of binary string greater than 6 (24 bits)':\n");
	printf("Expected Result: 89+/\n");
	printf("Actual Result:   %s\n\n", bin2b64Str(bin5));
	printf("Case 6: 'Length of binary string greater than 6 (36 bits)':\n");
	printf("Expected Result: hyb29t\n");
	printf("Actual Result:   %s\n\n", bin2b64Str(bin6));
	printf("Case 7: 'Length of binary string greater than 6 (54 bits)':\n");
	printf("Expected Result: uvwxyz012\n");
	printf("Actual Result:   %s\n\n", bin2b64Str(bin7));


	printf("Testing bin2hexStr ...\n\n");
	printf("Case 1: 11100101 (8 bits):\n");
	printf("Expected Result: E5\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin1));
	printf("Case 2: 000000111110 (12 bits):\n");
	printf("Expected Result: 03E\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin2));
	printf("Case 3: 1000001100110 (13 bits):\n");
	printf("Expected Result: 1066\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin3));
	printf("Case 4: 1000001100110010101 (19 bits):\n");
	printf("Expected Result: 41995\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin4));
	printf("Case 5: 111100111101111110111111 (24 bits):\n");
	printf("Expected Result: F3DFBF\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin5));
	printf("Case 6: 100001110010011011110110111101101101 (36 bits):\n");
	printf("Expected Result: 8726F6F6D\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin6));
	printf("Case 7: 111101010011101000111100111100011010111001 (42 bits):\n");
	printf("Expected Result: 3D4E8F3C6B9\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin24));
	
	printf("Case 8: 101110101111110000110001110010110011110100110101110110 (54 bits):\n");
	printf("Expected Result: 2EBF0C72CF4D76\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin7));
	/*
	printf("Case 9: 100111010011101101011100111100011010111001000110100001101010 (60 bits):\n");
	printf("Expected Result: 9D3B5CF1AE4686A\n");
	printf("Actual Result:   %s\n\n", bin2hexStr(bin25));
	*/

}
