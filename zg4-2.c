#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct NODE
{
    char name[10];
    struct NODE* next;
    struct NODE* down;
}node;

node* headnode;

void push(node* head, char* fname)
{
    node* nd = (node*)malloc(sizeof(node));
    strcpy(nd->name, fname); 
    nd->down = head->down;
    head->down = nd;
}//노드를 초기화 시켜서 삽입해주는 함수이다.

void pop(node* head, char* fname)
{
    if(head->down != head)
    {
        node* nd;
        node* prend = head;
        for(nd=head->down; strcmp(nd->name, fname) != 0 ; nd=nd->down)//이름이 같을 때 정지한다.
            prend=nd;
        prend->down = nd->down;
        free(nd);    
    }
}//같은 이름을 가진 노드를 찾고 그것을 프리 해주는 함수이다,

void person(char* fname)
{
    node* head = (node*)malloc(sizeof(node));
    strcpy(head->name, fname);
    head->next = headnode->next;
    headnode->next = head;
    head->down = head;
}//push함수의 head버전이다. 새로운 head를 만들어 연결한다.

void friend(char* name1, char* name2)
{
    node* findhead;
    for(findhead=headnode->next; strcmp(findhead->name, name1) != 0; findhead=findhead->next);
    push(findhead, name2);
    for(findhead=headnode->next; strcmp(findhead->name, name2) != 0; findhead=findhead->next);
    push(findhead, name1);
}//이름이 name1과 같은 head를 찾고 그 head에 name2라는 이름을 가진 노드를 push해준다. 이를 name2에 대해서도 해준다.

void unfriend(char* name1, char* name2)
{
    node* findhead;
    for(findhead=headnode->next; strcmp(findhead->name, name1) != 0; findhead=findhead->next);
    pop(findhead, name2);
    for(findhead=headnode->next; strcmp(findhead->name, name2) != 0; findhead=findhead->next);
    pop(findhead, name1);
}//이름이 name1과 같은 head를 찾고 그 head에 name2라는 이름을 가진 노드를 pop해준다. 이를 name2에 대해서도 해준다.

void list(char* fname)
{
    FILE* fp = fopen("output.txt","a");
    if(fp==NULL)
    {
        printf("OPEN ERROR!!\n");
        return;
    }
    node* findhead;
    for(findhead=headnode->next; strcmp(findhead->name, fname) != 0; findhead=findhead->next)
        if(findhead == headnode)
        {
            fprintf(fp,"NONE\n");
            fclose(fp);
            return;
        }//같은 이름을 가진 head가 없는 경우
    if(findhead->down == findhead)
    {
        fprintf(fp,"NONE\n");
        fclose(fp);
        return;
    }//같은 이름을 가진 head가 있으나 그 head에 연결된 node가 없는 경우
    node* nd;
    for(nd=findhead->down; nd != findhead; nd=nd->down)
        fprintf(fp,"%s ", nd->name);//이름들을 출력해준다.
    fprintf(fp,"\n");
    fclose(fp);
}//특정 이름을 가진 head에 연결 되어진 node들의 이름을 출력해주는 함수이다.

void question(char* name1, char* name2)
{
    FILE* fp = fopen("output.txt","a");
    if(fp==NULL)
    {
        printf("OPEN ERROR!!\n");
        return;
    }
    node* findhead;
    for(findhead=headnode->next; strcmp(findhead->name, name1) != 0; findhead=findhead->next);
	//같은 이름이 나올 때 정지한다.
    node* nd;
    for(nd=findhead->down; nd != findhead; nd=nd->down)
        if(strcmp(nd->name, name2) == 0)
        {
            fprintf(fp,"YES\n");
            fclose(fp);
            return;
        }//같은 이름이 있으면 YES를 출력한다.
    fprintf(fp,"NO\n");//같은 이름이 없어서 for문이 끝나는 경우에 NO를 출력해준다.
    fclose(fp);
    return;
}//name1의 이름을 가진 head에 name2라는 이름을 가지는 node가 있는지 검사하는 함수이다.

int main()
{
    FILE* fp = fopen("input.txt","r");
    if(fp==NULL)
    {
        printf("OPEN ERROR!!\n");
        return 1;
    }
    FILE* fp1 = fopen("output.txt","w");
    if(fp1==NULL)
    {
        printf("OPEN ERROR!!\n");
        return 1;
    }
    fclose(fp1);
    headnode = (node*)malloc(sizeof(node));
    headnode->next = headnode;
    char* name1 = (char*)malloc(sizeof(char)*10);
    char* name2 = (char*)malloc(sizeof(char)*10);
    char command;
    char trash;
    for(fscanf(fp,"%c",&command); command != 'X'; fscanf(fp,"%c%c",&trash,&command))
    {
        switch(command)//command의 값에 따라 적당함 함수가 실행된다.
        {
            case 'P': 
                fscanf(fp,"%s",name1);
                person(name1);
                break;
            case 'F':
                fscanf(fp,"%s %s",name1,name2);
                friend(name1,name2);
                break;
            case 'U':
                fscanf(fp,"%s %s",name1,name2);
                unfriend(name1,name2);
                break;
            case 'L':
                fscanf(fp,"%s",name1);
                list(name1);
                break;
            case 'Q':
                fscanf(fp,"%s %s",name1,name2);
                question(name1,name2);
                break;
            default: break;
        }
    }
    fclose(fp);
    free(headnode);
    free(name1);
    free(name2);//메모리를 해제시켜준다.
    return 0;
}
