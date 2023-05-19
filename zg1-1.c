#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partition(char str[][19], int n, int gesu, int num)
{
	int j;
	if (n == 1)
		return 0;
	for (j = 0; j < gesu / 2; j++)
		*(*(str + j) + num) = '/';
	partition(str, n - 1, gesu / 2, num + 2);
	partition(str + gesu / 2, n - 1, gesu / 2, num + 2);
	return 0;
}

int main()
{
	int gesu = 1, n, i, j, k;
	char str[512][19];
	for (j = 0; j < 512; j++)
		for (i = 0; i < 19; i++)
			str[j][i] = 'a';
	char string[10];
	scanf("%10s", string);
	for (n = strlen(string); n >= 2; n--)
		gesu = gesu * 2;
	n = strlen(string);
	for (j = 0; j <= gesu; j++)
		for (i = 0, k = 0; i <= 2 * n - 2; i = i + 2, k++)
			*(*(str + j) + i) = *(string + k);
	partition(str, n, gesu, 1);
	for (j = 0; j < gesu; j++)
	{
		for (i = 0; i < 2 * n - 1; i++)
			if (str[j][i] != 'a')
		    	printf("%c", str[j][i]);
		printf("\n");
	}
	return 0;
}
