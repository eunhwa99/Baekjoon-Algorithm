#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 987654321
int N;
int** arr;
int** visit;

void allocate() {
	arr = (int**)malloc(sizeof(int*) * N);
	visit = (int**)malloc(sizeof(int*) * (1 << N));
	
	for (int i = 0; i < N; i++)
	{
		arr[i] = (int*)malloc(sizeof(int) * N);
	}

	for (int i = 0; i < (1 << N); i++)
	{
		visit[i] = (int*)malloc(sizeof(int) * N);
		for (int j = 0; j < N; j++)
			visit[i][j] = -1;
	}
	
}

void input() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &arr[i][j]);
}

int min(int a, int b) {
	return a < b ? a : b;
}

int traverse(int city, int vs) {
	
	if (vs == (1 << N) - 1) {
		if (arr[city][0] > 0) return arr[city][0];
		return INF;
	}
	int& ret = visit[vs][city];

	if (ret != -1) return ret;
	ret = INF;

	int curvs = vs;
	for (int i = 0; i < N; i++) {

		if (curvs & (1 << i) || arr[city][i] == 0) continue; //이미 방문한 도시 or 경로가 없으면
		
			ret = min(traverse(i, vs | (1 << i)) + arr[city][i], ret);

		
	}
	return ret;
}

int main() {
	scanf("%d", &N);
	
	allocate();

	input();
	printf("%d\n",traverse(0, 1));

	for (int i = 0; i < N; i++)
		free(arr[i]);

	for (int i = 0; i < (1 << N); i++)
		free(visit[i]);
	free(arr);
	free(visit);
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