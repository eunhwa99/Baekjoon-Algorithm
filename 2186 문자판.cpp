#include<stdio.h>
#include<string.h>
int N, M, K, len, flag;
int dp[101][101][85], count;
char map[101][101];
int arr['Z' - 'A' + 1][10001];
int cnt['Z' - 'A' + 1];
char str[85];

int abs(int a, int b) {
	return a > b ? a - b : b - a;
}

int getCount(int y, int x, int num) {
	if (flag) return 0; //flag 변수 안넣으면 시간초과
	if (num == len) return 1;

	int& ret = dp[y][x][num];
	if (ret != -1) return ret;
	ret = 0;

	int next = str[num]-'A';
	if (cnt[next] == 0) flag = 1;

	for (int i = 0; i < cnt[next]; i++) { //여기서 최대 10000개를 탐색하므로 flag 변수 넣기
		//flag 안 사용하려면 현재 정점에서 K이하 만큼 이동시켜서 탐색
		int ny = arr[next][i] / M; 
		int nx = arr[next][i] % M;

		if ((ny != y && nx != x) || (ny == y && nx == x)) continue; // 대각선
		if (abs(ny, y) + abs(nx, x) > K) continue;
		ret += getCount(ny, nx, num + 1);
	} 
	return ret;
}

int main() {
	scanf("%d%d%d", &N, &M, &K);

	memset(dp, -1, sizeof(dp));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %c", &map[i][j]);
			arr[map[i][j] - 'A'][cnt[map[i][j]-'A']++] = i * M + j;
			
		}
	}

	scanf("%s", str);
	len = strlen(str);
	int ans = 0;
	
	int next = str[0] - 'A';
	for (int i = 0; i < cnt[next]; i++) {
		int ny = arr[next][i] / M;
		int nx = arr[next][i] % M;

		ans += getCount(ny, nx, 1);
	}
	printf("%d\n", ans);
}
