#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char*  hex2bin(char hex)
{

	static char hex_table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	static char bin_table[16][5] = {"0000", "0001", "0010", "0011", "0100",
							   		"0101","0110", "0111", "1000", "1001",
							   		"1010", "1011", "1100", "1101", "1110",
							   		"1111"};

	/* Declare Constants */
	int n = 16;
	int k;
	char *bin;

	/* Perform conversion */
	for(k=0;k<n;k++){
		//const char* 
		if (toupper(hex) == hex_table[k]) {
			bin = bin_table[k];
			break;	
		}
	}
	return bin;
}
