/****************************************************************************
 *                                                                          *
 * Filename: c2s1.c                                                         *
 *                                                                          *
 * Purpose : CryptoPals Challenge 2, Set 1.				                    *
 *                                                                          *
 * History : Date      Reason                                               *
 *           01-18-17  Created: CSE Studying                                *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bin2b64Char(char*);
char* bin2b64Str_test(char*);
char* hexstr2bin(char*);
int string_compare(char*, char*);
void testSuite(void);
char bin2hexChar(char* bin);

int main(void){

	
	//char* hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	//char* result = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
	
	//char* hex = "8726f6f6d";
	//char* result = "hyb29t";
	//char* bin;
	//char* b64;

	testSuite();
	/*
    printf("Performing Challenge 1 of Set 1 (CryptoPals) ...\n\n");
	printf("Length of hex string: %d\n", strlen(hex));
	bin = hexstr2bin(hex);
	b64 = bin2b64Str_test(bin);
	printf("Printing desired conversion: %s\n", result);
	printf("Printing your conversion:    %s\n\n", b64);
	if(string_compare(result,b64)==1)
		printf("...Success!\n\n");
	else{
		printf("...Failure!\n\n");
		if(strlen(result)==strlen(b64)){
			printf("At least you got the correct number of Base64 symbols:\n");
		}else{
			printf("You did not even get the correct number of Base64 symbols:\n");
		}
		printf("The correct number of Base64 symbols after conversion is  %d.\n", strlen(result));
		printf("The number of Base64 symbols after conversion you have is %d.\n\n", strlen(b64));
	}
	*/
	return 0;
}

