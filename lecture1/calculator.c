#include <cs50.h>
#include <stdio.h>

int sum(int x, int y);
int times(int x, int y);


int main(void){

    int x = get_int("x: ");
    int y = get_int("y: ");

    //printf("%i\n", sum(x, y));
    //printf("%i\n", times(x, y));

    // truncation happens when you divide an integer by an integer
    // floating point imprecision 
    printf("%.50f\n", (float) x / y );

}


int sum(int x, int y){

    return x+y;
}

int times(int x, int y){

    return x*y;
}

