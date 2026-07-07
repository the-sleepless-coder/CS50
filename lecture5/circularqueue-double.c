#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <stdlib.h>

#define CAPACITY 5

typedef struct
{
    int *items;
    int front;
    int rear;
    int size;
    int capacity;
}queue;

void init(queue *q)
{
    q->capacity = CAPACITY;
    q->items = malloc(sizeof(int)* q->capacity);

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
    return q->size == q->capacity;
}

void grow(queue *q)
{
    // 배열의 CAPACITY를 도달하게 되면, 
    // 기존에 할당된 배열의 크기를 2배로 늘리고 새로운 배열에 원소들을 할당해준다.
    int new_cap = q->capacity*2;
    
    int *new_array = malloc(sizeof(int) * new_cap);

    // 기존 원소를 새로운 함수에 0-idx 기준으로 재할당해준다.
    for(int i=0; i<q->size; i++)
    {
        int idx = (i + q->front) % q->capacity;
        new_array[i] = q->items[idx];
    }

    free(q->items);
    q->items = new_array;
    q->front = 0;
    q->rear = q->size;
    q->capacity = new_cap;
}

void enqueue(queue *q, int val)
{
    // array가 가득차면 2배의 크기를 할당해주고, 
    // enqueue를 진행한다.
    if(is_full(q))
    {
        printf("Reallocating array SIZE by *2: %d\n", q->size * 2);
        grow(q);
    }

    int rear = q->rear;
    q->items[rear] = val;

    // 모듈러 방식으로 순환하는 방식으로 rear인덱스를 관리해준다.
    // 이렇게 하면 dequeue로 인해 앞에 비어 있는 인덱스를 쓸 수 있게 된다. 
    q->rear = (q->rear+1) % q->capacity;
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
    q->front = (q->front + 1) % q->capacity;
    q->size --;

    return value;
}

void printqueue(queue *q)
{
    int front = q->front;
    
    for(int i=0; i<q->size; i++)
    {
        int idx = (i+front)% q->capacity;
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
    enqueue(&q, 100);
    enqueue(&q, 110);
    enqueue(&q, 120);
    enqueue(&q, 130);
    enqueue(&q, 140);

    printqueue(&q);

    return 0;


}