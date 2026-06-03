// Header files - access to the library to use standard functions
#include <stdio.h>
#include <cs50.h>

// Escape words helps to print certain text inambiguously
int main(void)
{
    string answer = get_string("What's your name? ");

    printf("hello, %s\n", answer );

    // printf("hello, \"world\"\n");
}
