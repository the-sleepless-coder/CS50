#include <stdio.h>

int main(void)
{
    int n;
    // reads data and hand over the address of the variable so that it can save it in the given address
    // 4 bytes of memory for the data
    printf("n: ");
    scanf("%i", &n);

    // print the data
    printf("n: %i\n", n);

    // s is already an address
    // s doesn't know when the memory is going to end
    // only 8bytes for the pointer is allocated, but the actual memory for the data that is to be saved in the heap is not allocated specifically which may cause problems in the memory  
    //malloc(), s[] 형태로 따로 할당된 메모리를 주지 않기 때문에 문제가 될 수 있음.
    char *s;
    // char s[4];
    // char *s = malloc(4);

    printf("s: ");
    scanf("%s",s);

    printf("%s: ");
}