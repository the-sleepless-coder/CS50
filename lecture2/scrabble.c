#include <cs50.h>
#include <stdio.h>

void cal_score(string player1, string player2, int scores[]);

int main(void){
    // find the winner of the scrablle game

    int scores[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

    // player의 string값을 입력 받는다.
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // 각 플레이어 당 점수를 계산하고,
    // 결과를 출력한다.
    cal_score(player1, player2, scores);

}

void cal_score(string player1, string player2, int scores[])
{
    int idx1 = 0; 
    int sum1 = 0;
    // 영어 문자일 경우 lowercase로 바꿔서 계산하고, 
    // 문자가 아니라면 점수를 계산하지 않고 다음 인덱스로 넘어간다.
    while( player1[idx1] != '\0'){
        char c = player1[idx1];
        if(c >= 'A' && c <= 'Z'){
            c += 32;
            int scoreIdx = c-'a';
            sum1 += scores[scoreIdx];
            
        }else if(c>='a' && c<='z'){
            int scoreIdx = c-'a';
            sum1 += scores[scoreIdx];
        }
        
        idx1++;
    }

    int idx2=0;
    int sum2=0;
    while( player2[idx2] != '\0'){
        char c = player2[idx2];
        if(c >= 'A' && c <= 'Z'){
            c += 32;

            int scoreIdx = c-'a';
            sum2 += scores[scoreIdx];
        }else if(c>='a' && c<='z'){
            int scoreIdx = c-'a';
            sum2 += scores[scoreIdx];
        }
        
        idx2++;
    }

    if(sum1>sum2){
        printf("Player 1 Wins!\n");
    }else if(sum1<sum2){
        printf("Player 2 Wins!\n");
    }else{
        printf("Tie!\n");
    }
}