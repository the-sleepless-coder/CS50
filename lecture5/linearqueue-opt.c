#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>

#define CAPACITY 5

// linear queue
// size변수를 따로 추가해준다.
// 그렇지 않으면, front rear인덱스에 따라서 배열의 시작과 끝은 측정할 수 있지만, 
// 배열의 크기를 관리하는 변수 size를 이용해 크기를 알 수 있기 때문이다.
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
}

bool is_empty(queue *q)
{
    return q->size == 0;
}

bool is_full(queue *q)
{
    return q->size == CAPACITY;
}

void enqueue(queue *q, int value)
{
    if(is_full(q))
    {
        printf("Queue is full \n ");
        return;
    }

    // 가장 마지막에 값을 추가한다.
    q->items[q->rear] = value;

    // 인덱스와 크기를 늘려준다.
    q->rear++;
    q->size++;
}

// 가장 앞에 있는 항목을 꺼내고,
// 주어진 배열에서 앞으로 배열의 원소를 하나씩 당긴다.
// dequeue할 시 O(N)
int dequeue(queue *q)
{
    if(is_empty(q))
    {
        printf("Queue is empty \n");
        return -1;
    }

    // front에서 출력하면 메모리 관리가 안되기 때문에, 
    // 뒤에 있는 항목을 앞으로 한칸씩 당겨준다.
    int value = q->items[0];

    for(int i=0; i<q->size-1; i++)
    {
        q->items[i] = q->items[i+1];
    }

    q->rear --;
    q->size --;

    return value;
}

// queue내 항목을 출력한다.
// queue 범위 내 값만 출력한다.
void printqueue(queue *q)
{
    if(is_empty(q))
    {
        printf("Queue is empty\n");
        return ;
    }

    int size = q->size;
    for(int i=0; i<size; i++)
    {
        printf("%d ", q->items[i]);
    }

    printf("\n");
}

int main(void)
{
    // queue 초기화
    queue q;
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

    enqueue(&q, 60);
    printqueue(&q);

    return 0;
}

