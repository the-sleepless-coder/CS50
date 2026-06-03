#include <cs50.h>
#include <stdio.h>
#include <string.h>

int strcmp_cust(char *s, char *t);

int main(void){
    /**
    int n = 50;
    int m = 50;
    
    // 숫자 자체가 같은지를 비교하는 연산
    if(n==m){
        printf("%p\n", &n);
        printf("%p\n", &m);
        
        printf("same number\n");
    }else{
        printf("%p", &n);
        printf("%p", &m);
        
        printf("different number\n");
    }

    return 0;
    * */

    char *s = get_string("s: ");
    char* t = get_string("t: ");
    
    // s, t의 시작 주소를 비교하는 연산
    // comparing 2 different addresses
    // 각 s, t 포인터 연산자가 갖고 있는 주소 값을 비교하는 것이기 때문에, 
    // 당연히 같은 문자열이 들어 있어도 주소값을 비교한 연산의 결과값이 다르게 나온다.
    if(strcmp_cust(s, t)==0){
        printf("s: %p\n", &s);
        printf("t: %p\n", &t);
        
        printf("Same\n");
    }else{
        printf("s: %p\n", &s);
        printf("t: %p\n", &t);
        
        printf("Different\n");
    }

    
}

int strcmp_cust(char *s, char *t)
{
    // 서로 같은 값인지를 확인하고, 
    // 같은 문자일 때만 연산 진행.
    while(*s == *t){
        // 끝까지 모두 같은 값이면,
        // 같은 값 임을 나타내는 0 반환.
        if(*s == '\0') return 0;
        
        // 다음 문자를 비교한다.
        s++;
        t++;
    }

    // 서로 다르면 차이 나는 값을 반환
    // 음수면 s가 t 앞이고,
    // 양수먄 s가 t뒤이다.
    return *s- *t;

}