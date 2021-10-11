#include<stdio.h>
int N, L, R, X, ans, min_, max_;
int rank[16];
int chk[16];


void solve(int idx, int sum) {
	if (sum > R) return;

	if (idx >= N) {
		if (sum < L) return;
		min_ = -1;
		max_ = 0;
		for (int i = 0; i < N; i++) {
			if (chk[i]) {
				if (min_ == -1 || min_>rank[i])
					min_ = rank[i];
				if (max_ < rank[i])
					max_ = rank[i];
			}
		}
		if (max_ - min_ >= X) {
			ans++; return;
		}
		return;
	}

	chk[idx] = 1;
	solve(idx + 1, sum + rank[idx]);
	chk[idx] = 0;
	solve(idx + 1, sum);

	//return ans;

}

int main() {
	scanf("%d%d%d%d", &N, &L, &R, &X);
	for (int i = 0; i < N; i++)
		scanf("%d", &rank[i]);

	//qsort(rank, sizeof(rank) / sizeof(int), sizeof(int), compare);
	solve(0, 0);
	printf("%d\n", ans);
}