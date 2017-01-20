#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char bin2hexChar(char*);

char *bin2hexStr(char *binStr){
    int loops, len = (int)strlen(binStr);
    int r = len % 4;
    if(r)
        r = 4 - r;

    char *paddedBin = (char *)malloc((len + r + 1)*sizeof(char));//+1 for null-terminator
    memset(paddedBin, '0', r);//add padding to top
    memcpy(paddedBin + r, binStr, len + 1);
    loops = (len + r) / 4;
    char *hexStr = (char *)malloc((loops + 1)*sizeof(char));//+1 for NUL
    int i;
    // Initialize quartet
    char *binQuartet = (char *)malloc((4+1)*sizeof(char));
    for(i = 0; i < loops; i++){
        // Copy in our 4 bytes
        memcpy(binQuartet, paddedBin + i * 4, 4);
        hexStr[i] = bin2hexChar(binQuartet);
    }
    // Free quartet memory
    free(binQuartet);
    hexStr[loops] = '\0';
    free(paddedBin);
    return hexStr;
}
