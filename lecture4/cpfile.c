#include <stdio.h>
#include <stdint.h>

// define byte as unsigned 8 bits
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // .cpfile src dest
    // copy one file to another
    // cp source destination
    // treat all the data s 0,1s
    FILE *src = fopen(argv[1],"rb");
    FILE *dst = fopen(argv[2], "wb");

    BYTE b;

    // read the the source file in byte sizes
    // send the bytes to the destination file
    while(fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);

}