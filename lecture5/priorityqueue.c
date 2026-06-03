#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

// 우선순위를 가지는 element를 만든다.
typedef struct {
    int value;
    int priority;
} Element;

// element의 집합을 배열로 관리하고, 
// size,capacity변수를 가진 pq를 만들어준다.
typedef struct
{
    Element *data;
    int size;
    int capacity;
}PriorityQueue;

void init(PriorityQueue *pq, int capacity)
{
    pq->data = malloc(capacity*sizeof(Element));
    pq->size = 0;
    pq->capacity = capacity;
}

void swap(Element *a, Element *b)
{
    Element temp = *a;
    *a = *b;
    *b = temp;
}

// value와 동일한 priority를 갖는다.
void push_max(PriorityQueue *pq, int value)
{   
    int priority = value;

    // 힙이 가득 차면, 
    // realloc을 써서 capacity를 2배 늘려준다.
    if(pq->size == pq->capacity)
    {
        pq->capacity *= 2;

        // 메모리 재할당 대상과 조정할 크기
        pq->data = realloc(
            pq->data,
            pq->capacity * sizeof(Element)
        );

        if(pq->data == NULL)
        {
            printf("Failed to reallocate memory when pushing\n");
            exit(1);
        }
        
    }

    // 배열에 해당 element를 
    int idx = pq->size;

    pq->data[idx].value = value;
    pq->data[idx].priority = priority;

    pq->size++;

    // heap의 최상단
    // 그러니까 배열로 표현된 트리의 가장 최상단 idx = 0에 도달하 때까지, 
    // 순서를 정렬해준다.
    while(idx>0)
    {
        int parentidx = (idx-1)/2;

        // maxheap기준(priority가 높인 기준)
        if(pq->data[parentidx].priority >= pq->data[idx].priority)
        {
            break;
        }
        // 삽입한 curr 노드의 priority가 더 높을 경우, 
        // parent와 바꿔준다.
        swap(&pq ->data[parentidx], &pq->data[idx]);

        // swap을 진행한 후 , 
        // 현재 위치를 parent위치로 갱신하고 다시 parent와 비교.
        idx = parentidx;
    }

}

// 가장 작은 값을 우선순위가 높은 순으로 넣는다.
void push_min(PriorityQueue *pq, int value)
{
    int priority = value;

    // 크기가 capacity에 도달하면, capacity를 늘려준다.
    if(pq->size==pq->capacity)
    {
        pq->capacity *= 2;

        pq->data = realloc(
            pq->data,
            pq->capacity*sizeof(Element)
        );

        if(pq->data==NULL)
        {
            printf("Failed to reallocate memory when pushing");
            exit(1);
        }
    }

    // 현재 값을 배열에 추가한다.
    int idx = pq->size;
    pq->data[idx].value = value;
    pq->data[idx].priority = priority;

    pq->size++;

    // 가장 우선순위가 작은 값이 root가 될때까지, 
    // parent으로 올려준다. 
    while(idx>0)
    {
        int parentidx = (idx-1)/2;

        if( pq->data[parentidx].priority > pq->data[idx].priority)
        {
            swap(&pq->data[parentidx], &pq->data[idx]);
        }
        else break;

        // 부모 단계에서 동일한 작업을 반복해준다.
        idx = parentidx;
    }


}


// 우선순위를 스스로 정할 수 있다.
void push_cust(PriorityQueue *pq, int value, int priority)
{
    // 힙이 가득 차면, 
    // realloc을 써서 capacity를 2배 늘려준다.
    if(pq->size == pq->capacity)
    {
        pq->capacity *= 2;

        // 메모리 재할당 대상과 조정할 크기
        pq->data = realloc(
            pq->data,
            pq->capacity * sizeof(Element)
        );

        if(pq->data == NULL)
        {
            printf("Failed to reallocate data\n");
            exit(1);
        }
        
    }

    // 배열에 해당 element를 
    int idx = pq->size;

    pq->data[idx].value = value;
    pq->data[idx].priority = priority;

    pq->size++;

    // heap의 최상단
    // 그러니까 배열로 표현된 트리의 가장 최상단 idx = 0에 도달하 때까지, 
    // 순서를 정렬해준다.
    while(idx>0)
    {
        int parentidx = (idx-1)/2;

        // maxheap기준(priority가 높인 기준)
        if(pq->data[parentidx].priority >= pq->data[idx].priority)
        {
            break;
        }
        // 삽입한 curr 노드의 priority가 더 높을 경우, 
        // parent와 바꿔준다.
        swap(&pq ->data[parentidx], &pq->data[idx]);

        // swap을 진행한 후 , 
        // 현재 위치를 parent위치로 갱신하고 다시 parent와 비교.
        idx = parentidx;
    }


}

int max_index (PriorityQueue *pq, int idx1, int idx2)
{
    if(pq->data[idx1].priority > pq->data[idx2].priority)
    {
        return idx1;
    }

    return idx2;
}

int min_index(PriorityQueue *pq, int idx1, int idx2)
{
    if(pq->data[idx1].priority < pq->data[idx2].priority)
    {
        return idx1;
    }

    return idx2;
}

