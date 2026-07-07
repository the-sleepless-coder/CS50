#include <stdio.h>
#include <stdlib.h>

#define BLOCKLEN 64
#define CENTER   ((BLOCKLEN - 1) / 2)

typedef struct block {
    struct block *left;
    int data[BLOCKLEN];
    struct block *right;
} block;

typedef struct {
    block *leftblock;
    block *rightblock;
    int leftindex;   // leftblock 안에서 첫 원소 위치
    int rightindex;  // rightblock 안에서 마지막 원소 위치
    long size;
} deque;

static block *newblock(void)
{
    block *b = malloc(sizeof(block));
    b->left = NULL;
    b->right = NULL;
    return b;
}

void init(deque *d)
{
    block *b = newblock();
    d->leftblock = b;
    d->rightblock = b;
    d->leftindex = CENTER + 1;   // 빈 상태: leftindex == rightindex + 1
    d->rightindex = CENTER;
    d->size = 0;
}

void push_right(deque *d, int val)
{
    if (d->rightindex == BLOCKLEN - 1) {
        block *b = newblock();
        b->left = d->rightblock;
        d->rightblock->right = b;
        d->rightblock = b;
        d->rightindex = -1;
    }
    d->rightindex++;
    d->rightblock->data[d->rightindex] = val;
    d->size++;
}

void push_left(deque *d, int val)
{
    if (d->leftindex == 0) {
        block *b = newblock();
        b->right = d->leftblock;
        d->leftblock->left = b;
        d->leftblock = b;
        d->leftindex = BLOCKLEN;
    }
    d->leftindex--;
    d->leftblock->data[d->leftindex] = val;
    d->size++;
}

int pop_right(deque *d)
{
    int val = d->rightblock->data[d->rightindex];
    d->rightindex--;
    d->size--;

    if (d->rightindex == -1) {
        block *prev = d->rightblock->left;
        if (prev == NULL) {
            d->rightindex = CENTER;
            d->leftindex = CENTER + 1;
        } else {
            free(d->rightblock);
            prev->right = NULL;
            d->rightblock = prev;
            d->rightindex = BLOCKLEN - 1;
        }
    }
    return val;
}

int pop_left(deque *d)
{
    int val = d->leftblock->data[d->leftindex];
    d->leftindex++;
    d->size--;

    if (d->leftindex == BLOCKLEN) {
        block *next = d->leftblock->right;
        if (next == NULL) {
            d->rightindex = CENTER;
            d->leftindex = CENTER + 1;
        } else {
            free(d->leftblock);
            next->left = NULL;
            d->leftblock = next;
            d->leftindex = 0;
        }
    }
    return val;
}

void printdeque(deque *d)
{
    block *b = d->leftblock;
    int idx = d->leftindex;

    for (long i = 0; i < d->size; i++) {
        printf("%d ", b->data[idx]);
        idx++;
        if (idx == BLOCKLEN) {   // 블록 경계 넘으면 다음 블록으로
            b = b->right;
            idx = 0;
        }
    }
    printf("\n");
}

void freedeque(deque *d)
{
    block *b = d->leftblock;
    while (b != NULL) {
        block *next = b->right;
        free(b);
        b = next;
    }
}

int main(void)
{
    deque d;
    init(&d);

    // 오른쪽으로 70개 push → 블록 경계(64) 넘김
    for (int i = 0; i < 70; i++)
        push_right(&d, i);

    // 왼쪽으로도 push
    push_left(&d, -1);
    push_left(&d, -2);
    push_left(&d, -3);

    printf("size = %ld\n", d.size);
    printdeque(&d);

    printf("pop_left 3: ");
    for (int i = 0; i < 3; i++)
        printf("%d ", pop_left(&d));
    printf("\n");

    printf("pop_right 3: ");
    for (int i = 0; i < 3; i++)
        printf("%d ", pop_right(&d));
    printf("\n");

    printf("size = %ld\n", d.size);
    printdeque(&d);

    freedeque(&d);
    return 0;
}