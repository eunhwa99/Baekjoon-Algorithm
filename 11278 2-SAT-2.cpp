#include<stdio.h>
int N, M, flag;
int arr[21];
int chk[101][2];

int check() {
	int first = 0;
	int sec = 0;

	for (int i = 0; i < M; i++) {
		if (chk[i][0] < 0)
			first = 1 - arr[-chk[i][0] - 1];
		else first = arr[chk[i][0] - 1];
		
		if (chk[i][1] < 0) sec = 1 - arr[-chk[i][1] - 1];
		else sec = arr[chk[i][1] - 1];
		
		if (!first && !sec) return 0;

	}
	return 1;
}

void solve(int idx) {
	if (flag) return;
	if (idx == N) {
		if (check()) { // 여기에 check 넣어주기
			flag = 1;
		}
		return;
	}
	
	arr[idx] = 1; //true
	solve(idx + 1);
	if (flag) return; // 여기에 flag 해주기
	arr[idx] = 0;
	solve(idx + 1);
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &chk[i][0], &chk[i][1]);
	}

	solve(0);
	printf("%d\n", flag);

	if (flag) {
		for (int i = 0; i < N; i++) {
			printf("%d ", arr[i]);	
		}
	}
	
}