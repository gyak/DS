#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
	int val;
	int vertex;
	struct _node* link;
}node;
node** graph;
typedef struct _line {
	int a, b;
	int val;
	struct _line* link;
}line;
line* root=NULL;
int* visited;
int* parent;
FILE* out;

void dfs(int);
void swap(line*,line*);
void sort();

int main()
{
	FILE* fp = fopen("input62.txt", "r");
	if (fp == NULL)
	{
		printf("open error!!\n");
		return 1;
	}
	out = fopen("output.txt", "w");
	int n, i, j, cost = 0, t, count = 0, key;
	node* temp, *ptr;
	line* tmp, *lptr=root;
	fscanf(fp, "%d", &n);//adjacency matrix의 가로, 세로 길이
	graph = (node**)malloc(sizeof(node*)*n);
	for (i = 0; i < n; i++)
		graph[i] = NULL;//인접리스트의 선언과 초기화
	visited = (int*)calloc(n, sizeof(int));//이곳에 방문한적이 있으면 1, 아니면 0 
	parent = (int*)calloc(n, sizeof(int));//이 노드의 근본이 어디인지를 알려주는 배열
	for (i = 0; i < n; i++)
		parent[i] = i;//i번째 원소를 i로 초기화 해준다.
	for (j = 0; j < n; j++)
		for (i = 0; i < n; i++)
		{
			fscanf(fp, "%d", &t);//matrix를 하나씩 읽어온다.
			if (t > -1 && i > j)//가중치 값이 두번씩 나오지 않게 우측 위쪽만 읽어주는 느낌이다.
			{
				tmp = (line*)malloc(sizeof(line));
				tmp->a = j;
				tmp->b = i;
				tmp->val = t;
				tmp->link = root;
				root = tmp;
			}//tmp의 할당과 초기화와 연결, 리스트의 제일 앞쪽에 넣어준다.
		}
	sort();//버블소트를 활용해서 정렬한다
	for (lptr = root; lptr; lptr = lptr->link)//간선의 노드를 하나씩 읽어가며
		if (parent[lptr->a] != parent[lptr->b])//간선의 양끝점의 근본이 다를 때
		{
			count++;//간선의 개수
			temp = (node*)malloc(sizeof(node));//@@@@@@@@@@@@@@@@@@@@@@@여기서부터
			temp->link = NULL;
			temp->vertex = lptr->b;
			temp->val = t;
			if (graph[lptr->a] == NULL)
				graph[lptr->a] = temp;
			else
			{
				for (ptr = graph[lptr->a]; ptr->link; ptr = ptr->link);
				ptr->link = temp;
			}
			temp = (node*)malloc(sizeof(node));
			temp->link = NULL;
			temp->vertex = lptr->a;
			temp->val = t;
			if (graph[lptr->b] == NULL)
				graph[lptr->b] = temp;
			else
			{
				for (ptr = graph[lptr->b]; ptr->link; ptr = ptr->link);
				ptr->link = temp;
			}//여기까지@@@@@@@@@@@@@@@@@ a리스트에 b를 추가해주고 b리스트에 a를 추가해준다.
			key = parent[lptr->b];
			cost = cost + lptr->val;//전체 비용에 지금 간선의 가중치를 더해준다.
			for (i = 0; i < n; i++)
				if (key == parent[i])
					parent[i] = parent[lptr->a];//b와 같은 근본을 가진 녀석들을 전부 a화통일 시킨다.
			if (count == n - 1)//간선의 개수가 n-1개일때 멈춘다.
				break;
		}
	dfs(0);//dfs 실행
	fprintf(out,"\n%d\n", cost);
	fclose(fp);
	for (i = 0; i < n; i++)
	{
		while (graph[i])
		{
			ptr = graph[i];
			graph[i] = graph[i]->link;
			free(ptr);
		}
	}//graph에 붙어있는 노드들을 프리해준다.
	free(graph);
	while (root)
	{
		lptr = root;
		root = root->link;
		free(lptr);
	}//간선 리스트를 프리해준다.
	free(visited);
	free(parent);
	return 0;
}

void dfs(int  v)
{
	node* w;
	fprintf(out, "%d ", v);
	visited[v] = 1;//방문했다는 표시를 해준다.
	for (w = graph[v]; w; w = w->link)
		if (!visited[w->vertex])//하나의 점에 대해 그 인접리스트에 대해서 다시 dfs를 진행한다.
			dfs(w->vertex);
}

void swap(line* p1, line* p2)
{
	int t = p1->val;
	p1->val = p2->val;
	p2->val = t;
	t = p1->a;
	p1->a = p2->a;
	p2->a = t;
	t = p1->b;
	p1->b = p2->b;
	p2->b = t;
}

void sort()
{
	line* i, *j;
	for(j=root; j->link->link; j = j->link )
		for(i=root; i->link->link; i = i->link)
			if((i->val) > (i->link->val))
				swap(i,i->link);
}