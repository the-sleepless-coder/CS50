#include <cs50.h>
#include <stdio.h>

int main(void){

    char c = get_char("Do you agree? ");
    // 모든 경우를 다 반영해야 한다.
    if(c=='y' || c =='Y'){
        printf("Agree.\n");
    }else if(c=='n' || c=='N'){
        printf("Not agreed.\n");
    }
}