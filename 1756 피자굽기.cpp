#include<stdio.h>
int D, N;
int oven[300001], pizza[300001];
int arr[300001];
int idx, last, ans;

int main() {
	scanf("%d%d", &D, &N);
	for (int i = 0; i < D; i++) {
		scanf("%d", &oven[i]);
		if (i == 0 || oven[i] < last) {
			arr[i] = oven[i];
			last = arr[i];
		}
		else if (oven[i] >= last) arr[i] = last;
		
	}

	last = D - 1;
	for (int i = 0; i < N; i++) {
		scanf("%d", &pizza[i]);

	}

	while (last >= 0) {
		if (arr[last] >= pizza[idx]) {
			idx++; // 피자 넣기
		}
		if (idx >= N) {
			ans = last + 1;
			break;
		}
		last--;
	}


	printf("%d\n", ans);

}