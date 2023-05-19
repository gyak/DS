#include<stdio.h>
#include<stdlib.h>

typedef enum {head, entry} tagfield; 
typedef struct matrix_node *matrix_pointer; 
typedef struct entry_node 
{ 
    int row; 
    int col; 
    int value; 
}entry_node;
typedef struct matrix_node 
{ 
    matrix_pointer down; 
    matrix_pointer right; 
    tagfield tag; 
    union 
    { 
        matrix_pointer next; 
        struct entry_node entry; 
    } u; 
}matrix_node;

matrix_pointer* hdnode;
matrix_pointer* thdnode;

matrix_pointer new_node()
{
    matrix_pointer temp = (matrix_pointer)malloc(sizeof(matrix_node));
    return temp;
}

matrix_pointer mread() 
{ 
	int num_rows, num_cols,num_terms, num_heads, i; 
    int row, col, value, current_row; 
    matrix_pointer temp, last, node;
    FILE* fp = fopen("input.txt","r");
    if(fp==NULL)
    {
        printf("open error!\n");
        return NULL;
    }
    

    fscanf(fp,"%d %d %d\n", &num_rows, &num_cols, &num_terms); 
    num_heads = (num_cols > num_rows) ? num_cols : num_rows; 
	//num_heads의 값을 num_cols과 num_rows중에 큰 값으로 정해준다.
    node = new_node(); 
    node->tag = entry; 
    node->u.entry.row = num_rows;
    node->u.entry.col = num_cols;
    node->u.entry.value = num_terms;
	//node에다가 값을 채운다.
    if (!num_heads) 
        node->right= node; 
	//입력받은 엔트리가 없는 경우를 생각한다.
	else 
    {  
        hdnode = (matrix_pointer*)malloc(sizeof(matrix_pointer)*num_heads);
        for (i=0; i<num_heads; i++) 
        { 
            temp = new_node(); 
            hdnode[i]= temp; 
            hdnode[i]->tag = head; 
            hdnode[i]->right= temp; 
            hdnode[i]->u.next=temp; 
        } //헤드를 초기화 시켜준다.
        current_row = 0; 
        last = hdnode[0]; 
        for (i=0; i<num_terms; i++) 
        { 
            fscanf(fp,"%d %d %d\n", &row, &col, &value);
            if (row > current_row) 
            {  
                last->right = hdnode[current_row]; 
                current_row = row; 
                last = hdnode[row]; 
            } //입력이 row순으로 이뤄지기 때문에 row의 값이 current_row보다 커진다는 것은 지금의 row에서는
			//더이상의 입력이 없다는 뜻이므로 마지막 노드의 right를 헤드에다가 연결시켜줘서 닫아준다.
            temp = new_node(); 
            temp->tag = entry; 
            temp->u.entry.row = row; 
            temp->u.entry.col = col; 
            temp->u.entry.value = value; 
			//새로운 엔트리를 만들어주고 값을 넣어서 초기화 해준다.
            last->right = temp;
			//해당 row의 제일 마지막에다가 지금 엔트리를 연결시켜준다.
            last = temp; 
			//last를 방금 만든 엔트리로 옮겨준다.
            (hdnode[col]->u.next)->down = temp;
			//해당 col의 제일 마지막에다가 지금 엔트리를 연결시켜준다.
            hdnode[col]->u.next= temp; 
			//next를 방금 만든 엔트리로 옮겨준다.
        }
        last->right = hdnode[current_row]; 
		//if문에서 해당 row를 못닫고 나왔으므로 마지막 row를 닫아준다.
        for (i=0; i<num_cols; i++) 
            hdnode[i]->u.next->down = hdnode[i]; 
		//각 헤드의 col쪽의 마지막 엔트리의 down을 헤드로 연결시켜서 col쪽을 닫아준다.
        for (i=0; i<num_heads-1; i++) 
            hdnode[i]->u.next = hdnode[i+1]; 
		//모든 헤드를 next로 연결시켜준다.
        hdnode[num_heads-1]->u.next = node; 
		//마지막 헤드의 next가 node를 가리키게 해준다.
        node->right = hdnode[0];
		//node의 right는 head를 가리킨다.
    } 
    fclose(fp);
    return node;
}

