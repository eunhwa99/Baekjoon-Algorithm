// 온풍기 맵:map
// 바람 퍼지는 맵: wind, temp
// 벽 표시: wall[x][y][0], wall[x][y][1]
//0: 오, 1: 왼: 2: 위, 3: 아래, 5: 조사(checkTemp)
//cnt: 온풍기 개수, choco: 먹은 초콜릿 개수
// 코드 최적화: dfs 최초 1번만 돌도록 상태 temp2에 저장 --> 0ms로 줄임
// 실수 부분: 가장자리 1씩 감소할 때 2번째 for 문에서 중복으로 감소시킴, 0 부터가 아닌 1열부터 C-2열까지 해야함
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
mystruct machine[400]; //온풍기 위치 및 방향

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
	//t가 0인 경우 (y, x)와 (y-1, x) 사이에 벽
	//t가 1인 경우에는 (y, x)와 (y, x+1) 사이에 벽이 있는 것이다.
	//오: (y,x),(y-1,x)&&(y-1,x),(y-1,x+1)//(y,x),(y,x+1) //(y,x),(y+1,x)&&(y+1,x),(y+1,x+1)
	//왼: (y,x), (y-1,x)&&(y-1,x),(y-1,x-1)//(y,x),(y,x-1)//(y,x)와 (y+1,x)&&(y+1,x),(y+1,x-1)
	//아: (y,x),(y,x-1)&&(y,x-1),(y+1,x-1) //(y,x),(y+1,x)//(y,x),(y,x+1)&&(y,x+1),(y+1,x+1)
	//위: (y,x),(y,x-1)&&(y,x-1),(y-1,x-1)//(y,x),(y-1,x)//(y,x),(y,x+1)&&(y,x+1),(y-1,x+1)
	if (amount == 0) return;

	vs[y][x] = 1;
	temp2[y][x] += amount;

	int ny, nx;

	if (direction == 0) {
		//동 (y,x),(y-1,x)&&(y-1,x),(y-1,x+1)//(y,x),(y,x+1) //(y,x),(y+1,x)&&(y+1,x),(y+1,x+1)
		ny = y - 1, nx = x + 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][0] == 0 && wall[y - 1][x][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		//동
		ny = y, nx = x + 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		//동 
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
			//서  (y,x), (y-1,x)&&(y-1,x),(y-1,x-1)//(y,x),(y,x-1)//(y,x)와 (y+1,x)&&(y+1,x),(y+1,x-1)
		ny = y - 1, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x][0] == 0 && wall[y - 1][x - 1][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
		//서 (y,x),(y,x-1)
		ny = y, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y][x - 1][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}

		//서 (y,x)와 (y+1,x)&&(y+1,x),(y+1,x-1)
		ny = y + 1, nx = x - 1;
		if (rangeCheck(ny, nx)) {
			if (wall[y + 1][x][0] == 0 && wall[y + 1][x - 1][1] == 0) {
				if (vs[ny][nx] == 0) {
					dfs(ny, nx, amount - 1, direction);
				}
			}
		}
	}
	else if (direction == 2) { //북
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
	else { //남
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

void step1(int status) { // 바람이 나온다
	if (status == 0) { //dfs 1번만 돌도록
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
void step2() { //온도가 조절된다..

	memcpy(temp, wind, sizeof(temp));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			for (int d = 0; d < 3; d += 2) {
				int ny = i + dy[d], nx = j + dx[d];
				int amount = 0;
				if (rangeCheck(ny, nx)) {
					amount = abs(wind[i][j] - wind[ny][nx]) / 4;
					if (d == 0) { //오른쪽 벽확인
						if (wall[i][j][1]) continue;
					}
					else if (d == 2) { //위쪽 벽 확인
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
