#include "RubbishHash.h"
#include <cstdio>

int main()
{
    unsigned long hash = 504981L;

    unsigned int x = 0;
    for(unsigned int i = 0; i < 10000; i++)
    {
        if(rubbish_hash(i) == hash) 
        {
            x = i;
            break;
        }
    }

    printf("Found x = %u, hash(x) = %lu\n", x, hash);

    return 0;
}