void mwrite(matrix_pointer node) 
{ 
    int i; 
    matrix_pointer temp, head=node->right; 
    FILE* fp = fopen("output.txt","w");
    fprintf(fp,"%d %d %d\n", node->u.entry.row, node->u.entry.col, node->u.entry.value); 
	//row의 개수, col의 개수, 총 node의 개수를 파일에다가 출력해준다.
    for(i=0; i<node->u.entry.row; i++) 
    { 
        for(temp=head->right; temp!=head; temp=temp->right) 
            fprintf(fp,"%d %d %d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
        head = head->u.next; 
    } //node를 하나씩 파일에다가 적어준다.
    fclose(fp);
    return;
}

void merase(matrix_pointer *node) 
{ 
    matrix_pointer x,y, head = (*node)->right; 
    int i; 
    for (i=0; i<(*node)->u.entry.row; i++) 
    { 
        y = head->right; 
        while (y != head) 
        { 
            x = y; 
            y = y->right; 
            free(x); 
        }//해당 row에 있는 엔트리들을 프리시켜준다.
        x = head; 
        head = head->u.next; //헤드를 다음 헤드로 넘거준다.
        free(x); //그러고 이전 헤드를 프리시켜준다.
    } 
    y = head; 
    while (y != *node) 
    { 
        x = y; 
        y = y->u.next; 
        free(x); 
    } //row보다 col이 클 때 남아있는 헤드들을 프리시켜준다.
    free(*node); //노드를 프리시켜준다.
    *node = NULL; 
}

matrix_pointer mtranspose(matrix_pointer nodein)
{
    matrix_pointer nodeout = new_node();
    nodeout->u.entry.row = nodein->u.entry.col;
    nodeout->u.entry.col = nodein->u.entry.row;
    nodeout->u.entry.value = nodein->u.entry.value;
	//nodein에서 nodeout에 넣을 정보를 가져와서 넣어준다.
    int num_rows = nodein->u.entry.col;
    int num_cols = nodein->u.entry.row;
    int num_terms = nodein->u.entry.value;
    int num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	//num_heads의 값을 num_cols과 num_rows중에 큰 값으로 정해준다.
    int i, row, col, value, current_row;
    matrix_pointer temp, last;
    /*nodeout관련 변수*/
    matrix_pointer thead = nodein->right;
    matrix_pointer tentry;
    matrix_pointer tlast = thead;
    
    
    if(!num_heads)
        nodeout->right = nodeout;
	//입력받은 엔트리가 없는 경우를 생각한다.
    else
    {
        thdnode = (matrix_pointer*)malloc(sizeof(matrix_pointer)*num_heads);
        for (i=0; i<num_heads; i++)
        {
            temp = new_node();
            thdnode[i] = temp;
            thdnode[i]->tag = head;
            thdnode[i]->right = temp;
            thdnode[i]->u.next = temp;
        }//헤드를 초기화 시켜준다.
        current_row = 0;
        last = thdnode[0];
        for(i=0; i<num_terms; i++)
        {

         
            tentry = tlast->down;
            if(tentry == thead && tlast != thead)
            {
                thead = thead->u.next;
                tentry = thead;
            }//어느 엔트리에서 down으로 가서 head가 된 경우에 헤드를 다음 헤드로 넘겨준다.
            if(tentry == thead)
            {
                for(; thead->down == thead; thead = thead->u.next);
                tentry = thead->down;
            }//헤드의 down에 연결된 엔트리가 있을 때 정지한다.
            tlast = tentry;
            row = tentry->u.entry.col;
            col = tentry->u.entry.row;
            value = tentry->u.entry.value;
			//그런 엔트리에서 row, col, value를 알아온다.

            if (row > current_row) 
            { 
                last->right = thdnode[current_row]; 
                current_row = row; 
                last = thdnode[row]; 
            } //입력이 row순으로 이뤄지기 때문에 row의 값이 current_row보다 커진다는 것은 지금의 row에서는
			//더이상의 입력이 없다는 뜻이므로 마지막 노드의 right를 헤드에다가 연결시켜줘서 닫아준다.
            temp = new_node(); 
            temp->tag = entry; 
            temp->u.entry.row = row; 
            temp->u.entry.col = col; 
            temp->u.entry.value = value; 
			//새로운 엔트리를 만들어주고 값을 넣어서 초기화 해준다.
            last->right = temp; 
			//해당 row의 제일 마지막에다가 지금 엔트리를 연결시켜준다.
            last = temp; 
			//last를 방금 만든 엔트리로 옮겨준다.
            thdnode[col]->u.next->down = temp; 
			//해당 col의 제일 마지막에다가 지금 엔트리를 연결시켜준다.
            thdnode[col]->u.next= temp; 
			//next를 방금 만든 엔트리로 옮겨준다.
        }
        last->right = thdnode[current_row]; 
		//if문에서 해당 row를 못닫고 나왔으므로 마지막 row를 닫아준다.
        for (i=0; i<num_cols; i++) 
            thdnode[i]->u.next->down = thdnode[i]; 
		//각 헤드의 col쪽의 마지막 엔트리의 down을 헤드로 연결시켜서 col쪽을 닫아준다.
        for (i=0; i<num_heads-1; i++) 
            thdnode[i]->u.next = thdnode[i+1]; 
		//모든 헤드를 next로 연결시켜준다.
        thdnode[num_heads-1]->u.next = nodeout; 
		//마지막 헤드의 next가 node를 가리키게 해준다.
        nodeout->right = thdnode[0];
		//node의 right는 head를 가리킨다.
    } 
    return nodeout;
}             

int main()
{
    matrix_pointer nodein = new_node();
    nodein = mread();
    matrix_pointer nodeout = new_node();
    nodeout = mtranspose(nodein);
    mwrite(nodeout);
    merase(&nodein);
    merase(&nodeout);
    free(hdnode);
    free(thdnode);
    return 0;
}
