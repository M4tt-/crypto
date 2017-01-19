char* bin2b64Str(char* binStr) {
 	//printf("Entered bin2b64Str().\n\n");
	char b64str[256];
	char finalb64str[256];
	char paddedBin[256];
    int i,r,t,loops;
	char buffer[] = {'0','0','0','0','0','0','\0'};

	//printf("Printing length of bitstream: %d\n", strlen(binStr));
	int count = 0;
	r = 6-strlen(binStr)%6;
	if(r!=6){
		loops = (int)strlen(binStr)/6+1;
		memmove(paddedBin,&buffer[6-r],r);
		memmove(&paddedBin[r],binStr,strlen(binStr)+1);
	}else{
		loops = (int)strlen(binStr)/6;
		memmove(paddedBin,binStr,strlen(binStr)+1);
	}
	//printf("Printing value of r (zeros to pad): %d\n", r);
	//printf("Printing required loop iterations: %d\n\n", loops);
	//printf("Printing intial bitstream: %s\n\n", binStr);
	//printf("Printing final bitstream: %s\n\n", paddedBin);
	//for(int k = 0;k<strlen(paddedBin);k++)
	//	printf("Printing paddedBin[%d]: %c\n",k,paddedBin[k]);
	for(i=0;i<loops;i++){
		char sextet[256];
		++count;
		//printf("For loop iteration: %d\n", count);
		//printf("Value of i: %d\n", i);
		//for(int j=0;j<strlen(paddedBin);j++)
		//	printf("Printing paddedBin[%d]: %c\n", j,paddedBin[j]);
		if(count!=loops){
			memcpy(sextet,&paddedBin[6*i],6);
			sextet[6]='\0';
		}else{
			memcpy(sextet,&paddedBin[6*i],7);
			sextet[6]='\0';
		}
		//printf("Printing sextet to convert: %s\n", sextet);
		b64str[i] = bin2b64Char(sextet);
	}
	//printf("Printing base64 converted string: %s", b64str);
	memcpy(finalb64str,b64str,loops);
	finalb64str[loops]='\0';
	/*
    char temp;
    int len = strlen(finalb64str)-1;
    int j;
    int k = len;
    
    for(j = 0; j < len; j++)
    {
        temp = finalb64str[k];
        finalb64str[k] = finalb64str[i];
        finalb64str[i] = temp;
        k--;
        if(k == (len / 2))
        {
            break;
        }
    }
	*/
    return finalb64str;
}
