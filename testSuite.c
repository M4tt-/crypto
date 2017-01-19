#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bin2b64Char(char*);
char* bin2b64Str(char*);
char* bin2b64Str_test(char*);
char* hex2bin(char);
char* hexstr2bin(char*);

void testSuite(void) {
 
	char* bin1 = "11100101";
	char* bin2 = "000000111110";
	char* bin3 = "1000001100110";
	char* bin4 = "1000001100110010101";
	char* bin5 = "111100111101111110111111";
	char* bin6 = "100001110010011011110110111101101101";
	char* bin7 = "101110101111110000110001110010110011110100110101110110";
	char* hex1 = "AF";
	char* hex2 = "9D2"; 
	char* hex3 = "5c2B"; 
	char* hex4 = "EE09F"; 
	char* hex5 = "095A26";
	char* hex6 = "F5DC380AF";
	char* hex7 = "F5DC380ABE";
	char* hex8 = "F5DC380ABEC452F";
	
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

	
    printf("Testing bin2b64Str ...\n\n");
	printf("Case 1: 'Length of binary string greater than 6 (8 bits)':\n");
	printf("Expected Result: Dl\n");
	printf("Actual Result:   %s\n\n", bin2b64Str_test(bin1));
	printf("Case 2: 'Length of binary string greater than 6 (12 bits)':\n");
	printf("Expected Result: A+\n");
	printf("Actual Result:   %s\n\n", bin2b64Str_test(bin2));
	printf("Case 3: 'Length of binary string greater than 6 (13 bits)':\n");
	printf("Expected Result: BBm\n");
	printf("Actual Result:   %s\n\n", bin2b64Str_test(bin3));
	printf("Case 4: 'Length of binary string greater than 6 (19 bits)':\n");
	printf("Expected Result: BBmV\n");
	printf("Actual Result:   %s\n\n", bin2b64Str_test(bin4));
	printf("Case 5: 'Length of binary string greater than 6 (24 bits)':\n");
	printf("Expected Result: 89+/\n");
	printf("Actual Result:   %s\n\n", bin2b64Str_test(bin5));
	printf("Case 6: 'Length of binary string greater than 6 (36 bits)':\n");
	printf("Expected Result: hyb29t\n");
	printf("Actual Result:   %s\n\n", bin2b64Str_test(bin6));
	printf("Case 7: 'Length of binary string greater than 6 (54 bits)':\n");
	printf("Expected Result: uvwxyz012\n");
	printf("Actual Result:   %s\n\n", bin2b64Str_test(bin7));
}
