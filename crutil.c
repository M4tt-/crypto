/****************************************************************************
 *                                                                          *
 * Filename: crutil.c                                                       *
 *																			*
 * Author: Matt Runyon														*					
 *                                                                          *
 * Purpose : Crypto Library implementation file			                    *
 *                                                                          *
 * Last Upated : 01-31-17		 							 				*
 *																			*
 * Notes: Letter frequency weights determined by stats found here:			*
 *	      https://en.wikipedia.org/wiki/Letter_frequency 	                *
 *                                                                          *
 *        Average English word length determined by study here:             *
 *        https://arxiv.org/ftp/arxiv/papers/1208/1208.6109.pdf             *
 *																			*
 *        Common Letter weights:						                    *
 *                                                                          *                               
 *		E = 12.702%/2.758% = 4.606											*
 *		T = 9.056%/2.758% = 3.284                                           *
 *		A = 8.167%/2.758% = 2.961                                           *
 *		O = 7.507%/2.758% = 2.722                                           *
 *		I = 6.966%/2.758% = 2.526                                           *
 *		N = 6.749%/2.758% = 2.447                                           *
 *		S = 6.327%/2.758% = 2.294                                           *
 *		H = 6.094%/2.758% = 2.209                                           *
 *		R = 5.987%/2.758% = 2.171                                           *
 *		D = 4.253%/2.758% = 1.542                                           *
 *		L = 4.025%/2.758% = 1.459                                           *
 *		U = 2.758%%/2.758% = 1                                              *
 *                                                                          *
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/***************************************************************
*															   *
*			// GLOBAL VARIABLES //							   *
*															   *
****************************************************************/

const double meanWordLength = 5.1;

char allLetters[52] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F','f', 'G', 'g', 'H', 'h',
						'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p',
						'Q', 'q', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x',
						'Y', 'y', 'Z', 'z'};

double allLetterStats[52] = {0.08167, 0.08167, 0.01492, 0.01492, 0.02782, 0.02782, 0.04253, 0.04253,
							 0.12702, 0.12702, 0.0228, 0.0228, 0.02015, 0.02015, 0.06094, 0.06094,
							 0.06966, 0.06966, 0.00153, 0.00153, 0.00772, 0.00772, 0.04025, 0.04025,
							 0.02406, 0.02406, 0.06749, 0.06749, 0.07507, 0.07507, 0.01929, 0.01929,
							 0.0095, 0.0095, 0.05987, 0.05987, 0.06327, 0.06327, 0.09056, 0.09056,
							 0.02758, 0.02758, 0.00978, 0.00978, 0.02360, 0.02360, 0.0015, 0.0015,
							 0.01974,0.01974, 0.0074, 0.0074};

double allLetterStats_short[26] = {0.08167, 0.01492, 0.02782, 0.04253,0.12702, 0.0228, 0.02015, 0.06094,
							 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507,0.01929,
							 0.0095, 0.05987, 0.06327,0.09056, 0.02758, 0.00978,0.02360, 0.0015,
							 0.01974, 0.0074};

char commonLetters[25] = {'E', 'e', 'T', 't', 'A', 'a', 'O', 'o', 'I', 'i', 'N', 'n',
						  'S', 's', 'H', 'h', 'R', 'r', 'D', 'd', 'L', 'l','U', 'u'};

double commonLetterWeight[25] = {4.606, 4.606, 3.284, 3.284, 2.961, 2.961, 2.722, 2.722,
								 2.526, 2.526, 2.447, 2.447, 2.294, 2.294, 2.209, 2.209,
								 2.171, 2.171, 1.542, 1.542, 1.459, 1.459, 1.000, 1.000};

double commonLetterStats[25] = {0.12702, 0.12702, 0.09056, 0.09056, 0.08167, 0.08167, 0.07507, 0.07507,
								 0.06966, 0.06966, 0.06749, 0.06749, 0.06327, 0.06327, 0.06094, 0.06094,
								 0.05987, 0.05987, 0.04253, 0.04253, 0.04025, 0.04025, 0.02758, 0.02758};

char nonAlphaNumericChars[9] = {'#', '*', '@', '[', '\\', ']', '^', '_', '`'};
char nonAlphaNumericChars_v2[15] = {'#', '*', '@', '[', '\\', ']', '^', '_', '`', '%', '$','&','+','=','~'};

char bin8_table[97][9] =  {"00001011","00001101","00100000","00100001","00100010","00100011",
						   "00100100","00100101","00100110","00100111","00101000","00101001",
						   "00101010","00101011","00101100","00101101","00101110","00101111",
						   "00110000","00110001","00110010","00110011","00110100","00110101",
						   "00110110","00110111","00111000","00111001","00111010","00111011",
						   "00111100","00111101","00111110","00111111","01000000","01000001",
						   "01000010","01000011","01000100","01000101","01000110","01000111",
						   "01001000","01001001","01001010","01001011","01001100","01001101",
						   "01001110","01001111","01010000","01010001","01010010","01010011",
						   "01010100","01010101","01010110","01010111","01011000","01011001",
						   "01011010","01011011","01011100","01011101","01011110","01011111",
						   "01100000","01100001","01100010","01100011","01100100","01100101",
						   "01100110","01100111","01101000","01101001","01101010","01101011",
						   "01101100","01101101","01101110","01101111","01110000","01110001",
						   "01110010","01110011","01110100","01110101","01110110","01110111",
						   "01111000","01111001","01111010","01111011","01111100","01111101",
						   "01111110"};

