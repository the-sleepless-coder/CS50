#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUCKET_COUNT 4
#define LOAD_VALUE 2

// 버킷을 연결리스트 형식으로 충돌 관리.
typedef struct node
{
    char name[100];
    struct node *next;
}node;

// 해시 테이블을 구조체로 관리.
// 값에 의한 호출이 아니라 참조에 의한 호출을 해야, 
// 값을 변경할 수 있기 때문에 bucket 포인터 변수를 들고 있는 bucket 포인터의 포인터를 hashtable을 구성할 때 만들어준다.
typedef struct
{
    node **buckets;
    int bucket_count;
    int size;
}hashtable;

// 전체 문자열 기반 해시값 형성
unsigned long hash(char* word, int bucket_count)
{
    unsigned long h = 5381;

    for(int i=0; word[i]!='\0';i++)
    {
        h = (h<<5) + h + tolower(word[i]);
    }

    return h % bucket_count;
}

hashtable* create_table(int bucket_count)
{
    hashtable *ht = malloc(sizeof(hashtable));
    ht->buckets = malloc(sizeof(node *)* bucket_count);

    for(int i=0; i<bucket_count; i++) ht->buckets[i] = NULL;

    ht->bucket_count = bucket_count;
    ht->size = 0;

    return ht;
}

// 리사이징 없는 bucket에 순수 삽입
void insert_node(hashtable* ht, char *name)
{
    unsigned long idx = hash(name, ht->bucket_count);
    node *newnode = malloc(sizeof(node));

    strcpy(newnode->name, name);

    newnode->next = ht->buckets[idx];
    ht->buckets[idx] = newnode;
    ht->size++;
}


// bucket 크기 2배로 리사이징 후 삽입
void resize(hashtable* ht)
{
    int old_count = ht->bucket_count;
    node **old_buckets = ht->buckets;
    
    // bucket *=2의 새로운 크기를 가진 hash table을 구성해준다.
    int new_count = old_count*2;
    ht-> buckets = malloc(sizeof(node*) * new_count);
    for(int i=0; i<new_count; i++) ht->buckets[i] = NULL;
    ht->bucket_count = new_count;
    ht->size = 0;
    
    for(int i=0; i<old_count; i++)
    {
        // 새로운 버킷 수에 맞춰서 노드를 새롭게 삽입해준다.
        node *ptr = old_buckets[i];
        while(ptr!=NULL)
        {
            insert_node(ht, ptr->name);
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    free(old_buckets);

    printf("Resized bucket count: %d\n", ht->bucket_count);
}

// 외부에서 호출하는 함수
// LOAD_FACTOR에 따라 현재 HASHTABLE에 값을 넣어주거나, 
// BUCKET 사이즈를 2배 늘린 HASHTABLE에 값을 넣어준다.
void put(hashtable *ht, char* name)
{
    if((ht->size + 1) > LOAD_VALUE * ht->bucket_count)
    {
        resize(ht);
    }
    insert_node(ht, name);
}

void print_table(hashtable* ht)
{
    for(int i=0; i<ht->bucket_count; i++)
    {
        // 각 버킷에 대해서 값이 존재하면, 
        // 연결 리스트로 이어진 값이 다 출력될 때까지 모든 bucket내 값을 출력해준다.
        if(ht->buckets[i]!=NULL)
        {
            printf("[Bucket %d]\n", i);

            node *ptr = ht->buckets[i];
            int num = 1;
            while(ptr!=NULL)
            {
                printf("%d: %s | ", num, ptr->name);
                node* next = ptr -> next;
                ptr = next;
                num++;
            }

            printf("\n");
        }
    }

}

void free_table(hashtable *ht)
{
    for (int i = 0; i < ht->bucket_count; i++)
    {
        node *ptr = ht->buckets[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    free(ht->buckets);
    free(ht);
}

int main(void)
{
    hashtable *ht = create_table(BUCKET_COUNT);

    char *names[] = {"Mario", "Luigi", "Yoshi", "Koopa Junior", "Luis", "Mario Junior","Old Loopa", "Mario Junior", "Princess Peach", "Toad", "Bowser", "Wario", "Waluigi", "Bowser Junior","Boo","Rosalina","Donkey Kong", "Diddy Kong"};
    int count = sizeof(names) / sizeof(names[0]);

    for (int i = 0; i < count; i++)
        put(ht, names[i]);

    printf("Final bucket count: %d, size: %d\n\n", ht->bucket_count, ht->size);
    print_table(ht);

    free_table(ht);

}