#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[]){

    // returning an exit status to show how the state of the program

    if(argc<=1){
        printf("Missing command-line argument\n");
        return 1;
    }else{
        for(int i=1; i < argc; i++){
            printf("hello there, %s \n", argv[i]);
        }
    }


}