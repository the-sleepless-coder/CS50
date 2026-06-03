#include <cs50.h>
#include <stdio.h>
#include <string.h>

int get_length(string s);

int main(void){
    string name = get_string("Name:");

    int result = strlen(name);

    printf("%d\n", result);

}

int get_length(string s){
    int n=0; 
    while(s[n] != '\0'){
        n++;
    }
    
    return n;
}