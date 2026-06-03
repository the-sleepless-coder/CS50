#include <cs50.h>
#include <stdio.h>


int main(int argc, string argv[])
{
    // string name = get_string("What's your name");
    
    if(argc >= 2){
        //printing all the name in the arguments
        for(int i = 1 ; i < argc; i++){
            printf("hello %s\n", argv[i]);
        }
        
    }else{
        printf("hello, world\n");
    }
    
}