#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char binChar2b64(char*);
char* binStr2b64(char*);

int main(void) {
 
	char* bin1 = "010101";
	char* bin2 = "001111";
	char* bin3 = "111111";
	char* bin4 = "0011";
	char* bin5 = "101";
	char* bin6 = "01";
	char* bin7 = "0";
	char* bin8 = "01000";
	char* bin9 = "11100101";
	char* bin10 = "000000111110";
	char* bin11 = "1000001100110"; 
	
	
    printf("Testing binChar2b64 ...\n\n");
	printf("Case 1: 'Length of binary string equal to 6':\n");
	printf("Expected Result: V.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin1));
	printf("Case 2: 'Length of binary string equal to 6':\n");
	printf("Expected Result: P.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin2));
	printf("Case 3: 'Length of binary string equal to 6':\n");
	printf("Expected Result: /.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin3));
	printf("Case 4: 'Length of binary string less than 6 (4 bits)':\n");
	printf("Expected Result: D.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin4));
	printf("Case 5: 'Length of binary string less than 6 (3 bits)':\n");
	printf("Expected Result: F.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin5));
	printf("Case 6: 'Length of binary string less than 6 (2 bits)':\n");
	printf("Expected Result: B.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin6));
	printf("Case 7: 'Length of binary string less than 6 (1 bit)':\n");
	printf("Expected Result: A.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin7));
	printf("Case 8: 'Length of binary string less than 6 (5 bits)':\n");
	printf("Expected Result: I.\n");
	printf("Actual Result: %c\n\n", binChar2b64(bin8));

    printf("Testing binStr2b64 ...\n\n");
	printf("Case 1: 'Length of binary string greater than 6 (8 bits)':\n");
	printf("Expected Result: Dl\n");
	printf("Actual Result: %s\n\n", binStr2b64(bin9));
	printf("Case 2: 'Length of binary string greater than 6 (12 bits)':\n");
	printf("Expected Result: A+\n");
	printf("Actual Result: %s\n\n", binStr2b64(bin10));
	printf("Case 3: 'Length of binary string greater than 6 (13 bits)':\n");
	printf("Expected Result: BBm\n");
	printf("Actual Result: %s\n\n", binStr2b64(bin11));
	printf("Case 4: 'Length of binary string less than 6 (4 bits)':\n");
	printf("Expected Result: D.\n");
	printf("Actual Result: %c\n\n", binStr2b64(bin4));
	printf("Case 5: 'Length of binary string less than 6 (3 bits)':\n");
	printf("Expected Result: F.\n");
	printf("Actual Result: %c\n\n", binStr2b64(bin5));
	printf("Case 6: 'Length of binary string less than 6 (5 bits)':\n");
	printf("Expected Result: I.\n");
	printf("Actual Result: %c\n\n", binStr2b64(bin8));
	printf("Case 7: 'Length of binary string less than 6 (1 bit)':\n");
	printf("Expected Result: A.\n");
	printf("Actual Result: %c\n\n", binStr2b64(bin7));

	
	/*
	printf("Case 1: Integer casting of 21/7:\n");
	printf("Expected result: 3\n");
	printf("Actual result: %d\n\n",(int)21/7);
	printf("Case 2: Integer casting of 22/7:\n");
	printf("Expected result: 3\n");
	printf("Actual result: %d\n\n",(int)22/7);
	printf("Case 3: Integer casting of 20/7:\n");
	printf("Expected result: 2\n");
	printf("Actual result: %d\n\n",(int)20/7);
	printf("Case 4: Integer casting of 1/7:\n");
	printf("Expected result: 0\n");
	printf("Actual result: %d\n\n",(int)1/7);
	*/
}
