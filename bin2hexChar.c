#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int string_compare(char *, char*);

char bin2hexChar(char* bin){

	static char hex_table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	static char bin_table[16][5] = {"0000", "0001", "0010", "0011", "0100",
							   		"0101","0110", "0111", "1000", "1001",
							   		"1010", "1011", "1100", "1101", "1110",
							   		"1111"};
	
	int i;
	int k = 16;
	char hex;

	for(i=0;i<k;i++){
		//printf("For loop iteration: %d\n", i+1);
		//printf("String to search for: %s\n", bin);
		//printf("String being queried: %s\n", bin_table[i]);
		if (string_compare(bin,bin_table[i])==1) {
			hex = hex_table[i];
			break;	
		}
	}
	return hex;
}
