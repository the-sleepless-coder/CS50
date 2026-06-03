#include <cs50.h>
#include <stdio.h>

int main(void){

    long dollars = 1;
    
    // 32 bits
    // integer overflow
    // 32bit을 넘어가게 될 경우 다시 음수가 됨.
    while(true){
        char c = get_char("Here's %li dollars. Double it and give it to the next person?", dollars);
        if(c=='y'){
            dollars *=2;
        }else {
            break;
        }
    }
    
    printf("Here's %li dollars", dollars);

}