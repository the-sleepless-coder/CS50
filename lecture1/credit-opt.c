#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

typedef struct{
    int digit;
    bool istrue;
}CardInfo;

CardInfo checksum(long cardnum);
int checkcardtype(long input, int digits, bool istrue);

int main(void){
    long input = get_long("Type in card num: ");

    // check the digits and the validation of the card_num
    CardInfo c = checksum(input);    
    int digits = c.digit;
    bool istrue = c.istrue;
    
    // check what type of card it is.
    checkcardtype(input, digits, istrue);

}

/* 풀이 방식 최적화 */
// 이번에는 동일하게 푸는데, 
// pow를 쓰지 않고 푸는 것이 좋을듯 하다.    
// 그렇지 않으면 up down casting의 복잡한 과정을 거쳐야하니까.
// 함수 단위로 정리.

// 카드 자리 수와 유효성 확인.
CardInfo checksum(long cardnum){
    long temp = cardnum;

    int idx = 0;
    long sum = 0;
    while( temp > 0 ){
        long num = temp % 10;
        temp = temp / 10;

        if(idx%2 == 0){
            sum += num;
        }else{
            int added_num = num*2;
            if(added_num>=10){
                sum += added_num / 10;
            }
            sum += added_num % 10;
        }
        
        idx++;
    }

    bool istrue = false;
    if( sum%10 ==0 ) istrue = true;

    //int* result = malloc(sizeof(int)*3);
    // result[0] = idx;
    // result[1] = istrue;
    
    // 카드 번호의 자리 수와 카드 숫자가 유효한지 확인하는 변수를 반환한다.
    CardInfo c1;
    c1.digit = idx;
    c1.istrue = istrue;

    return c1;
}

// 카드 유형 확인.
int checkcardtype(long input, int digits, bool istrue){
    double base = 10.0;
    int starting_num = (int) (input / pow(base, digits-2));
    string cardType = "";
    if((starting_num == 34 || starting_num==37) && digits == 15) cardType = "AMEX";
    else if(starting_num >=51 && starting_num<=55 && digits == 16)cardType="MASTERCARD";
    else if(starting_num>=40 && starting_num<=49 && (digits == 13||digits == 16))  cardType="VISA";
    
    if(strcmp(cardType,"")== 0) cardType="INVALID_CARD\n";
    
    // 카드 번호가 잘못됐거나, 카드 종류가 존재하지 않는다면 INVALID_CARD
    if( !istrue || strcmp(cardType, "INVALID_CARD") == 0 ) {
        if(!istrue) printf("INVALID\n");
        else if(cardType=="INVALID_CARD") printf("INVALID_CARD");
        return 1;
    }
    // 카드 번호가 유효하고, 카드가 존재하면 카드 타입 보여주기.
    else{
        printf("%s\n", cardType);
    }

    return 0;
}



/**
// 자리수를 더하고 확인하는 부분
long temp = input;

int idx = 0;
long sum = 0;
while( temp > 0 ){
    long num = temp % 10;
    temp = temp / 10;
    
    if(idx%2 == 0){
        sum += num;
    }else{
        int added_num = num*2;
        if(added_num>=10){
            sum += added_num / 10;
        }
        sum += added_num % 10;
    }
    
    idx++;
}

bool istrue = false;
if(sum % 10 == 0) istrue = true;

int digits = idx;
printf("digits: %d \n", digits);
*/