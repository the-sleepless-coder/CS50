#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){

    long num = get_long("Type in card num: ");

    double base = 10.0;
    int digits = (num==0) ? 1 :(int) (log10(num)) + 1;
    printf("digits: %d \n", digits);

    int sum = 0;
    for(int idx = 0; idx < digits; idx++){
        // 홀수번째 자리일 경우에는 그대로 더한다.
        double idxdo = (double) idx;
        if(idx % 2==0){
            sum += (long)(num/ pow(base, idx)) % 10;
            
        }
        // 짝수번째 자리일 경우에는 *2를 하고 각 자리의 합을 더한다.
        else{
            int doubled_num = (long)(num / pow(base, idx)) %10 * 2;
            
            int num_added = 0;
            if(doubled_num >= 10){
                num_added += doubled_num / 10;
                num_added += doubled_num % 10;
            }else{
                num_added += doubled_num % 10;
            }

            sum += num_added;
        }
        
    }
    
    int startingnum = -1;
    startingnum = (int) ( num / pow(base, digits - 2) );
    
    printf("SUM: %d\n", sum);
    printf("startingnum: %d\n", startingnum);

    // amex = 15, master = 16, visa = 13, 16
    string cardType = "";
    if((startingnum == 34 || startingnum==37) && digits == 15) cardType = "AMEX";
    else if(startingnum >=51 && startingnum<=55 && digits == 16)cardType="MASTERCARD";
    else if(startingnum>=40 && startingnum<=49 && (digits == 13||digits ==16))  cardType="VISA";
    
    if(cardType=="") cardType="INVALID_CARD";


    bool istrue = false;
    if(sum % 10 == 0) istrue = true;
    
    // 카드 번호가 잘못됐거나, 카드 자체가 존재하지 않는다면 INVALID_CARD
    if( !istrue || cardType=="INVALID_CARD" ) {
        if(!istrue) printf("INVALID\n");
        else if(cardType=="INVALID_CARD") printf("INVALID_CARD");
        return 1;
    }
    // 카드 번호가 유효하고, 카드가 존재하면 카드 타입 보여주기.
    else{
        printf("%s\n", cardType);
    }

    // multiply 2 to every other digit from second to last digit by 2 and add the product of the doubled number
    // add the sum of the digits that weren't multiplied by 2 to the sum of digits
    // if the last digit is 0 it's legit


}