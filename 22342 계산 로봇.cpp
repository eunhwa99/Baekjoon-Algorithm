#include<stdio.h>

int M, N, maxval;
int map[2001][2001]; //D
int cache[2001][2001]; //��°�
int dy[] = { 1,-1,0 }; //��
int dx[] = { 1,1,1 }; //��

//�� ĭ���� ������ �� �� �ִ� ĭ�� �ڽ��� ��°��� ������ ���´�.
//�ε���� �����ϴ� ĭ --> ��ĭ�� �������� ���� �� �밢���� ������ �Ʒ� �밢�� ����(�밢���� ����)
//���� �� ĭ���� ������ �ִ� ���� ������ �Ʒ�, ������, ���� ��.

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

	for (int j = 0; j < N; j++) { //��
		for (int i = 0; i < M; i++) { //��
			//print();
			cache[i][j] = cache[i][j] + map[i][j]; 
			if (maxval < cache[i][j]-map[i][j]) maxval = cache[i][j] - map[i][j];

			for (int d = 0; d < 3; d++) {
				int ny = i + dy[d], nx = j + dx[d];
				if (0 > ny || ny >= M || 0 > nx || nx >= N) continue; //���� ��
				if (cache[ny][nx] < cache[i][j]) cache[ny][nx] = cache[i][j];
			}
		}
	}

	printf("%d\n", maxval);
}