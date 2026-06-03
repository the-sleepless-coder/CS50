#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*int list[3];

    list[0]=1;
    list[1]=2;
    list[2]=3;

    for(int i=0; i<3; i++){
        printf("%i\n", list[i]);
    }
    */

    // allocating chunk of contiguous memory
    int *list = malloc(3*sizeof(int));
    if (list == NULL){
        return 1;
    }

    list[0]=1;
    list[1]=2;
    list[2]=3;

    // Time passes
    // reallocate a array that's a little bigger

    // leave data in their current locations,
    // and add contiguous additional memory next to it.

    // but you need to give the address of the chunk of memory that's to be reallocated.
    int *tmp = relloc(list, 4*sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    // copy the values to tmp
    /*for(int i=0; i<3; i++)
    {
        tmp[i] = list[i];
    }
    tmp[3]=4;
    */
   
    free(list);

    // rename tmp as list
    list = tmp; 

    for(int i=0; i<4; i++)
    {
        printf("%i \n", list[i]);
    }

    return 0;
}