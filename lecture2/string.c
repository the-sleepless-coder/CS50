#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void){
    string s = get_string("Input: ");

    printf("Output : ");

    // you do not have to redundantly calculate the length of s in the for loop
    for(int i = 0, len = strlen(s); i < len; i++){
        printf("%c", s[i]);
    }
    printf("\n");

}