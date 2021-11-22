#include<stdio.h>
int N, arr[26][3];
int dp[26][2];

int big(int a, int b) {
	return a > b ? a : b;
}

int solve(int cur, int end) {
	if (cur >= N) return 0;
	if (dp[cur][0] != -1 && dp[cur][1] != -1) return big(dp[cur][1], dp[cur][0]);


	//회의 참여
	if (dp[cur][0] == -1) {
			dp[cur][0] = arr[cur][2] + solve(cur + 2, arr[cur][1]);
	}

	if (dp[cur][1] == -1) {
		dp[cur][1] = big(dp[cur][1], solve(cur + 1, end));
	}

	return big(dp[cur][1], dp[cur][0]);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &arr[i][j]);
		}
		dp[i][0] = dp[i][1] = -1;
	}

	printf("%d\n", solve(0, 0));
}