char bin6_table[65][7] =   {"000000", "000001", "000010", "000011", "000100",
					   		"000101","000110", "000111", "001000", "001001",
					   		"001010", "001011", "001100", "001101", "001110",
					   		"001111", "010000", "010001", "010010", "010011",
							"010100", "010101", "010110", "010111", "011000",
							"011001", "011010", "011011", "011100", "011101",
							"011110", "011111", "100000", "100001", "100010",
							"100011", "100100", "100101", "100110", "100111",
							"101000", "101001", "101010", "101011", "101100",
							"101101", "101110", "101111", "110000", "110001",
							"110010", "110011", "110100", "110101", "110110",
							"110111", "111000", "111001", "111010", "111011",
							"111100", "111101", "111110", "111111", "000000"};

char bin4_table[16][5] = {"0000", "0001", "0010", "0011", "0100",
					   		"0101","0110", "0111", "1000", "1001",
					   		"1010", "1011", "1100", "1101", "1110",
					   		"1111"};

char base64_table[65] =      {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                            'w', 'x', 'y', 'z', '0', '1', '2', '3',
                            '4', '5', '6', '7', '8', '9', '+', '/','='};

char hex_table[17] = {'0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char hex2_table[97][3] = {"0A", "0D", "20", "21", "22", "23", "24", "25", "26", "27",
						  "28", "29", "2A", "2B", "2C", "2D", "2E", "2F", "30",
						  "31", "32", "33", "34", "35", "36", "37", "38",
						  "39", "3A","3B", "3C", "3D", "3E", "3F","40",
						  "41", "42", "43", "44", "45", "46", "47", "48",
						  "49", "4A","4B", "4C", "4D", "4E", "4F","50",
						  "51", "52", "53", "54", "55", "56", "57", "58",
						  "59", "5A","5B", "5C", "5D", "5E", "5F","60",
						  "61", "62", "63", "64", "65", "66", "67", "68",
						  "69", "6A","6B", "6C", "6D", "6E", "6F","70",
						  "71", "72", "73", "74", "75", "76", "77", "78",
						  "79", "7A","7B", "7C", "7D", "7E"};



char prascii_table[97] =   {'\n','\r',' ', '!', '"', '#', '$', '%%', '&', '\'', '(',')','*','+',',','-','.','/',
						 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
						 '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
						 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
						 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o' ,'p' ,'q', 'r', 's', 't', 'u',
						 'v', 'w', 'x', 'y', 'z', '{','|','}','~'};

/***************************************************************
*															   *
*			// hex2bin() //									   *
*															   *
****************************************************************/
char* hex2bin(char hex){

	int n = 16;
	int k;
	char* bin;

	for(k=0;k<n;k++){
		if (toupper(hex) == hex_table[k]) {
			bin = bin4_table[k];
			break;	
		}
	}
	return bin;
}

/***************************************************************
*															   *
*			// hexStr2bin() //								   *
*															   *
****************************************************************/
char* hexStr2bin(char *hex_str) {
 
    int i;
    char *str;
    size_t len = strlen(hex_str);

    char* bin_str = (char*)malloc(((len * 4) + 1) * sizeof(char));
    for (i = 0; i < (int)len; i++) {
      const char* binQuartet = hex2bin(hex_str[i]);
      memcpy(&bin_str[4*i], binQuartet,5);
    }
    return bin_str;
}

/***************************************************************
*															   *
*			// bin2hexChar() //								   *
*															   *
****************************************************************/
char bin2hexChar(char *bin){

    int k = 0;
    for(int i = 0; i < 4; i++){
        k = k * 2 + *bin++ - '0';
    }
    return hex_table[k];
}

/***************************************************************
*															   *
*			// bin2hexStr() //								   *
*															   *
****************************************************************/
char* bin2hexStr(char* binStr) {

    size_t loops, len = strlen(binStr);
    int r = len % 4;
    if(r)
        r = 4 - r;

    char *paddedBin = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
    memset(paddedBin, '0', r);//add padding to top
    memcpy(paddedBin + r, binStr, len + 1);
    loops = (len + r) / 4;
    char *hexStr = malloc((loops + 1)*sizeof(char));//+1 for NUL
    for(size_t i = 0; i < loops; i++){
        hexStr[i] = bin2hexChar(paddedBin + i * 4);
    }
    hexStr[loops] = '\0';
    free(paddedBin);
    return hexStr;
}

/***************************************************************
*															   *
*			// string_compare() //							   *
*															   *
****************************************************************/
int string_compare(char *str1, char *str2)
{
    int ctr=0;

    while(str1[ctr]==str2[ctr])
    {
        if(str1[ctr]=='\0'||str2[ctr]=='\0')
            break;
        ctr++;
    }
    if(str1[ctr]=='\0' && str2[ctr]=='\0')
        return 1;
    else
        return 0;
}

/***************************************************************
*															   *
*			// bin2b64Char() //								   *
*															   *
****************************************************************/
char bin2b64Char(char* bin)
{
	
	char buffer[] = {'0','0','0','0','0','0','\0'};
	char b64;
	int i,r;
	size_t len = strlen(bin);
	
	if(len<6){
		r = 6-len%6;
		memmove(&buffer[r],bin,len);
		for(i=0;i<64;i++){
			if(string_compare(buffer,bin6_table[i])==1){
				b64 = base64_table[i];
				break;
			}
		}
	}else{
		for(i=0;i<64;i++){
			if(string_compare(bin,bin6_table[i])==1){
				b64 = base64_table[i];
				break;
			}
		}
	}
	return b64;
}

/***************************************************************
*															   *
*			// bin2b64Str() //								   *
*															   *
****************************************************************/
char* bin2b64Str(char* binStr){

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
	char* b64str = (char *)malloc((strlen(binStr)+r + 1)*sizeof(char));
	for(i=0;i<loops;i++){
		char sextet[7];
		++count;
		memcpy(sextet,&paddedBin[6*i],6);
		sextet[6]='\0';
		b64str[i] = bin2b64Char(sextet);
	}
	b64str[loops]='\0';
	free(paddedBin);
    return b64str;
}

