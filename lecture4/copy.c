#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void){

    char *s = get_string("s:");

    //char *t = s;
    // allocate n bytes and return the address of the start of the chunk of memory
    char *t = malloc(strlen(s) + 1);
    // if malloc fails to allocate memory, return 1
    if(t==NULL) return 1;

    // copy each of the characters in t
    // copy the nul character also
    /**for(int i=0, n = strlen(s); i<=n; i++){
        t[i] = s[i];
    }
    */

    // dest, source
    stcpy(t, s);

    // t is essentially copying the same address s is pointing to
    // hence using the same address

    // if there is no alphabet to capitalize,
    // don't do it
    if(strlen(t)>0){
        t[0] = toupper(t[0]);
    }
    
    // s & t both were capitalized
    printf("s: %s\n", s);
    printf("t: %s\n", t);
    
    // string is a sequence of locations
    // so you need to allocate a new address and copying the characters from old to new

    free(s);
    free(t);

}
