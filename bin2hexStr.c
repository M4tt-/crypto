#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

extern char bin2hexChar(char*);

char* bin2hexStr(char* binStr) {
 	//printf("Entered bin2hexStr().\n\n");
	//char *hexStr;
	//char finalHexstr[256];
	char *paddedBin;
    int i,r;
	size_t loops;
	char buffer[] = {'0','0','0','0','\0'};

	//printf("Printing length of bitstream: %d\n", (int)strlen(binStr));
	int count = 0;
	r = 4-strlen(binStr)%4;
	if(r!=4){
		loops = (strlen(binStr)+r)/4;
		paddedBin = (char *)malloc(((strlen(binStr)+r)/4+1)*sizeof(char));
		memmove(paddedBin,&buffer[4-r],r);
		memmove(&paddedBin[r],binStr,strlen(binStr)+1);
	}else{
		loops = ceil(strlen(binStr)/4);
		paddedBin = (char *)malloc((loops+1)*sizeof(char));
		memmove(paddedBin,binStr,strlen(binStr)+1);
	}
	printf("Printing value of r (zeros to pad): %d\n", r);
	//printf("Printing required loop iterations: %d\n\n", loops);
	//printf("Printing intial bitstream: %s\n\n", binStr);
	//printf("Printing final bitstream: %s\n\n", paddedBin);
	//for(int k = 0;k<strlen(paddedBin);k++)
	//	printf("Printing paddedBin[%d]: %c\n",k,paddedBin[k]);
	//printf("Printing number of array elements in hexStr: %d\n",(int)(strlen(binStr)+r)/4+1);
	char *hexStr = (char *)malloc((loops)*sizeof(char));
	for(i=0;i<(int)loops;i++){
		char quartet[5];
		++count;
		//printf("For loop iteration: %d\n", count);
		//printf("Value of i: %d\n", i);
		//for(int j=0;j<strlen(paddedBin);j++)
		//	printf("Printing paddedBin[%d]: %c\n", j,paddedBin[j]);
		//if(count!=loops){
		//	memcpy(quartet,&paddedBin[4*i],4);
		//	quartet[4]='\0';
		//}else{
			memcpy(quartet,&paddedBin[4*i],4);
			quartet[4]='\0';
		//}
		//printf("Printing quartet to convert: %s\n", quartet);
		hexStr[i] = bin2hexChar(quartet);
	}
	//printf("Got out of for loop.\n");
	//printf("Attempting to access hexStr[%d] ...\n", loops);
	hexStr[loops] = '\0';
	//printf("Placed null terminator in hexStr.\n");
	//printf("Printing hex converted string: %s\n", hexStr);
	//memcpy(finalHexstr,hexStr,loops);
	//finalHexstr[loops]='\0';
	free(paddedBin);
    return hexStr;
}
