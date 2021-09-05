#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
// 완전 탐색: O(2^30) (1,2번 나무 중 하나 선택하는 경우의 수)

int T, W;
int arr[1001];
int cache[1001][31][2]; // cache[num][move][pos]: num초에 move번 이동하고 pos번 나무에 있을 때, 먹은 자두의 최대 개수

int eat(int num, int pos, int move) { //num 초
	//기저 사례
	if (move < 0 || num >= T) return 0;

	int& ret = cache[num][move][pos];
	if (ret != -1) return ret;
	ret = 0;

	if (arr[num] == pos)
		ret += 1;

	return ret = max(ret + eat(num + 1, pos, move), ret + eat(num + 1, 3 - pos, move - 1));
}

int main() {
	scanf("%d%d", &T, &W);

	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < T; i++) {
		scanf("%d", &arr[i]);
	}

	printf("%d\n", max(eat(0, 1, W), eat(0, 2, W - 1))); //시작하자마자 2번 나무로 가는 경우도 추가
}