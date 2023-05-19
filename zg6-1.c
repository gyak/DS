#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _node{
    int vertex;
    struct _node* link;
}node;
node** graph;
int n;
int* visited;
FILE* out;

void connected();
void dfs(int);

int main()
{
	FILE* fp = fopen("input61.txt", "r");
	if (fp == NULL)
	{
		printf("open error");
		return 1;
	}
	out = fopen("output.txt", "w");
	int i, j, t, yesno;
	node *temp, *ptr;
	fscanf(fp, "%d", &n);//adjacency matrix의 가로, 세로 길이
	visited = (int*)calloc(n, sizeof(int));//이곳에 방문한적이 있으면 1, 아니면 0 
	graph = (node**)malloc(sizeof(node*)*n);
	for (i = 0; i < n; i++)
		graph[i] = NULL;//인접리스트의 선언과 초기화
	for (j = 0; j < n; j++)
		for (i = 0; i < n; i++)
		{
			fscanf(fp, "%d", &yesno);//matrix를 하나씩 읽어간다.
			if (yesno == 1)//읽어온 값이 1일 때만 다음 동작을 수행한다.
 			{
				temp = (node*)malloc(sizeof(node));
				temp->link = NULL;
				temp->vertex = i;//새로 노드를 하나 만들어서 값을 초기화 해준다.
				ptr = graph[j];
				if (!graph[j])// 아무것도 연결되지 않았을 때
					graph[j] = temp;
				else//한개라도 연결되어 있다면 이 리스트의 제일 마지막에 삽입해준다.
				{
					for (; ptr->link; ptr = ptr->link);
					ptr->link = temp;
				}
			}
		}
	connected();
	for (i = 0; i < n; i++)
	{
		while (graph[i])
		{
			ptr = graph[i];
			graph[i] = graph[i]->link;
			free(ptr);
		}
	}//graph에 연결된 노드들을 프리 해준다.
	free(graph);//graph를 프리 해준다.
	free(visited);//visited 프리
	fclose(fp);
	fclose(out);
	return 0;
}

void connected()
{
    int i;
	for (i = 0; i < n; i++)
		if (!visited[i])//visited가 0인 아직 방문하지 않은 노드일 때 실행한다.
		{
			dfs(i);//dfs를 처리하는 과정에서 visited의 값이 변화한다.
			fprintf(out, "\n");
		}
}

void dfs(int v)
{
    node* w;
    visited[v] = 1;//방문했다는 표시를 해준다.
    fprintf(out, "%d ",v);
	for (w = graph[v]; w != NULL; w = w->link)//하나의 점에 대해 그 인접리스트에 대해서 다시 dfs를 진행한다.
		if (visited[w->vertex] == 0)
			dfs(w->vertex);
}