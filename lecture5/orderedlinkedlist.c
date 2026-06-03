#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;

    for(int i=0; i<3; i++)
    {
        node *n = malloc(sizeof(node));
        
        // if list is empty
        if(n==NULL)
        {
            return 1;
        }

        n->number = get_int("Number: ");
        n->next = NULL;

        // 첫 노드.
        if(list == NULL)
        {
            list=n;
        }
        // 숫자가 가장 작은 경우.(prepend)
        // list를 다음 노드로 배치하고, 
        // 시작을 n으로 잡는다.
        else if( n-> number < list ->number)
        {
            n->next = list;
            list = n;
        }
        else
        {
           for(node *ptr = list; ptr!=NULL; ptr = ptr ->next)
           {
            // 끝 노드에 들어갈 경우
            if(ptr->next == NULL)
            {
                ptr->next = n;
                break;
            }
            
            // 노드 중간에 값이 들어간 경우.
            if(n->number < ptr ->next -> number)
            {
                n->next = ptr->next;
                ptr->next = n;
                break;
            }
           } 
        }


    }

}