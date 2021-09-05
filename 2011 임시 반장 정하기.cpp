#include<stdio.h>

int n, arr[1001][5], max, max_i;
int cnt[1001];
int chk[1001][1001];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 5; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < n; i++) {

			int val = arr[i][j], count = 0;

			for (int k = i + 1; k < n; k++) {
				if (val == arr[k][j] && chk[i][k] == 0) {
					chk[i][k] = 1;
					count++;
					cnt[k]++;
				}
			}
			cnt[i] += count;
		}
	}

	max = cnt[0];
	max_i = 1;
	for (int i = 1; i < n; i++) {
		if (max < cnt[i]) {
			max = cnt[i];
			max_i = i + 1;
		}
	}
	printf("%d\n", max_i);

/* 시간 최적화 코드
* #include <stdio.h>

int main()
{
	int num, i, j, k, c, x, y, result = 0;
	scanf("%d", &num);
	int a[1000][5], b[1000];
	for (c = 0;c < 1000;c++)
	{
		b[c] = 0;
	}
	for (i = 0;i < num;i++)
	{
		scanf("%d %d %d %d %d", &a[i][0], &a[i][1], &a[i][2], &a[i][3], &a[i][4]);
	}
	for (j = 0;j < num;j++)
	{

		for (k = 1;k < num - j;k++)
		{
			if (a[j][0] == a[j + k][0] || a[j][1] == a[j + k][1] || a[j][2] == a[j + k][2] || a[j][3] == a[j + k][3] || a[j][4] == a[j + k][4])
			{
				b[j] += 1;
				b[j + k] += 1;
			}
		}
	}
	for (y = 0;y < num;y++)
	{
		if (b[y] > b[result])
		{
			result = y;
		}
	}
	printf("%d\n", result+1);
}
	/
}
*/
