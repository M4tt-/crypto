extern char bin2hexChar(char*);

char *bin2hexStr(char *binStr){
    size_t loops, len = strlen(binStr);
    int r = len % 4;
    if(r)
        r = 4 - r;

    char *paddedBin = malloc(len + r + 1);//+1 for null-terminator
    memset(paddedBin, '0', r);//add padding to top
    memcpy(paddedBin + r, binStr, len + 1);
    loops = (len + r) / 4;
    char *hexStr = malloc(loops + 1);//+1 for NUL
    for(size_t i = 0; i < loops; i++){
        hexStr[i] = bin2hexChar(paddedBin + i * 4);
    }
    hexStr[loops] = '\0';
    free(paddedBin);
    return hexStr;
}