Element pop_max(PriorityQueue *pq)
{   
    if(pq->size==0)
    {
        printf("PriorityQueue is empty\n");
        
        exit(1);
    }

    Element result = pq -> data[0];

    // 가장 끝 원소를 가져와서 재정렬을 함으로써, 
    // 완전 이진 트리의 형태를 유지한다.
    // 그러니까 중간에 있는 노드를 가져오면 완전 이진 트리 형태가 깨지기 때문에, 
    // 가장 마지막 원소를 가져와서 전체 힙을 재정렬하는 것이다.
    pq->data[0] = pq->data[pq->size-1];

    pq->size--;

    int idx = 0;

    int size = pq->size;
    while(1)
    {
        int left = idx*2+1;
        int right = idx*2+2;

        int largest = idx;

        // 자식 노드 중에서 가장 우선순위가 높은 값을 찾는다.
        if(left < size)
        {
            largest = max_index(pq, largest, left);
        }

        if( right < size)
        {
            largest = max_index(pq, largest, right);
        }

        // 현재 노드가 가장 크다면 정렬할 필요가 없기 때문에, 
        // while문을 break를 한다.
        if(largest == idx)
        {
            break;
        }

        // 부모 노드와 자식 노드 중에서 가장 큰 것을 바꾼다.
        swap(&pq->data[idx], &pq->data[largest]);
        
        // 자식 노드로 한칸 내려가서 재정렬하는 과정을 반복한다.
        idx = largest;

    }

    return result;
}

Element pop_min(PriorityQueue *pq)
{   
    if(pq->size==0)
    {
        printf("PriorityQueue is empty\n");
        
        exit(1);
    }

    Element result = pq -> data[0];

    // 가장 끝 원소를 가져와서 재정렬을 함으로써, 
    // 완전 이진 트리의 형태를 유지한다.
    // 그러니까 중간에 있는 노드를 가져오면 완전 이진 트리 형태가 깨지기 때문에, 
    // 가장 마지막 원소를 가져와서 전체 힙을 재정렬하는 것이다.
    pq->data[0] = pq->data[pq->size-1];

    pq->size--;

    int idx = 0;

    int size = pq->size;
    while(1)
    {
        int left = idx*2+1;
        int right = idx*2+2;

        int largest = idx;

        // 자식 노드 중에서 가장 우선순위가 높은 값을 찾는다.
        if(left < size)
        {
            largest = min_index(pq, largest, left);
        }

        if( right < size)
        {
            largest = min_index(pq, largest, right);
        }

        // 현재 노드가 가장 크다면 정렬할 필요가 없기 때문에, 
        // while문을 break를 한다.
        if(largest == idx)
        {
            break;
        }

        // 부모 노드와 자식 노드 중에서 가장 큰 것을 바꾼다.
        swap(&pq->data[idx], &pq->data[largest]);
        
        // 자식 노드로 한칸 내려가서 재정렬하는 과정을 반복한다.
        idx = largest;

    }

    return result;
}

void free_queue(PriorityQueue *pq)
{
    free(pq->data);
}

// 사용자가 정하는 priority에 따라서, 
// 우선순위에 따라 queue에 있는 것을 추출한다는 의미에서 priorityqueue이다.

// max heap : 가장 큰 값을 root에 위치시킨다. (부모 >= 자식)
// min heap : 가장 작은 값을 root에 위치시킨다. ( 부모 >= 자식)

// 부모 자식 관계를 배열에 저장한다.
// 그리고 위에서부타 아래로 왼쪽에서 오른쪽으로 차례대로 배열에 저장한다.
// Heap: 특정 정렬 조건을 가진 완전 이진 트리(Balanced Tree)

// priority queue(ADT)를 배열로 구현하면 
// 삽입 삭제 O(1)/ O(N) or vice versa

// 하지만 힙으로 구현하게 되면 전체 트리의 높이가 log(n)이기 때문에
// 삽입 삭제가 O(logN)이 될 수 있음

//   10 [0]
// 20[1]  30[2]
//40[3]    50[4]

/** 
        50
      /    \
30[parent]  40
   /
  60[idx]

        50[parent]
      /    \
    60[idx] 40
   /
  30
*/


int main(void)
{
    // pq 를 초기화한다.
    PriorityQueue pq;

    int num = get_int("Number of elements: ");
    init(&pq, num);

    // min maxheap을 정한다.
    char *c = get_string("Type in min/max heap pref: ");

    if(strcmp(c, "max")==0 || strcmp(c, "MAX")==0)
    {
        // pq에 주어진 개수의 값을 추가한다.
        for(int i=0; i<num ; i++)
        {
            int temp = get_int("Insert: ");
                 
            push_max(&pq, temp);
        }


        // pop할 횟수를 입력한다.
        int popsize = get_int("Number of pops: ");
        for(int i=0; i<popsize; i++)
        {
            Element popped = pop_max(&pq);
            
            printf("popped : %d\n", popped.value);
            
        }
    }
    else if(strcmp(c,"min")==0 || strcmp(c,"MIN")==0)
    {
        // pq에 주어진 개수의 값을 추가한다.
        for(int i=0; i<num ; i++)
        {
            int temp = get_int("Insert: ");
            
            //push_max(&pq, temp);        
            push_min(&pq, temp);
        }


        // pop할 횟수를 입력한다.
        int popsize = get_int("Number of pops: ");
        for(int i=0; i<popsize; i++)
        {
            Element popped = pop_min(&pq);
            
            printf("popped : %d\n", popped.value);
            
        }

    }

    free_queue(&pq);

    return 0;

}
