#include <cs50.h>
#include <stdio.h>

void meow(int num);
int get_positive_int(void);

int main(void)
{   
    // Abstracting the code down to functions
    int times = get_positive_int();
    meow(times);

    /**
    // checking the boolean everytime it goes through the while loop
    int n=0; 
    while(n < 3){
        printf("woof\n");
        n++;
    }
    */
    
    /*1.correctness - the code needs to work
      2.design - structuring the code 
      3.style - enhancing the aesthetic perspective of the code.
    */

}

int get_positive_int(void){
    // Declare a variable before initializing it.
    // 변수 선언을 먼저 하고 초기화를 해준다.
    int n;
    // Rather than using the while statement, use a do statement
    // 먼저 변수를 선언하고 초기화를 함으로써, 
    // while문 실행 전에 변수를 초기화를 하고 실행될 수 있도록 한다.
    do{
        n = get_int("Type in num: ");
    }
    while( n < 1);


    /**
    while(n<1){
        n=get_int("Type in num: ");
    }
    */

    return n;
}

// Use a function to implement the function
// local variables are only defined within the function
void meow(int num)
{
    for(int i = 0; i < num; i++){
        printf("meow \n");    
    }
}
