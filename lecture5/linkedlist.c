#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int number;
    struct node *next;
}node;

void linked_list_lifo(node *list);

int main(void)
{
    // pointer for beginning of the list
    // don't allocate a garbage value, but save null in the list variable
    node *list = NULL;

    for(int i=0 ; i<3; i++)
    {
        node *n  = malloc(sizeof(node));
        if(n==NULL)
        {
            // TO DO: free any memory already malloced
            return 1;
        }

        
        n->number = get_int("Number: ");
        n->next = NULL;

        // 그러니까 입력 받은 현재 숫자를,
        // 이전 노드의 다음 노드로 이어 붙여준다.
        // if list is empty
        if(list == NULL)
        {
            // 첫 헤더를 list에 넣어준다.
            list = n;
        }
        // if list has numbers already
        else
        {
            for(node *ptr = list; ptr!=NULL; ptr = ptr->next)
            {
                // 첫 헤더를 따라서 노드의 끝에
                // 현재 입력한 노드를 삽입한다.
                // The end of list,
                // add the node that you've just created
                if(ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // Time passes
    // pointers are variables that save the address of another variable
    // 마지막 노드에 도달하면 그때 멈춘다.
    node *ptr = list;
    while( ptr != NULL ){
        printf("%d ", ptr->number);
        ptr = ptr->next;
    }
    
    printf("\n");


    // Time Passes
    // undo each pointer while following the node
    node *ptr = list;
    while(ptr!=NULL)
    {
        // because you're going to free the pointer,
        // save the pointer in the "next pointer" variable
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    return 0;
}

void linked_list_lifo(node *list)
{
    for(int i=0 ; i<3; i++)
    {
        node *n  = malloc(sizeof(node));
        if(n==NULL)
        {
            return ;
        }

        // Allocate number and next address as null
        // (*n).number => n->number
        // link the element that you typed in before,
        // as the next element of the current node
        // 그러니까 현재 노드에 이전에 입력한 노드를 다음 노드로 이어준다.
        n->number = get_int("Number: ");
        n->next = list;

        list = n;
    }

}