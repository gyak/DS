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
	fscanf(fp, "%d", &n);//adjacency matrix�� ����, ���� ����
	graph = (node**)malloc(sizeof(node*)*n);
	for (i = 0; i < n; i++)
		graph[i] = NULL;//��������Ʈ�� ����� �ʱ�ȭ
	visited = (int*)calloc(n, sizeof(int));//�̰��� �湮������ ������ 1, �ƴϸ� 0 
	parent = (int*)calloc(n, sizeof(int));//�� ����� �ٺ��� ��������� �˷��ִ� �迭
	for (i = 0; i < n; i++)
		parent[i] = i;//i��° ���Ҹ� i�� �ʱ�ȭ ���ش�.
	for (j = 0; j < n; j++)
		for (i = 0; i < n; i++)
		{
			fscanf(fp, "%d", &t);//matrix�� �ϳ��� �о�´�.
			if (t > -1 && i > j)//����ġ ���� �ι��� ������ �ʰ� ���� ���ʸ� �о��ִ� �����̴�.
			{
				tmp = (line*)malloc(sizeof(line));
				tmp->a = j;
				tmp->b = i;
				tmp->val = t;
				tmp->link = root;
				root = tmp;
			}//tmp�� �Ҵ�� �ʱ�ȭ�� ����, ����Ʈ�� ���� ���ʿ� �־��ش�.
		}
	sort();//�����Ʈ�� Ȱ���ؼ� �����Ѵ�
	for (lptr = root; lptr; lptr = lptr->link)//������ ��带 �ϳ��� �о��
		if (parent[lptr->a] != parent[lptr->b])//������ �糡���� �ٺ��� �ٸ� ��
		{
			count++;//������ ����
			temp = (node*)malloc(sizeof(node));//@@@@@@@@@@@@@@@@@@@@@@@���⼭����
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
			}//�������@@@@@@@@@@@@@@@@@ a����Ʈ�� b�� �߰����ְ� b����Ʈ�� a�� �߰����ش�.
			key = parent[lptr->b];
			cost = cost + lptr->val;//��ü ��뿡 ���� ������ ����ġ�� �����ش�.
			for (i = 0; i < n; i++)
				if (key == parent[i])
					parent[i] = parent[lptr->a];//b�� ���� �ٺ��� ���� �༮���� ���� aȭ���� ��Ų��.
			if (count == n - 1)//������ ������ n-1���϶� �����.
				break;
		}
	dfs(0);//dfs ����
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
	}//graph�� �پ��ִ� ������ �������ش�.
	free(graph);
	while (root)
	{
		lptr = root;
		root = root->link;
		free(lptr);
	}//���� ����Ʈ�� �������ش�.
	free(visited);
	free(parent);
	return 0;
}

void dfs(int  v)
{
	node* w;
	fprintf(out, "%d ", v);
	visited[v] = 1;//�湮�ߴٴ� ǥ�ø� ���ش�.
	for (w = graph[v]; w; w = w->link)
		if (!visited[w->vertex])//�ϳ��� ���� ���� �� ��������Ʈ�� ���ؼ� �ٽ� dfs�� �����Ѵ�.
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