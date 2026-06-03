#include <cs50.h>
#include <stdio.h>

int main(void){
    // linear search 
    int numbers[7] = {10, 20, 50, 100, 1, 500, 5};

    int n = get_int("Number: ");

    //bool istrue =false;
    for(int i=0; i<7; i++){
        if(numbers[i] == n){
            printf("Found : %d\n", numbers[i]);
            //istrue = true;
            return 0;
        }

        //printf("%d ", numbers[i]);
    }
    
    //if(!istrue) printf("Not found: %d\n", n);
    printf("Not found: %d\n", n);
    return 1;
    
}
