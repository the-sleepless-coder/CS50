#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // open the file in write mode
    FILE *file = fopen("phonebook.csv", "a");
    if(file == NULL )
    {
        return 1;
    }
    
    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    // save in given format
    fprintf(file, "%s,%s\n", name, number);

    fclose(file);

}

