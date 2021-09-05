#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
// ���� Ž��: O(2^30) (1,2�� ���� �� �ϳ� �����ϴ� ����� ��)

int T, W;
int arr[1001];
int cache[1001][31][2]; // cache[num][move][pos]: num�ʿ� move�� �̵��ϰ� pos�� ������ ���� ��, ���� �ڵ��� �ִ� ����

int eat(int num, int pos, int move) { //num ��
	//���� ���
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

	printf("%d\n", max(eat(0, 1, W), eat(0, 2, W - 1))); //�������ڸ��� 2�� ������ ���� ��쵵 �߰�
}