#include<stdio.h>
#include<stdlib.h>
// 9465 ��ƼĿ
// ����: cache[i][j]: (i,j) ��ƼĿ�� �� ���!! �밢��, �밢�� ���� ���� �� �� �ִ�.
int T, n;
int* arr[2];
int* cache[2];
int getMax(int a, int b) {
	return a > b ? a : b;
}
int getSum(int y, int x) { //y�� ��, x�� ��
	if (x >= n) return 0;

	int& ret = cache[y][x];
	if (ret != -1) return ret;
	//ret = 0;
	if (y == 1) {
		ret = getMax(getSum(y - 1, x + 1), getSum(y - 1, x + 2)) + arr[y][x];
		//ret = getMax(ret, getSum(y, x + 1));
	}
	else {
		ret = getMax(getSum(y + 1, x + 1), getSum(y + 1, x + 2)) + arr[y][x];
	}

	return ret;
}

int main() {
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		scanf("%d", &n);

		for (int i = 0; i < 2; i++) {
			arr[i] = (int*)malloc(sizeof(int) * n);
			cache[i] = (int*)malloc(sizeof(int) * n);

			for (int j = 0; j < n; j++) {
				scanf("%d", &arr[i][j]);
				cache[i][j] = -1;
			}
			
		}

		int a = getSum(0, 0);
		int b = getSum(1, 0);

		printf("%d\n", getMax(a,b));


		for (int i = 0; i < 2; i++)
			free(arr[i]), free(cache[i]);
	}
}