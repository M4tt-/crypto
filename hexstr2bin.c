#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* hex2bin(char);

char* hexstr2bin(char *hex_str) {
 
  int i;
  char *str;
  size_t len = strlen(hex_str);
  // Hex Str length * 4 bits + 1 terminating char
  char* bin_str = (char*)malloc(((len * 4) + 1) * sizeof(char));
  for (i = 0; i < len - 1; i++) {
    const char* binQuartet = hex2bin(hex_str[i]);
    strcat(bin_str, binQuartet);
  }
  str = bin_str;
  free(bin_str);
  return str;
}
