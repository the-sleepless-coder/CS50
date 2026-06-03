#include <stdio.h>
#include <cs50.h>

// 함수 원형 선언.
void draw(int num);

int main(void){

    while(true){
        int num = get_int("Type in number: ");

        // 1~8 범위의 입력값만 받는다.
        if(num <=0 || num>=9 ) continue;

        // 굳이 이걸 함수화 시킬 필요가 있을까?
        draw(num);

    }
}


// 함수화해서 나타내보자.
void draw(int num){
    for(int n=1; n<=num; n++){
        // 빈 공간 space
        for(int s=1; s<= num-n; s++){
            printf(" ");
        }

        // 벽돌 bricks
        for(int b=1; b <= n; b++){
            printf("#");
        }

        printf("  ");

        // 벽돌 bricks
        for(int b=1; b <= n; b++){
            printf("#");
        }

        // 빈 공간 space
        for(int s=1; s<= num-n; s++){
            printf(" ");
        }

        printf("\n");
    }
}