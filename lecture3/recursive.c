#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void){

    int height = get_int("Height: ");
    draw(height);
}

// use a recursive function to draw mario bricks
void draw(int n){
    if(n<=0) return;
    
    draw(n-1);
    // get to the deepest depth,
    // and start printing the bricks

    // See which depth the recursion ends up through the base case, 
    // and check where the recursive case repeats itself
    // the next is bound to work
    for(int i=0; i<n; i++){
        printf("#");
    }
    printf("\n");

}