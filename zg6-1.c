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
	fscanf(fp, "%d", &n);//adjacency matrix�� ����, ���� ����
	visited = (int*)calloc(n, sizeof(int));//�̰��� �湮������ ������ 1, �ƴϸ� 0 
	graph = (node**)malloc(sizeof(node*)*n);
	for (i = 0; i < n; i++)
		graph[i] = NULL;//��������Ʈ�� ����� �ʱ�ȭ
	for (j = 0; j < n; j++)
		for (i = 0; i < n; i++)
		{
			fscanf(fp, "%d", &yesno);//matrix�� �ϳ��� �о��.
			if (yesno == 1)//�о�� ���� 1�� ���� ���� ������ �����Ѵ�.
 			{
				temp = (node*)malloc(sizeof(node));
				temp->link = NULL;
				temp->vertex = i;//���� ��带 �ϳ� ���� ���� �ʱ�ȭ ���ش�.
				ptr = graph[j];
				if (!graph[j])// �ƹ��͵� ������� �ʾ��� ��
					graph[j] = temp;
				else//�Ѱ��� ����Ǿ� �ִٸ� �� ����Ʈ�� ���� �������� �������ش�.
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
	}//graph�� ����� ������ ���� ���ش�.
	free(graph);//graph�� ���� ���ش�.
	free(visited);//visited ����
	fclose(fp);
	fclose(out);
	return 0;
}

void connected()
{
    int i;
	for (i = 0; i < n; i++)
		if (!visited[i])//visited�� 0�� ���� �湮���� ���� ����� �� �����Ѵ�.
		{
			dfs(i);//dfs�� ó���ϴ� �������� visited�� ���� ��ȭ�Ѵ�.
			fprintf(out, "\n");
		}
}

void dfs(int v)
{
    node* w;
    visited[v] = 1;//�湮�ߴٴ� ǥ�ø� ���ش�.
    fprintf(out, "%d ",v);
	for (w = graph[v]; w != NULL; w = w->link)//�ϳ��� ���� ���� �� ��������Ʈ�� ���ؼ� �ٽ� dfs�� �����Ѵ�.
		if (visited[w->vertex] == 0)
			dfs(w->vertex);
}