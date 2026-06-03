#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    string name;
    string number;
}people;

int main(void){
    string names[] = {"David", "John", "Yulia"};
    string numbers[] = {"+010-1234", "010-2750", "+010-1000"};

    string name = get_string("Name: ");
    for(int i=0; i<3; i++){
        if(strcmp(names[i], name) == 0){
            printf("Found %s \n", numbers[i]);
            return 1;
        
        }
    }

    printf("Not found\n");
    return 0;

}