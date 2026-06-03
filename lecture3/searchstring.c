#include <cs50.h>
#include <stdio.h>
#include <string.h>

int strcmp_cust( char* s1, char* s2 );

int main(void){

    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "tophat"};

    // strings have different lengths
    // 시작하는 주소만 확인하는 것이기 때문에, 
    // strcmp를 이용해서 모든 char가 같은지를 확인한다.
    /*while (*s1 == *s2)
    {
        if (*s1 == '\0')
            return 0;

        s1++;
        s2++;
    }

    각 주소지에 있는 값이 다 같은지를 확인한다.
    모든 값이 다 일치한다면 0을 반환
    다른 값이 발생하면 ascii 코드 상 차이를 반환한다. 
    그래서 음수가 나오면 사전 순으로 앞
    양수가 나오면 사전 순으로 뒤 
    return *s1 - *s2; 
    */
    string s = get_string("String: ");
    for(int i=0; i<6; i++){
        if(strcmp_cust(strings[i], s)==0){
            printf("Found\n");
            return 0;
        }
    }

    printf("Not found\n");
    return 1;

}


// 커스터마이징된 strcmp
int strcmp_cust( char* s1, char* s2 )
{   
    while(*s1==*s2){
        if(*s1=='\0') return 0;
        
        // 주소값에서 현재 타입만큼의 다음 주소로 넘어가서 확인한다.
        s1++;
        s2++;
    }
    
    return *s1-*s2;
}