#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node* treePointer;
typedef struct _node{
        int key;
        treePointer parent;
        treePointer leftChild, rightChild;
}node;
treePointer root = NULL;

int depth=0, count=0;

void insert(int);
int delete();
int sib(int);
int bin(int);
void swap(node*,node*);
void sort(node*);
int find(node*,int);

int main()
{
    char key = 'f';
    int num,check;
    while(key!='q')//key의 값으로 q를 받으면 종료한다.
    {
        scanf("%c",&key);
        if(key == 'i')//i가 들어오면 추가적으로 정수 하나를 더 받아준다.
            scanf("%d",&num);
        scanf("%*c");
        if(key == 'i')
        {
            check = find(root,num);//입력받은 정수가 트리 구조안에 있는지 체크하고 있으면 1을 리턴한다.
            if(check == 1)
                printf("Exist number\n");
            else
            {
                insert(num);//없으면 삽입을 시도한다.
                printf("Insert %d\n", num);
            }
        }
        else if(key == 'd')//d가 입력으로 들어온다.
        {
            if(count == 0)//현재 트리가 비어있으면 경고메세지를 출력한다.
                printf("The heap is empty\n");
            else
            {
                check = delete();//삭제하고 삭제된 key의 값을 리턴해서 출력해준다.
                printf("Delete %d\n", check);
            }
        }
    }
    return 0;
}

int sib(int n)//10의 거듭제곱을 리턴해준는 함수이다.
{
    int i,t=1;
    for(i=0; i<n; i++)
        t = t*10;
    return t;
}

int bin(int n)//입력받은 10진수 숫자를 2진수로 변환시켜 주는 함수이다.
{
    int i=0,t=0;
    while(n!=0)
    {
        t = t + n%2*sib(i++);
        n = n/2;
    }
    return t;
}

void swap(node* a, node* b)//a와 b의 key값을 비교해서 swap해준다.
{
    int t;
    if(a->key < b->key)
    {
        t = a->key;
        a->key = b->key;
        b->key = t;
    }
}

void sort(node* child)//트리의 제일 마지막 위치를 받아서 그의 parent를 따라 bubble sort를 해준다.
{
    node* temp;
    int i,j;
    for(i=0; i<depth; i++)
    {
        temp = child;
        for(j=0; j<depth; j++)
        {
            swap(temp->parent, temp);
            temp = temp->parent;
        }
    }
}

int find(node* nd, int num)//중복되는 key의 값이 트리에 있는지 확인하는 함수이다.
{
    if(nd == NULL)
        return 0;
    if(nd->key == num)
        return 1;
    if(nd->key < num)
        return 0;
    return find(nd->leftChild, num) + find(nd->rightChild, num);
}

void insert(int num)//데이터를 트리에 삽입시켜주는 함수이다.
{
    node* temp;
    node* nd = (node*)malloc(sizeof(node));
    nd->key = num;
    nd->parent = nd;
    nd->leftChild = NULL;
    nd->rightChild = NULL;//nd를 말록시켜주고 값을 초기화 시켜준다.
    count++;//count를 1증가시킨다.
    int bicount = bin(count);//현재의 count를 이진수로 바꿔서 저장한다.
    int t = bicount;
    int i;
    depth = 0;
    while(t >= 10)
    {
        depth++;
        t = t/10;
    }//현재의 depth를 구해준다.
    if(count == 1)//처음에는 root에 nd를 연결시켜준다.
        root = nd;
    else//각 위치를 이진수로 나타내어 각자리 숫자가 1이면 rightChild 0이면 leftChild로 이동한다.
    {
        i = depth;//현재의 깊이가 곧 이진수의 길이를 나타낸다.
        t = bicount;
        temp = root;
        while(i > 1)
        {
            t = t%sib(i);
            if(t/sib(i-1) == 1)//지금 보고있는 자리의 숫자가 1이면 rightChild
                temp = temp->rightChild;
            else//0이면 leftChild로 이동한다.
                temp = temp->leftChild;
            i--;
        }
        if(t%10 == 1)//마지막에 1이 남아 있으면 현재 노드의 오른쪽에 연결하고
            temp->rightChild = nd;
        else//0이 남아 있으면 현재 노드의 왼쪽에 연결한다.
            temp->leftChild = nd;
        nd->parent = temp;
        sort(nd);//연결 시키고 정렬시켜준다.
    }
    return;
}

int delete()//트리에서 가장 큰 값을 삭제해주는 함수이다.
{
    int del = root->key;//root의 key값이 가장 크므로 이를 저장한다.
    int i,t;
    node* temp;
    t = bin(count);
    depth = 0;
    while(t >= 10)
    {
        depth++;
        t = t/10;
    }//현재의 count를 이용해서 depth를 계산한다.
    i = depth;
    temp = root;
    t = bin(count);
    while(i > 0)
    {
        t = t%sib(i);
        if(t/sib(i-1) == 1)//지금 보고있는 자리의 숫자가 1이면 rightChild
            temp = temp->rightChild;
        else//0이면 leftChild로 이동한다.
            temp = temp->leftChild;
        i--;
    }
    root->key = temp->key;//root에다가 제일 마지막에 있던 key의 값을 저장한다.
    count--;
    if(count == 0)//직전 count가 1, 즉 한개의 노드만을 가지고 있는 트리의 경우 바로 root를 프리 해준다.
    {
        free(root);
        root = NULL;
        return del;
    }
    if(t == 1)//아니라면 마지막 t값이 1인 경우 부모 노드로 가서 그의 오른쪽 연결을 해제한다.
        (temp->parent)->rightChild = NULL;
    else//0이라면 왼쪽 연결을 해제한다.
        (temp->parent)->leftChild = NULL;
    free(temp);//그 노드를 프리시켜준다.
    t = bin(count);
    depth = 0;
    while(t >= 10)
    {
        depth++;
        t = t/10;
    }//줄어든 count에 대해 depth를 다시 계산한다.
    i = depth;
    temp = root;
    t = bin(count);
    while(i > 0)
    {
        t = t%sib(i);
        if(t/sib(i-1) == 1)
            temp = temp->rightChild;
        else
            temp = temp->leftChild;
        i--;
    }//줄어든 카운트의 위치로 이동한다.
    sort(temp);//그 후에 정렬해준다.
    if(root->leftChild)//그리고 루트와 바로  양쪽 밑의 key값을 비교해서 큰것이 위로 오게 바꿔준다.
        swap(root, root->leftChild);
    if(root->rightChild)
        swap(root, root->rightChild);
    return del;
}
