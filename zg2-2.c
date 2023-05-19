#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_array(int* arr, int n)
{
    int i, change=0, youngil=0;
    int* check=(int*)calloc(2*n-1, sizeof(int));
    for(i=0; i<n; i++)
    {
        if(arr[i]-arr[0]+(n-1)<0 || arr[i]-arr[0]+(n-1)>2*n-2)
            return 0;
		//배열의 첫 원소를 기준으로 가운데에 n-1번째에 딱 오게 만들었을 때, 그때쓰는 알고리즘이 arr[0]-arr[0]+(n-1)이다.
		//이와같은 방법으로 다른 원소들도 check[2*n-1]이라는 배열에 연결시켜주는데
		//그중에 0보다 작거나 2*n-1보다 크거나 같은 원소가 있는 경우는 연속적으로는 나올 수가 없으니까 바로 0을 리턴 해준다.
        check[arr[i]-arr[0]+(n-1)]++;
		//그러고 그러히 않은 경우에는 check배열에 해당하는 곳의 값을 1 더해준다. 
    }
    for(i=0; i<2*n-1; i++)
    {
        if(check[i]>1)
            return 0;
		//check[i]가 1이 넘는다는 것은 중복된 것이 나왔다는 뜻이므로 0을 리턴해준다.
        if(check[i]==1 && youngil==0)
        {
            change++;
            youngil=1;
        } 
        if(check[i]==0 && youngil==1)
            youngil=0;
    }//check의 값이 0에서 1로 넘어갈 때에만 change를 1 더해준다.
    free(check);
    if(change==1)
        return 1;
    else
        return 0;
	//change값이 1인 경우만 숫자가 연속적이라는 뜻이므로 1을 리턴해주고 나머지 경우에는 0을 리턴한다.
}

int main()
{
    int i,n;
    scanf("%d",&n);
    int* arr=(int*)malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
        scanf("%d",arr+i);
    printf("%d\n",check_array(arr,n));
    free(arr);
    return 0;
}