/***************************************************************
*															   *
*			// b64Char2bin() //								   *
*															   *
****************************************************************/
char* b64Char2bin(char b64){

	int n = 66;
	int k;
	char *bin;

	for(k=0;k<n;k++){
		if (b64 == base64_table[k]) {
			if(b64 == '='){
				break;
			}else{
				bin = bin6_table[k];
				break;
			}	
		}
	}
	return bin;
}

/***************************************************************
*														*
*			// b642bin() //		  					     *
*														*
****************************************************************/
char* b642bin(char *b64) {

	size_t loops, len = strlen(b64);
    int r = len % 4;
	char* paddedB64;
    if(r){
        r = 4 - r;
	    paddedB64 = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
	    memset(paddedB64, '=', len+r);//add padding to top
	    memcpy(paddedB64, b64, len);
		paddedB64[len+r] = '\0';
	}else{
    	paddedB64 = b64;
	}
	
	char* bin = malloc((6*strlen(paddedB64))*sizeof(char));
	for(int i = 0; i < strlen(paddedB64)/4; ++i){
		char* quartet = malloc(5*sizeof(char));
		memcpy(quartet, &paddedB64[4*i],4);
		quartet[4] = '\0';
		if(quartet[2] == '=' && quartet[3] == '='){
			if(quartet[1]!= 'A' && quartet[1]!= 'Q' && quartet[1]!= 'g' && quartet[1]!= 'w'){
				quartet[1] = 'A';
			}
			
			for(int k = 0; k < 66; ++k){
				if(quartet[0] == base64_table[k]){
					memcpy(&bin[24*i],bin6_table[k],6);
					break;
				}
			}
			for(int k = 0; k < 66; ++k){
				if(quartet[1] == base64_table[k]){
					memcpy(&bin[24*i+6],bin6_table[k],2);
					break;
				}
			}
			bin[24*i+8] = '\0';
		}else if(quartet[2] != '=' && quartet[3] == '='){
			if(quartet[2]!='A' && quartet[2]!= 'E' && quartet[2]!= 'I' && quartet[2]!= 'M' && quartet[2]!= 'Q'
				 && quartet[2]!= 'U' && quartet[2]!= 'Y' && quartet[2]!= 'c' && quartet[2]!= 'g'
				 && quartet[2]!= 'k' && quartet[2]!= 'o' && quartet[2]!= 's' && quartet[2]!= 'w'
				 && quartet[2]!= '0' && quartet[2]!= '4' && quartet[2]!= '8'){
				quartet[2] = 'A';
			}
			for(int j = 0; j < 3; ++j){
				for(int k = 0; k < 66; ++k){
					if(quartet[j] == base64_table[k]){
						memcpy(&bin[24*i+6*j],bin6_table[k],6);
						break;
					}
				}
			}
			for(int k = 0; k < 66; ++k){
				if(quartet[2] == base64_table[k]){
					break;
				}
			}
			bin[24*i+16] = '\0';
		}else{
			for(int j = 0; j < 4; ++j){
				for(int k = 0; k < 66; ++k){
					if(quartet[j] == base64_table[k]){
						if(i==0 && j==0)
							strcpy(bin,bin6_table[k]);
						else
							strcat(bin,bin6_table[k]);
						break;
					}
				}
			}
			if(i==strlen(paddedB64)/4){
				bin[24*(i+1)] = '\0';
			}
		}
		free(quartet);
	}
	return bin;
}

/***************************************************************
*														*
*			// dec2bin() //								*
*														*
****************************************************************/
char* dec2bin(int n, int pad){
	
	if(pow(2,pad)<n){
		printf("Insufficient number of bits for decimal to binary conversion.\nTerminating.\n");
		exit(1);
	}else{
		int delta=n, p=0,count=0;
		int ncopy = n;
		char ones[] = {'1','1'};
		char* bin = (char*)malloc((pad+1)*sizeof(char));
		memset(bin,'0',pad);
		while(delta!=0){
			int j=0;
			while(pow(2,j)<=delta){
				p=j;
				++j;
			}
			delta = abs(ncopy-pow(2,p));
			ncopy =delta;
			memcpy(&bin[pad-1-p],ones,1);
		count++;
		}
		bin[pad]='\0';
		return bin;
	}
}

/***************************************************************
*														*
*			// bin2prasciiChar() //						*
*														*
****************************************************************/
char bin2prasciiChar(char* bin){

	char prascii = '$';
	for(int i =0;i<97;++i){
		if(string_compare(bin,bin8_table[i])==1){
			prascii = prascii_table[i];
			break;
		}
	}
	return prascii;
}

/***************************************************************
*														*
*			// bin2prasciiStr() //							*
*														*
****************************************************************/
char* bin2prasciiStr(char* binStr){

	size_t loops, len = strlen(binStr);
    int r = len % 8;
    if(r)
        r = 8 - r;

    char *paddedBin = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
    memset(paddedBin, '0', r);//add padding to top
    memcpy(paddedBin + r, binStr, len + 1);
    loops = (len + r) / 8;
    char *prasciiStr = malloc((loops + 1)*sizeof(char));//+1 for NUL
	char octet[9];
	memset(octet, '0', 8);
	octet[8]='\0';
    for(size_t i = 0; i < loops; i++){
		memcpy(octet, &paddedBin[8*i],8);
        prasciiStr[i] = bin2prasciiChar(octet);
    }
    prasciiStr[loops] = '\0';
    free(paddedBin);
    return prasciiStr;
}

