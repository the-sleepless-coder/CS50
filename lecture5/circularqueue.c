#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>

#define CAPACITY 5

typedef struct
{
    int items[CAPACITY];
    int front;
    int rear;
    int size;
}queue;

void init(queue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;

    return;
}

bool is_empty(queue *q)
{

    return q->size == 0;
}

bool is_full(queue *q)
{
    return q->size == CAPACITY;
}

void enqueue(queue *q, int val)
{
    if(is_full(q))
    {
        printf("Queue is full: %d\n", val);
        return; 
    }

    int rear = q->rear;
    q->items[rear] = val;

    // 모듈러 방식으로 순환하는 방식으로 rear인덱스를 관리해준다.
    // 이렇게 하면 dequeue로 인해 앞에 비어 있는 인덱스를 쓸 수 있게 된다. 
    q->rear = (q->rear+1) % CAPACITY;
    q->size ++;
}

int dequeue(queue *q)
{
    if(is_empty(q)){
        printf("Queue is empty!\n");
        return -1;
    }

    int value = q->items[q->front];

    // 모듈러 방식으로 front 인덱스 관리
    q->front = (q->front + 1) % CAPACITY;
    q->size --;

    return value;
}

void printqueue(queue *q)
{
    int front = q->front;
    
    for(int i=0; i<q->size; i++)
    {
        int idx = (i+front)% CAPACITY;
        printf("%d ", q->items[idx]);
    }

    printf("\n");
}


int main(void)
{
    queue q;
    init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    
    printqueue(&q);

    int n = get_int("Dequeue N times : ");
    for(int i=0; i<n; i++)
    {
        printf("dequeue: %d \n", dequeue(&q));
    }
    printqueue(&q);

    enqueue(&q, 60);
    enqueue(&q, 70);
    enqueue(&q, 80);
    enqueue(&q, 90);
    
    printqueue(&q);

    return 0;


}