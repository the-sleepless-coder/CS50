#include <stdio.h>
#include <cs50.h>

int main(void){
    
    while(true){
        int num = get_int("Type in number: ");

        if(num <= 0 || num>=9) continue;

        // 각 블록을 반복하는 부분.
        for(int n=1; n<=num; n++){
            // space 공간을 출력하는 부분.
            for(int s=1; s <= num-n ; s++){
                printf(" ");
            }
            
            // brick 돌을 출력하는 부분.
            for(int b=1; b<=n; b++){
                printf("#");
            }

            printf("\n");
        }
    }
    



}