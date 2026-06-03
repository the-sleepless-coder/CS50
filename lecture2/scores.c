#include <stdio.h>
#include <cs50.h>

// Prototype
float cal_average(int scores[], int size);

int main(void){
    int num = get_int("Size of Arr: ");

    int scores[num]; 
    for(int n=0; n<num; n++){
        scores[n] = get_int("Type in num %d: ", n+1);
    }
    
    // (int + int)/ int -> truncates the result
    // to make it into a float 
    // it needs to be in a given value format int / float
    printf("Average: %f \n", cal_average(scores, num));


}

float cal_average(int scores[], int size){
    int tot = 0;
    // 이렇게 하면 포인터 변수를 쓰기 때문에, 
    // size 자체를 넘기는 것이 맞다.
    // int size = sizeof(scores) / scores(scores[0]);
    for(int i=0; i<size; i++){
        tot += scores[i]; 
    }

    return tot/ (float) size;

}