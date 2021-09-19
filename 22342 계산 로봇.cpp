#include<stdio.h>

int M, N, maxval;
int map[2001][2001]; //D
int cache[2001][2001]; //출력값
int dy[] = { 1,-1,0 }; //행
int dx[] = { 1,1,1 }; //열

//각 칸에서 영향을 줄 수 있는 칸에 자신의 출력값을 저장해 놓는다.
//부등식을 만족하는 칸 --> 별칸을 기준으로 왼쪽 위 대각선과 오른쪽 아래 대각선 사이(대각선도 포함)
//따라서 각 칸에서 영향을 주는 곳은 오른쪽 아래, 오른쪽, 왼쪽 위.

void print() {
	puts("");
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d", cache[i][j]);
		}
		puts("");
	}
}

int main() {
	scanf("%d%d", &M, &N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &map[i][j]);
		}
	}

	for (int j = 0; j < N; j++) { //열
		for (int i = 0; i < M; i++) { //행
			//print();
			cache[i][j] = cache[i][j] + map[i][j]; 
			if (maxval < cache[i][j]-map[i][j]) maxval = cache[i][j] - map[i][j];

			for (int d = 0; d < 3; d++) {
				int ny = i + dy[d], nx = j + dx[d];
				if (0 > ny || ny >= M || 0 > nx || nx >= N) continue; //범위 밖
				if (cache[ny][nx] < cache[i][j]) cache[ny][nx] = cache[i][j];
			}
		}
	}

	printf("%d\n", maxval);
}