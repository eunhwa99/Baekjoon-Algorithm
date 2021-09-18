#include<stdio.h>
#include<stdlib.h>
int n;
int** arr;
int** cache;
int getMax(int a, int b) {
	return a > b ? a : b;
}
int getSum(int y, int x) {
	//기저사례
	if (y >= n || x > y) return 0;

	int& ret = cache[y][x];
	if (ret != -1) return ret;

	return ret = getMax(getSum(y + 1, x), getSum(y + 1, x + 1)) + arr[y][x];
}

int main() {
	scanf("%d", &n);

	arr = (int**)malloc(sizeof(int*) * n);
	cache = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * (i + 1));
		cache[i] = (int*)malloc(sizeof(int) * (i + 1));

		for (int j = 0; j < i + 1; j++) {
			scanf("%d", &arr[i][j]);
			cache[i][j] = -1; // 초기화
		}
	}

	printf("%d\n", getSum(0, 0));

	for (int i = 0; i < n; i++) {
		free(arr[i]);
		free(cache[i]);
	}
	free(arr);
	free(cache);

}
/*
* #include<stdio.h>
#include<stdlib.h>
int n, tmp;
int* arr;
int* cache;
int getMax(int a, int b) {
	return a > b ? a : b;
}

int main() {
	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int) * n);
	cache = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		if (i == 0) {
			scanf("%d", &arr[i]);
			cache[i] = arr[i];
			continue;
		}

		for (int j = 0; j <= i; j++) {
			scanf("%d", &tmp);

			if (j == 0) cache[j] = tmp + arr[0]; //바로 위에꺼 더하기
			else if (j == i) cache[j] = tmp + arr[j-1]; // 가장 오른쪽 성분일 때: 왼쪽위 대각선하고만 더할 수 있다.
			else cache[j] = tmp + getMax(arr[j], arr[j - 1]);
		}
		for (int j = 0; j <= i; j++)
			arr[j] = cache[j]; //arr 삼각형 바로 업데이트
	}
	
	tmp = arr[0];
	for (int i = 1; i < n; i++)
		tmp = getMax(tmp, arr[i]);

	printf("%d\n", tmp);
	free(arr);
	free(cache);
}
*/
