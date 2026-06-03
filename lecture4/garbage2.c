#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x;
    int *y;
    
    x = malloc(sizeof(int));

    *x = 42; 
    //*y = 13;

    // 같은 포인터 변수에 값을 넣어준다.
    y=x;

    *y = 13;

    // 같은 포인터에 두 값을 넣기 때문에, 
    // 두 값 모두 13이 될 것이다
    printf("x: %d", *x);
    printf("y: %d\n", *y);
    

}