#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
#define SIZE 1000005
int N;
vector<int> tree[SIZE];
vector<int> arr[SIZE];
int dp[SIZE][2];
int vs[SIZE];

void makeTree(int cur) {
	vs[cur] = 1;
	for (int i = 0; i < arr[cur].size(); i++) {
		int next = arr[cur][i];
		if (vs[next] == 0) {
			tree[cur].push_back(next);
			makeTree(next);
		}
	}
}

int solve(int adp, int node) {
	
	int& ret = dp[node][adp];
	if (ret != -1) return ret;
	ret = 0;

	for (int i = 0; i < tree[node].size(); i++) {
		int next = tree[node][i];
		if (adp == 0) dp[node][adp] += solve(1, next) + 1;
		else dp[node][adp] += min(solve(0, next), solve(1,next)+1);
	}
	return ret;
}

int main() {
	scanf("%d", &N);

	for (int i = 1; i < N; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		arr[a].push_back(b);
		arr[b].push_back(a);
		dp[i][0] = dp[i][1] = -1;
	}

	dp[N][0] = dp[N][1] = -1;
	makeTree(1);
	printf("%d\n", min(solve(0, 1), solve(1, 1)+1));
}
