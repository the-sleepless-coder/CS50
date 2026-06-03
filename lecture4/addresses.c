#include <stdio.h>

typedef int integer;
//typedef char * string;

int main(void){
    // using the typedef, you can literally name a primitive type and give it a name
    integer n = 50;

    // where is the number saved?
    // save the address of n in the pointer variable which is an int

    // when you declare the address you use *p and the type of it
    int *p = &n;

    // when you want to dereference and find the variable,
    // you don't need to specify the data type
    printf("%i address : %p\n", *p, p);

    // the strings are contiguous, specifically 1 byte apart
    // s is storing the first byte of the characters
    // you can find the end by the nul character, without having to know the full characters within the string

    // pointer s which includes a char in the address.
    char *s = "HI!";

    // getting the address of each of the characters
    // &s would mean to get the address of the pointer, which is a totally different thing.
    printf("%p \n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);

}