/***************************************************************
*															   *
*			// prasciChar2bin() //							   *
*															   *
****************************************************************/
char* prasciiChar2bin(char prascii){

	char *bin = malloc(9*sizeof(char));
	for(int i =0;i<97;++i){
		if(prascii==prascii_table[i]){
			memcpy(bin,bin8_table[i],8);
			break;
		}
	}
	bin[8] = '\0';
	return bin;
}

/***************************************************************
*															   *
*			// prasciiStr2bin() //							   *
*															   *
****************************************************************/
char* prasciiStr2bin(char *prascii) {
 
    int i;
    size_t len = strlen(prascii);

    char* bin_str = (char*)malloc(((len * 8) + 1) * sizeof(char));
    for (i = 0; i < (int)len; i++) {
      char* binOctet = (char*)malloc(9*sizeof(char));
	  memcpy(binOctet,prasciiChar2bin(prascii[i]),8);
      memcpy(&bin_str[8*i], binOctet,8);
    }
    bin_str[8*len] = '\0';
    return bin_str;
}

/***************************************************************
*															   *
*			// hex2prasciiChar() //							   *
*															   *
****************************************************************/
char hex2prasciiChar(char* hex){

	char prascii = '0';
	char hexUpper[3];
	hexUpper[0] = hex[0];
	hexUpper[1] = toupper(hex[1]);
	hexUpper[2] = '\0';
	
	for(int i =0;i<97;++i){
		if(string_compare(hexUpper,hex2_table[i])==1){
			prascii = prascii_table[i];
			break;
		}
	}
	return prascii;
}

/***************************************************************
*															   *
*			// hex2prasciiStr() //							   *
*															   *
****************************************************************/
char* hex2prasciiStr(char* hexStr){

	size_t loops, len = strlen(hexStr);
    int r = len % 2;
    if(r)
        r = 2 - r;

    char *paddedHex = malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
    memset(paddedHex, '0', r);//add padding to top
    memcpy(paddedHex + r, hexStr, len + 1);
    loops = (len + r) / 2;
    char *prasciiStr = malloc((loops + 1)*sizeof(char));//+1 for NUL
    for(size_t i = 0; i < loops; i++){
		char* duet = (char*)malloc(3*sizeof(char));
		memset(duet, '0', 2);
		duet[2]='\0';
		memcpy(duet, &paddedHex[2*i],2);
        prasciiStr[i] = hex2prasciiChar(duet);
		free(duet);
    }
    prasciiStr[loops] = '\0';
    free(paddedHex);
    return prasciiStr;
}

/***************************************************************
*															   *
*			// prasciiChar2hex() //							   *
*															   *
****************************************************************/
char* prasciiChar2hex(char prascii){

	char *hex = malloc(3*sizeof(char));
	for(int i =0;i<97;++i){
		if(prascii==prascii_table[i]){
			memcpy(hex,hex2_table[i],3);
			break;
		}
	}
	hex[3] = '\0';
	return hex;
}

/***************************************************************
*															   *
*			// prasciiStr2hex() //							   *
*															   *
****************************************************************/
char* prasciiStr2hex(char *prascii) {
 
    int i;
    size_t len = strlen(prascii);

    char* hex_str = (char*)malloc(((len * 2) + 1) * sizeof(char));
    for (i = 0; i < (int)len; i++) {
      char* hexDuet = (char*)malloc(3*sizeof(char));
	  memcpy(hexDuet,prasciiChar2hex(prascii[i]),2);
      memcpy(&hex_str[2*i], hexDuet,2);
    }
    hex_str[2*len] = '\0';
    return hex_str;
}

/***************************************************************
*															   *
*			// charand() //									   *
*															   *
****************************************************************/
char charand(char bit1,char bit2){
	
	if(bit1 == '1' && bit2 == '1')
		return '1';
	else 
		return '0';

}

/***************************************************************
*															   *
*			// strand() //									   *
*															   *
****************************************************************/
char* strand(char* str1,char* str2){
	
	char* and = (char*)malloc((strlen(str1)+1)*sizeof(char));
	for(int i=0;i<(int)strlen(str1);++i){
		const char temp = charand(str1[i],str2[i]);
		and[i] = temp;
	}
	and[strlen(str1)]='\0';
	return and;

}

/***************************************************************
*															   *
*			// charxor() //									   *
*															   *
****************************************************************/
char charxor(char bit1,char bit2){
	
	if((bit1 == '1' && bit2 == '0') || (bit1 == '0' && bit2 == '1'))
		return '1';
	else 
		return '0';

}

/***************************************************************
*															   *
*			// strxor() //									   *
*															   *
****************************************************************/
char* strxor(char* str1, char* str2){
	
	char* xor = malloc((strlen(str1)+1));
	for(int i=0;i<(int)strlen(str1);++i){
		const char temp = charxor(str1[i],str2[i]);
		xor[i] = temp;
	}
	xor[strlen(str1)]='\0';
	return xor;
}

/***************************************************************
*															   *
*			// hexxor() //									   *
*															   *
****************************************************************/
char* hexxor(char* str1, char* str2){

	int binlen;
	int len1 = strlen(str1);
	char* bxor;
	char* hxor;
	if(strlen(str1)!=strlen(str2)){
		printf("This is a fixed width XOR function -- each hex string must be the same length!\n");
		exit(1);
	}else{
		binlen = 4*len1;
		char* bin1 = (char*)malloc((binlen+1)*sizeof(char));
		char* bin2 = (char*)malloc((binlen+1)*sizeof(char));
		memcpy(bin1,hexStr2bin(str1),binlen+1);
		memcpy(bin2,hexStr2bin(str2),binlen+1);
		bin2 = hexStr2bin(str2);
		bxor = strxor(bin1,bin2);
		hxor = bin2hexStr(bxor);
		return hxor;
	}
}

