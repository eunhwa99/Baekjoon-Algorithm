#include<stdio.h>
#include<string.h>
int N, minV = -1, val;
int map[15][5];
int arr[4];
int chk[15];
int idxV[16]; // 답 

void change(int cnt) {
	memset(idxV, 0, sizeof(idxV));
	for (int i = 0; i < cnt; i++)
		idxV[i] = chk[i];
}

void solve(int idx, int cnt, int a, int b, int c, int d, int cost) {

	if (a >= arr[0] && b >= arr[1] && c >= arr[2] && d >= arr[3]) {
		
			if (minV == -1 || minV > cost) {
				minV = cost;
				change(cnt);
			}
			else if (minV == cost) {
				int flag = 0;
				for (int i = 0; i < cnt; i++) {
					if (idxV[i] > chk[i]) {
						flag = 1; break;
					}
					else if (idxV[i] < chk[i]) {
						flag = -1;
						break;
					}
				}
				// 모든 문자가 같다.
				if (!flag && idxV[cnt] != 0) flag = 1; //기존에 있는 것이 더 길다 (사전 순으로 뒤)
				if (flag == 1) change(cnt);
			}
			return;
		
	}

	if (idx == N) return;

	chk[cnt] = idx;

	solve(idx + 1, cnt + 1, a + map[idx][0], b + map[idx][1], c + map[idx][2], d + map[idx][3], cost + map[idx][4]);
	solve(idx + 1, cnt,a,b,c,d,cost);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < 4; i++) scanf("%d", &arr[i]);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 5; j++)
			scanf("%d", &map[i][j]);
	}

	solve(0, 0, 0, 0, 0, 0, 0);

	printf("%d\n", minV);
	if (minV != -1) {
		for (int i = 0; i < (idxV[i]+1) != 0; i++) {
			printf("%d ", idxV[i] + 1);
		}
	}

}