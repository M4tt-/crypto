#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int string_compare(char str1[], char str2[])
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
