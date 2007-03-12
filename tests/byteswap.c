
#include <byteswap.h>
#include <stdio.h>

int verbose = 0;

int main(int c, char **argv)
{
    unsigned short a16,b16,c16; 
    unsigned long a32,b32,c32; 
    unsigned long long int a64,b64,c64; 
    int result = 0;
    
    a16 = 0x1234;
    b16 = bswap_16(a16);
    c16 = 0x3412;
    
    a32 = 0x12345678;
    b32 = bswap_32(a32);
    c32 = 0x78563412;

    a64 = 0x0102030405060708LL;
    b64 = bswap_64(a64);
    c64 = 0x0807060504030201LL;
    if (c16 != b16) {
        result = 1;
        printf("bswap_16 converation error: %04x %04x\n",a16,b16);
    }    
    if (c32 != b32) {
        result = 1;
        printf("bswap_32 converation error: %04x %04x\n",a32,b32);
    }
    if (c64 != b64) {
        result = 1;
        printf("bswap_64 converation error %8x%08x %08x%08x\n",(int)(a64>>32),(int)(a64),(int)(b64>>32),(int)(b64));
    }
    return result;
}
