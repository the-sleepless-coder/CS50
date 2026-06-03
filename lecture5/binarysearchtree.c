#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;

node* insert_node(node *currnode, int number);
void maketree(node **tree);
bool search(node *node, int target);
void preorder(node *node);
void inorder(node *node);
void postorder(node *node);
int strcmp_cust(char *s1, char *s2);

int main(void)
{
    // 노드 간 관계를 생성해서 트리를 만든다.
    node *root = NULL;
    maketree(&root);

    // 순회 방식을 결정한다.
    char *buf = get_string("How do you wish to traverse the tree? (pre/in/post) ");

    if(strcmp_cust(buf, "pre")==0)
    {
        preorder(root);
    }
    else if(strcmp_cust(buf, "in")==0)
    {
        inorder(root);
    }
    else if(strcmp_cust(buf, "post")==0)
    {
        postorder(root);
    }

    printf("\n");

    // 찾고 싶은 숫자를 찾는다.
    while(true)
    {
        int target = get_int("What number do you wish to find? ");

        bool result = search(root, target);


        if(result)
        {
            printf("Number : %d exists\n", target);
        }
        else
        {
            printf("Number: %d DOES NOT exist\n", target);
        }
        
        char c =  get_char("Do you wish to find another number? (Y/N) ");
        if(c == 'Y' || c == 'y')
        {
            continue;
        }
        else if(c=='N'||c=='n')
        {
            break;
        }
    }
    
}

// 노드를 삽입하고, 
// 노드의 주소값을 반환한다.
node* insert_node(node *currnode, int number)
{
    // 노드를 재귀함수를 타고 들어가면서 탐색
    // 루트에 삽입, 혹은 리프 노드의 맞는 자리에 삽입
    if(currnode == NULL)
    {
        node *newnode = malloc(sizeof(node));
        if(newnode ==NULL){
            printf("Failed to allocate new node\n");
            return NULL;
        }
        
        newnode -> number = number;
        newnode -> left = NULL;
        newnode -> right = NULL;
        
        return newnode;

    }
    // 현재 노드보다 작은 경우 왼쪽 탐색
    // 리프 노드에 도달하면, 
    // 왼쪽 노드 자리에 삽입한다.
    else if(number < currnode->number)
    {
        currnode -> left = insert_node(currnode->left, number);
    }
    else if( number > currnode -> number)
    {
        currnode -> right = insert_node(currnode->right, number);
    }

    // 재귀 함수로 모든 트리를 순회하고 노드를 삽입하고나서는, 
    // 트리의 root노드를 반환한다.
    return currnode;
}

void maketree(node **tree)
{
    printf("Making tree ...\n");
    // pass by value이기 떄문에,
    // 포인터 변수 *tree를 담은 포인터 변수 형태로 **tree 변수를 넘겨준다.
    while(true)
    {
        int number = get_int("Number: ");

        *tree = insert_node(*tree, number);

        char c = get_char("Do you want to add more nodes(Y/N) \n");
        
        if(c=='Y'||c=='y')
        {
            continue;
        }
        else if(c=='N'||c=='n')
        {
            break;
        }
    }
}

bool search(node *node, int target)
{
    // 리프 노드까지 갔는데 없으면,
    // false를 반환.
    if(node == NULL)
    {
        return false;
    }
    // target이 현재 노드보다 더 크다면,
    // 오른쪽을 탐색.
    else if(node->number < target)
    {
        return search(node->right, target);
    }
    // target이 현재 노드 보다 작다면,
    // 왼쪽을 탐색.
    else if(node -> number > target)
    {
        return search(node->left, target);
    }
    else
    {
        return true;
    }
}

// 각 서브트리에서 어떻게 노드를 순회할 것인지를 보여줌.
// 현재 노드 - 왼쪽 - 오른쪽 순으로 출력.
void preorder(node *node)
{
    if(node == NULL)
    {
        return;
    }

    // 현재 - 왼쪽 - 오른쪽 순으로 탐색.
    // 현재 - 현재 - 현재 ... 
    // 왼쪽 - 오른쪽 
    printf("%d ", node->number);
    preorder(node->left);
    preorder(node->right);
}

// 왼쪽 - 현재노드 - 오른쪽 순으로 출력.
void inorder(node *node)
{
    if(node == NULL)
    {
        return;
    }

    // 왼쪽 - 왼쪽 - 왼쪽 ...
    // 가운데 - 오른쪽 
    inorder(node->left);
    printf("%d ", node->number);
    inorder(node ->right);
}

void postorder(node *node)
{
    if(node == NULL)
    {
        return;
    }

    postorder(node -> left);
    postorder(node -> right);
    printf("%d ", node->number);
}

int strcmp_cust(char *s1, char *s2)
{

    // 문자열이 같을 때 while문 처리
    while( *s1 == *s2 )
    {
        // 둘다 문자열이 똑같은데,
        // 문자열 끝에 도달하면 같다를 반환.
        if(*s1 == '\0') return 0;
        
        // 다음 문자 확인
        s1++;
        s2++;
    }

    // 서로 다르면 문자 차이를 반환
    // 음수면 s1이 앞,
    // 양수면 s2이 뒤
    return *s1 - *s2;
}

