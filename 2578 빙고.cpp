#include<stdio.h>
int map[5][5];
int chk[5][5];
int arr[25]; // 각 숫자별 맵 위의 위치
int bingo[12], count;

int main() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			scanf("%d", &map[i][j]);
			arr[map[i][j]] = i * 5 + j;
		}
	}


	for (int i = 1; i < 26; i++) {
		int a;
		scanf("%d", &a);
		int row = arr[a] / 5;
		int col = arr[a] % 5;
		chk[row][col] = i; // 몇 번째로 그 수가 지워지는지 저장
	}

	int max = 0;
	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 5; j++) {
			if (max < chk[i][j]) max = chk[i][j];
		}
		bingo[count++] = max;
		max = 0;
	}

	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 5; j++) {
			if (max < chk[j][i]) max = chk[j][i];
		}
		bingo[count++] = max;
		max = 0;
	}

	max = 0;
	int y = 0, x = 0;
	while (x < 5 && y < 5) {
		if (max < chk[y][x]) max = chk[y][x];
		x += 1, y += 1;

	}
	bingo[count++] = max;

	max = 0;
	y = 0, x = 4;
	while (x >= 0 && y < 5) {
		if (max < chk[y][x]) max = chk[y][x];
		x -= 1, y += 1;

	}
	bingo[count++] = max;

	for (int i = 0; i < count; i++) {

		for (int j = i + 1; j < count; j++) {
			if (bingo[i] > bingo[j]) {
				int tmp = bingo[i];
				bingo[i] = bingo[j];
				bingo[j] = tmp;
			}
		}
	}

	printf("%d\n", bingo[2]);
}