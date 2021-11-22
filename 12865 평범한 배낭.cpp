#include<stdio.h>
#include<string.h>
int N, K;
int arr[101][2];
int dp[101][100002];

//회의실 배정 문제는 순서대로 나열 되어 있기 때문에 포함할지 안할지만 결정하면 되는데
//이 문제는 어떤 순서로 포함하냐에 따라 결과가 달라지기 때문에 단순이 dp[][2]가 아니라
//weight 별로 따로 계산해주어야 함.
int big(int a, int b) {
	return a > b ? a : b;
}
int solve(int cur, int weight) {
	if (cur >= N) return 0;
	if (weight >= K) return 0;
	if (dp[cur][weight] != -1) return dp[cur][weight];

	
	if (weight + arr[cur][0] <= K) {
			dp[cur][weight] = solve(cur + 1, weight + arr[cur][0]) + arr[cur][1];
	}
	dp[cur][weight] = big(dp[cur][weight], solve(cur + 1, weight));

	return dp[cur][weight];
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
		//dp[i][0] = dp[i][1] = -1;
	}

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(0, 0));


}