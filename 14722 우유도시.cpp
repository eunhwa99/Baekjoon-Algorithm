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
	if (arr[r][c] == 0) { //���� ��ġ�� ����
		if (pre == 3 || pre == 2) {
			
			// ���ô� ���
			tmp = max_(solve(r + 1, c, arr[r][c]), solve(r, c + 1, arr[r][c])) + 1;
		}
		//�ȸ��ô� ���
		tmp2 = max_(solve(r + 1, c, pre), solve(r, c + 1, pre));
		dp[r][c][pre] = max_(tmp, tmp2);
	}
	else if (arr[r][c] == 1) { //����
		if (pre == 0) {
			tmp = max_(solve(r + 1, c, arr[r][c]), solve(r, c + 1, arr[r][c])) + 1;
		}
		//�ȸ��ô� ���
		tmp2 = max_(solve(r + 1, c, pre), solve(r, c + 1, pre));
		dp[r][c][pre] = max_(tmp, tmp2);
	}
	else if (arr[r][c] == 2) { //�ٳ���
		if (pre == 1) {
			tmp = max_(solve(r + 1, c, arr[r][c]), solve(r, c + 1, arr[r][c])) + 1;
		}
		//�ȸ��ô� ���
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