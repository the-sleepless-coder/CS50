#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cs50.h>

// 노드 값과 다음 노드의 포인터를 저장한다.
typedef struct node
{
    int value;
    struct node *next;
}node;

// node간 관계를 queue라는 자료구조로 구현.
// front, rear가 인덱스가 아닌, 노드로 표현해서 큐를 관리.
typedef struct
{
    node *front;
    node *rear;
    int size;
}Queue;

void init(Queue *q)
{
    q->front= NULL;
    q->rear = NULL;
    q->size = 0;
}

bool is_empty(Queue *q)
{
    return q->size == 0; 
}

void enqueue(Queue *q, int value)
{
    // newnode에 값을 할당해준다.
    node *newnode = malloc(sizeof(node));
    if(newnode==NULL)
    {
        printf("failed to allocate memory\n");
        return;
    }

    newnode -> value = value;
    newnode -> next = NULL;

    // queue의 가장 마지막에 새로운 node를 더해준다.
    // 매번 순회하면 연결리스트로 만드는 의미가 없다.
    // rear변수로 가장 마지막 주소에 연결해서 노드를 삽입하면 된다.
    node *ptr = q->front;
    // 큐가 비어 있다면, 
    // front에 ptr를 넣어준다.
    if(ptr == NULL)
    {
        q->front = newnode;    
        q->rear = newnode;
        /**
        ptr = newnode;
        q->front = ptr;
        */
    }
    // 큐가 비어 있지 않다면 가장 마지막에 넣어준다.
    else{
        q->rear->next = newnode;
        q->rear = newnode;
        /** 
        while(ptr != NULL)
        {
            // 큐의 마지막에 처음으로 도달했을 때,
            // newnode를 삽입해준다.
            if(ptr->next==NULL)
            {
                ptr -> next = newnode;
                break;
            }
            ptr = ptr->next;
        }*/
    
    }
    
    // 크기를 늘려준다.
    q->size++;

}

// 연결 리스트에서 가장 앞의 front위치를 옮겨주면서, 
// Queue를 관리해준다.
int dequeue(Queue *q)
{
    if(is_empty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }

    node *ptr = q->front;

    int value = ptr -> value;

    // 가장 앞의 노드를 다음 노드로 옮긴다.
    q->front = q->front ->next;
    if(q->front == NULL)
    {
        q->rear = NULL;
    }

    free(ptr);

    q -> size--;

    return value;
}


void printqueue(Queue *q)
{
    if(is_empty(q))
    {
        printf("Queue is empty\n");
        return;
    }    

    printf("Queue: ");

    // 연결리스트의 가장 마지막 까지 큐를 출력한다.
    node *ptr = q->front;
    while(ptr != NULL)
    {
        printf("%d ", ptr->value);
        ptr = ptr -> next;
    }

    printf("\n");
}   


int main(void)
{
    Queue q;
    init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    printqueue(&q);
    
    enqueue(&q, 50);
    enqueue(&q, 60);

    printqueue(&q);

    
    int n = get_int("Dequeue N times : ");
    for(int i=0; i<n; i++)
    {
        printf("dequeue: %d \n", dequeue(&q));
    }
    printqueue(&q);

    enqueue(&q, 70);
    printqueue(&q);

    return 0;

}
