#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define N 26

// 각 단어의 알파벳을, children배열에 넣는다.
// 각 계층별로 children배열의 주소값을 따라가고, 
// 단어의 끝에 도달하면 isend = true를 반환한다.
// root- a p p l - e
//             \ - i - c - a - t - i - o - n

// 트라이는 탐색 시간은 O(N)이지만, 
// 대신 각 알파벳 별로 children배열만큼 메모리 공간을 소모한다.
typedef struct node
{
    struct node *children[26]; // 알파벳을 나타내는 노드 배열, 원소는 26개 [26개 원소를 가진 노드 포인터 배열]
    bool isend;      // 단어의 끝을 나타냄. 
    //char * number; // 번호를 저장하기 위함. 
} node;

node *create_node(void){
    node *newnode = malloc(sizeof(node));

    if(newnode == NULL)
    {
        printf("Failed to allocate node");
        exit(1);
    }

    // 변수 초기화
    for(int i=0; i<N; i++)
    {
        newnode->children[i] = NULL;
    }

    newnode->isend = false;

    return newnode;
}

// 주어진 단어를 트라이 자료구조에 넣는다.
bool insert(node *root, char *word)
{
    node *ptr = root;

    // 단어의 끝에 도달할 때까지, 
    // 한 알파벳 씩 트라이 구조에 넣어준다.
    for(int i=0; word[i]!='\0'; i++)
    {
        char c = tolower(word[i]);

        if(c < 'a' || c > 'z')
        {
            return false;
        }

        int cidx = c-'a';

        // 트라이 구조 내 child배열에 이미 존재하는 인덱스라면,
        // 해당 인덱스를 활용한다.
        if(ptr->children[cidx]==NULL)
        {
            ptr->children[cidx] = create_node();
        }

        // 자식 노드로 옮겨 가서, 
        // 단어의 다음 알파벳에 대한 주소에서 동일한 작업을 반복한다.
        ptr=ptr->children[cidx];
    }

    // 단어 끝에 도달하면 isend = true를 저장하고, 
    // true를 반환한다. 
    ptr ->isend = true;
    
    return true;
}

// 트라이 구조 내 삽입한 단어가 있는지를 확인해본다.
bool search(node* root, char *word)
{
    node *ptr = root;

    for(int i=0; word[i]!='\0'; i++)
    {
        char c = tolower(word[i]);

        // 알파벳 검사.
        if(c<'a' || c > 'z')
        {
            return false;
        }

        int cidx = c-'a';

        // 단어 주소에 값이 없다면, 
        // false 반환.
        if(ptr->children[cidx] == NULL)
        {
            return false;
        }

        // 단어의 다음 알파벳에 대한 확인도 진행.
        ptr = ptr->children[cidx];

    }

    // ex. application을 넣고 app을 찾는다면, 
    // 단어의 끝에 도달해야만 true를 반환해야 한다. 
    // 그렇지 않으면 트라이에 들어 있지 않는 app도 true를 반환한다.

    // 반드시 단어의 끝에 도달하면, 
    // true를 반환한다.
    return ptr->isend;
}

// 할당된 메모리를 해제한다.
void free_trie(node *root)
{
    if(root==NULL)
    {
        return;
    }

    // 할당된 노드에 대해서는 재귀적으로 함수를 타고 들어가서, 
    // 해당된 노드에 대해서는 동적으로 할당된 메모리를 해제해준다.
    for(int i=0; i<N; i++)
    {
        free_trie(root -> children[i]);
    }

    free(root);

}

int main()
{
    node *root = create_node();

    int n = 6;
    char *word1 = "apple";
    char *word2 = "application";
    char *word3 = "beard";
    char *word4 = "bird";
    char *word5 = "canvas";
    char *word6 = "canaria";
    
    char *words[n];
    words[0]=word1;
    words[1]=word2;
    words[2]=word3;
    words[3]=word4;
    words[4]=word5;
    words[5]=word6;

    // 단어를 트라이 구조에 넣는다.
    for(int i=0; i<n; i++)
    {
        insert(root, words[i]); 
    }

    // 찾고자 하는 단어를 입력해본다.
    // 최소 한번은 입력 받고 while문이 실행돼야 하기 때문에,
    // do-while문을 활용한다.
    char * find;
    do{
        find = get_string("What word do you wish to find? / (0 To stop) ");
        if(strcmp(find, "0")==0)
        {
            break;
        }

        bool exists = search(root, find);
        
        printf("%s : %s\n", find, exists ? "exists" : "not there");

    }while(true);
    
    
    free_trie(root);

    return 0;
}
