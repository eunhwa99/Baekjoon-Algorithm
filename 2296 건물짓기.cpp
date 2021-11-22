#include<stdio.h>
int N;
int arr[1001][3];
int dp[1001][2];
int big(int a, int b) {
	return a > b ? a : b;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d%d", &arr[i][0], &arr[i][1], &arr[i][2]);
		
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N-(i+1); j++) {
			if (arr[j][0] > arr[j+1][0]) {
				int tmp[3];
				tmp[0] = arr[j][0], tmp[1] = arr[j][1], tmp[2] = arr[j][2];
				for (int k = 0; k < 3; k++) {
					arr[j][k] = arr[j+1][k];
					arr[j+1][k] = tmp[k];
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		dp[i][0] = dp[i][1] = arr[i][2];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[i][1] > arr[j][1]) {
				dp[i][0] = big(dp[i][0], arr[i][2] + dp[j][0]);
			}
			if (arr[i][1] < arr[j][1]) {
				dp[i][1] = big(dp[i][1], arr[i][2] + dp[j][1]);
			}
		}
	}

	int max = 0;
	for (int i = 0; i < N; i++) {	
		max = big(max, dp[i][0]);
		max = big(max, dp[i][1]);
	}

	printf("%d\n", max);
}