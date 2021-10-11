#include<stdio.h>

int N;
int arr[1001][1001];
int dp[1001][1001][4];

int max_(int a, int b) {
	return a > b ? a : b;
}

int solve(int r, int c, int pre) {
	if (r >= N || c >= N || r < 0 || c < 0) return 0;

	if (dp[r][c][pre] != -1) return dp[r][c][pre];

	int tmp = 0, tmp2 = 0;
	if (arr[r][c] == 0) { //현재 위치가 딸기
		if (pre == 3 || pre == 2) {
			
			// 마시는 경우
			tmp = max_(solve(r + 1, c, arr[r][c]), solve(r, c + 1, arr[r][c])) + 1;
		}
		//안마시는 경우
		tmp2 = max_(solve(r + 1, c, pre), solve(r, c + 1, pre));
		dp[r][c][pre] = max_(tmp, tmp2);
	}
	else if (arr[r][c] == 1) { //초코
		if (pre == 0) {
			tmp = max_(solve(r + 1, c, arr[r][c]), solve(r, c + 1, arr[r][c])) + 1;
		}
		//안마시는 경우
		tmp2 = max_(solve(r + 1, c, pre), solve(r, c + 1, pre));
		dp[r][c][pre] = max_(tmp, tmp2);
	}
	else if (arr[r][c] == 2) { //바나나
		if (pre == 1) {
			tmp = max_(solve(r + 1, c, arr[r][c]), solve(r, c + 1, arr[r][c])) + 1;
		}
		//안마시는 경우
		tmp2 = max_(solve(r + 1, c, pre), solve(r, c + 1, pre));
		dp[r][c][pre] = max_(tmp, tmp2);
	}

	return dp[r][c][pre];

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
			for (int k = 0; k < 4; k++) dp[i][j][k] = -1;
		}
	}
	printf("%d\n", solve(0, 0, 3));
}