#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* hex2bin(char);

char* hexstr2bin(char *hex_str) {
 
  int i;
  char *str;
  size_t len = strlen(hex_str);
  //printf("Printing length of hex string: %d\n", len);
  //printf("Printing required loop iterations: %d\n\n", (int)len/4);
  // Hex Str length * 4 bits + 1 terminating char
  char* bin_str = (char*)malloc(((len * 4) + 1) * sizeof(char));
  for (i = 0; i < len; i++) {
	//printf("For loop iteration: %d\n", i+1);
    const char* binQuartet = hex2bin(hex_str[i]);
	//printf("Printing marked quartet for conversion: %s\n", binQuartet);
    memcpy(&bin_str[4*i], binQuartet,5);
  }
  str = bin_str;
  free(bin_str);
  return str;
}
