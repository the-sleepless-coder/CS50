#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(void){

    string s = get_string("Before: ");

    printf("After: ");

    for(int i=0, len = strlen(s); i < len ; i++){
        /* 
        if( s[i] >='a' && s[i] <='z' ){
            s[i] = s[i] - ('a'-'A');
        }  
        printf("%c", s[i]);
        */
        printf("%c", toupper(s[i]));
    }
    printf("\n");


}