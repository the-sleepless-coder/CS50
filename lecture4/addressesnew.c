#include <stdio.h>

int main(void){

    char *s = "HI!";

    // pointer arithmetic
    // since pointers are numbers, you can just add numbers to it to access certain points
    // go to the address of the next byte to find the character in the given address that are 1byte apart
    printf("%c\n", *s );
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));

    printf("%s\n", s+1);

    // synctactic sugar
    // user friendly syntaxes that are used to express harder and weirder syntax
    // square brackets are used so that I don't need to use the address expressed in bytes 
    // char *s = "HI";
    // *(s+1)
    // s[1]
}