#include <cs50.h>
#include <stdio.h>

int calChange(int num, int changeArr[]);

int main(void){
    
    int num = get_int("Change Owed: ");
    int changeArr[] = {25, 10, 5, 1};

    int result = calChange(num, changeArr);

    printf("total coins: %d ",result);

}

int calChange(int num, int changeArr[]){
    int idx = 0;
    int totCoins = 0;

    // printf("num: %d ", num);
    while(num != 0){
        int changeToken = changeArr[idx++];
        int tokens = num / changeToken; 
        
        num = num - changeToken * tokens; 
        
        totCoins += tokens;
        printf("%d coin : %d\n", changeToken, tokens);
    }

    return totCoins;

}