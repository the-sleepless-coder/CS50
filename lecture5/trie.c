#include <stdio.h>
#include <stdbool.h>


#define N 26


// 각 노드는 다음 노드를 가리킨다는 점에서 linked list와 유사하다.
// 다만 노드의 구성이 각 알파벳을 나타내는 노드 배열 형태로 표현한다는 점이다.
typedef struct node
{
    struct node *children[26]; // 노드 포인터 배열[26]
    //char *number;
    bool isend;
} node;

// 할당 받은 노드(자식 노드 배열, 끝 노드 여부)를 반환한다.
node *create_node(void)
{
    node *newnode = malloc(sizeof(node));
    if(newnode == NULL)
    {
        printf("Failed to allocate root node");
        exit(1);
    }

    // 반환 받은 노드 값 초기화
    for(int i=0; i<N; i++)
    {
        newnode->children[i] = NULL;
    }

    newnode->isend = false;
    
    return newnode;
}

// 트라이 구조 내에, 단어의 알파벳을 입력한다. 
bool insert(node *root, char *word)
{
    node *ptr = root;

    int widx = 0;
    while(word[widx] != '\0')
    {   
        char c = tolower(word[widx]);

        if(c<'a' || c>'z')
        {
            return false;
        }

        int charidx = c-'a';

        // 이미 존재하는 단어 조합을 활용하기 위해, 
        // 값이 존재하지 않을 때 자식 노드에 반환 받은 노드를 넣는다.
        // a p p 
        //     \ l e
        if(ptr->children[charidx]==NULL)
        {
            ptr->children[charidx] = create_node(); 
        }
        
        // 새로 배정 받거나/이미 존재하는 자식 노드 포인터를 따라간다.
        ptr = ptr -> children[charidx];

        widx++;
    }

    // 단어의 끝임을 표시한다.
    ptr -> isend = true;

    return true;
}

// 찾고자 하는 단어가, 
// 트라이 구조 내 노드 배열의 포인터가 연결된 형태로 존재하는지 확인한다.
bool search(node *root, char *word)
{
    node *ptr = root;

    int widx = 0;
    while(word[widx] != '\0')
    {
        char c = tolower(word[widx]);

        // 알파벳이 아니거나
        if( c < 'a' || c>'z')
        {
            return false;
        }

        // 노드 배열의 포인터가 연결된 형태로 표현되지 않는다면,
        // FALSE를 반환한다.
        int cidx = c-'a';

        if(ptr->children[cidx]==NULL)
        {
            return false;
        }
        
        ptr = ptr -> children[cidx];

        widx++;
        
    }

    return ptr -> isend;
}

void free_trie(node *root)
{
    if(root == NULL)
    {
        return;
    }

    for(int i=0; i<N; i++)
    {
        free_trie(root->children[i]);
    }

    free(root);
}

int main(void)
{
    // Trie Root생성
    node *root = create_node();

    int n = 6;

    char *word1 = "apple";
    char *word2 = "bear";
    char *word3 = "application";
    char *word4 = "bearable";
    char *word5 = "unbearable";
    char *word6 = "applicable";
    
    char *words[n];

    words[0] = word1;
    words[1] = word2;
    words[2] = word3;
    words[3] = word4;
    words[4] = word5;
    words[5] = word6;
    
    for(int i=0; i<n; i++)
    {
        insert(root, words[i]);    
    }
    
    

}

/*
root
 |
 E
 |
 M
 |\
 M I
 |  \
 A   L
 |    \
(end)  Y(end)
*/