/***************************************************************
*															   *
*			// transposeCharArray() //						   *
*															   *
****************************************************************/
char** transposeCharArray(char** A, int m, int n){

	char** tarray = (char**)malloc((n)*sizeof(char*));
	for(int i = 0; i < n; ++i){
		printf("Transposing row %d ...\n\n",i+1);
		tarray[i] = (char*)malloc((m+1)*sizeof(char));
		for(int j = 0; j < m;++j){
			printf("Swapping column %d ...\n",j+1);
			tarray[i][j] = A[j][i];
		}
		tarray[i][m] = '\0';
	}
	return tarray;
}

/***************************************************************
*															   *
*			// cat2DCharMat() //							   *
*															   *
****************************************************************/
char* cat2dCharMat(char** A, int m, int n){
	
	char* temp = malloc((m*n+1)*sizeof(char));
	int length = 0;
	for(int i = 0; i < m;++i){
		memcpy(&temp[n*i], A[i],strlen(A[i]));
		length += (int)strlen(A[i]);
	}
	temp[length] = '\0';
	printf("Length of concatenated string is %d chars.\n",strlen(temp));
	return temp;
}

/***************************************************************
*															   *
*			// printNbitBin() //							   *
*															   *
****************************************************************/
void printNbitBin(int n){
	
	if(n==0){
		printf("Can't print a zero bit number! Terminating.\n");
		exit(1);
	}else{
		for(int i = 0;i<pow(2,n);++i){
			if(i==0){
				printf("\n{ \"%s\",", dec2bin(i,n));
			}else if(i==pow(2,n)-1){
				printf("\"%s\"};\n\n",dec2bin(i,n));
			}else{
				printf("\"%s\",",dec2bin(i,n));
			}
		}
	}
}

/***************************************************************
*														*
*			// textFile2Array() //							*
*														*
****************************************************************/
char** textFile2Array(char* file){

    int i = 0;
    int lines_allocated = pow(2,9);
    int max_line_len = pow(2,6);

    char **lines = (char **)malloc(sizeof(char*)*lines_allocated);
    FILE *fp = fopen(file, "r");
    if (fp == 0)
    {
        fprintf(stderr, "failed to open %s\n",file);
        exit(1);
    }
    while (i < lines_allocated)
    {
		lines[i] = malloc(max_line_len*sizeof(char));
		if(fgets(lines[i],max_line_len-1,fp)==NULL)
			break;
		else{
			for(int j=0;j<strlen(lines[i]);++j){
				if(lines[i][j]=='\n')
					lines[i][j] = '\0';
			}
		}
        i += 1;
    }
    fclose(fp);
    return lines;
}

