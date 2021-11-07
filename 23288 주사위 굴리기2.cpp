#include<stdio.h>

int N, M, K;
int map[21][21];
int score[21][21];
int dice[6];
int cnt, dir, total;
int dy[] = { 1,0,-1,0 }; //아래, 오른쪽, 위, 왼쪽
int dx[] = { 0,1,0,-1 };

void dfs(int y, int x) {
	score[y][x] = map[y][x];
	cnt++;

	for (int d = 0; d < 4; d++) {
		int ny = y + dy[d];
		int nx = x + dx[d];
		if (0 > ny || ny >= N || 0 > nx || nx >= M) continue;
		if (score[ny][nx] || map[ny][nx] != map[y][x]) continue;
		dfs(ny, nx);
	}
	//score[y][x] *= cnt;
}

void scoredfs(int y, int x) {
	score[y][x] *= cnt;

	for (int d = 0; d < 4; d++) {
		int ny = y + dy[d];
		int nx = x + dx[d];
		if (0 > ny || ny >= N || 0 > nx || nx >= M) continue;
		if (map[ny][nx] == map[y][x] && score[ny][nx] == map[ny][nx])
			scoredfs(ny, nx);
	}
}

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d ", score[i][j]);
		}
		puts(" ");
	}
}

void rolldice(int direction) {
	int tmp = dice[0];
	if (direction == 0) { //아래
		dice[0] = dice[4];
		dice[4] = dice[2];
		dice[2] = dice[5];
		dice[5] = tmp;
	}
	else if (direction == 1) { //오른쪽
		dice[0] = dice[3];
		dice[3] = dice[2];
		dice[2] = dice[1];
		dice[1] = tmp;
	}
	else if (direction == 2) { //위
	
		dice[0] = dice[5];
		dice[5] = dice[2];
		dice[2] = dice[4];
		dice[4] = tmp;
	}
	else { //왼쪽
		dice[0] = dice[1];
		dice[1] = dice[2];
		dice[2] = dice[3];
		dice[3] = tmp;
	}
}
int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	dice[0] = 1, dice[1] = 3, dice[2] = 6, dice[3] = 4, dice[4] = 2, dice[5] = 5;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (score[i][j] == 0) {
				cnt = 0;
				dfs(i, j);
				scoredfs(i, j);
			}
		}
	}
	//print();

	dir = 1; //오른쪽
	int cy = 0, cx = 0; // 처음 위치
	for (int t = 0; t < K; t++) {
		int ny = cy + dy[dir];
		int nx = cx + dx[dir];
		if (0 > ny || ny >= N || 0 > nx || nx >= M) {
			dir = (dir + 2) % 4;
			ny = cy + dy[dir], nx = cx + dx[dir];
		}
		cy = ny, cx = nx;
		rolldice(dir);
		total += score[cy][cx];

		if (dice[2] > map[cy][cx]) {
			dir = (dir + 3) % 4;
		}
		else if (dice[2] < map[cy][cx]) {
			dir = (dir + 1) % 4;
		}
	
	}

	printf("%d\n", total);
}