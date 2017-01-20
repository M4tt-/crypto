#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char bin2b64Char(char*);

char* bin2b64Str(char* binStr) {

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
	//printf("Printing value of r (zeros to pad): %d\n", r);
	//printf("Printing required loop iterations: %d\n\n", loops);
	//printf("Printing intial bitstream: %s\n\n", binStr);
	//printf("Printing final bitstream: %s\n\n", paddedBin);
	char* b64str = (char *)malloc((strlen(binStr)+r + 1)*sizeof(char));
	for(i=0;i<loops;i++){
		char sextet[7];
		++count;
		//printf("For loop iteration: %d\n", count);
		//printf("Value of i: %d\n", i);
		memcpy(sextet,&paddedBin[6*i],6);
		sextet[6]='\0';
		//printf("Printing sextet to convert: %s\n", sextet);
		b64str[i] = bin2b64Char(sextet);
	}
	b64str[loops]='\0';
	//printf("Printing base64 converted string: %s\n", b64str);
	free(paddedBin);
    return b64str;
}
