#include<stdio.h>
#include<string.h>
int R, C, Y, X, len, boxNum, test, total;
char map[16][16];
char arr[51];
int dx[] = { 1,0,-1,0 }; 
int dy[] = { 0,1,0,-1 }; //오, 아, 왼, 위

int check(int y, int x, int dirInt) {
	int nx, ny;
	if (map[y][x] == '#') {
		return 0; //이동 X
	}
	else if (map[y][x] == 'b' || map[y][x] == 'B') {
		ny = y + dy[dirInt], nx = x + dx[dirInt];
		if (map[ny][nx] == '#' || map[ny][nx] == 'B' || map[ny][nx] == 'b') return 0; //이동 X
		
		if (map[y][x] == 'b') map[y][x] = '.';
		else if (map[y][x] == 'B') map[y][x] = '+', boxNum--;

		if (map[ny][nx] == '+') map[ny][nx] = 'B', boxNum++; //목표지점 옮긴 박스 수 감소
		else if (map[ny][nx] == '.') map[ny][nx] = 'b';
	}
	
	return 1;
}

int solve() {
	int cy = Y, cx = X;
	int nx = 0, ny = 0, dirInt;

	for (int i = 0; i < len; i++) {
		char dir = arr[i];
		switch (dir) {
		case 'U':
			dirInt = 3;
			break;
		case 'D':
			dirInt = 1;
			break;
		case 'L':
			dirInt = 2;
			break;
		case 'R':
			dirInt = 0;
			break;
		}
		nx = cx + dx[dirInt], ny = cy + dy[dirInt];
		if (check(ny, nx, dirInt)) {
			cx = nx, cy = ny; //이동
		}
		Y = cy, X = cx;
		if (boxNum == total) {
			
			return 1;
		}
	}
	//Y = cy, X = cx;
	return 0;
}

void printMap() {
	if (map[Y][X] == '+') map[Y][X] = 'W';
	else map[Y][X] = 'w';
	
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%c", map[i][j]);
		}
		puts("");
	}
}

int main() {
	while (1) {
		test++;
		scanf("%d%d", &R, &C);
		boxNum = total= 0;

		if (R == 0 && C == 0) {
			break;
		}
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf(" %c", &map[i][j]);
				if (map[i][j] == 'w' || map[i][j] == 'W') { 
					Y = i, X = j;
					if (map[i][j] == 'w') map[i][j] = '.';
					else map[i][j] = '+';
				}
				else if (map[i][j] == 'b') total++;
				else if (map[i][j] == 'B') total++, boxNum++;
			}
		}
		scanf("%s", arr);
		len = strlen(arr);

		printf("Game %d: %s\n", test, solve() ? "complete" : "incomplete");
		printMap();
	}
	return 0;
}