/***************************************************************
*															   *
*			// textFile2String() //							   *
*															   *
****************************************************************/
char* textFile2String(char* file){

    int i = 0;
    int lines_allocated = pow(2,8);
    int max_line_len = pow(2,6);
	int len;

    FILE *fp = fopen(file, "r");
	if (fp == 0)
    {
        fprintf(stderr, "failed to open %s\n",file);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fseek(fp, SEEK_SET, 0);
    char* lines = malloc(len);
    while (i < lines_allocated)
    {
		char* buffer = malloc(max_line_len);
		if(fgets(buffer,max_line_len,fp)==NULL)
			break;
		buffer[strcspn(buffer, "\n")] = '\0';
		if(i==0)
			strcpy(lines,buffer);
		else
			strcat(lines,buffer);
        i += 1;
		free(buffer);
    }
    fclose(fp);

    return lines;
}

/***************************************************************
*															   *
*			// findMaxElement() //							   *
*															   *
****************************************************************/
int findMaxElement(double* array, int len){
	
	int index=0;
	double max = -pow(2,32);
	for(int i = 0;i<len;++i){
		if((double)array[i]>=max){
			max = (double)array[i];
			index = i;
		}
	}
	return index;
}

/***************************************************************
*															   *
*			// findMinElement() //							   *
*															   *
****************************************************************/
int findMinElement(double* array, int len){
	
	int index=0;
	double max = pow(2,32);
	for(int i = 0;i<len;++i){
		if((double)array[i]<=max){
			max = (double)array[i];
			index = i;
		}
	}
	return index;
}

/***************************************************************
*															   *
*			// scorePlaintext() //							   *
*															   *
****************************************************************/
double scorePlaintext(char* plaintext){

	double score = 0;
	double typicalSpaceCount = strlen(plaintext)/meanWordLength;
	int spaceCount = 0;
	for(int i=0;i<(int)strlen(plaintext);++i){
		for(int j=0; j<24;++j){
			if(plaintext[i]==commonLetters[j]){
				score += commonLetterWeight[j]; // Reward common letters
			}
		}
		for(int k=0; k<9;++k){
			if(plaintext[i]==nonAlphaNumericChars[k]){
				score += -2*commonLetterWeight[findMaxElement(commonLetterWeight,24)]; // Penalize uncommon chars
			}
		}
		if(plaintext[i]== ' ')
			spaceCount += 1;
	}
	if((double)spaceCount < 0.5*typicalSpaceCount)
		score += -2*commonLetterWeight[findMaxElement(commonLetterWeight,24)]; // Penalize lack of spaces

	if((double)spaceCount < 1.2*typicalSpaceCount && (double)spaceCount > 0.8*typicalSpaceCount)
		score += 2*commonLetterWeight[findMaxElement(commonLetterWeight,24)]; // Reward acceptable amount of spaces

	return score;
}

/***************************************************************
*															   *
*			// scorePlaintext_chiSquare() //				   *
*															   *
****************************************************************/
double scorePlaintext_chiSquare(char* plaintext){

	double score = 0;
	double count[26];
	double chiSquares[27];
	for(int i = 0; i < 26; ++i)
		count[i] = 0;
	int spaceCountReal = 0;
	double spaceCountExpected = strlen(plaintext)/meanWordLength;
	for(int j = 0; j < strlen(plaintext); ++j){
		if(plaintext[j]=='A' || plaintext[j]=='a')
			count[0] += 1;
		else if(plaintext[j]=='B' || plaintext[j]=='b')
			count[1] += 1;
		else if(plaintext[j]=='C' || plaintext[j]=='c')
			count[2] += 1;
		else if(plaintext[j]=='D' || plaintext[j]=='d')
			count[3] += 1;
		else if(plaintext[j]=='E' || plaintext[j]=='e')
			count[4] += 1;
		else if(plaintext[j]=='F' || plaintext[j]=='f')
			count[5] += 1;
		else if(plaintext[j]=='G' || plaintext[j]=='g')
			count[6] += 1;
		else if(plaintext[j]=='H' || plaintext[j]=='h')
			count[7] += 1;
		else if(plaintext[j]=='I' || plaintext[j]=='i')
			count[8] += 1;
		else if(plaintext[j]=='J' || plaintext[j]=='j')
			count[9] += 1;
		else if(plaintext[j]=='K' || plaintext[j]=='k')
			count[10] += 1;
		else if(plaintext[j]=='L' || plaintext[j]=='l')
			count[11] += 1;
		else if(plaintext[j]=='M' || plaintext[j]=='m')
			count[12] += 1;
		else if(plaintext[j]=='N' || plaintext[j]=='n')
			count[13] += 1;
		else if(plaintext[j]=='O' || plaintext[j]=='o')
			count[14] += 1;
		else if(plaintext[j]=='P' || plaintext[j]=='p')
			count[15] += 1;
		else if(plaintext[j]=='Q' || plaintext[j]=='q')
			count[16] += 1;
		else if(plaintext[j]=='R' || plaintext[j]=='r')
			count[17] += 1;
		else if(plaintext[j]=='S' || plaintext[j]=='s')
			count[18] += 1;
		else if(plaintext[j]=='T' || plaintext[j]=='t')
			count[19] += 1;
		else if(plaintext[j]=='U' || plaintext[j]=='u')
			count[20] += 1;
		else if(plaintext[j]=='V' || plaintext[j]=='v')
			count[21] += 1;
		else if(plaintext[j]=='W' || plaintext[j]=='w')
			count[22] += 1;
		else if(plaintext[j]=='X' || plaintext[j]=='x')
			count[23] += 1;
		else if(plaintext[j]=='Y' || plaintext[j]=='y')
			count[24] += 1;
		else if(plaintext[j]=='Z' || plaintext[j]=='z')
			count[25] += 1;
		else if(plaintext[j]==' ')
			spaceCountReal += 1;
	}
	for(int k = 0; k < 26; ++k){
		chiSquares[k] = pow((count[k]/strlen(plaintext)-allLetterStats_short[k]),2)/allLetterStats_short[k];
	}
	chiSquares[26] = pow(spaceCountReal-spaceCountExpected,2)/spaceCountExpected;
	for(int i = 0; i < 27; ++i)
		score += chiSquares[i];

	return score;
}

/***************************************************************
*															   *
*			// getHammingDistance() //						   *
*															   *
****************************************************************/
int getHammingDistance(char* str1, char* str2){

	if(strlen(str1)!=strlen(str2)){
		printf("The Hamming distance is reserved for strings of equal length. Terminating (1).\n");
		exit(1);
	}else{
		int count = 0;
		char* binStr1 = (char*)malloc((8*strlen(str1)+1)*sizeof(char));
		char* binStr2 = (char*)malloc((8*strlen(str2)+1)*sizeof(char));
		binStr1 = prasciiStr2bin(str1);
		binStr2 = prasciiStr2bin(str2);
		for(int i = 0; i < strlen(binStr1);++i){
			if(binStr1[i]!=binStr2[i])
				++count;
		}
		free(binStr1);
		free(binStr2);
		return count;
	}
}

/***************************************************************
*															   *
*			// xorcyph_getSingleByteHexKey() //				   *
*															   *
****************************************************************/
char* xorcyph_getSingleByteBinKey(char* bin){   

	double scores[97];
	memset(scores, 0,97);
	int len = strlen(bin); // get length of input
	int keyIndex = 0;
    for(int i = 0;i<97;++i){ // for every plaintext letter
		char* key = (char*)malloc((len+1)*sizeof(char));
		char* xord = (char *)malloc((len+1)*sizeof(char));
		char* plaintext = (char*)malloc((len/8+1)*sizeof(char));
		for(int j = 0; j<len/8;++j){
			memcpy(&key[8*j],bin8_table[i],8);
		}
		key[len]='\0';
		memcpy(xord,strxor(bin,key),len);//try decryption with key
		xord[len] = '\0';
		memcpy(plaintext, bin2prasciiStr(xord),len/8); // Convert binary to ASCII
		plaintext[len/8] = '\0';
		scores[i] = scorePlaintext_chiSquare(plaintext);
		free(key);
		free(xord);
		free(plaintext);
	}
	keyIndex = findMinElement(scores,97);
	return bin8_table[keyIndex];
}
/***************************************************************
*															   *
*			// xorcyph_encryptHexKey() //					   *
*															   *
****************************************************************/
char* xorcyph_encryptHexKey(char* plaintext, char* hexKey){

	int len = strlen(plaintext);
	int keyLen = strlen(hexKey);
	char* keyBuff = (char*)malloc((2*len+1)*sizeof(char));
	for(int i = 0; i<len;++i){
		int charsLeft = 2*len-keyLen*i;
		if(charsLeft>=keyLen){
			memcpy(&keyBuff[keyLen*i],hexKey,keyLen);
		}else{
			memcpy(&keyBuff[keyLen*i],hexKey,charsLeft);
			break;
		}
	}
	keyBuff[2*len]='\0';
	return hexxor(prasciiStr2hex(plaintext),keyBuff);
}

/***************************************************************
*															   *
*			// xorcyph_decryptHex() //						   *
*															   *
****************************************************************/
char* xorcyph_decryptHex(char* hex, char* key){   

	char* keyBuff = (char*)malloc((strlen(hex)+1)*sizeof(char));
	char* plainHex;
	if(strlen(hex)!=strlen(key)){
		for(int k = 0; k<strlen(hex)/2;++k){
			memcpy(&keyBuff[2*k],key,2);
		}
		keyBuff[strlen(hex)]='\0';
	}else
		keyBuff = key;
	
	plainHex = hexxor(hex,keyBuff);
	free(keyBuff);
	return plainHex;
}

/***************************************************************
*															   *
*			// xorcyph_encryptPlainKey() //					   *
*															   *
****************************************************************/
char* xorcyph_encryptPlainKey(char* plaintext, char* plainKey){

	char* hexKey = prasciiStr2hex(plainKey);
	return xorcyph_encryptHexKey(plaintext,hexKey);
}

/***************************************************************
*															   *
*			// xorcyph_getSingleByteHexKey() //				   *
*															   *
****************************************************************/
char* xorcyph_getSingleByteHexKey(char* hex){   

	double scores[97];
	memset(scores, 0,97);
	int len = strlen(hex); // get length of input
	int keyIndex = 0;
    for(int i = 0;i<97;++i){ // for each of 16 hex chars
		char* key = (char*)malloc((len+1)*sizeof(char));
		char* xord = (char *)malloc((len+1)*sizeof(char));
		char* plaintext = (char*)malloc((len/2+1)*sizeof(char));
		for(int j = 0; j<len/2;++j){
			memcpy(&key[2*j],hex2_table[i],2);
		}
		key[len]='\0';
		memcpy(xord,hexxor(hex,key),len+1);//try decryption with key
		memcpy(plaintext, hex2prasciiStr(xord),len/2); // Convert binary to ASCII
		plaintext[len/2] = '\0';
		scores[i] = scorePlaintext_chiSquare(plaintext);
		free(key);
		free(xord);
		free(plaintext);
	}
	keyIndex = findMinElement(scores,97);
	return hex2_table[keyIndex];
}

/***************************************************************
*															   *
*			// xorcyph_encryptBinKey() //					   *
*															   *
****************************************************************/
char* xorcyph_encryptBinKey(char* plaintext, char* binKey){

	int len = strlen(plaintext);
	int keyLen = strlen(binKey);
	char* keyBuff = (char*)malloc((8*len+1)*sizeof(char));
	for(int i = 0; i<len;++i){
		int charsLeft = 8*len-keyLen*i;
		if(charsLeft>=keyLen){
			memcpy(&keyBuff[keyLen*i],binKey,keyLen);
		}else{
			memcpy(&keyBuff[keyLen*i],binKey,charsLeft);
			break;
		}
	}
	keyBuff[8*len]='\0';
	return strxor(prasciiStr2bin(plaintext),keyBuff);
}

/***************************************************************
*															   *
*			// xorcyph_decryptBin() //				   		   *
*															   *
****************************************************************/
char* xorcyph_decryptBin(char* bin, char* key){   

	int len = strlen(bin);
	char* keyBuff = (char*)malloc((len+1)*sizeof(char));
	for(int k = 0; k<len/8;++k){
		memcpy(&keyBuff[8*k],key,8);
	}
	keyBuff[len]='\0';

	return strxor(bin,keyBuff);
}

/***************************************************************
*															   *
*			// xorcyph_findEncryptedHexLine() //			   *
*															   *
****************************************************************/
int xorcyph_findEncryptedHexLine(char** lines, int numLines){

	double scores[numLines];
	int index,line_length = 60;
	char** decryptedLines = (char**)malloc((numLines)*sizeof(char));
	memset(scores,0,numLines);
	for(int i = 0; i < numLines; ++i){
		decryptedLines[i] = (char*)malloc((line_length+1)*sizeof(char));
		char* lineKey = xorcyph_getSingleByteHexKey(lines[i]);
		decryptedLines[i] = hex2prasciiStr(xorcyph_decryptHex(lines[i],lineKey));
		scores[i] = scorePlaintext_chiSquare(decryptedLines[i]);
		free(decryptedLines[i]);
	}
	index = findMinElement(scores,numLines);
	return index;
}

/***************************************************************
*														*
*			// xorcyph_findLeastNormalizedHammingBytes() //	*
*														*
****************************************************************/
int* xorcyph_findLeastNormalizedHammingBytes(char* bin, int n){

	int MAX_KEYSIZE = 40;
	if(MAX_KEYSIZE > strlen(bin)/16){
		printf("Error: Key size cannot be larger than %d for this string. Terminating.\n",strlen(bin)/16);
		exit(1);
	}
	if(n > MAX_KEYSIZE){
		printf("Error: Either decrease number of bytes or increase MAX_KEYSIZE. Terminating.\n");
		exit(1);
	}
	double* hammingDistances = (double*)malloc((MAX_KEYSIZE)*sizeof(double));
	for(int keySize = 2;keySize <= MAX_KEYSIZE; ++keySize){
		char* block1 = (char*)malloc((8*keySize+1)*sizeof(char));
		char* block2 = (char*)malloc((8*keySize+1)*sizeof(char));
		memcpy(block1,bin,8*keySize);
		memcpy(block2,&bin[8*keySize],8*keySize);
		block1[8*keySize] = '\0';
		block2[8*keySize] = '\0';
		hammingDistances[keySize-2] = (double)getHammingDistance(block1,block2)/keySize;
		free(block1);
		free(block2);
	}
	int* byteSizes = malloc(n*sizeof(int));
	for(int i = 0; i < n; ++i){
		int indexMin = findMinElement(hammingDistances,MAX_KEYSIZE-1);
		byteSizes[i] = indexMin+2;
		hammingDistances[indexMin] = pow(2,16);
	}
	free(hammingDistances);
	return byteSizes;
}

/***************************************************************
*														*
*			// xorcyph_decryptNbyteRepKey() //               *
*														*
****************************************************************/
char* xorcyph_decryptNbyteRepKey(char* bin, int keySize){

	/* Break cipher text into keySize blocks -- VERIFIED*/
	int numBlocks = strlen(bin)/(8*keySize); // number of block to analyze
	char partitionsArray[numBlocks][8*keySize+1];
	char partitionsArrayT[keySize][8*numBlocks+1];

	printf("Creating %d partitions (%d bytes each) from ciphertext ...",numBlocks,keySize);
	for(int i = 0; i<numBlocks;++i){
		memcpy(partitionsArray[i],&bin[8*i*keySize],8*keySize);
		partitionsArray[i][8*keySize] = '\0';
																						//printf("partitions[%d]: %s\n\n", i, partitionsArray[i]);
	}

	/* Transpose blocks so that each new block i contains the i'th ordered byte of each old block -- VERIFIED*/
	printf("Success.\nJoining the first byte of each partition to create %d new partitions (%d bytes each) ...", keySize,numBlocks);
	for(int i = 0; i < keySize; ++i){
		for(int j = 0; j < numBlocks; ++j){
			//printf("Printing partitions[%d]: %s", j,8*i,partitions[j]);
			memcpy(&partitionsArrayT[i][8*j],&partitionsArray[j][8*i],8);
			//if(j==numBlocks-1)
			//	partitionsT[i][8*(j+1)] = '\0';
		}
	}
	
	printf("Success.\nPerforming single byte XOR decryption on each partition ...");
	char* cipherKey = malloc((8*keySize+1));
	if(!cipherKey){
		printf("Cannot allocate memory for cipherKey. Terminating.\n");
		exit(1);
	}
	for(int i = 0; i < keySize; ++i){ 
		//printf("Decrypting Partition #%d\n",i+1);
		double scores[97];
		memset(scores, 0,97);
		int len = strlen(partitionsArrayT[i]); // get length of input
		char* partitionsT = partitionsArrayT[i];
		int keyIndex = 0;

		/* For every potential 1 byte key, attempt decryption of partition. Record scores. */
	    for(int j = 0;j<97;++j){
			//printf("Extending key: %s...",bin8_table[j]); 
			char* key = (char*)malloc((len+1)*sizeof(char));
			char* xord = (char *)malloc((len+1)*sizeof(char));
			char* plaintext = (char*)malloc((len/8+1)*sizeof(char));

			/* Duplicate key into string until size matches partition */
			for(int k = 0; k<len/8;++k){
				memcpy(&key[8*k],bin8_table[j],8);
			}
			key[len]='\0';
			//printf("Complete.\nXOR'ing with ciphertext ...");
			/* XOR the cipher text with key and convert to ASCII */
			//printf("Printing key: %s (%d chars)\n", key, strlen(key));
			//printf("Printing partition: %s (%d chars)\n", partitionsT, strlen(partitionsT));
			memcpy(xord,strxor(partitionsT,key),len+1);//try decryption with key
			xord[len] = '\0';
			//printf("Complete.\nConverting to ASCII ...", xord);
			strcpy(plaintext, bin2prasciiStr(xord)); // Convert binary to ASCII
			//printf("Key: %s\n Plaintext: %s\n", key, plaintext);
			//printf("Plaintext[%d]: %s\n",i, plaintext);
			//printf("xorcyph_decrypt(): Successfully converted XOR'd input to plaintext ... \n");
			//printf("Complete.\nScoring plaintext ...");
			plaintext[len/8] = '\0';
			/* Score the resulting plaintext */
			scores[j] = scorePlaintext_chiSquare(plaintext);
			//printf("Complete.\nFreeing key ...");
			//printf("xorcyph_decrypt(): Successfully scored plaintext ... \n");
			free(key);
			//printf("Complete.\nFreeing xord ...");
			free(xord);
			//printf("Complete.\nFreeing plaintext...");
			//free(plaintext);
			//printf("Complete.\n");
			//printf("xorcyph_decrypt(): Successfully freed plaintext ... \n");
		}
		//printf("Exited for loop.\n");
		/* Print all scores */
		//printf("The scores for partition #%d are:\n",i);
		for(int q = 0; q < 97; ++q){
			//printf("scores[%d] = %s: %f\n", q,bin8_table[q],scores[q]);
		}
		/* Find the highest scoring 1-byte key and save it*/
		keyIndex = findMinElement(scores,97);
		char* byteKey = bin8_table[keyIndex];
		if(i==0)
			strcpy(cipherKey,byteKey);
		else
			strcat(cipherKey,byteKey);
		//printf("Printing key for byte %d: %s\n", i+1,byteKey);
		//printf("Highest score: %f (scores[%d])\n", scores[keyIndex],keyIndex);
	}
	cipherKey[8*keySize] = '\0';
	//printf("Success.\nPrinting Vigenere Cipher key: %s\n", cipherKey);
	
	return cipherKey;
}

/***************************************************************
*														*
*			// aes_128_ecb() //							*
*														*
****************************************************************/
char* aes_128_ecb(char* bin, char* key){


	return bin;

}
