#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define N 26

// hashtable에서 bucket역할 = node
typedef struct node
{
    // bucket name , next node에 대한 포인터
    char name[100];
    struct node *next;

} node;

unsigned int hash(char *word);
void printtable(node *table[]);
void maketable(char *names[], int count, node *table[]);

int main(void)
{
    // node pointer를 저장하는 배열 table[26];
    node *table[N];
    
    for(int i=0; i<N; i++)
    {
        table[i] = NULL;
    }

    // char 포인터를 저장하는 배열
    char *names[] = {"Mario", "Luigi", "Yoshi", "Koopa Junior", "Luis", "Mario Junior"};

    // 배열 전체 크기 / 원소 하나 크기
    int count = sizeof(names) / sizeof(names[0]);

    // names 배열에 있는 이름을, hash table에 입력한다.
    maketable(names, count, table);

    // hash table에 있는 값을 알파벳 순서대로 출력한다.
    printtable(table);

}

void printtable(node *table[])
{
     for(int i=0; i<N; i++)
    {
        // 알파벳 별 이름 출력.
        if(table[i]!=NULL)
        {
            printf("* The name starts with %c \n", 'A'+i);
        
            node *ptr = table[i];
            
            // 각 bucket별 모든 이름 출력.
            int num = 1;
            while(ptr!=NULL)
            {
                if(num==1)
                {
                    printf("%dst name is %s |", num ,ptr->name);
                }else if(num==2)
                {
                    printf("%dnd name is %s |", num ,ptr->name);
                }else if(num==3)
                {
                    printf("%drd name is %s |", num ,ptr->name);
                }else
                {
                    printf("%dth name is %s |", num ,ptr->name);
                }
                ptr = ptr->next;
                num ++;
            }
            
            printf("\n");
        }



    }
}

void maketable(char *names[], int count, node *table[])
{
    for(int i=0; i<count; i++)
    {
        int idx = hash(names[i]);

        // 새로운 노드 할당.
        node *newnode = malloc(sizeof(node)); 
        if(newnode==NULL)
        {
            printf("Failed to allocate node\n");
            return ;
        }

        // 할당된 노드에 이름 입력
        // 기존 table에 있는 노드를 next node로 포인터를 이어주고,
        // table에 새로운 노드를 삽입.
        strcpy(newnode->name, names[i]);
        newnode -> next = table[idx];
        table[idx] = newnode;

    }

}

// hash function에 의해 bucket에 대한 인덱스를 형성한다.
unsigned int hash(char *word)
{
    return toupper(word[0])- 'A';
}
