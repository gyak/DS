#include <stdio.h>
#include <string.h>
#define max_string_size 100
#define max_pattern_size 100
int failure[max_pattern_size];
char string[max_string_size];
char pat[max_pattern_size];

int pmatch(char* string, char* pat, int check)
{
    int i=check, j=0;
	//check의 값에 의해 매칭을 하는 문자열의 시작위치가 바뀐다. 
    int lens = strlen(string);
    int lenp = strlen(pat);
    while(i < lens && j < lenp)//i와 j가 범위를 벗어나지 못하게 하는 조건이다.
    {
        if(string[i]==pat[j])
        {
            i++;
            j++;
        }
        else if(j==0)//스트링과 패턴의 첫 원소가 일치할때까지 i를 1씩 키워가면서 비교한다.
            i++;
        else
            j = failure[j-1]+1;
		//j가 0이 아니고 패턴과 다를 때 바로 직전의 j값에 해당하는 failure 원소가 가리키는 위치로 j를 보낸다.
    }
    return ((j==lenp)?(i-lenp):-1);
	//반복문이 끝이 났을 때 j와 lenp가 같으면 현재의 i값에서 패턴의 길이만큼 뒤로간 값을 리턴하니까 패턴과 일치하는 시작위치를 알려주게 된다.
	//만약 j와 lenp가 다르다면 패턴과 끝까지 일치하지 못한 채로 스트링의 범위를 벗어났다는 것이므로 -1을 리턴해준다.
}

void fail(char* pat)
{
    int i,j, n=strlen(pat);
    failure[0] = -1;
    for(j=1; j<n; j++:)
    {
        i = failure[j-1];//i의 값을 바로 직전의 failure의 원소의 값으로 초기화 해준다.
        while((pat[j]!=pat[i+1]) && (i >= 0))
            i = failure[i];//패턴의 j,i+1번째 원소가 일치하거나 i가 0보다 작아질때까지 failure를 타고 진행한다.
        if(pat[j] == pat[i+1])
            failure[j] = i+1;//패턴의 j,i+1번째 원소가 일치하면 failure[j]의 값을 바로 전 값보다 1크게 넣어준다.
        else 
            failure[j] = -1;//i가 0보다 작다면 failure를 -1로 넣어준다.
    }
}

int main()
{
    char string[max_string_size], pat[max_pattern_size],i,check=0;
    int arr[max_string_size]={0};
	//arr이라는 배열의 원소를 전부다 0으로 초기화 시킨다.
    scanf("%s",string);
    scanf("%s",pat);
    fail(pat);
    for(i=0; i<strlen(string); i++)
        arr[pmatch(string,pat,i)]++;
	//포문 안에서 i의 값에 의해 매칭을 하는 문자열의 시작위치가 바뀐다. 
	//예를들어 i가 0일 때는 처음부터 시작하고 i가 2일 때는 string[2]부터 문자열이 시작된다.
	//그리고 pmatch에 의해서 문자열에서 패턴과 처음 일치하는 위치가 리턴되는데 그 리턴 값에 해당하는 arr원소를 1씩 더해준다.
    for(i=0; i<strlen(string); i++)
    {
        if(arr[i]>=1)//arr의 원소 값이 1보다 크거나 같으면 그때의 i 값을 출력해준다.
            printf("%d\n",i);    
    }
    return 0;   
}
