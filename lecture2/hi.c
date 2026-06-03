#include <stdio.h>
#include <cs50.h>

int main(void){
    char c1 = 'H';
    char c2 = 'I';
    char c3 = '!';

    string words[2];

    words[0] = "HI!";
    words[1] = "BYE!";

    printf("%c%c%c\n", words[0][0], words[0][1], words[0][2]);
    printf("%s\n", words[1]);

    //printf("%i %i %i %i %i %i\n", s[0], s[1], s[2], s[3], s[4], s[5]);
    
    //printf("%c%c%c \n", s[0], s[1], s[2]);
    //printf("%c%c%c \n", c1, c2, c3);
    //printf("%i %i %i \n", c1, c2, c3);
}