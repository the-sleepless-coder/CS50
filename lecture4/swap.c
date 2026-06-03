#include <cs50.h>
#include <stdio.h>

void swap_ref(int *a, int *b);
void swap(int a, int b);

int main(void){
    int x = 1;
    int y = 2;

    // you need to pass on the address so that you can actually change the value in the given address
    printf("x is %i, y is %i\n", x, y);
    swap_ref(&x, &y);
    printf("x is %i, y is %i\n", x, y);
    
}


void swap_ref(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// pass by value
void swap(int a, int b)
{
    // tmp에 a를 담아두고, 
    // b에 tmp를 넣어둔다.
    int tmp = a;
    a = b;
    b=tmp;

}