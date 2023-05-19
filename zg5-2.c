#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int key;
    struct _node* parent;
    struct _node* left;
    struct _node* right;
}node;

int fincount, findepth=0;
node* root;
int makeTree(node**,node*,int*,int,int);
void inorder(node*);
void postorder(node*);

int main()
{
    int i,j,t;
    int* heap;
    scanf("%d",&fincount);//총 몇개의 입력을 받는지 표준 입출력으로 받아준다.
    heap = (int*)malloc(sizeof(int)*(fincount+1));
    for(i=1; i<fincount+1; i++)
        scanf("%d",heap+i);//주어진 값들을 heap에다가 저장한다.
    for(i=1; i<fincount; i++)
        for(j=i+1; j<fincount+1; j++)
            if(heap[i] == heap[j])
            {
                printf("cannot construct BST\n");
                return 0;
            }//중복되는 값이 있는지 체크한다.
    t = fincount;
    while(t>1)
    {
        findepth++;
        t = t/2;
    }//최종 depth가 얼마인지 계산한다.
    t = makeTree(&root, root, heap, 1, 0);//주어진 입력으로 트리를 만든다.
    printf("Inorder: ");
    inorder(root);//inorder 방식으로 출력한다.
    printf("\nPostorder: ");
    postorder(root);//postorder 방식으로 출력한다.
    printf("\n");
    return 0;
}

int makeTree(node** ptr, node* par, int* heap, int count, int depth)
{//함수를 재귀적으로 호출해서 트리를 만든다.
    if(depth > findepth || count > fincount)//최종 depth보다 깊거나 최종 count보다 커지는 경우에 다시 뒤로 돌아간다.
        return count-1;
    node* nd = (node*)malloc(sizeof(node));
    nd->key = heap[count];//현재 count에 해당하는 값을 nd에 넣어준다.
    nd->parent = par;//nd의 데이터를 초기화 시켜준다.
    *ptr = nd;//ptr에다가 nd를 연결시켜준다.
    int nowkey = nd->key;//현재의 key값을 저장한다.
    if(fincount%2 == 0 && count == fincount-1)//마지막 노드의 부모 노드가 하나의 자식 노드를 가지는 경우이다.
    {
        if(heap[fincount] > nowkey)//기존의 key값과 비교해서 크면 오른쪽에 연결한다.
            count = makeTree(&(nd->right), nd, heap, count+1, depth+1);
        else//작으면 왼쪽에 연결한다.
            count = makeTree(&(nd->left), nd, heap, count+1, depth+1);
        return count;
    }
    count = makeTree(&(nd->left), nd, heap, count+1, depth+1);
    count = makeTree(&(nd->right), nd, heap, count+1, depth+1);
	//현재 노드를 중심으로 왼쪽, 오른쪽에다가 새로운 노드를 연결시킨다.
    return count;
}

void inorder(node* nd)
{//inorder 방식으로 출력한다
    if(nd)
    {
        inorder(nd->left);
        printf("%d ", nd->key);
        inorder(nd->right);
    }
}

void postorder(node* nd)
{//postorder 방식으로 출력한다
    if(nd)
    {
        postorder(nd->left);
        postorder(nd->right);
        printf("%d ", nd->key);
    }
}
