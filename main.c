#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//extern char bin2b64Char(char*);
//extern char* bin2b64Str(char*);
//extern char* bin2b64Str_test(char*);
//extern char* hex2bin(char);
//extern char* hexstr2bin(char*);
//extern char bin2hexChar(char*);
extern void testSuite(void);

int main(void) {
 
	testSuite();
	return 0;
}
