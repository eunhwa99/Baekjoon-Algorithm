// ��ǳ�� ��:map
// �ٶ� ������ ��: wind, temp
// �� ǥ��: wall[x][y][0], wall[x][y][1]
//0: ��, 1: ��: 2: ��, 3: �Ʒ�, 5: ����(checkTemp)
//cnt: ��ǳ�� ����, choco: ���� ���ݸ� ����
// �ڵ� ����ȭ: dfs ���� 1���� ������ ���� temp2�� ���� --> 0ms�� ����
// �Ǽ� �κ�: �����ڸ� 1�� ������ �� 2��° for ������ �ߺ����� ���ҽ�Ŵ, 0 ���Ͱ� �ƴ� 1������ C-2������ �ؾ���
#include<stdio.h>
#include<string.h>
int R, C, K, W, cnt, choco;
int map[21][21], wind[21][21], temp[21][21], wall[21][21][2], temp2[21][21];
int vs[21][21];
int dy[] = { 0,0,-1,1 };
int dx[] = { 1,-1,0,0 }; 

typedef struct mystruct {
	int y, x, dir;
}mystruct;
mystruct machine[400]; //��ǳ�� ��ġ �� ����

void print() {
	puts("");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", wind[i][j]);
		}
		puts(" ");
	}
}

int checkTemp() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == 5) {
				if (wind[i][j] < K) return 0;
			}
		}
	}
	return 1;
}

int rangeCheck(int y, int x) {
	if (y < 0 || y >= R || x < 0 || x >= C) return 0;
	return 1;
}


void dfs(int y, int x, int amount, int direction) {
	//t�� 0�� ��� (y, x)�� (y-1, x) ���̿� ��
	//t�� 1�� ��쿡�� (y, x)�� (y, x+1) ���̿� ���� �ִ� ���̴�.
	//��: (y,x),(y-1,x)&&(y-1,x),(y-1,x+1)//(y,x),(y,x+1) //(y,x),(y+1,x)&&(y+1,x),(y+1,x+1)
	//��: (y,x), (y-1,x)&&(y-1,x),(y-1,x-1)//(y,x),(y,x-1)//(y,x)�� (y+1,x)&&(y+1,x),(y+1,x-1)
	//��: (y,x),(y,x-1)&&(y,x-1),(y+1,x-1) //(y,x),(y+1,x)//(y,x),(y,x+1)&&(y,x+1),(y+1,x+1)
	//��: (y,x),(y,x-1)&&(y,x-1),(y-1,x-1)//(y,x),(y-1,x)//(y,x),(y,x+1)&&(y,x+1),(y-1,x+1)
	if (amount == 0) return;

	vs[y][x] = 1;
	temp2[y][x] += amount;

	int ny, nx;

	if (direction == 0) {
		//�� (y,x),(y-1,x)&&(y-1,x),(y-1,x+1)//(y,x),(y,x+1) //(y,x),(y+1,x)&&(y+1,x),(y+1,x+1)
		ny = y - 1, nx = x + 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][0] == 0 && wall[y - 1][x][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		//��
		ny = y, nx = x + 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		//�� 
		ny = y + 1, nx = x + 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y + 1][x][0] == 0 && wall[y + 1][x][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
	}
	else if (direction == 1) {
			//��  (y,x), (y-1,x)&&(y-1,x),(y-1,x-1)//(y,x),(y,x-1)//(y,x)�� (y+1,x)&&(y+1,x),(y+1,x-1)
		ny = y - 1, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][0] == 0 && wall[y - 1][x - 1][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		//�� (y,x),(y,x-1)
		ny = y, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x - 1][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}

		//�� (y,x)�� (y+1,x)&&(y+1,x),(y+1,x-1)
		ny = y + 1, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y + 1][x][0] == 0 && wall[y + 1][x - 1][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
	}
	else if (direction == 2) { //��
		//(y, x), (y, x - 1) && (y, x - 1), (y - 1, x - 1)//(y,x),(y-1,x)//(y,x),(y,x+1)&&(y,x+1),(y-1,x+1)
		ny = y - 1, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x-1][1] == 0 && wall[y][x - 1][0] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		ny = y - 1, nx = x;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][0] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		ny = y - 1, nx = x + 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][1] == 0 && wall[y][x + 1][0] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
	}
	else { //��
		// (y,x),(y,x-1)&&(y,x-1),(y+1,x-1) //(y,x),(y+1,x)//(y,x),(y,x+1)&&(y,x+1),(y+1,x+1)
		ny = y + 1, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x - 1][1] == 0 && wall[y + 1][x - 1][0] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		ny = y + 1, nx = x;
		if (rangeCheck(ny, nx)) {
			if (wall[y + 1][x][0] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		ny = y + 1, nx = x + 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][1] == 0 && wall[y + 1][x + 1][0] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
	}

}

void step1(int status) { // �ٶ��� ���´�
	if (status == 0) { //dfs 1���� ������
		for (int t = 0; t < cnt; t++) {
			int cy = machine[t].y, cx = machine[t].x, cdir = machine[t].dir;
			int ny = cy + dy[cdir], nx = cx + dx[cdir];
			memset(vs, 0, sizeof(vs));
			dfs(ny, nx, 5, cdir);
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			wind[i][j] += temp2[i][j];
		}
	}

}

int abs(int a) {
	return a > 0 ? a : -a;
}
void step2() { //�µ��� �����ȴ�..

	memcpy(temp, wind, sizeof(temp));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			for (int d = 0; d < 3; d += 2) {
				int ny = i + dy[d], nx = j + dx[d];
				int amount = 0;
				if (rangeCheck(ny, nx)) {
					amount = abs(wind[i][j] - wind[ny][nx]) / 4;
					if (d == 0) { //������ ��Ȯ��
						if (wall[i][j][1]) continue;
					}
					else if (d == 2) { //���� �� Ȯ��
						if (wall[i][j][0]) continue;
					}
					if (wind[i][j] > wind[ny][nx])
					{
						temp[ny][nx] += amount;
						temp[i][j] -= amount;
					}
					else {
						temp[ny][nx] -= amount;
						temp[i][j] += amount;
					}
				}
			}
		}
	}

	memcpy(wind, temp, sizeof(temp));
}

void step3() {

	for (int i = 0; i < R; i++) {
		
		if (wind[i][0] > 0) 
			wind[i][0] -= 1;
		if (wind[i][C - 1] > 0)
			wind[i][C - 1] -= 1;
	}

	for (int j = 1; j < C - 1; j++) {
		if (wind[0][j] > 0)
			wind[0][j] -= 1;
		if (wind[R - 1][j] > 0)
			wind[R - 1][j] -= 1;
	}

	choco++;

}

int main() {
	scanf("%d%d%d", &R, &C, &K);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &map[i][j]);
			if (1 <= map[i][j] && map[i][j] <= 4) {
				machine[cnt++] = { i,j,map[i][j] - 1 };
			}
		}
	}

	scanf("%d", &W);
	for (int i = 0; i < W; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		wall[a - 1][b - 1][c] = 1;
	}
	while (1) {
		step1(choco);
		//print();
		step2();
		//print();
		step3();
		//print();
		if (checkTemp()) break;
		if (choco > 100) {
			choco = 101;
			break;
		}
	}

	
	printf("%d\n", choco);
}
