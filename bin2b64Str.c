char* binStr2b64(char* binStr) {
 
	char sextet[256];
	char b64str[256];
	char finalb64str[256];
    int i,r,t,loops;
	char buffer[] = {'0','0','0','0','0','0','\0'};

	int count = 0;
	r = 6-strlen(binStr)%6;
	if(r!=6)
		loops = (int)strlen(binStr)/6+1;
	else
		loops = (int)strlen(binStr)/6;
	for(i=strlen(binStr)-1;i>=0;i=i-6){
		++count;
		if(count==loops){
			memmove(&buffer[r],binStr,6-r);
			strncpy(sextet,buffer,6);
		}
		else if(count==1)
			strncpy(sextet,&binStr[i-5],7);
		else
			strncpy(sextet,&binStr[i-5],6);
		b64str[count-1] = binChar2b64(sextet);
	}
	memcpy(finalb64str,b64str,loops);
	
	int end = strlen(finalb64str);
	for(i = 0; i < (end+1)/2; i++) {
	    t          = finalb64str[i];
	    finalb64str[i]   = finalb64str[end-1];
	    finalb64str[end-1] = t;
	    end--;
	}
    return finalb64str;
}
